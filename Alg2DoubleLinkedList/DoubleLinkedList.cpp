#include "DoubleLinkedList.h"
#include <iostream>

// swap
void swap(DoubleLinkedList& first, DoubleLinkedList& second) noexcept
{
	DoubleLinkedList::Node* tempHead = first.head();
	DoubleLinkedList::Node* tempTail = first.tail();
	int tempCount = first.count_;
	first.head_ = second.head();
	first.tail_ = second.tail();
	first.count_ = second.count_;
	second.head_ = tempHead;
	second.tail_ = tempTail;
	second.count_ = tempCount;
}

// 1. ����������� "�����������" � �������� ����� ���������� ������
DoubleLinkedList::DoubleLinkedList (const DoubleLinkedList & src)
{
	Node* curr = src.head();
	this->insertTail(curr->item_);
	for (int i = 0; i < src.count_ - 1; i++)
	{
		curr = curr->next_;
		this->insertTail(curr->item_);
	}
}

// 2. ���������� ��������� ������������
DoubleLinkedList& DoubleLinkedList::operator= (const DoubleLinkedList& list)
{
	if (&list != this)
	{
		DoubleLinkedList tempList(list);
		swap(tempList, *this);
	}
	return *this;
}

// 3. ����������� �����������, ������� �������� ����� ������������� �� ������� ������
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src): count_(0), head_(nullptr), tail_(nullptr)
{
	swap(src, *this);
}

// 4. �������� ������������ ������������, ������� �������� ����� ������������� �� ������� ������
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& src)
{
	if (&src == this)
	{
		return *this;
	}
	DoubleLinkedList tempList;
	swap(tempList, src);
	swap(tempList, *this);
	return *this;
}

std::ostream& operator<<(std::ostream& out, DoubleLinkedList& list) {
	list.outAll();
	return out;
}

// �������� �������������� ���� � ����� ������
void DoubleLinkedList::insertTail(Node* x)
{
	x->prev_ = tail();
	if (tail() != nullptr) {
		tail()->next_ = x;
	}
	else {
		head_ = x;
	}
	tail_ = x;
	count_++;
}

// �������� �������������� ���� � ������ ������
void DoubleLinkedList::insertHead(Node* x)
{   // x->prev_ == nullptr,  x->next_ == nullptr  
	x->next_ = head();
	if (head() != nullptr) {
		// ������ ��� �� ���� � ����� ������� ����� � ������, � ���������
		head()->prev_ = x;
	}
	else {
		// ������ ��� ���� � ����� ������� ����� � ������, � ���������
		tail_ = x;
	}
	head_ = x;
	count_++;  // ����� ��������� ������ �����������
}

// �������� ��������� ���� 
void DoubleLinkedList::deleteNode(Node* x)
{
	if (x == nullptr) {
		throw ("DoubleLinkedList::deleteNode  - ������� ����� ����� ���������� ����");
	}
	if (x->prev_ != nullptr) {
		// ��������� �� ������ ������
		(x->prev_)->next_ = x->next_;
	}
	else {
		// ��������� ������ ������,  ������ ������� ���������� ������
		head_ = x->next_;
	}
	if (x->next_ != nullptr) {
		// ��������� �� �����
		(x->next_)->prev_ = x->prev_;
	}
	else {
		// ��������� �����
		tail_ = x->prev_;
	}
	delete x;      // 
	count_--;     // ����� ��������� ������ �����������
}

// ����� ���� (�����) � �������� ���������  
DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
	Node* x = head();
	while (x != nullptr && x->item_ != item) {
		x = x->next_;
	}
	return x;
}

// ������ ���������� ���� �� ����� 
DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
	x->item_ = item;
	return x;
}

// ������ � ���������� ��������� ���� ������
int DoubleLinkedList::headItem() const
{
	if (head() != nullptr) {
		return head()->item_;
	}
	throw ("headItem - ������ ����!");
}

int& DoubleLinkedList::headItem()
{
	if (head() != nullptr) {
		return head()->item_;
	}
	throw ("headItem - ������ ����!");
}

