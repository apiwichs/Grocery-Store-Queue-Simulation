/* =====================================================================
 *  Grocery Store Queue Simulation (C++)
 * =====================================================================
 *
 *  Course Context:
 *    ECE 244 — Programming Fundamentals
 *
 *  ---------------------------------------------------------------------
 *  PROJECT DESCRIPTION
 *  ---------------------------------------------------------------------
 *
 *  This project implements a time-based grocery store checkout simulation
 *  in C++. The system models customers arriving over time and being served
 *  by dynamically managed checkout registers.
 *
 *  The simulation supports two operating modes:
 *
 *    1) Single Queue Mode
 *       - All customers wait in a shared virtual queue
 *       - Free registers pull the next waiting customer when available
 *
 *    2) Multiple Queue Mode
 *       - Each register maintains its own queue
 *       - New customers join the register with the fewest total items
 *
 *  The simulation advances in discrete time steps provided through input
 *  commands and processes customer arrivals, departures, and register
 *  events accordingly.
 *
 *  ---------------------------------------------------------------------
 *  CORE FEATURES
 *  ---------------------------------------------------------------------
 *
 *  - Event-driven simulation using command-based input
 *  - Dynamic opening and closing of checkout registers
 *  - Linked-list–based queue implementation
 *  - Explicit heap memory management (no STL containers)
 *  - Tracks and reports customer wait-time statistics
 *
 *  ---------------------------------------------------------------------
 *  INPUT COMMANDS
 *  ---------------------------------------------------------------------
 *
 *  register open <ID> <secPerItem> <setupTime> <timeElapsed>
 *      Opens a new register with the specified parameters.
 *
 *  register close <ID> <timeElapsed>
 *      Closes an existing register after advancing simulation time.
 *
 *  customer <items> <timeElapsed>
 *      Adds a new customer with the given number of items.
 *
 *  ---------------------------------------------------------------------
 *  SIMULATION OUTPUT
 *  ---------------------------------------------------------------------
 *
 *  During execution, the program reports:
 *    - Customer arrivals
 *    - Customer departures
 *    - Register open/close events
 *
 *  At termination, the following statistics are printed:
 *    - Maximum customer wait time
 *    - Average customer wait time
 *    - Standard deviation of wait time
 *
 *  ---------------------------------------------------------------------
 *  FILE ORGANIZATION
 *  ---------------------------------------------------------------------
 *
 *  main.cpp
 *      - Simulation driver and command processing
 *
 *  Customer.h / Customer.cpp
 *      - Customer object (arrival time, departure time, items)
 *
 *  QueueList.h / QueueList.cpp
 *      - Linked-list queue implementation
 *
 *  Register.h / Register.cpp
 *      - Checkout register logic and timing
 *
 *  RegisterList.h / RegisterList.cpp
 *      - Linked list of active registers
 *
 *  ---------------------------------------------------------------------
 *  ACADEMIC INTEGRITY NOTICE
 *  ---------------------------------------------------------------------
 *
 *  This repository is provided for educational and demonstration purposes
 *  only. It reflects an independent implementation created by the author.
 *
 *  Students currently enrolled in ECE 244 or similar courses should not
 *  copy or submit this code for academic credit.
 *
 *  ---------------------------------------------------------------------
 *  AUTHOR
 *  ---------------------------------------------------------------------
 *
 *  Apiwich "Ohm" Sumeksri
 *  Electrical & Computer Engineering
 *  University of Toronto
 *
 * =====================================================================
 */
