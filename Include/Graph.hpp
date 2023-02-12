#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;

template <typename T> class Node
{
private:
  T data_;
  std::vector<Node<T> *> neighbors_;

public:
  /**
   * For a second there I had a concern calling the copy constructor of the
   * data might cause an error, since there is no memory allocated for it. But,
   * calling *new* on Node allocates memory for its data members as well!
   */
  Node (const &data) : data_ (data){};
  ~Node ();
};

template <typename T> class Graph
{
private:
  std::unordered_map<T, Node<T> *> nodes;

public:
  Graph (/* args */);
  ~Graph ();

  void
  addNode (const T &data)
  {
    Node<T> *node = new Node (data);
    nodes[data] = node;
  }

  void
  addEdge ()
  {
  }
};


/**
 * The Client of this class, doesn't need or want to know about the Node wrapper for its data
*/