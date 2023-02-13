#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <algorithm>
#include <limits>
#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::queue;
using std::stack;
using std::unordered_map;
using std::unordered_set;
using std::vector;

template <typename T> class Node;
template <typename T> struct Edge;
template <typename T> class Graph;

template <typename T> using node_ptr = std::shared_ptr<Node<T> >;
template <typename T> using node_weak_ptr = std::weak_ptr<Node<T> >;
template <typename T> using edge_ptr = std::shared_ptr<Edge<T> >;

template <typename Container, typename DataType> class Iterator;

template <typename Container, typename DataType> class DfsIterator;

template <typename T> using Container = std::unordered_map<T, node_ptr<T> >;

// template <typename Container, typename DataType>
template <typename T> using iterator = Iterator<Container<T>, T>;
template <typename T> using const_iterator = Iterator<Container<T>, const T>;

template <typename T> using dfs_iterator = DfsIterator<Container<T>, T>;
template <typename T>
using dfs_const_iterator = DfsIterator<Container<T>, const T>;

template <typename T> class Node
{
private:
  T data_;
  std::vector<edge_ptr<T> > neighbors_;

  friend iterator<T>;
  friend const_iterator<T>;

  friend dfs_iterator<T>;
  friend dfs_const_iterator<T>;

public:
  /**
   * For a second there I had a concern calling the copy constructor of the
   * data might cause an error, since there is no memory allocated for it. But,
   * calling *new* on Node allocates memory for its data members as well!
   */
  Node (const T &data) : data_ (data){};
  ~Node (){};

  const std::vector<edge_ptr<T> > &
  getEdges ()
  {
    return neighbors_;
  }

  const T &
  getData ()
  {
    return data_;
  }

  void
  addEdge (edge_ptr<T> e)
  {
    neighbors_.push_back (e);
  }
};

template <typename T> struct Edge
{
  node_weak_ptr<T> node;
  const int weight;
};

/**
 * Wondering if edges make sense out of the context of a graph, as in path
 * To eliminate this prev_and_dist struct
 */
template <typename T> struct prev_and_dist
{
  // not a reference since I want it to be nullable
  std::shared_ptr<T> prev; // I don't think it should be a weak reference
  int dist;
};

template <typename Container, typename DataType> class Iterator
{
private:
  typename Container::const_iterator iter_;
  friend DfsIterator<Container, DataType>;

public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = DataType;
  using pointer = DataType *;
  using reference = DataType &;
  using difference_type = std::ptrdiff_t;

  Iterator (typename Container::const_iterator iter) : iter_ (iter){};
  Iterator (Iterator &other) : iter_ (other.iter_){};
  ~Iterator (){};

  Node<DataType>
  getNode ()
  {
    return iter_->second->data_;
  }

  reference
  operator* ()
  {
    return iter_->second->data_;
  }

  Iterator &
  operator= (const Iterator &other)
  {
    iter_ = other.iter_;
    return *this;
  }

  Iterator &
  operator++ ()
  {
    ++iter_;
    return *this;
  }

  Iterator
  operator++ (int)
  {
    auto tmp = *this;
    ++iter_;
    return tmp;
  }

  bool
  operator== (const Iterator &other) const
  {
    return iter_ == other.iter_;
  }

  bool
  operator!= (const Iterator &other) const
  {
    return !(*this == other);
  }
};

template <typename Container, typename DataType> class DfsIterator
{
private:
  //   Node<DataType> *node_;
  std::unordered_set<std::shared_ptr<Node<DataType> > > visited_;
  stack<std::shared_ptr<Node<DataType> > > stack_;

public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = DataType;
  using pointer = DataType *;
  using reference = DataType &;
  using difference_type = std::ptrdiff_t;

  DfsIterator (std::shared_ptr<DataType> n) { stack_.push (n); };
  DfsIterator (const DfsIterator &other) { copy_iter (other); };
  DfsIterator (const typename Graph<DataType>::iterator &iter)
  {
    // TODO: verify this doesn't cause a bug for example with other end
    // iterator
    auto i = iter.iter_;
    if (i != nullptr)
      {
        stack_.push (i->second);
      }
  };
  ~DfsIterator (){};

  DfsIterator &
  copy_iter (const DfsIterator &other)
  {
    visited_ = other.visited_;
    stack_ = other.stack_;
    return *this;
  }

  reference
  operator* ()
  {
    // TODO: check if empty - not the iterators responsibility
    return stack_.top ()->data_;
  }

  DfsIterator &
  operator= (const DfsIterator &other)
  {
    copy_iter (other);
    return *this;
  }

  void
  advance ()
  {
    auto node = stack_.top ();
    stack_.pop ();
    visited_.insert (node);
    for (auto e : node->neighbors_)
      {
        if (visited_.find (e->node.lock ()) == visited_.end ())
          {
            stack_.push (e->node.lock ());
          }
      }
  }

  DfsIterator &
  operator++ ()
  {
    advance ();
    return *this;
  }

  DfsIterator
  operator++ (int)
  {
    auto tmp = *this;
    advance ();
    return tmp;
  }

  bool
  operator== (const DfsIterator &other) const
  {
    return stack_ == other.stack_;
  }

  bool
  operator!= (const DfsIterator &other) const
  {
    return !(*this == other);
  }
};

