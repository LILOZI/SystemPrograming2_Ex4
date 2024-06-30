// @author: oz.atar@msmail.ariel.ac.il

#include "doctest.h"

#include "Tree.hpp"
#include "Complex.hpp"

TEST_CASE("Test tree degree")
{
    Tree<int> tree;
    CHECK_EQ(tree.get_max_children(), 2);
    Tree<int, 2> tree2;
    CHECK_EQ(tree2.get_max_children(), 2);
    Tree<int, 3> tree3;
    CHECK_EQ(tree3.get_max_children(), 3);
}

TEST_CASE("Test add root")
{
    Tree<int> tree;
    Node<int> root(1);
    CHECK_THROWS(tree.add_root(nullptr));
    CHECK_NOTHROW(tree.add_root(&root));
}

TEST_CASE("Test add sub node")
{
    Node<int> root(1);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    
    SUBCASE("overflow children in binary tree")
    {
        Tree<int> tree;
        tree.add_root(&root);
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        CHECK_THROWS(tree.add_sub_node(&root, &child4));
    }

    SUBCASE("overflow children in ternary tree")
    {
        Tree<int, 3> tree;
        tree.add_root(&root);
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&root, &child4);
        CHECK_THROWS(tree.add_sub_node(&root, &child5));
    }

    SUBCASE("add sub node to nullptr")
    {
        Tree<int> tree;
        tree.add_root(&root);
        CHECK_THROWS(tree.add_sub_node(nullptr, &child2));
    }

}

