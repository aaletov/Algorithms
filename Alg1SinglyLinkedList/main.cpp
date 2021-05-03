#include <iostream>
#include <cstdlib>
#include <ctime>
#include "list.h"

int smallRand();
int randSign();
bool isSorted(const SinglyLinkedList& const list);
bool isSet(const SinglyLinkedList& const list);
SinglyLinkedList genList(int len = NULL, int order = 1);


void tests();

void myTest()
{
    int arr1[] = {
        -31956, -31884, -31688, -30841, -29981, -29468, -29355, -28217, -28189, -27270, -27034,
        -26697, -26291, -25579, -23550, -23540, -23135, -22395, -22343, -21371, -21357, -21120,
        -20391, -20096, -18593, -17460, -17071, -16376, -14792, -14389, -14249, -13557, -12737,
        -12264, -11013, -10020, -8910, -8483, -7759, -7120, -6498, -2853, -2211, -1878, -1233,
        -824, -794, -100, 893, 1941, 1957, 2506, 3305, 3640, 3998, 5236, 5348, 5680, 7129,
        8179, 8786, 9457, 10371, 10392, 10706, 12164, 12363, 15406, 16341, 19627, 19730, 20271,
        21174, 21260, 22633, 23022, 23879, 23901, 24136, 25149, 25549, 26233, 27426, 28432, 28515,
        29158, 29237, 30609, 31756, 32225
    };
    int arr2[] = { 
        -31807, -29217, -28470, -27654, -27478, -26740, -26680, -26435, -24864, -24319, -21885,
        -21110, -20982, -20199, -19942, -19698, -19241, -18301, -18005, -17686, -17463, -17164,
        -16988, -16904, -16798, -16468, -16347, -13557, -13442, -12066, -8600, -7915, -7228, -7095,
        -5207, -4542, -1052, 138, 2269, 3729, 5335, 5415, 6043, 6286, 7362, 7580, 7697, 8626, 9477,
        11140, 11855, 12131, 12364, 12473, 14712, 17210, 17566, 18394, 18638, 19400, 20756, 20782,
        21342, 21912, 22723, 22994, 24006, 25385, 28187, 30042, 31145, 31354, 31621
    };
    int arr3[] = {
        1
    };
    SinglyLinkedList list1;
    SinglyLinkedList list2;
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++)
    {
        list1.insertItem(arr1[i]);
    }
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++)
    {
        list2.insertItem(arr2[i]);
    }
    SinglyLinkedList list3 = list1;
    list3.intersect(list2);
    list3.outAll();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    SinglyLinkedList list1 = genList(15, 1000);
    SinglyLinkedList list2 = genList(10, 1000);
    SinglyLinkedList list3 = genList(12, 1000);
    SinglyLinkedList list4 = genList(30, 1000);

    std::cout << "Первый список:" << std::endl;
    list1.outAll();
    std::cout << "Второй список:" << std::endl;
    list2.outAll();
    std::cout << "Третий список:" << std::endl;
    list3.outAll();
    std::cout << std::endl;

    std::cout << "Тест на сортировку" << std::endl;

    if (isSorted(list4))
    {
        std::cout << "Список отсортирован" << std::endl;
    }
    else
    {
        std::cout << "Список НЕ отсортирован" << std::endl;
    }
    std::cout << "Тест на множество" << std::endl;
    if (isSet(list4))
    {
        std::cout << "Список является множеством" << std::endl;
    }
    else
    {
        std::cout << "Список НЕ является множеством" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Объединение множеств:" << std::endl;
    SinglyLinkedList list5 = list1 + list2;
    list5.outAll();
    std::cout << "Вычитание множеств:" << std::endl;
    SinglyLinkedList list6 = list1 - list2;
    list6.outAll();
    std::cout << "Пересечение множеств:" << std::endl;
    SinglyLinkedList list7 = list1 * list2;
    list7.outAll();

    std::cout << std::endl;
    std::cout << "Мутирующие (?) методы:" << std::endl;
    std::cout << "Включение" << std::endl;
    list1.include(list2);
    list1.outAll();

    std::cout << "Исключение" << std::endl;
    list1.exclude(list2);
    list1.outAll();

    std::cout << "Пересечение" << std::endl;
    list1.intersect(list2);
    list1.outAll();

    std::cout << "Элемент" << std::endl;
    std::cout << list2[5] << std::endl;
    std::cout << "Следующий" << std::endl;
    std::cout << list2.successor(list2[5]) << std::endl;
    std::cout << "Предыдущий" << std::endl;
    std::cout << list2.predecessor(list2[5]) << std::endl;

    tests();

    return 0;
}