// ������ � ���������� ���������� ���� ������
int DoubleLinkedList::tailItem() const
{
	if (tail() != nullptr) {
		return tail()->item_;
	}
	throw ("tailItem - ������ ����!");
}

int& DoubleLinkedList::tailItem()
{
	if (tail() != nullptr) {
		return tail()->item_;
	}
	throw ("tailItem - ������ ����!");
}

// �������� ������� � ������ ������
void DoubleLinkedList::insertHead(int item)
{   
	insertHead(new Node(item));
}


// �������� ������� � ����� ������
void DoubleLinkedList::insertTail(int item)
{  
	insertTail(new Node(item));
}

// ������� ������� � ������ ������
bool DoubleLinkedList::deleteHead()
{
	if (head() == nullptr) {
		return 0;  // ������ ����, �������� ���
	}
	deleteNode(head());
	return 1;      // ������ ��� �� ����, �������� ������
}

// ������� ������� �� ������ ������
bool DoubleLinkedList::deleteTail()
{
	if (tail() == nullptr) {
		return 0;
	}
	deleteNode(tail());
	return 1; 
}

// �������� ���� � �������� ���������  
bool DoubleLinkedList::deleteItem(const int item, bool all)
{
	if (searchItem(item) == false)
	{
		return false;
	}
	if (all == false) {
		deleteNode(searchNode(item));
	}
	else
	{
		do
		{
			deleteNode(searchNode(item));
		} while (searchItem(item) == true);
	}
	return true; 
}

// ����� ������ � �������� ���������  
bool DoubleLinkedList::searchItem(int item)
{   
	return (searchNode(item) != nullptr);
}


// ������ ���������� ���� �� ����� 
bool DoubleLinkedList::replaceItem(int itemOld, int itemNew, bool all)
{
	if (searchItem(itemOld) == false)
	{
		return false;
	}
	if (all == false)
	{
		searchNode(itemOld)->item_ = itemNew;
	}
	else
	{
		do
		{
			searchNode(itemOld)->item_ = itemNew;
		} while (searchItem(itemOld) == true);
	}
	return true; 
}

// ����� ��������� ������ � ��������� ���� � ����������� �������� ����� 
void DoubleLinkedList::outAll()
{
	Node* current = head();       // ��������� �� �������
	while (current != nullptr) {
		std::cout << current->item_ << ' ';
		current = current->next_;  // ������� � ���������� ��������
	}
	std::cout << std::endl;
}

// ���������� ������	
DoubleLinkedList::~DoubleLinkedList()
{
	Node* current = nullptr;   // ��������� �� �������, ���������� ��������
	Node* next = head();        // ��������� �� ��������� �������
	while (next != nullptr) {  // ���� ���� ��� �������� � ������
		current = next;
		next = next->next_;    // ������� � ���������� ��������
		delete current;        // ������������ ������
	}
}

bool operator==(DoubleLinkedList& list1, DoubleLinkedList& list2)
{
	if (list1.head() == list2.head() && list1.head()->next_ == list2.head()->next_ && list1.count_ == list2.count_)
	{
		return true;
	}
	else if (list1.count_ != list2.count_)
	{
		return false;
	}
	DoubleLinkedList::Node* curr1 = list1.head_;
	DoubleLinkedList::Node* curr2 = list2.head_;
	if (curr1->item_ != curr2->item_)
	{
		return false;
	}
	do
	{
		if (curr1->next_ == nullptr)
		{
			return true;
		}
		curr1 = curr1->next_;
		curr2 = curr2->next_;
	} while (curr1->item_ == curr2->item_);
	return false;
}

void DoubleLinkedList::concat(DoubleLinkedList& src)
{
	Node* x = src.head_;
	if (src.head_ != nullptr)
		while (x != nullptr) {
			this->insertTail(x);
			x = x->next_;
		}

	src.head_ = nullptr;
	src.tail_ = nullptr;
	src.count_ = 0;
}