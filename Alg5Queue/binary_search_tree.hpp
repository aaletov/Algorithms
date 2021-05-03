#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <cmath>
#include <limits.h>
#include <functional>
#include <stack>
#include <queue>
#include "functions.hpp"

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree() :
        root_(nullptr)
    {}
    BinarySearchTree(const BinarySearchTree<T>& src) = delete;
    BinarySearchTree(BinarySearchTree<T>&& src);
    virtual ~BinarySearchTree() = default;
    bool insert(const T& key);
    bool deleteKey(const T& key);
    void print(std::ostream& out, int CELL_SIZE = -1) const;
    int getCount() const;
    int getHeight() const;
    bool recursiveSearch(const T& key);
    bool iterativeSearch(const T& key);
    template <typename Callable>
    void inorderWalk(Callable callback) const
    {
        this->inorderWalk(root_, callback);
    }
    template <typename Callable>
    void iterativeInorderWalk(Callable callback) const
    {
        this->iterativeInorderWalk(root_, callback);
    }
    template <typename Callable>
    void levelOrderWalk(Callable callback) const
    {
        this->levelOrderWalk(root_, callback);
    }

private:
    Node<T>* root_;
    void insertNode(Node<T>* node);
    void deleteSubTree(Node<T>* node);
    int getHeightSubTree(const Node<T>* node) const;
    int getCountSubTree(Node<T>* node) const;
    Node<T>* recursiveSearch(Node<T>* node, const T& key) const;
    Node<T>* iterativeSearchNode(Node<T>* node, const T& key) const;
    template <typename Callable>
    void inorderWalk(Node<T>* node, Callable callback) const;
    template <typename Callable>
    void iterativeInorderWalk(Node<T>* node, Callable callback) const;
    template <typename Callable>
    void levelOrderWalk(Node<T>* node, Callable callback) const;
    friend void swap(BinarySearchTree<T>& left, BinarySearchTree<T>& right);
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src)
{
    delete this;
    root_ = nullptr;
    swap(&this, src);
}

template <typename T>
bool BinarySearchTree<T>::insert(const T& key)
{
    if (this->recursiveSearch(key) == true)
    {
        return false;
    }
    Node<T>* node = new Node<T>{ key, nullptr, nullptr, nullptr };
    this->insertNode(node);
    return true;
}

template <typename T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
    Node<T>* node = recursiveSearch(root_, key);
    if (node == nullptr)
    {
        return false;
    }
    Node<T>* p = node->p_;
    Node<T>* left = node->left_;
    Node<T>* right = node->right_;
    if (node == root_)
    {
        Node<T>* minRight = right;
        while (minRight->left_ != nullptr)
        {
            minRight = minRight->left_;
        }
        T minRightKey = minRight->key_;
        if (minRight == right)
        {
            right = nullptr;
        }
        minRight = nullptr;
        this->deleteKey(minRightKey);
        root_ = new Node<T>{ minRightKey, left, right, p };
        if (left != nullptr)
        {
            left->p_ = root_;
        }
        if (right != nullptr)
        {
            right->p_ = root_;
        }
        delete node;
        return true;
    }
    if (left == nullptr && right == nullptr)
    {
        if (p->left_ == node)
        {
            delete node;
            p->left_ = nullptr;
        }
        else
        {
            delete node;
            p->right_ = nullptr;
        }
    }
    else if (left == nullptr && right != nullptr)
    {
        if (p->left_ == node)
        {
            delete node;
            p->left_ = right;
        }
        else
        {
            delete node;
            p->right_ = right;
        }
    }
    else if (left != nullptr && right == nullptr)
    {
        if (p->left_ == node)
        {
            delete node;
            p->left_ = left;
        }
        else
        {
            delete node;
            p->right_ = left;
        }
    }
    else
    {
        Node<T>* minRight = right;
        while (minRight->left_ != nullptr)
        {
            minRight = minRight->left_;
        }
        T minRightKey = minRight->key_;
        if (minRight == right)
        {
            right = nullptr;
        }
        minRight = nullptr;
        this->deleteKey(minRightKey);
        if (p->left_ == node)
        {
            p->left_ = new Node<T>{ minRightKey, left, right, p };
            left->p_ = p->left_;
        }
        else
        {
            p->right_ = new Node<T>{ minRightKey, left, right, p };
            left->p_ = p->right_;
        }
        delete node;
    }
    return true;
}

template <typename T>
void BinarySearchTree<T>::print(std::ostream& out, int CELL_SIZE) const
{
    if (root_ == nullptr)
    {
        out << "Tree is empty" << '\n';
        return;
    }
    Node<T>* node = root_;
    if (CELL_SIZE <= 0)
    {
        CELL_SIZE = trunc(log10(INT_MAX)) + 1 + 1 + 2;
    }

    int currCellSize = CELL_SIZE * pow(2, this->getHeightSubTree(node) - 1);
    int leftSpace;
    int rightSpace;
    //int level = 0;
    int currCellsCount = 1;
    int currDequeSize;
    std::deque<Node<T>*> deque;

    deque.push_back(node);
    while (containsValues(deque))
    {
        currDequeSize = deque.size();
        if (deque[0] != root_)
        {
            currCellSize /= 2;
            leftSpace = (currCellSize - 1) / 2;
            rightSpace = currCellSize - leftSpace;
            out << '\n';
            for (int i = 0; i < currDequeSize; i++)
            {
                out << std::setw(leftSpace) << '|' << std::setw(rightSpace) << ' ';
            }
            out << '\n';
        }
        for (int i = 0; i < currDequeSize; i++)
        {
            if (deque[i] == nullptr)
            {
                deque.push_back(nullptr);
                deque.push_back(nullptr);
            }
            else
            {
                deque.push_back(deque[i]->left_);
                deque.push_back(deque[i]->right_);
            }
            printNode(out, deque[i], currCellSize);
        }
        for (int i = 0; i < currDequeSize; i++)
        {
            deque.pop_front();
        }
        out << '\n';
    }
    out << '\n';
}

