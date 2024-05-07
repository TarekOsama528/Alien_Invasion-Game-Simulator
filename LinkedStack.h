#pragma once
using namespace std;
#include "StackADT.h"
#include "Node.h"

template<typename T>
class LinkedStack : public StackADT<T> {

	Node<T>* Top;
	int counter;
public:
	LinkedStack() {
		Top = NULL;
		counter = 0;
	}
	bool isEmpty() const {
		return Top;
	}
	bool push(const T& data) {
		Node<T>* newnode = new Node<T>;
		newnode->setItem(data);
		newnode->setNext(Top);
		Top = newnode;
		counter++;
		return true;

	}
	bool pop(T& data) {
		if (!isEmpty()) {
			data = NULL;
			return false;
		}
		Node<T>* delptr = Top;
		data = delptr->getItem();
		if (counter == 1)
		{
			Top = NULL;
		}
		else
		{
			Top = Top->getNext();
		}
		delete delptr;
		counter--;
		return true;
	}
	bool peek(T& data) const {
		if (!isEmpty()) {
			return false;
		}
		data = Top->getItem();
		return true;
	}
	void print() {
		Node<T>* temp = Top;
		cout << "[ ";
		for (int i = 0; i < counter; i++) {
			cout << temp->getItem()<<", ";
			temp=temp->getNext();
		}
		cout << " ]";
		//cout << endl;
	}
	void setcount(int c) {
		counter = c;
	}
	int getcount() {
		return counter;
	}
	~LinkedStack() {};
};