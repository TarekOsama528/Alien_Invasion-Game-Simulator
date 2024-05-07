#pragma once
using namespace std;
#include <iostream>
#include "Base_Unit.h"
#define max 1000



template <typename T>
class Array {
	int size;
	int length;
	T items[max];
public:
	void setcount(int c) {
		length = c;
	}
	int getcount() {
		return length;
	}
	Array() {
		size = max;
		length = 0;
	}
	bool Add(T data) {
		if (length == max) {
			return false;
		}
		items[length] = data;
		length++;
		return true;
	}
	bool Remove(int index,T& item) {
		if (length == 0) {
			return false;
		}
		item = items[index];
		items[index] = items[length - 1];
		length--;
		return true;
	}
	void print() {
		cout << "[ ";
		for (int i = 0; i < length; i++) {
			cout << items[i]<<", ";
		}
		cout << " ]";
		//cout << endl;
	}
	bool peek(T& item) {
		if (length == 0)
		{
			item = NULL;
			return false;
		}
		int random = rand() % getcount();
		item = items[random];
		return true;
	}
	bool remove(T item) {
		if (length == 0) return false;
		for (size_t i = 0; i < length; i++)
		{
			if (items[i] == item) {
				items[i] = items[length - 1];
				length--;
			}
		}
		return true;
	}
};


