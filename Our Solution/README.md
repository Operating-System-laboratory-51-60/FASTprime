# Multiprocess Prime Number Calculator
**Submission Type:** Man-Made Implementation (Modular Architecture)

## 1. Project Overview
This project is a high-performance system designed to calculate prime numbers within a given range using **Parallel Processing**. Unlike standard scripts that run on a single processor, this solution uses the C `fork()` system call to split the workload across multiple CPU cores, minimizing execution time.

The system is engineered with a **Modular Architecture**, separating the User Interface, Process Management, and Mathematical Logic into distinct files for maintainability and scalability.

## 2. File Structure & Architecture
The project consists of four main components:

* **`interface.c` (The Controller):**
    * Acts as the central dashboard/menu for the user.
    * Compiles and executes other components based on user input.
    * Provides a clean, text-based interface to avoid complex command-line arguments.

* **`main.c` (The Process Manager):**
    * Handles the Operating System level tasks: Forking, File I/O, and Timing.
    * Splits the number range into chunks and assigns them to child processes.
    * Merges results from temporary files into the final `prime.txt`.

* **`primes.c` & `primes.h` (The Logic Module):**
    * Contains the optimized mathematical algorithm to detect prime numbers.
    * Isolated from the OS logic to ensure clean code separation.

* **`plotter.py` (The Visualizer):**
    * An automation script written in Python.
    * Runs benchmarks on the C executable with increasing core counts.
    * Generates a performance graph (Time vs. Cores) using `matplotlib`.

## 3. How to Run in WSL

### Step 1: Install Dependencies
Open your WSL terminal and run:
```bash
sudo apt update
sudo apt install build-essential python3-matplotlib
```
### Step 2: Compile the System
Run these two commands to build the project manually:
#### 1 Compile the Worker (Math Engine):
```bash
gcc main.c primes.c -o prime_app
```
#### 2 Compile the Interface (Menu):
```bash
gcc interface.c -o run_interface
```

### Step 3: Execute
Launch the main interface:
```bash
./run_interface
```

## 4. Usage Guide

* Option 1 (Run Benchmark): Calculates primes in a range and saves them to prime.txt.

* Option 2 (Generate Graph): Runs the benchmark multiple times (1 to N cores) and saves a graph image (e.g., benchmark_1000_10000.png).