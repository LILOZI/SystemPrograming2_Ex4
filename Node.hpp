// @author: oz.atar@msmail.ariel.ac.il

#pragma once

template <typename T>
struct Node
{
    int key;
    T value;
    vector<Node<T>*> children;
    Node(T value) : value(value) {}
};