// @author: oz.atar@msmail.ariel.ac.il

#pragma once

#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <stdexcept>
#include <iostream>
using std::vector;
using std::stack;
using std::queue;
using std::invalid_argument;
using std::cout;
using std::endl;

#include "Iterators.hpp"
#include "Node.hpp"

template <typename T, size_t max_children = 2>
class Tree
{
    private:
        Node<T>* root;
    public:

        /** 
         * @brief Default constructor, create a binary tree.
        **/
        Tree() : root(nullptr) {};
        
        int add_root(Node<T>* node);

        int add_sub_node(Node<T> *parent, Node<T>* child);

        int get_max_children() const
        {
            return max_children;
        }
        Dfs_scan<T> pre_order_begin()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> pre_order_end()
        {
            return Dfs_scan<T>(nullptr);
        }

        Dfs_scan<T> post_order_begin()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> post_order_end()
        {
            return Dfs_scan<T>(nullptr);
        }

        Dfs_scan<T> in_order_begin()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> in_order_end()
        {
            return Dfs_scan<T>(nullptr);
        }

        Dfs_scan<T> begin_dfs_scan()
        {
            return Dfs_scan<T>(this->root);
        }

        Dfs_scan<T> end_dfs_scan()
        {
            return Dfs_scan<T>(nullptr);
        }

        Bfs_scan<T> begin_bfs_scan()
        {
            return Bfs_scan<T>(this->root);
        }

        Bfs_scan<T> end_bfs_scan()
        {
            return Bfs_scan<T>(nullptr);
        }

        Bfs_scan<T> begin()
        {
            return Bfs_scan<T>(this->root);
        }

        Bfs_scan<T> end()
        {
            return Bfs_scan<T>(nullptr);
        }

        heapIterator<T> heap_begin()
        {
            return heapIterator<T>(this->root);
        }
        heapIterator<T> heap_end()
        {
            return heapIterator<T>(nullptr);
        }

};

template <typename T, size_t max_children>
int Tree<T, max_children>::add_root(Node<T>* node)
{
    if (node == nullptr) 
    {
        throw std::invalid_argument("Can not initialize tree with a null node.");
    }
    this->root = node;
    return 0;
}

template <typename T, size_t max_children>
int Tree<T, max_children>::add_sub_node(Node<T> *parent, Node<T>* child) {
    if (parent == nullptr) {
        throw std::invalid_argument("Can not add a child to a null parent.");
    }
    if(parent->children.size() == max_children) {
        throw std::invalid_argument("Parent node already has the maximum number of children.");
    }
    parent->children.push_back(child);
    return 0;
}

template <typename T>
class Tree<T, 2>
{
    private:
        Node<T>* root;
    public:

        /** 
         * @brief Default constructor, create a binary tree.
        **/
        Tree() : root(nullptr) {};
        
        int add_root(Node<T>* node);

        int add_sub_node(Node<T> *parent, Node<T>* child);

        int get_max_children() const
        {
            return 2;
        }

    PreOrderIterator<T> pre_order_begin()
    {
        return PreOrderIterator<T>(this->root);
    }

    PreOrderIterator<T> pre_order_end()
    {
        return PreOrderIterator<T>(nullptr);
    }

    PostOrderIterator<T> post_order_begin()
    {
        return PostOrderIterator<T>(this->root);
    }

    PostOrderIterator<T> post_order_end()
    {
        return PostOrderIterator<T>(nullptr);
    }

    InOrderIterator<T> in_order_begin()
    {
        return InOrderIterator<T>(this->root);
    }

    InOrderIterator<T> in_order_end()
    {
        return InOrderIterator<T>(nullptr);
    }

    Dfs_scan<T> begin_dfs_scan()
    {
        return Dfs_scan<T>(this->root);
    }

    Dfs_scan<T> end_dfs_scan()
    {
        return Dfs_scan<T>(nullptr);
    }

    Bfs_scan<T> begin_bfs_scan()
    {
        return Bfs_scan<T>(this->root);
    }

    Bfs_scan<T> end_bfs_scan()
    {
        return Bfs_scan<T>(nullptr);
    }

    static Bfs_scan<T> begin_bfs_scan(Node<T>* root)
    {
        return Bfs_scan<T>(root);
    }

    static Bfs_scan<T> end_bfs_scan(Node<T>* root)
    {
        return Bfs_scan<T>(nullptr);
    }

    Bfs_scan<T> begin()
    {
        return Bfs_scan<T>(this->root);
    }

    Bfs_scan<T> end()
    {
        return Bfs_scan<T>(nullptr);
    }

    heapIterator<T> heap_begin()
    {
        return heapIterator<T>(this->root);
    }
    heapIterator<T> heap_end()
    {
        return heapIterator<T>(nullptr);
    }
};

template <typename T>
int Tree<T, 2>::add_root(Node<T>* node)
{
    if (node == nullptr) 
    {
        throw std::invalid_argument("Can not initialize tree with a null node.");
    }
    this->root = node;
    return 0;
}

template <typename T>
int Tree<T, 2>::add_sub_node(Node<T> *parent, Node<T>* child) 
{
    if (parent == nullptr) {
        throw std::invalid_argument("Can not add a child to a null parent.");
    }
    if(parent->children.size() == 2) {
        throw std::invalid_argument("Parent node already has the maximum number of children.");
    }
    parent->children.push_back(child);
    return 0;
}

