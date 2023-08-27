#include <iostream>
#include "simpleIntLinkedList.h"
using namespace std;

ListNode::ListNode(int n)
{
	_item = n;
	_next = NULL;
}

void List::insertHead(int n)
{
	ListNode *aNewNode = new ListNode(n);
	aNewNode->_next = _head;
	_head = aNewNode;
	_size++;
};

void List::removeHead()
{
	if (_size > 0) {
		ListNode *temp = _head;
		_head = _head->_next;
		delete temp;
		_size--;
	}
}

void List::print() {
	ListNode* pointer = _head;
	for (int i = 0; i < _size; i++) {
		cout << pointer->_item << " ";
		pointer = pointer->_next;
	}
	cout << endl;
}

bool List::exist(int n) {
	ListNode* pointer = _head;
	for (int i = 0; i < _size; i++) {
		if (pointer->_item == n) {
			return 1;
		}
		pointer = pointer->_next;
	}
	return 0;
}

int List::headItem()
{
	return 0; // modify this
}

List::~List()
{
	while (_size != 0)
		removeHead();
};

