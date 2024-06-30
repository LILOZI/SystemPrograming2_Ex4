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

#include "Node.hpp"


template <typename T>
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

        Node<T>* operator->() const
        {
            return current;
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
                while(current == nullptr && !st.empty())
                {
                    current = st.top();
                    st.pop();
                }
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

template <typename T>
class PostOrderIterator
{
    private:
        stack<Node<T>*> st;
        Node<T>* current;

        void findFirst();

    public: 
        PostOrderIterator(Node<T>* root) : current(root)
        {
            if(root != nullptr)
            {
                st.push(root);
                this->findFirst();
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

        Node<T>* operator->() const
        {
            return current;
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
                while(temp == nullptr && !st.empty())
                {
                    temp = st.top();
                    st.pop();
                }
                if(st.empty())
                {
                    current = temp;
                    return *this;
                }
                for(int i = temp->children.size() -1 ; i >= 0 ; --i)
                {
                    if(temp->children[(size_t)i] != nullptr)
                    {
                    st.push(temp->children[(size_t)i]);
                    }
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
            return !(*this == other);
        }
};

template <typename T>
class InOrderIterator
{
    private:
        stack<Node<T>*> st;
        Node<T>* current;

        void findFirst();
    public:

        InOrderIterator(Node<T>* root) : current(root)
        {
            if(root != nullptr)
            {
                st.push(root);
                this->findFirst();
            }
        }
        ~InOrderIterator() 
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

        Node<T>* operator->() const
        {
            return current;
        }

        InOrderIterator& operator++()
        {
            if(st.empty())
            {
                current = nullptr;
            }
            else
            {
                auto temp = st.top();
                st.pop();
                while(temp == nullptr && !st.empty())
                {
                    temp = st.top();
                    st.pop();
                }
                if(temp->children.size() > 0)
                {
                    if(temp->children.size() == 1)
                    {
                        st.push(temp);
                        st.push(temp->children[0]);
                        temp->children.clear();
                        current = st.top();
                        this->findFirst();
                    }
                    else
                    {
                        st.push(temp->children[1]);
                        st.push(temp);
                        st.push(temp->children[0]);
                        temp->children.clear();
                        current = st.top();
                        this->findFirst();
                    }
                }
                else
                {
                    current = temp;
                }
            }
            return *this;
        }

        InOrderIterator operator++(int)
        {
            InOrderIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const InOrderIterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const InOrderIterator& other) const
        {
            return current != other.current;
        }
};

template <typename T>
class Dfs_scan
{
    private:
        stack<Node<T>*> st;
    public :
        Dfs_scan(Node<T>* root)
        {
            if(root != nullptr)
            {
                st.push(root);
            }
        }
        ~Dfs_scan() 
        {
            while(!st.empty())
            {
                st.pop();
            }
        }

        T& operator*() const
        {
            return st.top()->value;
        }

        Node<T>* operator->() const
        {
            return st.top();
        }

        Dfs_scan& operator++()
        {
            if(!st.empty())
            {
                Node<T>* current = st.top();
                st.pop();
                while(current == nullptr && !st.empty())
                {
                    current = st.top();
                    st.pop();
                }
                for(int i = current->children.size() - 1; i >= 0; --i)
                {
                    if(current->children[(size_t)i] != nullptr)
                    {
                    st.push(current->children[(size_t)i]);
                    }
                }
            }
                
            return *this;
        }

        Dfs_scan operator++(int)
        {
            Dfs_scan tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Dfs_scan& other) const
        {
            if(st.empty() && other.st.empty())
            {
                return true;
            }
            if(st.empty())
            {
                return false;
            }
            if(other.st.empty())
            {
                return false;
            }
            return st.top() == other.st.top();
        }

        bool operator!=(const Dfs_scan& other) const
        {
            return !(*this == other);
        }
};

template <typename T>
class Bfs_scan
{
    private:
        queue<Node<T>*> q;
    public:
        Bfs_scan(Node<T>* root)
        {
            if(root != nullptr)
            {
                q.push(root);
            }
        }
        ~Bfs_scan() 
        {
            while(!q.empty())
            {
                q.pop();
            }
        }

        T& operator*() const
        {
            return q.front()->value;
        }

        Node<T>* operator->() const
        {
            return q.front();
        }

        Bfs_scan& operator++()
        {
            if(!q.empty())
            {
                Node<T>* current = q.front();
                q.pop();
                while(current == nullptr && !q.empty())
                {
                    current = q.front();
                    q.pop();
                }
                for(int i = 0; i < current->children.size(); ++i)
                {
                    if(current->children[(size_t)i] != nullptr)
                    {
                        q.push(current->children[(size_t)i]);
                    }
                }
            }
            return *this;
        }

        Bfs_scan operator++(int)
        {
            Bfs_scan tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Bfs_scan& other) const
        {
            if(q.empty() && other.q.empty())
            {
                return true;
            }
            if(q.empty())
            {
                return false;
            }
            if(other.q.empty())
            {
                return false;
            }
            return q.front() == other.q.front();
        }

        bool operator!=(const Bfs_scan& other) const
        {
            return !(*this == other);
        }
};

template <typename T>
class heapIterator
{
    private:
        vector<Node<T>*> vec;
        int i;
        
    public:

        heapIterator(Node<T>* root) : vec()
        {
            i = 0;
            if(root != nullptr)
            {
                for(auto it = Bfs_scan<T>(root); it != Bfs_scan<T>(nullptr); ++it)
                {
                    if(it.operator->() != nullptr)
                    {
                        vec.push_back(it.operator->());
                    }
                }
                std::make_heap(vec.begin(), vec.end(), [](Node<T>* a, Node<T>* b) { return a->value > b->value; });
            }
        }
        
        ~heapIterator()
        {
            vec.clear();
        }

        T& operator*() const
        {
            return vec[0]->value;
        }

        Node<T>* operator->() const
        {
            return vec[0];
        }

        heapIterator& operator++()
        {
            if(!vec.empty())
            {
                vec.erase(vec.begin());
            }
            return *this;
        }

        heapIterator operator++(int)
        {
            heapIterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const heapIterator& other) const
        {
            if(vec.empty() && other.vec.empty())
            {
                return true;
            }
            if(vec.empty() != other.vec.empty())
            {
                return false;
            }
            return vec[0]->value == other.vec[0]->value;
        }

        bool operator!=(const heapIterator& other) const
        {
            return !(*this == other);
        }
};

template <typename T>
void PostOrderIterator<T>::findFirst()
{
    while(st.top()->children.size() > 0)
    {
        auto temp = st.top();
        for(int i = temp->children.size() -1 ; i >= 0 ; --i)
        {
            if(temp->children[(size_t)i] != nullptr)
            {
                st.push(temp->children[(size_t)i]);
            }
        }
        temp->children.clear();
    }
    current = st.top();
    st.pop();
    while(current == nullptr && !st.empty())
    {
        current = st.top();
        st.pop();
    }
}

template <typename T>
void InOrderIterator<T>::findFirst()
{
    auto temp = st.top();
    while(temp->children.size() > 0)
    {
        if(temp->children.size() == 1)
        {
            st.push(temp->children[0]);
        }
        else
        {
            st.pop();
            st.push(temp->children[1]);
            st.push(temp);
            st.push(temp->children[0]);
        }
        temp->children.clear();
        temp = st.top();
        if(temp == nullptr)
        {
            while(temp == nullptr && !st.empty())
            {
                st.pop();
                if(!st.empty())
                {
                    temp = st.top();
                }
            }
            break;
        }  
    }
    current = temp;
    st.pop();
}