template <typename T> class Graph
{
private:
  Container<T> nodes_;

public:
  using iterator = iterator<T>;
  using const_iterator = const_iterator<T>;

  Graph (){};
  ~Graph (){};

  void
  addNode (const T &data)
  {
    auto node = std::make_shared<Node<T> > (Node<T> (data));
    nodes_[data] = node;
  }

  void
  addEdge (const T &src, const T &dest, const int weight = 1)
  {
    auto si = nodes_.find (src);
    auto di = nodes_.find (dest);

    if (si != nodes_.end () && di != nodes_.end ())
      {
        auto edge = std::make_shared<Edge<T> > (Edge<T>{ di->second, weight });
        si->second->addEdge (edge);
      }
    else
      {
        throw "Nodes aren't there mannnnn";
      }
  }

  template <typename Func>
  void
  DFS (const T &src, Func visit)
  {
    unordered_set<node_ptr<T> > visited;
    stack<node_ptr<T> > stack;

    stack.push (nodes_[src]);

    while (!stack.empty ())
      {
        auto node = stack.top ();
        stack.pop ();

        if (visited.find (node) == visited.end ())
          {
            visit (node->getData ());
            visited.insert (node);
            for (auto e : node->getEdges ())
              {
                if (visited.find (e->node.lock ()) == visited.end ())
                  {
                    stack.push (e->node.lock ());
                  }
              }
          }
      }
  }

  template <typename Func>
  void
  BFS (const T &src, Func visit)
  {
    unordered_set<node_ptr<T> > visited;
    queue<node_ptr<T> > queue;

    queue.push (nodes_[src]);

    while (!queue.empty ())
      {
        auto node = queue.front ();
        queue.pop ();

        if (visited.find (node) == visited.end ())
          {
            visit (node->getData ());

            visited.insert (node);

            for (auto e : node->getEdges ())
              {
                if (visited.find (e->node.lock ()) == visited.end ())
                  {
                    queue.push (e->node.lock ());
                  }
              }
          }
      }
  }

  int
  CC ()
  {
    unordered_set<T> visited;
    int num_components = 0;
    for (auto np : nodes_)
      {
        if (visited.find (np.first) == visited.end ())
          {
            ++num_components;
            DFS (np.second->getData (),
                 [&visited] (auto elem) { visited.insert (elem); });
          }
      }

    return num_components;
  }

  std::unique_ptr<std::unordered_map<T, prev_and_dist<T> > >
  Dijkstra (const T &src)
  {
    std::unordered_map<T, prev_and_dist<T> > nodes;

    std::vector<T> min_heap;
    auto min_heap_cmp = [&nodes] (auto ln, auto rn) {
      return nodes[ln].dist > nodes[rn].dist;
    };

    for (auto node : nodes_)
      {
        prev_and_dist<T> pd;
        pd.dist = INT_MAX;
        pd.prev = nullptr;

        nodes[node.first] = pd;
        min_heap.push_back (node.first);
      }

    nodes[src] = { nullptr, 0 };
    std::make_heap (min_heap.begin (), min_heap.end (), min_heap_cmp);

    while (!min_heap.empty ())
      {
        std::pop_heap (min_heap.begin (), min_heap.end (), min_heap_cmp);
        T min_dist_node = min_heap.back ();
        min_heap.pop_back ();

        for (auto edge : nodes_[min_dist_node]->getEdges ())
          {
            auto edge_node = edge->node.lock ()->getData ();
            if (std::find (min_heap.begin (), min_heap.end (), edge_node)
                != min_heap.end ())
              {
                auto alt_dist = nodes[min_dist_node].dist + edge->weight;

                if (alt_dist < nodes[edge_node].dist)
                  {
                    nodes[edge_node].dist = alt_dist;
                    auto sp = std::shared_ptr<T> (new T (edge_node));
                    nodes[edge_node].prev = sp;
                  }
              }
          }
      }

    return std::move (
        std::unique_ptr<std::unordered_map<T, prev_and_dist<T> > > (
            new std::unordered_map<T, prev_and_dist<T> > (nodes)));
  }

  iterator
  begin ()
  {
    return iterator (nodes_.begin ());
  }

  iterator
  end ()
  {
    return iterator (nodes_.end ());
  }

  const_iterator
  cbegin ()
  {
    return const_iterator (nodes_.cbegin ());
  }

  const_iterator
  cend ()
  {
    return const_iterator (nodes_.cend ());
  }
};

#endif // __GRAPH_HPP__

/**
 * The Client of this class, doesn't need or want to know about the Node
 * wrapper for its data, think of a List, I've never asked for the Node of one.
 */