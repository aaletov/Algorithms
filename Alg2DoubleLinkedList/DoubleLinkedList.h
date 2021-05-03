#ifndef __DOUBLE_LINKED_LIST
#define __DOUBLE_LINKED_LIST
#include <iostream>

//  DoubleLinkedList.h - ������ ������� ������ ����� �����  
class DoubleLinkedList
{
private:
    // ���  Node ������������ ��� �������� �������� ������, ���������� �� 
    // ��������� � ������� ���� next_ � �������������� � ������� ���� prev_
    struct Node         // ����� ��������������  ������ � ������ DoubleLinkedList
    {
        int item_;        // �������� �������� ������
        Node* next_;      // ��������� �� ��������� ������� ������
        Node* prev_;      // ��������� �� �������������� ������� ������

        // ����������� ��� �������� ������ �������� ������. 
        Node(int item, Node* next = nullptr, Node* prev = nullptr) : item_(item), next_(next), prev_(prev) { }
    };

    int count_;         // ������� ����� ���������
    Node* head_;        // ������ ������� ������
    Node* tail_;        // ��������� ������� ������

    // ������ � ��������� ���� ������
    Node* head() const { return head_; }

    // ������ � ���������� ���� ������
    Node* tail() const { return tail_; }

    // ������� �������������� ���� � ����� ������
    void insertTail(Node* x);

    // �������� �������������� ���� � ������ ������
    void insertHead(Node* x); // (int item);

    // �������� ��������� ���� 
    void deleteNode(Node* x);

    // ����� ���� (�����) � �������� ���������  
    Node* searchNode(int item);

    // ������ ���������� ���� �� ����� 
    Node* replaceNode(Node* x, int item);

public:

    // ����������� "�� ���������" - �������� ������� ������
    DoubleLinkedList() : count_(0), head_(nullptr), tail_(nullptr) {  }

    // 1. ����������� "�����������" � �������� ����� ���������� ������
    DoubleLinkedList(const DoubleLinkedList& src);

    // 2. ���������� ��������� ������������
    DoubleLinkedList& operator= (const DoubleLinkedList& list);
    
    // 3. ����������� �����������, ������� �������� ����� ������������� �� ������� ������
    DoubleLinkedList(DoubleLinkedList&& src);

    // 4. �������� ������������ ������������, ������� �������� ����� ������������� �� ������� ������
    DoubleLinkedList& operator=(DoubleLinkedList&& src);

    // ���������� ��������� ������
    int �ount()const { return count_; }

    // ������ � ���������� ��������� ���� ������
    int headItem() const;
    int& headItem();

    // ������ � ���������� ���������� ���� ������
    int tailItem() const;
    int& tailItem();

    // �������� ������� � ������ ������
    void insertHead(int item);

    // �������� ������� � ����� ������
    void insertTail(int item);

    // ������� ������� � ������ ������
    bool deleteHead();

    // ������� ������� �� ������ ������
    bool deleteTail();

    // �������� ���� � �������� ���������  
    bool deleteItem(const int item, bool all = false);

    // ����� ������ � �������� ���������  
    bool searchItem(int item);

    // ������ ���������� ���� �� ����� 
    bool replaceItem(int itemOld, int itemNew, bool all = false);

    // ����� ��������� ������ � ��������� ���� � ����������� �������� ����� 
    void outAll();

    // ���������� ������	
    virtual ~DoubleLinkedList();


    friend void swap(DoubleLinkedList& first, DoubleLinkedList& second) noexcept;

    friend std::ostream& operator<<(std::ostream& out, DoubleLinkedList& list);

    friend bool operator==(DoubleLinkedList& list1, DoubleLinkedList& list2);

    void concat(DoubleLinkedList& src);
};
#endif
