#include"myList.h"
#include<iostream>
using namespace std;
//构造函数（列表生成）
template<class T>
myList<T>::myList(int s)//尾插法生成链表(
{
	Node<T>* currPtr = head = new Node<T>;
	Node<T>* newNode;
	for (int i = 0; i < s; i++)
	{
		newNode = new Node<T>;
		currPtr->next = newNode;
		newNode->prev = currPtr;
		currPtr = newNode;
	}
	currPtr = NULL;
	sz = s;//
}
//追加节点
template<class T>
void myList<T>::push_back(ElemType d)
{
	Node<T>* currPtr = head;
	Node<T>* newNode = new Node<T>;
	while (currPtr->next != NULL)currPtr = currPtr->next;
	currPtr->next = newNode;
	newNode->next = NULL;
	newNode->prev = currPtr;
	newNode->data = d;
	sz++;
}
//
template<class T>
void myList<T>::insert(int n, ElemType d)
{
	if (n <= 0)throw 0;
	Node<T>* currPtr = head;
	Node<T>* newNode = new Node<T>;
	while (n--)currPtr = currPtr->next;
	newNode->prev = currPtr->prev;
	currPtr->prev->next = newNode;
	newNode->next = currPtr;
	currPtr->prev = newNode;
	newNode->data = d;
	sz++;
}
//
template<class T>
void myList<T>::erase(int n)
{
	if (n < 0)throw 0;
	Node<T>* currPtr = head->next;
	while (n--)currPtr = currPtr->next;
	if (currPtr->next == NULL)
	{
		
		currPtr->prev->next = NULL;
		delete currPtr;
	}
	else
	{
		currPtr->prev->next = currPtr->next;
		currPtr->next->prev = currPtr->prev;
		delete currPtr;
	}
	sz--;
}
//
template<class T>
void myList<T>::change(int n, ElemType d)
{
	if (n <= 0)throw 0;
	Node<T>* currPtr = head;
	while (n--)currPtr = currPtr->next;
	currPtr->data = d;
}
//
template<class T>
Node<T>* myList<T>::operator[](int n)
{
	Node<T>* currPtr = head->next;
	if (n < 0||n>=sz)throw 1;
	while (n--)currPtr = currPtr->next;
	return currPtr;
}
template<class T>
int myList<T>::size()
{
	return sz;
}