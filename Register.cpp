//Include necessary headers and libraries
#include "Register.h"
#include <iostream>

using namespace std;

// Register class implementation
Register::Register(int ID, double secPerItem,
                   double overheadPerCustomer, double entryTime)
{
    registerTag          = ID;
    secondsPerUnit       = secPerItem;
    fixedCustomerOverhead = overheadPerCustomer;
    freeTimestamp        = entryTime;

    link        = nullptr;
    waitingLine = new QueueList();
}

Register::~Register(){
    delete waitingLine;
    waitingLine = nullptr; }

QueueList* Register::get_queue_list() {
    return waitingLine;
}

Register* Register::get_next(){
    return link;
}

int Register::get_ID() {
    return registerTag;
}

double Register::get_secPerItem() {
    return secondsPerUnit;
}

double Register::get_overheadPerCustomer(){
    return fixedCustomerOverhead;
}

double Register::get_availableTime() {
    return freeTimestamp;
}

void Register::set_next(Register* next) {
    link = next;
}

void Register::set_availableTime(double availableSince) {
    freeTimestamp = availableSince;
}

double Register::calculateDepartTime() {
    Customer* activeCustomer = waitingLine->get_head();
    if (activeCustomer == nullptr) {
        return -1;
    }

    const double arrivalInstant = activeCustomer->get_arrivalTime();
    const int itemsInBasket     = activeCustomer->get_numOfItems();

    double serviceBegin = freeTimestamp;
    if (arrivalInstant > serviceBegin) {
        serviceBegin = arrivalInstant;
    }

    return serviceBegin
         + (itemsInBasket * secondsPerUnit)
         + fixedCustomerOverhead;
}

void Register::departCustomer(QueueList* doneList) {
    if (waitingLine->get_head() == nullptr) return;

    const double completionTime = calculateDepartTime();
    Customer* finishedCustomer = waitingLine->dequeue();

    finishedCustomer->set_departureTime(completionTime);
    freeTimestamp = completionTime;

    doneList->enqueue(finishedCustomer);
}

void Register::print(){
    cout << "Register ID: " << registerTag << endl;
    cout << "Time per item: " << secondsPerUnit << endl;
    cout << "Overhead per customer: " << fixedCustomerOverhead << endl;

    if (waitingLine->get_head() != nullptr) {
        cout << "Queue has customers:\n";
        waitingLine->print();
    }
}
