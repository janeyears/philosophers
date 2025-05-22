# philosophers

**philosophers** is a concurrency project from the Hive curriculum that simulates the classic **Dining Philosophers Problem**. It is designed to teach fundamental concepts in multithreading, synchronization, and managing shared resources in C.

## 🚀 Project Overview

The objective is to create a program where philosophers alternate between thinking, eating, and sleeping. Each philosopher must pick up two forks (shared resources) to eat, without causing deadlocks or starvation.

This project focuses on:

- Creating and managing multiple threads
- Synchronizing access to shared resources using mutexes
- Preventing deadlock and data races
- Handling timing and precision in multithreaded applications

## 📁 Project Structure

### ✅ Mandatory Part

- Simulate the behavior of **N** philosophers around a table, each needing two forks to eat.
- Implement the following rules:
  - Philosophers take forks (mutexes), eat, sleep, and think in a loop.
  - If a philosopher doesn’t eat within a certain time, they die.
- Display each philosopher's state (eating, sleeping, thinking, died) with timestamps.
- Prevent deadlocks and ensure the simulation ends when a philosopher dies or all have eaten a certain number of times (optional argument).

### Program Usage

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

- number_of_philosophers: Number of philosophers (and forks)
- time_to_die: Time (in ms) a philosopher can go without eating
- time_to_eat: Time (in ms) a philosopher spends eating
- time_to_sleep: Time (in ms) a philosopher spends sleeping
- number_of_times_each_philosopher_must_eat (optional): If all philosophers have eaten this many times, the simulation stops

./philo 5 800 200 200

## 🧠 What I Learned

- Creating and managing threads with pthread
- Synchronizing access using mutexes to prevent race conditions
- Simulating real-time delays and accurately managing timing
- Preventing deadlock through careful resource allocation
