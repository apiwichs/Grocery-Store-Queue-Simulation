#ifndef REGISTER_H
#define REGISTER_H

#include "QueueList.h"

class Register {
private:
    int registerTag;              // formerly ID
    double secondsPerUnit;        // formerly secPerItem
    double fixedCustomerOverhead; // formerly overheadPerCustomer
    double freeTimestamp;         // formerly availableTime
    QueueList* waitingLine;       // formerly queue
    Register* link;               // formerly next

public:
    Register(int ID, double secPerItem,
             double overheadPerCustomer, double entryTime);
    ~Register();

    int get_ID();
    double get_secPerItem();
    double get_overheadPerCustomer();
    double get_availableTime();
    Register* get_next();
    QueueList* get_queue_list();

    void set_availableTime(double availableSince);
    void set_next(Register* next);

    double calculateDepartTime();
    void departCustomer(QueueList* doneList);

    void print();
};

#endif // REGISTER_H
