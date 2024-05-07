#pragma once
#include<iostream>
#include"LinkedQueue.h"
#include"Drones.h"
#include "Base_Unit.h"



class SpecialQueue :public LinkedQueue<AD*> {
public:
    bool enqueueFront(AD*& newEntry) {
        Node<AD*>* newNodePtr = new Node<AD*>(newEntry);
        if (isEmpty()) {
            frontPtr = newNodePtr;
            backPtr = newNodePtr;
        }
        else {
            newNodePtr->setNext(frontPtr);
            frontPtr = newNodePtr;
        }
        return true;
    }

    bool dequeueRear(AD*& rearEntry) {
        if (isEmpty())
            return false;

        Node<AD*>* currentPtr = frontPtr;
        Node<AD*>* previousPtr = nullptr;

        // Traverse to the end of the queue
        while (currentPtr->getNext() != nullptr) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->getNext();
        }

        // currentPtr now points to the last node
        rearEntry = currentPtr->getItem();
        delete currentPtr;

        if (previousPtr != nullptr) {
            previousPtr->setNext(nullptr);
            backPtr = previousPtr;
        }
        else { // if there was only one element
            frontPtr = nullptr;
            backPtr = nullptr;
        }
        counter--;
        return true;
    }
};

