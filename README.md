# Bank Management System (OOP Version)
In this project, I rebuilt my previous bank management system using object-oriented programming (OOP) principles, adding nine new features.

The goal is to make the code more scalable, maintainable, and expandable by implementing OOP concepts such as encapsulation, inheritance, and abstraction. This also serves as training in OOP concepts to build a strong foundation for the next stage of learning (backend development using C#).

The system is divided into three main sections: customer management, user management, and transactions. It is structured with multiple interactive interfaces on the application console.

The user interface code has been separated from the logical code into dedicated classes.

This was done as a training and preparation step for separating the front-end and back-end in the future, following good software engineering principles.

The project can be considered complete, although I am currently working on a currency exchange extension.

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
