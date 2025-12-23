#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:
string getMode();

// Register
void parseRegisterAction(stringstream& lineStream, string mode);
void openRegister(stringstream& lineStream, string mode);
void closeRegister(stringstream& lineStream, string mode);

// Customer
void addCustomer(stringstream& lineStream, string mode);

// Helper functions
bool getInt(stringstream& lineStream, int& iValue);
bool getDouble(stringstream& lineStream, double& dValue);
bool foundMoreArgs(stringstream& lineStream);

// Global variables
RegisterList* registerList;
QueueList* doneList;
QueueList* singleQueue;
double expTimeElapsed;

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0.0;

  string mode = getMode();

  cout << "> ";
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "register") {
      parseRegisterAction(ss, mode);
    } else if (cmd == "customer") {
      addCustomer(ss, mode);
    } else {
      cout << "Invalid operation" << endl;
    }

    cout << "> ";
  }

  cout << "Finished at time " << expTimeElapsed << " Statistics:" << endl;

  double sum = 0.0, sumSq = 0.0, maxWait = 0.0;
  int count = 0;

  for (Customer* c = doneList->get_head(); c != nullptr; c = c->get_next()) {
    double wait = c->get_departureTime() - c->get_arrivalTime();
    sum += wait;
    sumSq += wait * wait;
    if (wait > maxWait) maxWait = wait;
    count++;
  }

  if (count == 0) {
    cout << "Maximum wait time: 0" << endl;
    cout << "Average wait time: 0" << endl;
    cout << "Standard Deviation of wait time: 0" << endl;
  } else {
    double avg = sum / count;
    double sd = sqrt((sumSq / count) - (avg * avg));
    cout << "Maximum wait time: " << maxWait << endl;
    cout << "Average wait time: " << avg << endl;
    cout << "Standard Deviation of wait time: " << sd << endl;
  }

  delete registerList;
  delete singleQueue;
  delete doneList;

  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to simulate multiple queues:\n> ";
  getline(cin, mode);

  if (mode == "single")
    cout << "Simulating a single queue ..." << endl;
  else if (mode == "multiple")
    cout << "Simulating multiple queues ..." << endl;

  return mode;
}

void addCustomer(stringstream& lineStream, string mode) {
  int items;
  double dt;

  if (!getInt(lineStream, items) || !getDouble(lineStream, dt)) {
    cout << "Error: too few arguments" << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  expTimeElapsed += dt;

  Register* r =
      registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  while (r != nullptr) {
    int id = r->get_ID();
    double depart = r->calculateDepartTime();
    r->departCustomer(doneList);
    cout << "Departed a customer at register ID " << id
         << " at " << depart << endl;

    if (mode == "single" && singleQueue->get_head() != nullptr &&
        r->get_queue_list()->get_head() == nullptr) {
      r->get_queue_list()->enqueue(singleQueue->dequeue());
    }

    r = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  }

  cout << "A customer entered" << endl;
  Customer* c = new Customer(expTimeElapsed, items);

  if (mode == "single") {
    Register* freeR = registerList->get_free_register();
    if (freeR != nullptr) {
      freeR->get_queue_list()->enqueue(c);
      cout << "Queued a customer with free register " << freeR->get_ID()
           << endl;
    } else {
      cout << "No free registers" << endl;
      singleQueue->enqueue(c);
    }
  } else {
    Register* best = registerList->get_min_items_register();
    if (best != nullptr) {
      best->get_queue_list()->enqueue(c);
      cout << "Queued a customer with quickest register "
           << best->get_ID() << endl;
    } else {
      delete c;
    }
  }
}

void parseRegisterAction(stringstream& lineStream, string mode) {
  string op;
  lineStream >> op;
  if (op == "open")
    openRegister(lineStream, mode);
  else if (op == "close")
    closeRegister(lineStream, mode);
  else
    cout << "Invalid operation" << endl;
}

void openRegister(stringstream& lineStream, string mode) {
  int ID;
  double spi, setup, dt;

  if (!getInt(lineStream, ID) || !getDouble(lineStream, spi) ||
      !getDouble(lineStream, setup) || !getDouble(lineStream, dt)) {
    cout << "Error: too few arguments" << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  expTimeElapsed += dt;

  Register* r =
      registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  while (r != nullptr) {
    int id = r->get_ID();
    double depart = r->calculateDepartTime();
    r->departCustomer(doneList);
    cout << "Departed a customer at register ID " << id
         << " at " << depart << endl;

    if (mode == "single" && singleQueue->get_head() != nullptr &&
        r->get_queue_list()->get_head() == nullptr &&
        r->get_availableTime() <= expTimeElapsed) {
      r->get_queue_list()->enqueue(singleQueue->dequeue());
      cout << "Queued a customer with free register " << r->get_ID()
           << endl;
    }

    r = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  }

  for (Register* p = registerList->get_head(); p != nullptr; p = p->get_next()) {
    if (p->get_ID() == ID) {
      cout << "Error: register " << ID << " is already open" << endl;
      return;
    }
  }

  Register* reg = new Register(ID, spi, setup, expTimeElapsed);
  registerList->enqueue(reg);
  cout << "Opened register " << ID << endl;

  if (mode == "single" && singleQueue->get_head() != nullptr) {
    reg->get_queue_list()->enqueue(singleQueue->dequeue());
    cout << "Queued a customer with free register " << ID << endl;
  }
}

void closeRegister(stringstream& lineStream, string mode) {
  int ID;
  double dt;

  if (!getInt(lineStream, ID) || !getDouble(lineStream, dt)) {
    cout << "Error: too few arguments" << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  expTimeElapsed += dt;

  Register* r =
      registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  while (r != nullptr) {
    int id = r->get_ID();
    double depart = r->calculateDepartTime();
    r->departCustomer(doneList);
    cout << "Departed a customer at register ID " << id
         << " at " << depart << endl;

    if (mode == "single" && singleQueue->get_head() != nullptr &&
        r->get_queue_list()->get_head() == nullptr) {
      r->get_queue_list()->enqueue(singleQueue->dequeue());
    }

    r = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
  }

  Register* removed = registerList->dequeue(ID);
  if (removed == nullptr) {
    cout << "Error: register " << ID << " is not open" << endl;
    return;
  }

  delete removed;
  cout << "Closed register " << ID << endl;
}

bool getInt(stringstream& lineStream, int& iValue) {
  string token;
  lineStream >> token;
  if (lineStream.fail()) return false;
  iValue = stoi(token);
  return true;
}

bool getDouble(stringstream& lineStream, double& dValue) {
  string token;
  lineStream >> token;
  if (lineStream.fail()) return false;
  dValue = stod(token);
  return true;
}

bool foundMoreArgs(stringstream& lineStream) {
  string extra;
  lineStream >> extra;
  return !lineStream.fail();
}