template <typename T>
template <typename Callable>
void BinarySearchTree<T>::inorderWalk(Node<T>* node, Callable callback) const
{
    if (node != nullptr)
    {
        this->inorderWalk(node->left_, callback);
        callback(node);
        this->inorderWalk(node->right_, callback);
    }
}

template <typename T>
template <typename Callable>
void BinarySearchTree<T>::iterativeInorderWalk(Node<T>* node, Callable callback) const
{
    std::stack<Node<T>*> stack;
    while (!stack.empty() || node != nullptr)
    {
        if (!stack.empty())
        {
            node = stack.top();
            stack.pop();
            callback(node);
            if (node->right_ != nullptr)
            {
                node = node->right_;
            }
            else
            {
                node = nullptr;
            }
        }
        while (node != nullptr)
        {
            stack.push(node);
            node = node->left_;
        }
    }
}

template <typename T>
template <typename Callable>
void BinarySearchTree<T>::levelOrderWalk(Node<T>* node, Callable callback) const
{
    if (node == nullptr)
    {
        return;
    }
    std::queue<Node<T>*> queue;
    do
    {
        callback(node);
        if (node->left_ != nullptr)
        {
            queue.push(node->left_);
        }
        if (node->right_ != nullptr)
        {
            queue.push(node->right_);
        }
        if (!queue.empty())
        {
            node = queue.front();
            queue.pop();
        }
    } while (!queue.empty() || (queue.empty() && ((node->left_ == nullptr) != (node->right_ == nullptr))));
    if (node->p_ != nullptr)
    {
        callback(node);
    }
}

struct counter_t
{
    int count = 0;
    void incr()
    {
        count++;
    }
};

template <typename T>
int BinarySearchTree<T>::getCount() const
{
    return this->getCountSubTree(root_);
}

template <typename T>
int BinarySearchTree<T>::getCountSubTree(Node<T>* node) const
{
    counter_t counter;
    this->inorderWalk< >(node,
        [&counter](Node<T>* node) mutable {
            (&counter)->incr();
        }
    );
    return counter.count;
}

template <typename T>
int BinarySearchTree<T>::getHeight() const
{
    return getHeightSubTree(root_);
}

template <typename T>
bool BinarySearchTree<T>::recursiveSearch(const T& key)
{
    if (this->recursiveSearch(root_, key) != nullptr)
    {
        return true;
    }
    return false;
}

template <typename T>
bool BinarySearchTree<T>::iterativeSearch(const T& key)
{
    if (this->iterativeSearchNode(root_, key) != nullptr)
    {
        return true;
    }
    return false;
}

template <typename T>
void BinarySearchTree<T>::insertNode(Node<T>* node)
{
    Node<T>* y = nullptr;
    Node<T>* x = root_;
    while (x != nullptr)
    {
        y = x;
        if (node->key_ < x->key_)
        {
            x = x->left_;
        }
        else
        {
            x = x->right_;
        }
    }
    node->p_ = y;
    if (y == nullptr)
    {
        root_ = node;
    }
    else if (node->key_ < y->key_)
    {
        y->left_ = node;
    }
    else
    {
        y->right_ = node;
    }
}

template <typename T>
void BinarySearchTree<T>::deleteSubTree(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->left_ != nullptr)
    {
        this->deleteSubTree(node->left_);
    }
    if (node->right_ != nullptr)
    {
        this->deleteSubTree(node->right_);
    }
    if (node->left_ == nullptr && node->right_ == nullptr)
    {
        if (node->p_->left_ == node)
        {
            node->p_->left_ = nullptr;
        }
        else
        {
            node->p_->right_ = nullptr;
        }
        delete node;
    }
}

template <typename T>
int BinarySearchTree<T>::getHeightSubTree(const Node<T>* node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    int left = 1;
    int right = 1;
    if (node->left_ != nullptr)
    {
        left += this->getHeightSubTree(node->left_);
    }
    if (node->right_ != nullptr)
    {
        right += this->getHeightSubTree(node->right_);
    }
    return std::max(left, right);
}

template <typename T>
Node<T>* BinarySearchTree<T>::recursiveSearch(Node<T>* node, const T& key) const
{
    if (node == nullptr || key == node->key_)
    {
        return node;
    }
    if (key < node->key_)
    {
        return this->recursiveSearch(node->left_, key);
    }
    else
    {
        return this->recursiveSearch(node->right_, key);
    }
}

template <typename T>
Node<T>* BinarySearchTree<T>::iterativeSearchNode(Node<T>* node, const T& key) const
{
    while (node != nullptr && key != node->key_)
    {
        if (key < node->key_)
        {
            node = node->left_;
        }
        else
        {
            node = node->right_;
        }
    }
    return node;
}

template <typename T>
void swap(BinarySearchTree<T>& left, BinarySearchTree<T>& right)
{
    std::swap(left.root_, right.root_);
}

#endif
