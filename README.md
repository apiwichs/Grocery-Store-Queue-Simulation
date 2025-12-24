# 🛒 Grocery Store Queue Simulation (C++)

---

## 1. Project Overview

This project implements a time-based simulation of a grocery store checkout
system. Customers arrive over simulated time and are served by checkout
registers that can open and close dynamically.

The simulation processes user commands sequentially, advancing a global
simulation clock and updating customer and register states accordingly.

---

## 2. Queueing Modes

The simulation operates in one of two modes, selected at startup.

### Single Queue Mode
- All customers wait in one shared virtual queue.
- When a register becomes available, it immediately serves the next
  waiting customer.
- If multiple registers are free, the register closest to the head of the
  register list is selected.

### Multiple Queue Mode
- Each register maintains its own queue.
- Upon arrival, a customer joins the register whose queue has the fewest
  total items.
- If multiple registers tie, the one closest to the head of the register
  list is selected.
- Customers do not switch queues once assigned.

---

## 3. Simulation Time Model

- The simulation maintains a global clock starting at time 0.
- Each command includes a `timeElapsed` parameter.
- Before executing a command:
  - The simulation clock is advanced by `timeElapsed`.
  - All customer departures that occur within this time window are processed.
- Customer departures are processed in order of earliest departure time,
  regardless of register position in the list.

---

## 4. Input Commands

All input is provided through standard input using the formats below.
Each command advances the simulation clock by the specified `timeElapsed`.

---

### 4.1 Open a Register

**Command**  
`register open <ID> <secPerItem> <setupTime> <timeElapsed>`

**Description**
- Opens a new checkout register.
- `ID` must be unique.
- `secPerItem` specifies processing time per item.
- `setupTime` is the fixed overhead per customer.
- Simulation time is advanced before the register is opened.
- In single queue mode:
  - If customers are waiting, the new register immediately serves
    the next customer.
- If the register ID already exists, an error is reported.

---

### 4.2 Close a Register

**Command**  
`register close <ID> <timeElapsed>`

**Description**
- Closes an existing checkout register.
- Simulation time is advanced before closing.
- All customer departures that occur before the close are processed.
- If the register exists:
  - It is removed from the system and its memory is freed.
- If the register does not exist, an error is reported.
- Registers are guaranteed to be idle when closed.

---

### 4.3 Add a Customer

**Command**  
`customer <items> <timeElapsed>`

**Description**
- Adds a new customer to the simulation.
- `items` specifies the number of items the customer has.
- Simulation time is advanced before the customer arrives.
- In single queue mode:
  - The customer joins a free register if available;
    otherwise, the shared queue.
- In multiple queue mode:
  - The customer joins the register with the fewest total items.
  - If no registers are open, the customer is discarded.

---

## 5. Simulation Output

### Runtime Output
The program reports:
- Customer arrivals
- Customer departures (including register ID and departure time)
- Register opening and closing events

### End-of-Simulation Statistics
After end-of-file input, the program reports:
1. Maximum customer wait time
2. Average customer wait time
3. Standard deviation of customer wait time

Customer wait time is defined as:  
`departure time − arrival time`

---

## 6. Academic Context

This project was developed for **ECE 244 – Programming Fundamentals**.

Academic Integrity Notice:
This repository is shared for demonstration purposes only.
Students currently enrolled in ECE 244 or similar courses should not copy
or submit this code for academic credit.

---

## 7. Author

Apiwich Sumeksri  
Electrical & Computer Engineering  
University of Toronto
