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

// 1. Конструктор "копирования" – создание копии имеющегося списка
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

// 2. Перегрузка оператора присваивания
DoubleLinkedList& DoubleLinkedList::operator= (const DoubleLinkedList& list)
{
	if (&list != this)
	{
		DoubleLinkedList tempList(list);
		swap(tempList, *this);
	}
	return *this;
}

// 3. Конструктор перемещения, который передает право собственности на область памяти
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src): count_(0), head_(nullptr), tail_(nullptr)
{
	swap(src, *this);
}

// 4. Оператор присваивания перемещением, который передает право собственности на область памяти
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

// Вставить сформированный узел в хвост списка
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

// Вставить сформированный узел в начало списка
void DoubleLinkedList::insertHead(Node* x)
{   // x->prev_ == nullptr,  x->next_ == nullptr  
	x->next_ = head();
	if (head() != nullptr) {
		// список был НЕ пуст – новый элемент будет и первым, и последним
		head()->prev_ = x;
	}
	else {
		// список был пуст – новый элемент будет и первым, и последним
		tail_ = x;
	}
	head_ = x;
	count_++;  // число элементов списка увеличилось
}

// Удаление заданного узла 
void DoubleLinkedList::deleteNode(Node* x)
{
	if (x == nullptr) {
		throw ("DoubleLinkedList::deleteNode  - неверно задан адрес удаляемого узла");
	}
	if (x->prev_ != nullptr) {
		// удаляется НЕ голова списка
		(x->prev_)->next_ = x->next_;
	}
	else {
		// удаляется голова списка,  второй элемент становится первым
		head_ = x->next_;
	}
	if (x->next_ != nullptr) {
		// удаляется НЕ хвост
		(x->next_)->prev_ = x->prev_;
	}
	else {
		// удаляется хвост
		tail_ = x->prev_;
	}
	delete x;      // 
	count_--;     // число элементов списка уменьшилось
}

// Поиск узла (адрес) с заданным значением  
DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
	Node* x = head();
	while (x != nullptr && x->item_ != item) {
		x = x->next_;
	}
	return x;
}

// Замена информации узла на новое 
DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
	x->item_ = item;
	return x;
}

// Доступ к информации головного узла списка
int DoubleLinkedList::headItem() const
{
	if (head() != nullptr) {
		return head()->item_;
	}
	throw ("headItem - список пуст!");
}

int& DoubleLinkedList::headItem()
{
	if (head() != nullptr) {
		return head()->item_;
	}
	throw ("headItem - список пуст!");
}

// Доступ к информации хвостового узла списка
int DoubleLinkedList::tailItem() const
{
	if (tail() != nullptr) {
		return tail()->item_;
	}
	throw ("tailItem - список пуст!");
}

int& DoubleLinkedList::tailItem()
{
	if (tail() != nullptr) {
		return tail()->item_;
	}
	throw ("tailItem - список пуст!");
}

// Вставить элемент в голову списка
void DoubleLinkedList::insertHead(int item)
{   
	insertHead(new Node(item));
}


// Вставить элемент в хвост списка
void DoubleLinkedList::insertTail(int item)
{  
	insertTail(new Node(item));
}

// Удалить элемент с головы списка
bool DoubleLinkedList::deleteHead()
{
	if (head() == nullptr) {
		return 0;  // список пуст, удалений нет
	}
	deleteNode(head());
	return 1;      // список был НЕ пуст, удаление головы
}

// Удалить элемент из хвоста списка
bool DoubleLinkedList::deleteTail()
{
	if (tail() == nullptr) {
		return 0;
	}
	deleteNode(tail());
	return 1; 
}

// Удаление узла с заданным значением  
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

// Поиск записи с заданным значением  
bool DoubleLinkedList::searchItem(int item)
{   
	return (searchNode(item) != nullptr);
}


// Замена информации узла на новое 
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

// Вывод элементов списка в текстовом виде в стандартный выходной поток 
void DoubleLinkedList::outAll()
{
	Node* current = head();       // Указатель на элемент
	while (current != nullptr) {
		std::cout << current->item_ << ' ';
		current = current->next_;  // Переход к следующему элементу
	}
	std::cout << std::endl;
}

// Деструктор списка	
DoubleLinkedList::~DoubleLinkedList()
{
	Node* current = nullptr;   // указатель на элемент, подлежащий удалению
	Node* next = head();        // указатель на следующий элемент
	while (next != nullptr) {  // пока есть еще элементы в списке
		current = next;
		next = next->next_;    // переход к следующему элементу
		delete current;        // освобождение памяти
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