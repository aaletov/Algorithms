#include <iostream>
#include <fstream>
#include "queue_array.hpp"
#include "func.hpp"

int main()
{
    QueueArray<int> x(10);
    QueueArray<int> y(5);
    const int NUMS[] = { 1, 1, 2, 3, 5, 8, 11, 19, 30, 49, 79, 128 };

    std::cout << "Trying to push all array:" << '\n';
    try
    {
        for (int i = 0; i < sizeof(NUMS) / sizeof(NUMS[0]); i++)
        {
            x.push_back(NUMS[i]);
        }
    }
    catch (std::exception& exc)
    {
        std::cerr << exc.what() << '\n';
    }
    std::cout << "Trying to pop() more elements than queue has:" << '\n';
    try
    {
        for (int i = 0; i < 11; i++)
        {
            std::cout << x.front() << ' ';
            x.pop();
        }
    }
    catch (const std::exception& exc)
    {
        std::cerr << '\n' << exc.what() << '\n';
    }
    std::cout << "Pushing first 5 elements into queue and pop()-ing 2:" << '\n';
    for (int i = 0; i < 5; i++)
    {
        y.push_back(NUMS[i]);
    }
    for (int i = 0; i < 2; i++)
    {
        std::cout << y.front() << ' ';
        y.pop();
    }
    std::cout << '\n';
    std::cout << "Pushing elements 6-7 into queue and pop()-ing 5:" << '\n';
    for (int i = 5; i < 7; i++)
    {
        y.push_back(NUMS[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        std::cout << y.front() << ' ';
        y.pop();
    }

    std::cout << '\n' << "Trees:" << '\n';
    std::ofstream file;
    file.open("out.txt");
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2;

    for (int i = 3; i < 10; i++)
    {
        tree1.insert(NUMS[i]);
    }
    for (int i = 9; i > 2; i--)
    {
        tree2.insert(NUMS[i]);
    }
    tree1.print(file, 3);
    tree2.print(file, 3);
    
    std::cout << "levelOrderWalk(tree1):" << '\n';
    int tempHeight = tree1.getHeight();
    tree1.levelOrderWalk<>(
        [tempHeight](Node<int>* node) {
            std::cout << node->key_ << ' ';
        }
    );
    std::cout << '\n' << "levelOrderWalk(tree2):" << '\n';
    tempHeight = tree2.getHeight();
    tree2.levelOrderWalk<>(
        [tempHeight](Node<int>* node) {
            std::cout << node->key_ << ' ';
        }
    );
    std::cout << '\n' << "Trees are in file" << '\n' << "Trees are ";
    if (!isSame(tree1, tree2))
    {
        std::cout << "NOT";
    }
    std::cout << " same" << '\n';
    file.close();

    BinarySearchTree<int> tree;
    tree.insert(15);
    tree.insert(9);
    tree.insert(4);
    tree.insert(5);
    tree.insert(13);
    tree.insert(16);
    tree.print(std::cout);

    std::cout << "iterativeInorderWalk(iterative):" << '\n';
    tree.iterativeInorderWalk<>(
        [](Node<int>* node) {
            std::cout << node->key_ << ' ';
        }
    );
    std::cout << '\n';

    std::cout << "levelOrderWalk(iterative):" << '\n';
    tempHeight = tree.getHeight();
    tree.levelOrderWalk<>(
        [tempHeight](Node<int>* node) {
            std::cout << node->key_ << ' ';
        }
    );
    std::cout << '\n' << '\n';

}
