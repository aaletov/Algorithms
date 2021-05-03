#ifndef __DOUBLE_LINKED_LIST
#define __DOUBLE_LINKED_LIST
#include <iostream>

//  DoubleLinkedList.h - Дважды связный список целых чисел  
class DoubleLinkedList
{
private:
    // Тип  Node используется для описания элемента списка, связанного со 
    // следующим с помощью поля next_ и предшествующим с помощью поле prev_
    struct Node         // может использоваться  только в классе DoubleLinkedList
    {
        int item_;        // значение элемента списка
        Node* next_;      // указатель на следующий элемент списка
        Node* prev_;      // указатель на предшествующий элемент списка

        // Конструктор для создания нового элемента списка. 
        Node(int item, Node* next = nullptr, Node* prev = nullptr) : item_(item), next_(next), prev_(prev) { }
    };

    int count_;         // счетчик числа элементов
    Node* head_;        // первый элемент списка
    Node* tail_;        // последний элемент списка

    // Доступ к головному узлу списка
    Node* head() const { return head_; }

    // Доступ к хвостовому узлу списка
    Node* tail() const { return tail_; }

    // Всавить сформированный узел в хвост списка
    void insertTail(Node* x);

    // Вставить сформированный узел в начало списка
    void insertHead(Node* x); // (int item);

    // Удаление заданного узла 
    void deleteNode(Node* x);

    // Поиск узла (адрес) с заданным значением  
    Node* searchNode(int item);

    // Замена информации узла на новое 
    Node* replaceNode(Node* x, int item);

public:

    // Конструктор "по умолчанию" - создание пустого списка
    DoubleLinkedList() : count_(0), head_(nullptr), tail_(nullptr) {  }

    // 1. Конструктор "копирования" – создание копии имеющегося списка
    DoubleLinkedList(const DoubleLinkedList& src);

    // 2. Перегрузка оператора присваивания
    DoubleLinkedList& operator= (const DoubleLinkedList& list);
    
    // 3. Конструктор перемещения, который передает право собственности на область памяти
    DoubleLinkedList(DoubleLinkedList&& src);

    // 4. Оператор присваивания перемещением, который передает право собственности на область памяти
    DoubleLinkedList& operator=(DoubleLinkedList&& src);

    // Количество элементов списка
    int сount()const { return count_; }

    // Доступ к информации головного узла списка
    int headItem() const;
    int& headItem();

    // Доступ к информации хвостового узла списка
    int tailItem() const;
    int& tailItem();

    // Вставить элемент в голову списка
    void insertHead(int item);

    // Вставить элемент в хвост списка
    void insertTail(int item);

    // Удалить элемент с головы списка
    bool deleteHead();

    // Удалить элемент из хвоста списка
    bool deleteTail();

    // Удаление узла с заданным значением  
    bool deleteItem(const int item, bool all = false);

    // Поиск записи с заданным значением  
    bool searchItem(int item);

    // Замена информации узла на новое 
    bool replaceItem(int itemOld, int itemNew, bool all = false);

    // Вывод элементов списка в текстовом виде в стандартный выходной поток 
    void outAll();

    // Деструктор списка	
    virtual ~DoubleLinkedList();


    friend void swap(DoubleLinkedList& first, DoubleLinkedList& second) noexcept;

    friend std::ostream& operator<<(std::ostream& out, DoubleLinkedList& list);

    friend bool operator==(DoubleLinkedList& list1, DoubleLinkedList& list2);

    void concat(DoubleLinkedList& src);
};
#endif
