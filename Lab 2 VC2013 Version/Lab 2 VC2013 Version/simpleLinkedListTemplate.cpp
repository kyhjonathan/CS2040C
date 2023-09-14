#pragma once

#ifndef SIMPLELINKEDLISTTEMPLATEHPP
#define SIMPLELINKEDLISTTEMPLATEHPP

#include <iostream>
#include "simpleLinkedListTemplate.h"
using namespace std;


template <class T>
ListNode<T>::ListNode(T n)
{
	_item = n;
	_next = NULL;
}

template <class T>
void List<T>::insertHead(T n)
{
	ListNode<T> *aNewNode = new ListNode<T>(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

template <class T>
void List<T>::removeHead()
{
	if (_size > 0) {
		ListNode<T> *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

template <class T>
void List<T>::print(bool withNL) {

	ListNode<T> *temp = _head;
	while (temp) {
		cout << temp->_item;
		if (withNL)
			cout << endl;
		else
			cout << " ";
		temp = temp->_next;
	}
	cout << endl;

}

template <class T>
bool List<T>::exist(T n) {
	ListNode<T>* ptr = _head;
	while(ptr) {
		if (ptr->content() == n) {
			return true;
		}
		ptr = ptr->_next;
	}
	return false;
}

template <class T>
T List<T>::headItem()
{
	if (_size)
		return *_head;
}

template <class T>
T List<T>::extractMax()
{
	ListNode<T>* ptr = _head;
	ListNode<T>* bef_max = NULL;
	ListNode<T>* max_ptr = _head;
	T max = ptr->_item;
	while (ptr->_next) {
		if (ptr->_next->_item > max) {
			max_ptr = ptr->_next;
			max = ptr->_next->_item;
			bef_max = ptr;
		}
		ptr = ptr->_next;
	}
	if (max_ptr == _head) {
		removeHead();
	}
	else {
		ptr = max_ptr;
		bef_max->_next = max_ptr->_next;
		delete ptr;
		_size--;
	}
	// if there are duplicates maximas in the list, return the leftmost one (the one closest to the _head)
	return max;
}

template <class T>
void List<T>::reverseOp() {
	if (_size < 2) {
		return;
	}
	ListNode<T>* current = _head;
	ListNode<T>* prev = NULL;
	ListNode<T>* next = current->_next;
	for (int i = 0; i < _size-1; i++) {
		next = current->_next;
		current->_next = prev;
		prev = current;
		current = next;
	}
	current->_next = prev;
	_head = current;
}



template <class T>
List<T>::~List()
{
	while (_head)
		removeHead();
};


#endif