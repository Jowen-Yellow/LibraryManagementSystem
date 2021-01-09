#pragma once
#include<iostream>
#include"library.h"
//定义节点类
typedef Book ElemType;
template<class T>
class Node
{
public:
	Node(Node<T>* p = NULL, Node<T>* n = NULL) :prev(p), next(n) {}
	ElemType data;//存放数据
	Node<T>* prev;//前一个节点
	Node<T>* next;//后一个节点
};
//定义列表
template<class T>
class myList
{
public:
	myList(int s = 0);
	void push_back(ElemType d);
	void insert(int n, ElemType d);
	Node<T>* operator[](int n);
	void erase(int n);
	void change(int n, ElemType d);
	int size();
	void clear();
	bool empty();
private:
	Node<T>* head;//头结点
	int sz;//列表长度
};
