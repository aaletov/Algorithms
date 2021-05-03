#pragma once
// successor is the first item, for which comparisonFcn == false
// predecessor is the last item, for which comparisonFnc == true
// e.g. if 
// bool comparisonFcn(T* x1, T* x2)
// {
//     return x1 > x2;
// }
// (default) then successor would be the first item, which is bigger than x 
// and predecessor would be the last item, which is lesser than x
// so the list would be sorted ascending
 
#include <iostream>

class SinglyLinkedList
{
public:
    SinglyLinkedList() : count_(0), min_(nullptr), max_(nullptr) {}
    SinglyLinkedList(const SinglyLinkedList& list);
    virtual ~SinglyLinkedList();
    int operator[] (const int index) const;
    friend SinglyLinkedList operator+(SinglyLinkedList& list1, SinglyLinkedList& list2);
    friend SinglyLinkedList operator-(SinglyLinkedList& list1, SinglyLinkedList& list2);
    friend SinglyLinkedList operator*(SinglyLinkedList& list1, SinglyLinkedList& list2);
    bool insertItem(int item);
    bool searchItem(int item) const;
    bool deleteItem(int item);
    int min() const;
    int max() const;
    int successor(int item) const;
    int predecessor(int item) const;
    void include(SinglyLinkedList& list);
    void exclude(SinglyLinkedList& list);
    void intersect(SinglyLinkedList& list);
    void outAll();
    void toArray(int* arr);
    int getCount() const;
private:
    struct Node      
    {
        int item_;    
        Node* next_;     
        Node(int& item, Node* next = nullptr) : item_(item), next_(next) { }
    };
    int count_;         
    Node* min_;        
    Node* max_;        
    void insertMin(Node* x);
    void insertMax(Node* x);
    bool insertNode(Node* x);
    void deleteNode(Node* x);
    Node* searchNode(int item) const;
    Node* searchSuccessor(int item) const;
    Node* searchPredecessor(int item) const;
};
