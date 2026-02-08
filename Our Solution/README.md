# Multiprocess Prime Number Calculator

## Project Documentation

Submission Type: Man-Made Implementation (Modular Architecture)

------------------------------------------------------------------------

## 1. Project Overview

This project is a high-performance system designed to calculate prime
numbers within a given range using multiprocessing via fork().

It uses modular architecture separating:

-   User Interface
-   Process Management
-   Mathematical Logic
-   Visualization

------------------------------------------------------------------------

## 2. System Architecture

### Controller (run.c)

Provides menu interface and executes commands safely using system().

### Worker (main.c + primes.c)

Handles:

-   fork()
-   load balancing
-   prime computation
-   file writing
-   synchronization using wait()

### Mathematical Logic (primes.c)

Uses 6k ± 1 optimization to improve efficiency by reducing divisor
checks.

### Plotter (plotter.py)

Runs benchmarks and generates graphs using matplotlib.

------------------------------------------------------------------------

## 3. File Structure

Man_Made_Implementation/ - main.c - primes.c - primes.h - run.c -
plotter.py

Outputs: - prime.txt - benchmark.png

------------------------------------------------------------------------

## 4. Compilation

Install dependencies:

sudo apt update sudo apt install build-essential python3-matplotlib

Compile:

gcc main.c primes.c -o prime_app gcc run.c -o run

Run:

./run

------------------------------------------------------------------------

## 5. Features

-   multiprocessing using fork()
-   modular architecture
-   efficient prime detection
-   load balancing
-   performance visualization

------------------------------------------------------------------------

## 6. Concepts Used

-   fork()
-   wait()
-   multiprocessing
-   file I/O
-   synchronization
-   modular programming

------------------------------------------------------------------------

## 7. Conclusion

Demonstrates real-world system programming, performance optimization,
and modular software design.
