#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <iomanip>
#include <deque>
#include "node.hpp"

template <typename T>
void printNode(std::ostream& out, Node<T>* node, int cellSize);
template <typename T>
bool isLeftestNode(Node<T>* node);
template <typename T>
bool containsValues(std::deque<T*>& deque);

template <typename T>
bool containsValues(std::deque<T*>& deque)
{
    bool x = false;
    for (int i = 0; i < deque.size(); i++)
    {
        x = x || deque[i] != nullptr;
        if (x)
        {
            break;
        }
    }
    return x;
}

template <typename T>
bool isLeftestNode(Node<T>* node)
{
    bool isLeftest = true;
    while (isLeftest && node->p_ != nullptr)
    {
        isLeftest = node->p_->left_ == node;
        node = node->p_;
    }
    return isLeftest;
}

template <typename T>
int getLevel(Node<T>* node)
{
    int level = 0;
    if (node == nullptr)
    {
        throw - 1;
    }
    else
    {
        while (node->p_ != nullptr)
        {
            node = node->p_;
            level++;
        }
    }
    return level;
}

template <typename T>
void printNode(std::ostream& out, Node<T>* node, int cellSize)
{
    if (node != nullptr)
    {
        int keyLen;
        if (node->key_ != 0)
        {
            keyLen = trunc(log10(abs(node->key_))) + 1;
        }
        else
        {
            keyLen = 1;
        }
        int leftSpace = (cellSize - keyLen - 2) / 2;
        int rightSpace = cellSize - leftSpace - keyLen;
        out << std::setw(leftSpace) << '(' << node->key_ << ')' << std::setw(rightSpace - 1) << ' ';
    }
    else
    {
        out << std::setw(cellSize /*- 1*/) << ' ';
    }
}

#endif