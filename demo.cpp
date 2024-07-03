#include "Tree.hpp"


int main(void)
{
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child(2);
    tree.add_sub_node(&root, &child);
    Node<int> child2(3);
    tree.add_sub_node(&root, &child2);
    tree.add_sub_node(&child, nullptr);
    Node<int> child3(4);
    tree.add_sub_node(&child, &child3);
    Node<int> child4(5);
    tree.add_sub_node(&child2, &child4);
    Node<int> child5(6);
    tree.add_sub_node(&child2, &child5);

    tree.drawTree();
    
    return 0;
}