#include <iostream>
#include "DoubleLinkedList.h"

int main() 
{
	setlocale(LC_ALL, "Russian");
	DoubleLinkedList list;   
	list.insertHead(2);      
	list.insertHead(3);
	list.insertHead(1);
	list.outAll();          

	list.insertHead(2);
	list.insertTail(1);
	list.outAll();
	list.replaceItem(1, 9, true);
	list.outAll();
	list.replaceItem(3, 13);
	list.outAll();
	list.deleteTail();
	list.outAll();
	list.deleteItem(9);
	list.outAll();
	list.deleteItem(2, true);
	list.outAll();

	list.insertHead(1);

	std::cout << ((list.searchItem(1)) ? "1 found" : "1 not found") << std::endl;
	std::cout << ((list.searchItem(8)) ? "8 found" : "8 not found") << std::endl;

	DoubleLinkedList  list1 = list;  // Копирование списка
	list1.insertHead(4);         
	list1.insertHead(5);         
	list1.deleteHead();          
	list1.outAll();
	list1.insertHead(6);
	list1.deleteHead();
	list1.outAll();        

	std::cout << list1;
	std::cout << list;
	if (list1 == list)
	{
		std::cout << "Списки совпадают" << std::endl;
	}
	else
	{
		std::cout << "Списки не совпадают" << std::endl;
	}
	list.insertHead(4);
	std::cout << list1;
	std::cout << list;
	if (list1 == list)
	{
		std::cout << "Списки совпадают" << std::endl;
	}
	else
	{
		std::cout << "Списки не совпадают" << std::endl;
	}
	list.concat(list1);
	list.outAll();

	return 0;
}