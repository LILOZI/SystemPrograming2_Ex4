<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Tree Visualization Library</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
        }
        h1, h2, h3 {
            color: #333;
        }
        pre {
            background: #f4f4f4;
            padding: 10px;
            border: 1px solid #ddd;
            overflow-x: auto;
        }
        code {
            font-family: monospace;
            background: #f4f4f4;
            padding: 2px 4px;
            border-radius: 4px;
        }
    </style>
</head>
<body>
    <h1>Tree Visualization Library</h1>
    <p>This project is a comprehensive implementation of a tree data structure, designed to support various traversal methods and visualization using the SFML library. It includes multiple iterators for tree traversal and a graphical representation of the tree.</p>

    <h2>Features</h2>
    <ul>
        <li><strong>Tree Data Structure:</strong> Supports binary and general trees with customizable maximum children.</li>
        <li><strong>Tree Traversals:</strong> Implements PreOrder, PostOrder, InOrder, Depth-First Search (DFS), Breadth-First Search (BFS), and Heap traversal.</li>
        <li><strong>Tree Visualization:</strong> Utilizes SFML to create an interactive graphical representation of the tree, with tooltips and hover effects.</li>
    </ul>

    <h2>Requirements</h2>
    <ul>
        <li><strong>C++17 or later</strong></li>
        <li><strong>SFML Library:</strong> Download and install from <a href="https://www.sfml-dev.org/download.php" target="_blank">SFML Official Site</a></li>
    </ul>

    <h2>Installation</h2>
    <ol>
        <li>Clone the repository:
            <pre><code>git clone &lt;repository_url&gt;
cd &lt;repository_directory&gt;</code></pre>
        </li>
        <li>Compile the project using the provided <code>Makefile</code>:
            <pre><code>make all</code></pre>
        </li>
    </ol>

    <h2>Usage</h2>

    <h3>Creating a Tree</h3>
    <p>You can create both binary trees and general trees with a specified maximum number of children.</p>
    <pre><code>#include "Tree.hpp"
#include "Node.hpp"

int main() {
    Tree&lt;int&gt; binaryTree;
    Node&lt;int&gt;* root = new Node&lt;int&gt;(10);
    Node&lt;int&gt;* child1 = new Node&lt;int&gt;(20);
    Node&lt;int&gt;* child2 = new Node&lt;int&gt;(30);
    
    binaryTree.add_root(root);
    binaryTree.add_sub_node(root, child1);
    binaryTree.add_sub_node(root, child2);

    binaryTree.drawTree();

    return 0;
}</code></pre>

    <h3>Traversing the Tree</h3>
    <p>This library supports various traversal methods. Here are some examples:</p>

    <h4>PreOrder Traversal</h4>
    <pre><code>for(auto it = binaryTree.pre_order_begin(); it != binaryTree.pre_order_end(); ++it) {
    std::cout &lt;&lt; *it &lt;&lt; " ";
}</code></pre>

    <h4>PostOrder Traversal</h4>
    <pre><code>for(auto it = binaryTree.post_order_begin(); it != binaryTree.post_order_end(); ++it) {
    std::cout &lt;&lt; *it &lt;&lt; " ";
}</code></pre>

    <h4>InOrder Traversal</h4>
    <pre><code>for(auto it = binaryTree.in_order_begin(); it != binaryTree.in_order_end(); ++it) {
    std::cout &lt;&lt; *it &lt;&lt; " ";
}</code></pre>

    <h4>Depth-First Search (DFS) Traversal</h4>
    <pre><code>for(auto it = binaryTree.begin_dfs_scan(); it != binaryTree.end_dfs_scan(); ++it) {
    std::cout &lt;&lt; *it &lt;&lt; " ";
}</code></pre>

    <h4>Breadth-First Search (BFS) Traversal</h4>
    <pre><code>for(auto it = binaryTree.begin_bfs_scan(); it != binaryTree.end_bfs_scan(); ++it) {
    std::cout &lt;&lt; *it &lt;&lt; " ";
}</code></pre>

    <h3>Drawing the Tree</h3>
    <p>The tree can be visualized in a graphical window using SFML. The nodes will be displayed with hoverable tooltips showing the node values.</p>
    <pre><code>binaryTree.drawTree();</code></pre>

    <h2>Detailed Class Documentation</h2>

    <h3><code>Tree</code> Class</h3>

    <h4>Constructors</h4>
    <ul>
        <li><code>Tree()</code>: Default constructor for creating a binary tree.</li>
    </ul>

    <h4>Methods</h4>
    <ul>
        <li><code>int add_root(Node&lt;T&gt;* node)</code>: Adds a root node to the tree. Throws <code>invalid_argument</code> if the node is null.</li>
        <li><code>int add_sub_node(Node&lt;T&gt;* parent, Node&lt;T&gt;* child)</code>: Adds a child node to a parent node. Throws <code>invalid_argument</code> if the parent is null or already has the maximum number of children.</li>
        <li><code>int get_max_children() const</code>: Returns the maximum number of children allowed per node.</li>
    </ul>

    <h4>Iterators</h4>
    <ul>
        <li><code>PreOrderIterator&lt;T&gt; pre_order_begin()</code>, <code>pre_order_end()</code></li>
        <li><code>PostOrderIterator&lt;T&gt; post_order_begin()</code>, <code>post_order_end()</code></li>
        <li><code>InOrderIterator&lt;T&gt; in_order_begin()</code>, <code>in_order_end()</code></li>
        <li><code>Dfs_scan&lt;T&gt; begin_dfs_scan()</code>, <code>end_dfs_scan()</code></li>
        <li><code>Bfs_scan&lt;T&gt; begin_bfs_scan()</code>, <code>end_bfs_scan()</code></li>
        <li><code>heapIterator&lt;T&gt; heap_begin()</code>, <code>heap_end()</code></li>
    </ul>

    <h3><code>Node</code> Class</h3>

    <h4>Constructors</h4>
    <ul>
        <li><code>Node(const T&amp; value)</code>: Constructs a node with a given value.</li>
    </ul>

    <h4>Attributes</h4>
    <ul>
        <li><code>T value</code>: The value stored in the node.</li>
        <li><code>std::vector&lt;Node&lt;T&gt;*&gt; children</code>: A vector of pointers to child nodes.</li>
    </ul>

    <h2>Examples</h2>

    <h3>Creating and Visualizing a Binary Tree</h3>
    <pre><code>#include "Tree.hpp"
