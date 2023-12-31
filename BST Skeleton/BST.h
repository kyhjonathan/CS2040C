#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
	T _item;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	int _height;
public:
	TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; };

	friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
	int _size;
	TreeNode<T>* _root;
	void _printTree(int indent, TreeNode<T>*, bool withHeight);

	// The following functions are optional for you to implement. 
	TreeNode<T>*  _insert(TreeNode<T>* current, T x);
	void _inOrderPrint(TreeNode<T>*);
	void _postOrderPrint(TreeNode<T>*);
	void _preOrderPrint(TreeNode<T>*);
	TreeNode<T>* _rightRotation(TreeNode<T>*);
	TreeNode<T>* _leftRotation(TreeNode<T>*);
	TreeNode<T>* _searchMax(TreeNode<T>*);
	TreeNode<T>* _searchMin(TreeNode<T>*);
	TreeNode<T>* _search(TreeNode<T>*, T);
	void _destroySubTree(TreeNode<T>*);

public:
	BinarySearchTree() { _root = NULL; _size = 0; }
	~BinarySearchTree();
	int size() { return _size; };
	void insert(T);
	void printTree(bool withHeight = 1);
	void inOrderPrint();
	void postOrderPrint();
	void preOrderPrint();
	T searchMax() {
		TreeNode<T>* max = _searchMax(_root);
		return max->_item;
	};
	T searchMin() { 
		TreeNode<T>* min = _searchMin(_root);
		return min->_item;
	};
	bool exist(T);
	T search(T x) { return T(); };
	T successor(T);
	void update_height(TreeNode<T>*);

};



template <class T>
void BinarySearchTree<T>::insert(T x)
{
	_root = _root ? _insert(_root, x) : new TreeNode<T>(x);
	if (_size == 0) _size++;
}

template <class T>
bool BinarySearchTree<T>::exist(T x) {
	TreeNode<T>* current = _root;
	while (current) {
		if (current->_item == x) {
			return true;
		}
		if (current->_item < x) {
			if (current->_right) {
				current = current->_right;
				if (current->_item > x) {
					return false;
				}
			}
			if (!current->_right) {
				return false;
			}
		}
		if (current->_item > x) {
			if (current->_left) {
				current = current->_left;
				if (current->_item < x) {
					return false;
				}
			}
			if (!current->_left) {
				return false;
			}
		}
	}
	return true;
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {

	if (!node)
		return;

	if (node->_right)
		_printTree(indent + 2, node->_right, withHeight);
	for (int i = 0; i < indent; i++)
		cout << "  ";
	cout << node->_item;
	if (withHeight)
		cout << "(h=" << node->_height << ")";
	cout << endl;
	if (node->_left)
		_printTree(indent + 2, node->_left, withHeight);


};

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
	_printTree(0, _root, withHeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {

	_preOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	cout << node->_item << " ";
	_preOrderPrint(node->_left);
	_preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
	if (node->_left)
		_destroySubTree(node->_left);
	if (node->_right)
		_destroySubTree(node->_right);
	delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
	if (_root)
		_destroySubTree(_root);
}



template <class T>
void BinarySearchTree<T>::inOrderPrint() {
	_inOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_inOrderPrint(node->_left);
	cout << node->_item << " ";
	_inOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T>::postOrderPrint() {
	_postOrderPrint(_root);
	cout << endl;
}


template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
	if (!node) return;
	_postOrderPrint(node->_left);
	_postOrderPrint(node->_right);
	cout << node->_item << " ";
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {

	if (current->_item > x)
	{
		if (current->_left) {
			current->_left = _insert(current->_left, x);
		}
		else
		{
			current->_left = new TreeNode<T>(x);
			_size++;
			update_height(current);
		}
	}
	else if (x > current->_item) {
		if (current->_right) {
			current->_right = _insert(current->_right, x);
		}
		else
		{
			current->_right = new TreeNode<T>(x);
			_size++;
			update_height(current);
		}
	}
	else
		return current; // When the node already existed in the tree

	return current;

}

template <class T>
void BinarySearchTree<T>::update_height(TreeNode<T>* current) {
	if (!current->_left || !current->_right) {
		return;
	}
	current->_height = std::max(current->_left->_height, current->_right->_height) + 1;
}


template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
	if (!current->_right) {
		return current;
	}
	return _searchMax(current->_right);
}


template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
	if (!current->_left) { 
		return current;
	}
	return _searchMin(current->_left);
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_search(TreeNode<T>* current, T x) {
	return NULL;
}

template <class T>
T BinarySearchTree<T>::successor(T x)
{
	TreeNode<T>* current = _root;
	while (current->_item <= x) {
		current = current->_right;
	}
	if (current->_item > x) {
		while (current->_left) {
			current = current->_left;
		}
	}
	return current->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node)
{
	return node;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node)
{
	return node;
}
