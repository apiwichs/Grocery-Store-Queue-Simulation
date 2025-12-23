//Include necessary header files
#include "RegisterList.h"
#include <iostream>

using namespace std;

//RegisterList class implementation
RegisterList::RegisterList() {
    startNode = nullptr;
    nodeCount = 0;
}

RegisterList::~RegisterList() {
    Register* walker = startNode;

    while (walker != nullptr) {
        Register* nextHop = walker->get_next();
        walker->set_next(nullptr);   // detach for safety
        delete walker;
        walker = nextHop;
    }

    startNode = nullptr;
    nodeCount = 0;
}

Register* RegisterList::get_head() {
    return startNode;
}

int RegisterList::get_size() {
    return nodeCount;
}

Register* RegisterList::get_min_items_register(){
    if (startNode == nullptr) {
        return nullptr; }

    Register* currentRegister = startNode;
    Register* minRegister = currentRegister;

    QueueList* minQueue = minRegister->get_queue_list();
    int minItemCount = minQueue->get_items();

    currentRegister = currentRegister->get_next();

    while (currentRegister != nullptr) {
        QueueList* currentQueue = currentRegister->get_queue_list();
        int currentItemCount = currentQueue->get_items();

        if (currentItemCount < minItemCount) {
            minItemCount = currentItemCount;
            minRegister = currentRegister;
        }

        currentRegister = currentRegister->get_next();
    }

    return minRegister;
}



Register* RegisterList::get_free_register(){
    for (Register* r = startNode; r != nullptr; r = r->get_next()) {
        if (r->get_queue_list()->get_head() == nullptr) {
            return r;
        }
    }
    return nullptr;
}

void RegisterList::enqueue(Register* newRegister) {
    if (newRegister == nullptr) return;

    newRegister->set_next(nullptr);

    if (startNode == nullptr) {
        startNode = newRegister;
        nodeCount++;
        return;
    }

    Register* tail = startNode;
    while (tail->get_next() != nullptr) {
        tail = tail->get_next();
    }

    tail->set_next(newRegister);
    nodeCount++;
}

bool RegisterList::foundRegister(int ID){
    for (Register* r = startNode; r != nullptr; r = r->get_next()) {
        if (r->get_ID() == ID) return true;
    }
    return false;
}

Register* RegisterList::dequeue(int ID){
    Register* prevNode = nullptr;
    Register* currNode = startNode;

    while (currNode != nullptr && currNode->get_ID() != ID) {
        prevNode = currNode;
        currNode = currNode->get_next();
    }

    if (currNode == nullptr) return nullptr; // not found

    // removing head
    if (prevNode == nullptr) {
        startNode = currNode->get_next();
    } else {
        prevNode->set_next(currNode->get_next());
    }

    currNode->set_next(nullptr);
    nodeCount--;

    return currNode;
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed){
    Register* bestRegister = nullptr;
    double bestDepartTime = 0.0;

    for (Register* r = startNode; r != nullptr; r = r->get_next()) {
        const double departT = r->calculateDepartTime(); // -1 if empty

        if (departT >= 0) {
            if (bestRegister == nullptr || departT < bestDepartTime) {
                bestRegister = r;
                bestDepartTime = departT;
            }
        }
    }

    if (bestRegister == nullptr) return nullptr;      // all queues empty
    if (bestDepartTime <= expTimeElapsed) return bestRegister;

    return nullptr;
}

void RegisterList::print(){
    for (Register* r = startNode; r != nullptr; r = r->get_next()) {
        r->print();
    }
}
