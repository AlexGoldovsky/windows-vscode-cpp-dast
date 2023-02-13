#include <memory>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

using std::stack;
using std::unordered_map;
using std::unordered_set;
using std::vector;

template <typename T> class Node;

template <typename T> class Graph;

template <typename Container, typename DataType> class Iterator;

template <typename Container, typename DataType> class DfsIterator;

template <typename T>
using Container = std::unordered_map<T, std::shared_ptr<Node<T> > >;

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
  std::vector<std::shared_ptr<Node<T> > > neighbors_;

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

  const std::vector<std::shared_ptr<Node<T> > > &
  getNeighbors ()
  {
    return neighbors_;
  }

  const T &
  getData ()
  {
    return data_;
  }

  void
  AddNeighbor (std::shared_ptr<Node> n)
  {
    neighbors_.push_back (n);
  }
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
    for (auto n : node->neighbors_)
      {
        if (visited_.find (n) == visited_.end ())
          {
            stack_.push (n);
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
  ~Graph (){

  };

  void
  addNode (const T &data)
  {
    auto node = std::make_shared<Node<T> > (Node<T> (data));
    nodes_[data] = node;
  }

  void
  addEdge (const T &src, const T &dest)
  {
    auto si = nodes_.find (src);
    auto di = nodes_.find (dest);

    if (si != nodes_.end () && di != nodes_.end ())
      {
        si->second->AddNeighbor (di->second);
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
    unordered_set<std::shared_ptr<Node<T> > > visited;
    stack<std::shared_ptr<Node<T> > > stack;

    stack.push (nodes_[src]);

    while (!stack.empty ())
      {
        auto node = stack.top ();
        stack.pop ();
        visit (node->getData ());
        visited.insert (node);
        for (auto n : node->getNeighbors ())
          {
            if (visited.find (n) == visited.end ())
              {
                stack.push (n);
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
        if (visited.find(np.first) == visited.end())
          {
            ++num_components;
            DFS (np.second->getData (),
                 [&visited] (auto elem) { visited.insert (elem); });
          }
      }

    return num_components;
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