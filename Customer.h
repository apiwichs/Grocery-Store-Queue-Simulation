#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <iostream>

class Customer {
private:
    double entryMoment;        // time customer enters the system (seconds)
    double exitMoment;         // time customer leaves the system
    int    itemTotal;          // number of items to process
    Customer* successorNode;   // next customer in line

public:
    // Construction / Destruction
    Customer(double entryStamp, int basketCount);
    ~Customer();

    // Accessors
    double get_arrivalTime() const;
    double get_departureTime() const;
    int get_numOfItems() const;
    Customer* get_next() const;

    // Mutators
    void set_arrivalTime(double timeValue);
    void set_departureTime(double timeValue);

    void set_numOfItems(int newCount);
    void set_next(Customer* nextNode);

    // Output
    void print() const;
};

#endif // CUSTOMER_HPP


