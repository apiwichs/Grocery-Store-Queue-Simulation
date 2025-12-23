#ifndef QUEUELIST_HPP
#define QUEUELIST_HPP

#include "Customer.h"

class QueueList {
private:
    Customer* queueHead;   // head of FIFO queue

public:
    QueueList();
    explicit QueueList(Customer* firstNode);
    ~QueueList();

    Customer* get_head();

    int get_items();               // total items across all customers
    void enqueue(Customer* node);  // add at back
    Customer* dequeue();           // remove from front

    void print();
};

#endif // QUEUELIST_HPP
