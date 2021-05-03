#include <fstream>
#include "binary_search_tree.hpp"
#include "functions.hpp"

bool testFunction(BinarySearchTree<int>* tree, std::ostream& out);

int main()
{
    std::ostream& out = std::cout;

    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2;
    BinarySearchTree<int> tree3;
    BinarySearchTree<int> tree4;

    const int INTS1[] = { 8, 4, 12, 9, 10 };
    const int INTS2[] = { 1, 3, 7, 11, 15 };
    const int INTS3[] = { 1 };

    for (int i = 0; i < sizeof(INTS1) / sizeof(INTS1[0]); i++)
    {
        tree1.insert(INTS1[i]);
    }
    for (int i = 0; i < sizeof(INTS2) / sizeof(INTS2[0]); i++)
    {
        tree2.insert(INTS2[i]);
    }
    for (int i = 0; i < sizeof(INTS3) / sizeof(INTS3[0]); i++)
    {
        tree3.insert(INTS3[i]);
    }
    
    testFunction(&tree1, out);
    testFunction(&tree2, out);
    testFunction(&tree3, out);
    //empty tree
    testFunction(&tree4, out);

}

bool testFunction(BinarySearchTree<int>* tree, std::ostream& out)
{
    try
    {
        out << "Tree:" << '\n';
        out << "Count of nodes = " << tree->getCount() << '\n';
        out << "Height of tree = " << tree->getHeight() << '\n' << '\n';

        out << '\n';
        tree->print(out, 5);
        out << '\n';
        out << '\n' << '\n';

        out << "inorderWalk(recursion):" << '\n';
        tree->inorderWalk<>(
            [&out](Node<int>* node) {
                out << node->key_ << ' ';
            }
        );
        out << '\n';

        out << "iterativeInorderWalk(iterative):" << '\n';
        tree->iterativeInorderWalk<>(
            [&out](Node<int>* node) {
                out << node->key_ << ' ';
            }
        );
        out << '\n';

        out << "levelOrderWalk(iterative):" << '\n';
        int tempHeight = tree->getHeight();
        tree->levelOrderWalk<>(
            [tempHeight, &out](Node<int>* node) {
                out << node->key_ << ' ';
            }
        );
        out << '\n' << '\n';

        if (tree->iterativeSearch(5)) out << "5 is in tree->\n\n";

        tree->deleteKey(8);

        out << "Count of nodes = " << tree->getCount() << '\n';
        out << "Height of tree = " << tree->getHeight() << '\n' << '\n';

        out << '\n';
        tree->print(out, 5);
        out << '\n';


        tree->deleteKey(15);

        out << "Count of nodes = " << tree->getCount() << '\n';
        out << "Height of tree = " << tree->getHeight() << '\n' << '\n';

        out << '\n';
        tree->print(out, 5);
        out << '\n';

        tree->deleteKey(5);

        out << "Count of nodes = " << tree->getCount() << '\n';
        out << "Height of tree = " << tree->getHeight() << '\n' << '\n';

        out << '\n';
        tree->print(out, 5);
        out << '\n';

        tree->deleteKey(4);
        tree->deleteKey(12);

        out << "Count of nodes = " << tree->getCount() << '\n';
        out << "Height of tree = " << tree->getHeight() << '\n' << '\n';

        out << '\n';
        tree->print(out, 5);
        out << '\n';

        return true;
    }
    catch (std::exception& exc)
    {
        std::cerr << exc.what();
        return false;
    }
}