int smallRand()
{
    return rand() / 1000;
}

int randSign()
{
    return (rand() % 2 == 0) ? 1 : -1;
}

SinglyLinkedList genList(int len, int order)
{
    if (len == NULL)
    {
        len = 100 + smallRand() * randSign();
    }
    SinglyLinkedList list;
    for (int i = 0; i < len; i++)
    {
        list.insertItem(rand() * randSign() / order);
    }
    return list;
}

bool isSorted(const SinglyLinkedList& const list)
{
    int len = list.getCount();
    for (int i = 1; i < len; i++)
    {
        if (list[i - 1] >= list[i])
        {
            return false;
        }
    }
    return true;
}

bool isSet(const SinglyLinkedList& const list)
{
    int len = list.getCount();
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (list[i] == list[j])
            {
                return false;
            }
        }
    }
    return true;
}

bool isIncluded(const SinglyLinkedList& const term1, const SinglyLinkedList& const term2, const SinglyLinkedList& const sum)
{
    int len = sum.getCount();
    for (int i = 0; i < len; i++)
    {
        if (term1.searchItem(sum[i]) || term2.searchItem(sum[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool isExcluded(const SinglyLinkedList& const minuend, const SinglyLinkedList& const subtrahend, const SinglyLinkedList& const difference)
{
    int len = difference.getCount();
    for (int i = 0; i < len; i++)
    {
        if (minuend.searchItem(difference[i]) && !subtrahend.searchItem(difference[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool isIntersected(const SinglyLinkedList& const factor1, const SinglyLinkedList& const factor2, const SinglyLinkedList& const product)
{
    int len = product.getCount();
    for (int i = 0; i < len; i++)
    {
        if (factor1.searchItem(product[i]) && factor2.searchItem(product[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void tests()
{
    std::cout << "Include test" << std::endl;
    for (int i = 0; i < 1000; i++)
    {
        // std::cout << "1: " << i << std::endl;
        SinglyLinkedList list1 = genList();
        SinglyLinkedList list2 = genList();
        SinglyLinkedList list3 = list1;
        list3.include(list2);
        if (isIncluded(list1, list2, list3))
        {
            continue;
        }
        else
        {
            throw "Not included correctly";
        }
    }
    std::cout << "Passed" << std::endl;

    std::cout << "Exclude test" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        // std::cout << "2: " << i << std::endl;
        SinglyLinkedList list1 = genList();
        SinglyLinkedList list2 = genList();
        SinglyLinkedList list3 = list1;
        list3.exclude(list2);
        if (isExcluded(list1, list2, list3))
        {
            continue;
        }
        else
        {
            throw "Not excluded correctly";
        }
    }
    std::cout << "Passed" << std::endl;

    std::cout << "Intersection test" << std::endl;
    for (int i = 0; i < 1000; i++)
    {
        /*std::cout << "3: " << i << std::endl;*/
        SinglyLinkedList list1 = genList();
        SinglyLinkedList list2 = genList();
        SinglyLinkedList list3 = list1;
        list3.intersect(list2);

        //list1.outAll(); //
        //std::cout << std::endl; //
        //list2.outAll(); // 
        //std::cout << std::endl; //
        //list3.outAll(); // 
        //std::cout << std::endl; //

        if (isIntersected(list1, list2, list3))
        {
            continue;
        }
        else
        {
            throw "Not intersected correctly";
        }
    }
    std::cout << "Passed" << std::endl;
}
