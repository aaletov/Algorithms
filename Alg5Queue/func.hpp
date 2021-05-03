#ifndef FUNC_HPP
#define FUNC_HPP

#include "binary_search_tree.hpp"

template <typename T>
bool isSame(BinarySearchTree<T>&tree1, BinarySearchTree<T>& tree2)
{
    bool state = true;
    try
    {
        tree1.inorderWalk(
            [&tree2, &state](Node<T>* node) mutable 
            {
                state = state && tree2.iterativeSearch(node->key_);
                if (state == false)
                {
                    throw - 1;
                }
            }
        );
    }
    catch (...)
    {
        return false;
    }
    return true;
}

#endif