#include "Node.hpp"

int main() {
    Tree&lt;int, 2&gt; tree;
    Node&lt;int&gt;* root = new Node&lt;int&gt;(1);
    Node&lt;int&gt;* leftChild = new Node&lt;int&gt;(2);
    Node&lt;int&gt;* rightChild = new Node&lt;int&gt;(3);
    
    tree.add_root(root);
    tree.add_sub_node(root, leftChild);
    tree.add_sub_node(root, rightChild);

    tree.drawTree();

    return 0;
}</code></pre>

    <h3>Traversing a Tree in Different Orders</h3>
    <pre><code>#include "Tree.hpp"
#include "Node.hpp"
#include &lt;iostream&gt;

int main() {
    Tree&lt;int, 2&gt; tree;
    Node&lt;int&gt;* root = new Node&lt;int&gt;(1);
    Node&lt;int&gt;* leftChild = new Node&lt;int&gt;(2);
    Node&lt;int&gt;* rightChild = new Node&lt;int&gt;(3);
    
    tree.add_root(root);
    tree.add_sub_node(root, leftChild);
    tree.add_sub_node(root, rightChild);

    std::cout &lt;&lt; "PreOrder Traversal: ";
    for(auto it = tree.pre_order_begin(); it != tree.pre_order_end(); ++it) {
        std::cout &lt;&lt; *it &lt;&lt; " ";
    }
    std::cout &lt;&lt; std::endl;

    std::cout &lt;&lt; "PostOrder Traversal: ";
    for(auto it = tree.post_order_begin(); it != tree.post_order_end(); ++it) {
        std::cout &lt;&lt; *it &lt;&lt; " ";
    }
    std::cout &lt;&lt; std::endl;

    std::cout &lt;&lt; "InOrder Traversal: ";
    for(auto it = tree.in_order_begin(); it != tree.in_order_end(); ++it) {
        std::cout &lt;&lt; *it &lt;&lt; " ";
    }
    std::cout &lt;&lt; std::endl;

    std::cout &lt;&lt; "DFS Traversal: ";
    for(auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        std::cout &lt;&lt; *it &lt;&lt; " ";
    }
    std::cout &lt;&lt; std::endl;

    std::cout &lt;&lt; "BFS Traversal: ";
    for(auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        std::cout &lt;&lt; *it &lt;&lt; " ";
    }
    std::cout &lt;&lt; std::endl;

    return 0;
}</code></pre>

    <h2>License</h2>
    <p>This project is licensed under the MIT License - see the <a href="LICENSE">LICENSE</a> file for details.</p>

    <h2>Author</h2>
    <p>Orel Nissan</p>

    <h2>Contributions</h2>
    <p>Contributions are welcome! Please submit a pull request or open an issue to discuss your changes.</p>
</body>
</html>
