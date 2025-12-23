//Include necessary header files and libraries
#include "QueueList.h"
#include "Customer.h"

#include <iostream>
using namespace std;

//QueueList class implementation
QueueList::QueueList() { queueHead = nullptr; }


// Initialize queue with one customer
QueueList::QueueList(Customer* firstNode) { queueHead = firstNode; }

// Destructor: free entire queue
QueueList::~QueueList() {
    Customer* current = queueHead;
    while (current != nullptr) {
        Customer* toRemove = current;
        current = current->get_next();
        toRemove->set_next(nullptr);
        delete toRemove;
    }
    queueHead = nullptr;
}

Customer* QueueList::get_head() { return queueHead; }

void QueueList::enqueue(Customer* node) {
    if (node == nullptr) return;
    node->set_next(nullptr);

    if (queueHead == nullptr) {
        queueHead = node;
        return;
    }

    Customer* iterator = queueHead;
    while (iterator->get_next() != nullptr) {
        iterator = iterator->get_next();
    }
    iterator->set_next(node);
}

Customer* QueueList::dequeue() {
    if (queueHead == nullptr) return nullptr;

    Customer* removedNode = queueHead;
    queueHead = queueHead->get_next();

    removedNode->set_next(nullptr);
    return removedNode;
}

int QueueList::get_items() {
    int totalItems = 0;

    for (Customer* it = queueHead; it != nullptr; it = it->get_next()) {
        totalItems += it->get_numOfItems();
    }

    return totalItems;
}

void QueueList::print(){
    for (Customer* it = queueHead; it != nullptr; it = it->get_next()) 
        it->print();
}
