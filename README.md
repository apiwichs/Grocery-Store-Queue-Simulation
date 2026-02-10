# 🛒 Grocery Store Queue Simulation

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Queues%20%26%20Heaps-orange)
![Discrete Simulation](https://img.shields.io/badge/Simulation-Discrete--Event-green)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen)

A **time-driven discrete-event simulation** of a grocery store checkout system, modeling customer arrivals, service times, and dynamic register management using efficient C++ data structures.

The simulator advances a global clock, processes events in chronological order, and supports both **single-queue** and **multi-queue** checkout policies with full statistical analysis of customer wait times.

---

## 🚀 Highlights

- ⏱️ Time-accurate discrete-event simulation  
- 🧾 Dynamic register open/close handling  
- 🧍 Single-queue and multi-queue checkout models  
- 📊 Max / average / standard deviation wait-time analysis  
- ⚙️ Command-driven simulation via standard input  
- 🧠 Priority-based event processing  
- ♻️ Safe dynamic memory management  

---

## 🧠 Simulation Modes

### 🔹 Single Queue Mode
- All customers wait in one shared queue
- Any available register immediately serves the next customer
- Tie-breaking is based on register creation order

### 🔹 Multiple Queue Mode
- Each register maintains its own queue
- Incoming customers join the register with the **fewest total items**
- Ties are broken by register creation order
- Customers never switch queues once assigned

---

## ⏱️ Simulation Time Model

- A **global simulation clock** starts at time `0`
- Every command includes a `timeElapsed` value
- Before executing a command:
  - The clock advances by `timeElapsed`
  - All customer departures within that interval are processed
- Departures are handled strictly by **earliest departure time**, independent of register order

---

## 📥 Input Commands

All commands are read from **standard input** and processed sequentially.

### Open a Register
```
register open <ID> <secPerItem> <setupTime> <timeElapsed>
```

- Opens a new checkout register
- Register IDs must be unique
- Advances simulation time before opening
- In single-queue mode, idle customers are immediately served

---

### Close a Register
```
register close <ID> <timeElapsed>
```

- Advances simulation time before closing
- All departures before close are processed
- Registers are guaranteed to be idle when closed

---

### Add a Customer
```
customer <items> <timeElapsed>
```

- Adds a customer with a specified item count
- Time advances before arrival
- Queue selection depends on simulation mode
- In multi-queue mode, customers are discarded if no registers are open

---

## 📤 Program Output

### Runtime Output
The simulation reports:
- Customer arrivals
- Customer departures (with register ID and departure time)
- Register open/close events

### End-of-Simulation Statistics
After EOF, the program prints:
1. **Maximum customer wait time**
2. **Average customer wait time**
3. **Standard deviation of customer wait time**

**Wait Time Definition:**  
`departure time − arrival time`

---

## 🏗️ Implementation Details

- Implemented in **C++ (STL-based)**
- Uses:
  - Queues for customer management
  - Ordered structures for event timing
  - Dynamic memory allocation with proper cleanup
- Designed to scale cleanly with increasing customers and registers

---

## 🎓 Academic Context

Developed for **ECE 244 – Programming Fundamentals**  
University of Toronto

**Academic Integrity Notice**  
This repository is provided for **demonstration and portfolio purposes only**.  
Students currently enrolled in ECE 244 or similar courses should **not copy or submit** this code for academic credit.

---

## 👤 Author

**Apiwich Sumeksri**  
Electrical & Computer Engineering  
University of Toronto
