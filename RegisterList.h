#ifndef REGISTERLIST_HPP
#define REGISTERLIST_HPP

#include "Register.h"

class RegisterList {
private:
    Register* startNode;   // head of the register list
    int nodeCount;         // number of registers tracked

public:
    RegisterList();
    ~RegisterList();

    Register* get_head();
    int get_size();

    Register* get_min_items_register();
    Register* get_free_register();
    Register* calculateMinDepartTimeRegister(double expTimeElapsed);

    bool foundRegister(int ID);

    void enqueue(Register* newRegister);
    Register* dequeue(int ID);
    void print();
};

#endif // REGISTERLIST_HPP
