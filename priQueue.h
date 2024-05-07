
#pragma once
#include "priNode.h"
#include <iostream>
using namespace std;
#include "Base_Unit.h"





//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head;
    int counter;
public:
    void setcount(int c) {
        counter = c;
    }
    int getcount() {
        return counter;
    }
    priQueue() : head(nullptr) { counter = 0; }

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            counter++;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        counter++;
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty() || counter==0)
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        temp = NULL;
        counter--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem();
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
    void print() {
        priNode<T>* temp = head;
        int pri = 0;
        cout << "[ ";
        for (int i = 0; i < counter; i++) {

            cout << temp->getItem(pri) << ", ";
            temp = temp->getNext();
        }
        cout << " ]";
        //cout << endl;
    }
};
