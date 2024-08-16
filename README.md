


<h1 align="center">Multi-threading in C</h1>

<p align="center">
  <img alt="Github top language" src="https://img.shields.io/github/languages/top/mitchellkolb/threading-in-C?color=01518D">

  <img alt="Github language count" src="https://img.shields.io/github/languages/count/mitchellkolb/threading-in-C?color=01518D">

  <img alt="Repository size" src="https://img.shields.io/github/repo-size/mitchellkolb/threading-in-C?color=01518D">

  <img alt="Github stars" src="https://img.shields.io/github/stars/mitchellkolb/threading-in-C?color=01518D" />
</p>

<p align="center">
<img
    src="https://img.shields.io/badge/Programming Language-%2300599b?style=for-the-badge&logo=C&logoColor=white"
    alt="Website Badge" />
<img
    src="https://img.shields.io/badge/Linux-D5A72A?style=for-the-badge&logo=Linux&logoColor=white"
    alt="Website Badge" />
</p>

I explored the pthread.h library in C to solve math problems with multi-threading. I wanted to see how I can use threads, mutexes, and barriers to handle complex mathematical computations and ensure race condition-free operations.  



![project image](resources/mult-threading-gif.gif)

<details>
<summary style="color:#5087dd">Watch the Full Video Demo Here</summary>

[![Full Video Demo Here](https://img.youtube.com/vi/7tln4s4ttao/0.jpg)](https://www.youtube.com/watch?v=7tln4s4ttao)

</details>

---


# Table of Contents
- [What I Learned](#what-i-learned-in-this-project)
- [Tools Used / Development Environment](#tools-used--development-environment)
- [Team / Contributors / Teachers](#team--contributors--teachers)
- [How to Set Up](#how-to-set-up)
- [Project Overview](#project-overview)
  - [Introduction](#introduction)
  - [Mutex](#mutex)
  - [Barriers](#barriers)
  - [Results and Observations](#results-and-observations)
  - [Future Work](#future-work)
- [References](#references)
- [Acknowledgments](#acknowledgments)

---




# What I Learned in this Project
- Main ideas around Parallel Computing and Concurrent Programming. (Parallelism vs Concurrency)
- Principles of threads and their advantages/disadvantages over processes.
- Thread synchronization tools like mutex locks, join, condition variables and barriers. 
- Thread management terms like race condition, critical region, and deadlocks.
- Semaphores and their advantages over condition variables.




# Tools Used / Development Environment
- C
- VS Code
- Terminal
- Ubuntu
- Linux





# Team / Contributors / Teachers
- [Mitchell Kolb](https://github.com/mitchellkolb)
- Professor. K.C. Wang





# How to Set Up
This project was implemented on my local machine inside of a virtual machine using:
- Ubuntu Version 20.04.03 found at this [link](http://lt.releases.ubuntu.com/20.04.3/).
> [!NOTE]
> I had to use this version of Ubuntu but it is not required to run this codebase. 
- Clone this repository 
- Open terminal at the codebase `~.../multi-threading-in-C/Barriers/` or `~.../multi-threading-in-C/Mutexes/`
- Run my `mk` file to compile the codebase and run the a.out executable.





# Project Overview
While learning about thread management in C, I worked on a project that involved using the pthreads library to solve math problems. This project focuses on two main problems: calculating the sum of matrix elements using threads and solving a system of linear equations with Gauss elimination using concurrent threads.

## Introduction
In this project, I applied multithreading techniques using the pthread.h library in C to solve math problems efficiently. These tasks helped me understand the principles of parallel computing and concurrent programming, particularly the differences between parallelism and concurrency. Parallelism involves executing multiple tasks simultaneously in real time, typically on systems with multiple processing elements like multiprocessor or multicore systems. Each task runs on a separate processor core, allowing true simultaneous execution. Concurrency, on the other hand, involves executing tasks logically in parallel. On single CPU systems, tasks take turns executing, giving the illusion of simultaneous execution through multitasking. 

## Mutex
The first task I worked on involved computing the sum of all elements in an 8x8 matrix of integers using threads. Each thread was responsible for computing the partial sum of a unique row. Each thread computes the partial sum of its assigned row and then waits for all other threads to finish. Once all threads have completed their tasks, the main thread computes the final sum by adding all the partial sums. To make sure I had thread-safe access to the shared global sum variable, I used a mutex. By using a mutex, I avoided race conditions and ensured that only one thread could update the global total at any time. This task emphasized the importance of thread synchronization when dealing with shared resources and introduced me to concepts like critical regions and deadlock prevention.

## Barriers
The other task involved solving a system of linear equations using Gauss elimination with concurrent threads. The Gauss elimination algorithm consists of row reduction and back substitution. While the specifics of gauss elimination and back subsitiion are complicated and math based the main idea of this is that their are lots of repeated steps where some threads complete their computation faster than others. But to move onto the next set of steps each thread needs the results of every other thread so I need a way of syncing all the threads together. I used barriers to synchronize threads at different phases of the algorithm, ensuring all threads completed the current step before moving on to the next. This included steps like partial pivoting, reducing the matrix, and back substitution. This task highlighted the use of barriers as a synchronization mechanism to coordinate the progress of multiple threads.

## Results and Observations
During development, I observed several key points. The use of mutexes was crucial in preventing race conditions and ensuring correct updates to shared variables. Barriers effectively synchronized threads, allowing them to perform complex operations like Gauss elimination concurrently. These multithreading techniques significantly improved the efficiency of solving computational problems, especially when threads operated independently within their assigned tasks. Additionally, I learned about the advantages and disadvantages of threads compared to processes, and the importance of thread management functions like pthread_create, pthread_join, and pthread_exit.

## Future Work
Future improvements could include optimizing thread management to further reduce execution time and exploring advanced synchronization mechanisms such as condition variables and semaphores. Semaphores, in particular, offer advantages over condition variables by including a counter, making them more general and flexible for certain types of thread cooperation. Additionally, extending the implementation to larger matrices and more complex systems of equations could provide more information into the efficiency of multithreading in computational problems.

## References
The assignment is described on chapter 4 of the [Systems Programming Book](https://link.springer.com/book/10.1007/978-3-319-92429-8).



--- 
# Acknowledgments
This codebase and all supporting materials was made as apart of a course for my undergrad at WSU for CPTS 360 - Systems Programming C/C++ in the Spring of 2023. 

