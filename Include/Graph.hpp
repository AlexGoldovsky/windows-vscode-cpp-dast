#include <unordered_map>
#include <vector>

#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

using std::unordered_map;
using std::vector;

template <typename T> class Node;

template <typename Container, typename DataType> class Iterator;

template <typename T> using Container = std::unordered_map<T, Node<T> *>;

// template <typename Container, typename DataType>
template <typename T> using iterator = Iterator<Container<T>, T>;

template <typename T> using const_iterator = Iterator<Container<T>, const T>;

template <typename T> class Node
{
private:
  T data_;
  std::vector<Node<T> *> neighbors_;

public:
  friend iterator<T>;
  friend const_iterator<T>;
  /**
   * For a second there I had a concern calling the copy constructor of the
   * data might cause an error, since there is no memory allocated for it. But,
   * calling *new* on Node allocates memory for its data members as well!
   */
  Node (const T &data) : data_ (data){};
  ~Node ();

  void
  AddNeighbor (Node *n)
  {
    neighbors_.push_back (n);
  }
};

template <typename Container, typename DataType> class Iterator
{
private:
  typename Container::const_iterator iter_;

public:
  using iterator_cartegory = std::forward_iterator_tag;
  using value_type = DataType;
  using pointer = DataType *;
  using reference = DataType &;
  using difference_type = std::ptrdiff_t;

  Iterator (typename Container::const_iterator iter) : iter_ (iter){};
  Iterator (Iterator &other) : iter_ (other.iter_){};
  ~Iterator (){};

  //   *, ->

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

template <typename T> class Graph
{
  //   using Container = std::unordered_map<T, Node<T> *>;

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
    Node<T> *node = new Node<T> (data);
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
 * wrapper for its data
 */