TEST_CASE("Test pre order traversal")
{   
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    Node<int> child6(6);
    
    SUBCASE("left child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 4, 3, 5, 6};
        PreOrderIterator<int> it = tree.pre_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.pre_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("right child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 4, 3, 5, 6};
        PreOrderIterator<int> it = tree.pre_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.pre_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("full tree")
    {
        Node<int> child7(7);
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, &child5);
        tree.add_sub_node(&child3, &child6);
        tree.add_sub_node(&child3, &child7);
        vector<int> expected = {1, 2, 4, 5, 3, 6, 7};
        PreOrderIterator<int> it = tree.pre_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.pre_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
}

TEST_CASE("Test post order traversal")
{
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    Node<int> child6(6);
    Node<int> child7(7);

    SUBCASE("full tree")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, &child5);
        tree.add_sub_node(&child3, &child6);
        tree.add_sub_node(&child3, &child7);
        vector<int> expected = {4, 5, 2, 6, 7, 3, 1};
        PostOrderIterator<int> it = tree.post_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.post_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("left child is nullptr")
    {
        // first node in "post order" (leftmost leaf) is null
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {4, 2, 5, 6, 3, 1};
        PostOrderIterator<int> it = tree.post_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.post_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("right child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {4, 2, 5, 6, 3, 1};
        PostOrderIterator<int> it = tree.post_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.post_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    } 
}

TEST_CASE("Test in order traversal")
{
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    Node<int> child6(6);
    Node<int> child7(7);

    SUBCASE("full tree")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, &child5);
        tree.add_sub_node(&child3, &child6);
        tree.add_sub_node(&child3, &child7);
        vector<int> expected = {4, 2, 5, 1, 6, 3, 7};
        InOrderIterator<int> it = tree.in_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.in_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("left child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {2, 4, 1, 5,3 ,6};
        InOrderIterator<int> it = tree.in_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.in_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("right child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {4, 2, 1, 5, 3, 6};
        InOrderIterator<int> it = tree.in_order_begin();
        auto vecIt = expected.begin();
        while(it != tree.in_order_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
}

TEST_CASE("Test DFS traversal")
{
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    Node<int> child6(6);
    Node<int> child7(7);

    SUBCASE("full tree")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, &child5);
        tree.add_sub_node(&child3, &child6);
        tree.add_sub_node(&child3, &child7);
        vector<int> expected = {1, 2, 4, 5, 3, 6, 7};
        Dfs_scan<int> it = tree.begin_dfs_scan();
        auto vecIt = expected.begin();
        while(it != tree.end_dfs_scan())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
    
    SUBCASE("left child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 4, 3, 5, 6};
        Dfs_scan<int> it = tree.begin_dfs_scan();
        auto vecIt = expected.begin();
        while(it != tree.end_dfs_scan())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("right child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 4, 3, 5, 6};
        Dfs_scan<int> it = tree.begin_dfs_scan();
        auto vecIt = expected.begin();
        while(it != tree.end_dfs_scan())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
}

TEST_CASE("Test BFS traversal")
{
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    Node<int> child6(6);
    Node<int> child7(7);

    SUBCASE("full tree")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, &child5);
        tree.add_sub_node(&child3, &child6);
        tree.add_sub_node(&child3, &child7);
        vector<int> expected = {1, 2, 3, 4, 5, 6, 7};
        Bfs_scan<int> it = tree.begin_bfs_scan();
        auto vecIt = expected.begin();
        while(it != tree.end_bfs_scan())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
    
    SUBCASE("left child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 3, 4, 5, 6};
        Bfs_scan<int> it = tree.begin_bfs_scan();
        auto vecIt = expected.begin();
        while(it != tree.end_bfs_scan())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("right child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 3, 4, 5, 6};
        Bfs_scan<int> it = tree.begin_bfs_scan();
        auto vecIt = expected.begin();
        while(it != tree.end_bfs_scan())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
}

TEST_CASE("Test make heap")
{
    Tree<int> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    Node<int> child6(6);
    Node<int> child7(7);

    SUBCASE("full tree")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, &child5);
        tree.add_sub_node(&child3, &child6);
        tree.add_sub_node(&child3, &child7);
        vector<int> expected = {1, 2, 3, 4, 5, 6, 7};
        heapIterator<int> it = tree.heap_begin();
        auto vecIt = expected.begin();
        while(it != tree.heap_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
    
    SUBCASE("left child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 3, 4, 5, 6};
        heapIterator<int> it = tree.heap_begin();
        auto vecIt = expected.begin();
        while(it != tree.heap_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }

    SUBCASE("right child is nullptr")
    {
        tree.add_sub_node(&root, &child2);
        tree.add_sub_node(&root, &child3);
        tree.add_sub_node(&child2, &child4);
        tree.add_sub_node(&child2, nullptr);
        tree.add_sub_node(&child3, &child5);
        tree.add_sub_node(&child3, &child6);
        vector<int> expected = {1, 2, 3, 4, 5, 6};
        heapIterator<int> it = tree.heap_begin();
        auto vecIt = expected.begin();
        while(it != tree.heap_end())
        {   
            CHECK(*it == *vecIt);
            ++it;
            ++vecIt;
        }
    }
}

TEST_CASE("Test 3-nary runs DFS")
{
    
    Tree<int, 3> tree;
    Node<int> root(1);
    tree.add_root(&root);
    Node<int> child2(2);
    Node<int> child3(3);
    Node<int> child4(4);
    Node<int> child5(5);
    Node<int> child6(6);
    Node<int> child7(7);
    tree.add_sub_node(&root, &child2);
    tree.add_sub_node(&root, &child3);
    tree.add_sub_node(&root, &child7);
    tree.add_sub_node(&child2, &child4);
    tree.add_sub_node(&child2, &child5);
    tree.add_sub_node(&child3, &child6);
    vector<int> expected = {1, 2, 4, 5, 3, 6, 7};
    Dfs_scan<int> pre = tree.pre_order_begin();
    Dfs_scan<int> post = tree.post_order_begin();
    Dfs_scan<int> in = tree.in_order_begin();
    Dfs_scan<int> dfs = tree.begin_dfs_scan();
    auto vecIt = expected.begin();
    while(pre != tree.pre_order_end() && 
    post != tree.post_order_end() && in != tree.in_order_end() 
    && dfs != tree.end_dfs_scan())
    {   
        CHECK(*pre == *vecIt);
        CHECK(*post == *vecIt);
        CHECK(*in == *vecIt);
        CHECK(*dfs == *vecIt);
        ++pre;
        ++post;
        ++in;
        ++dfs;
        ++vecIt;
    }
}

TEST_CASE("Complex")
{
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3(4, 6);

    SUBCASE("init")
    {
        Complex pureReal(1);
        Complex ans1(1, 0);
        CHECK(pureReal == ans1);
        Complex pureImaginary(0, 1);
        Complex ans2(0, 1);
        CHECK(pureImaginary == ans2);
        Complex zero;
        Complex ans3(0, 0);
        CHECK(zero == ans3);
        Complex copy(c1);
        CHECK(copy == c1);
    }

    SUBCASE("addition")
    {
        Complex c4 = c1 + c2;
        CHECK(c4 == c3);
    }

    SUBCASE("subtraction")
    {
        Complex c4 = c3 - c2;
        CHECK(c4 == c1);
    }

    SUBCASE("multiplication")
    {
        Complex c4 = c1 * c2;
        Complex ans(-5, 10);
        CHECK(c4 == ans);
    }

    SUBCASE("greater")
    {
        CHECK(c2 > c1);
        CHECK(c2 < c3);
        CHECK(c1 <= c3);
        CHECK(c3 >= c2);
    }
}