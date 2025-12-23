//Include necessary header files and libraries
#include "Customer.h"
#include <iostream>
using namespace std;

//Customer class imlementation
Customer::Customer(double entryStamp, int basketCount)
{
    entryMoment   = entryStamp;
    exitMoment    = -1;
    itemTotal     = basketCount;
    successorNode = nullptr;
}

Customer::~Customer()
{
    successorNode = nullptr;
}


double Customer::get_arrivalTime() const
{
    return entryMoment;
}

double Customer::get_departureTime() const
{
    return exitMoment;
}

int Customer::get_numOfItems() const
{
    return itemTotal;
}

Customer* Customer::get_next() const
{
    return successorNode;
}

void Customer::set_arrivalTime(double timeValue) { entryMoment = timeValue; }

void Customer::set_departureTime(double timeValue) { exitMoment = timeValue; }

void Customer::set_numOfItems(int newCount) { itemTotal = newCount; }

void Customer::set_next(Customer* nextNode) { successorNode = nextNode; }


void Customer::print() const
{
    cout << "Arrival time: " << entryMoment << endl;
    cout << "Departure time: ";
    if (exitMoment < 0) {
        cout << "N/A";
    } else {
        cout << exitMoment;
    }
    cout << endl;

    cout << "Number of items: " << itemTotal << endl;
}
