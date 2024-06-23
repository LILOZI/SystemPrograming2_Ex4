#include "doctest.h"

#include "Tree.hpp"

TEST_CASE("Test pre order traversal")
{   
    //
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child(2);
    tree.add_sub_node(&root, &child);
    Node<int> child2(3);
    tree.add_sub_node(&root, &child2);
    Node<int> child3(4);
    tree.add_sub_node(&child, &child3);
    Node<int> child4(5);
    tree.add_sub_node(&child2, &child4);
    Node<int> child5(6);
    tree.add_sub_node(&child2, &child5);
    vector<int> expected = {1, 2, 4, 3, 5, 6};
    Tree<int>::PreOrderIterator it = tree.pre_order_begin();
    auto vecIt = expected.begin();
    while(it != tree.pre_order_end())
    {   
        CHECK(*it == *vecIt);
        ++it;
        ++vecIt;
    }
    // SUBCASE("")
    // {

    // }
    
}

TEST_CASE("Test post order traversal")
{
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child(2);
    tree.add_sub_node(&root, &child);
    Node<int> child2(3);
    tree.add_sub_node(&root, &child2);
    Node<int> child3(4);
    tree.add_sub_node(&child, &child3);
    Node<int> child4(5);
    tree.add_sub_node(&child2, &child4);
    Node<int> child5(6);
    tree.add_sub_node(&child2, &child5);
    vector<int> expected = {4, 2, 5, 6, 3, 1};
    Tree<int>::PostOrderIterator it = tree.post_order_begin();
    auto vecIt = expected.begin();
    while(it != tree.post_order_end())
    {   
        CHECK(*it == *vecIt);
        ++it;
        ++vecIt;
    }
}