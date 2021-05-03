#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct Node
{
    T key_;
    Node<T>* left_;
    Node<T>* right_;
    Node<T>* p_;
};

#endif
