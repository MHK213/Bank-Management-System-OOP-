# Bank Management System (OOP Version)
In this project, I rebuilt my previous Bank Management System using Object-Oriented Programming (OOP) principles.
The goal was to make the code more modular, maintainable, and scalable by applying OOP concepts such as encapsulation, inheritance, and abstraction.

The system is divided into two main parts: Clients Management and Users Management, and it is structured into multiple interactive interfaces.

The UI code was separated from the logic code into dedicated classes.
This was done as a training and preparation step for future front-end and back-end separation, following good software architecture principles.

The project is incomplete;

## Features:
  ### Clients Management
   - View list of customers
  - Add, delete, edit, and search for customers
  - Withdraw and deposit funds
  - Check account balance
  ### User Management
  - View list of users
  - Add, delete, edit, and search for users
  - Assign permissions during user creation
  - Admin cannot be deleted.
  - Each user has specific access rights depending on their role
  ### Authentication System
  - Login and logout functionality
  - Access control based on user permissions

## Interfaces Overview
  ### 1 - Main Interface:
   Includes options for:
   - Displaying clients list
   - Adding, deleting, editing, or searching for a client
   - Transactions
   - Managing users
   - Logging out
  ### 2 - Transactions Interface:
  Provides functions for:
  - Withdrawals
  - Deposits
  - Checking balances
  ### 3 - User Management Interface:
  Allows to:
  - Displaying users list
  - Adding, deleting, editing, or searching for a client
  - Control permissions

## Data Storage
Customer and user information are stored in text files that act as a simple database.
Each record is processed and updated directly from these files.

## Project Structure
The project is divided into multiple classes, each responsible for a specific part of the system.
Utilizes my custom C++ libraries i created (available on my GitHub account) for improved modularity and reusability
