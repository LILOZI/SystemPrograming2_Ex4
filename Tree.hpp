

#pragma once

#include <vector>
#include <stack>
#include <stdexcept>
using std::vector;
using std::stack;
using std::invalid_argument;


#include <iostream>
using std::cout;
using std::endl;

template <typename T>
struct Node
{
    int key;
    T value;
    vector<Node<T>*> children;
    Node(T value) : value(value) {}
};

template <typename T>
class Tree
{
    private:
        
        int max_children;

    public:
        Node<T>* root;
        Tree() : max_children(2), root(nullptr) {}
        Tree(int max_children) : max_children(max_children), root(nullptr) {}

        int add_root(Node<T>* node);

        int add_sub_node(Node<T> *parent, Node<T>* child);

        class PreOrderIterator
        {
            private:
                stack<Node<T>*> st;
                Node<T>* current;
            public:

                PreOrderIterator(Node<T>* root) : current(root)
                {
                    if(root != nullptr)
                    {
                        for(int i = root->children.size() - 1; i >= 0; --i)
                        {
                            st.push(root->children[(size_t)i]);
                        }
                    }
                }
                ~PreOrderIterator() 
                {
                    while(!st.empty())
                    {
                        st.pop();
                    }
                }

                T& operator*() const
                {
                    return current->value;
                }

                T* operator->() const
                {
                    return &(current->value);
                }

                PreOrderIterator& operator++()
                {
                    if(st.empty())
                    {
                        current = nullptr;
                    }
                    else
                    {
                        current = st.top();
                        st.pop();
                        for(int i = current->children.size() - 1; i >= 0; --i)
                        {
                            st.push(current->children[(size_t)i]);
                        }  
                    }
                    return *this;
                }

                PreOrderIterator operator++(int)
                {
                    PreOrderIterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                bool operator==(const PreOrderIterator& other) const
                {
                    return current == other.current;
                }

                bool operator!=(const PreOrderIterator& other) const
                {
                    return current != other.current;
                }
        };

        class PostOrderIterator
        {
            private:
                stack<Node<T>*> st;
                stack<Node<T>*> st2;
                Node<T>* current;

                void findFirst();

            public:
                 
                PostOrderIterator(Node<T>* root)
                {
                    if(root != nullptr)
                    {
                        st.push(root);
                        this->findFirst();
                        // for(int i = root->children.size() - 1; i >= 0; --i)
                        // {
                        //     st.push(root->children[(size_t)i]);
                        // }
                        // root->children.clear();
                        // current = st.top();
                        // st.pop();
                        // for(int i = current->children.size() - 1; i >= 0; --i)
                        // {
                        //     st.push(current->children[(size_t)i]);
                        // }
                        // current->children.clear();
                    }
                }
                ~PostOrderIterator() 
                {
                    while(!st.empty())
                    {
                        st.pop();
                    }
                }

                T& operator*() const
                {
                    return current->value;
                }

                T* operator->() const
                {
                    return &(current->value);
                }

                PostOrderIterator& operator++()
                {
                    if(st.empty())
                    {
                        current = nullptr;
                    }
                    else
                    {
                        auto temp = st.top();
                        for(int i = temp->children.size() -1 ; i >= 0 ; --i)
                        {
                            st.push(temp->children[(size_t)i]);
                        }
                        temp->children.clear();
                        current = st.top();
                        st.pop();
                    }
                    return *this;
                }

                PostOrderIterator operator++(int)
                {
                    PostOrderIterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                bool operator==(const PostOrderIterator& other) const
                {
                    return current == other.current;
                }

                bool operator!=(const PostOrderIterator& other) const
                {
                    return this->current != other.current;
                }
        };

    PreOrderIterator pre_order_begin()
    {
        return PreOrderIterator(this->root);
    }

    PreOrderIterator pre_order_end()
    {
        return PreOrderIterator(nullptr);
    }

    PostOrderIterator post_order_begin()
    {
        return *(new PostOrderIterator(this->root));
    }

    PostOrderIterator post_order_end()
    {
        return *(new PostOrderIterator(nullptr));
    }

};


template <typename T>
int Tree<T>::add_root(Node<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Can not initialize tree with a null node.");
    }
    this->root = node;
    return 0;
}

template <typename T>
int Tree<T>::add_sub_node(Node<T> *parent, Node<T>* child) {
    if (parent == nullptr) {
        throw std::invalid_argument("Can not add a child to a null parent.");
    }
    if(parent->children.size() == this->max_children) {
        throw std::invalid_argument("Parent node already has the maximum number of children.");
    }
    if(child == nullptr) {
        throw std::invalid_argument("Can not add a null child to a parent.");
    }
    parent->children.push_back(child);
    return 0;
}

template <typename T>
void Tree<T>::PostOrderIterator::findFirst()
{
    while(st.top()->children.size() > 0)
    {
        auto temp = st.top();
        for(int i = temp->children.size() -1 ; i >= 0 ; --i)
        {
            st.push(temp->children[(size_t)i]);
        }
        temp->children.clear();
    }
    current = st.top();
    st.pop();
}