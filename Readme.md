# Advanced Tree Data Structure with SFML Visualization

## Introduction
This project features an advanced tree data structure implemented in C++, capable of handling various child node configurations. It integrates visualization using the Simple and Fast Multimedia Library (SFML), supporting both generic and binary trees with multiple traversal iterators. Nodes can be added dynamically, and the tree structure can be visualized in a graphical interface.

## Key Features
- **Generic Tree Architecture**: The Tree class supports any data type and allows a customizable number of children per node using a template parameter `k`.
- **Binary Tree Specialization**: Tailored functionality for binary trees (`k=2`), providing specialized operations.
- **Graphical Visualization**: SFML is used to create a graphical representation of the tree, with nodes depicted as circles and connections as lines.
- **Traversal Iterators**: Includes depth-first search (DFS), breadth-first search (BFS), and specific tree traversal iterators (in-order, pre-order, post-order).
- **Custom Display Precision**: Node data can be formatted with specific precision for display purposes.

## Dependencies
- **C++ Compiler**: Requires C++11 or newer.
- **SFML**: Ensure SFML is installed and properly linked. The project uses the RobotoFlex-Regular.ttf font, located in the `guiResources` directory.

## Directory and Files
- `Tree.hpp`: Implements the Tree class and its binary specialization.
- `Node.hpp`: Defines the Node class for tree nodes.
- `Iterators.hpp`: Contains iterator classes for different tree traversal methods.
- `Complex.hpp/cpp`: Implements a class for complex numbers, with necessary operator overloads.
- `Test.cpp, TestCounter.cpp, doctest.h`: Contains tests using the doctest framework.

## Tree Class Template
The Tree class template allows for creating a tree with specified data type `T` and maximum children `k`.

### Methods:
- `Tree()`: Initializes the tree with a null root pointer.
- `void add_root(Node<T> &root)`: Adds a root node, throws an error if a root already exists.
- `void add_sub_node(Node<T>& parent, Node<T> child)`: Adds a child node to a parent, throws an error if the parent has reached the maximum number of children.

### Iterators:
- `Dfs_scan<T> begin_in_order()`, `end_in_order()`
- `Dfs_scan<T> begin_pre_order()`, `end_pre_order()`
- `Dfs_scan<T> begin_post_order()`, `end_post_order()`
- `Bfs_scan<T> begin_bfs_scan()`, `end_bfs_scan()`
- `Dfs_scan<T> begin_dfs_scan()`, `end_dfs_scan()`
- `Bfs_scan<T> begin()`, `end()`
- `heapIterator<T> heap_begin()`, `heap_end()`

## Visualization
The Tree class includes methods for drawing the tree using SFML.

- `void draw()`: Public method that creates a window and handles the tree drawing process.
- 
## Binary Tree Specialization
The binary tree specialization offers additional methods specific to binary trees.

### Iterators:
Similar to the generic tree, with appropriate specializations for binary trees.

### Example:
```cpp
#include "Tree.hpp"
int main() {
    Tree<int, 3> tree;  // Tree allowing up to 3 children per node.

    Node<int> root(1);
    tree.add_root(root);

    Node<int> child1(2);
    Node<int> child2(3);

    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);

    tree.draw();  // Opens a window to visualize the tree.

    return 0;
}
