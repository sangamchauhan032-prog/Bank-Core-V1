# BankCore

BankCore is a basic banking management system that I built using C++ and SQLite.

I started this project to improve my C++ skills and understand how databases work with a C++ application. It runs in the terminal and allows users to perform basic banking operations.

## What can it do?

- Check account details using an account ID
- Create a new bank account
- Deposit money
- Withdraw money
- Check whether the account has enough balance before withdrawal
- View previous transactions
- Store account and transaction data in an SQLite database

## Technologies I used

- C++
- SQLite
- CMake

## Running the project

You need a C++ compiler, CMake and SQLite3 installed.

Open the project folder in PowerShell and run:

```powershell
cmake -S . -B build
cmake --build build
.\build\BankCore.exe
```

## Project structure

```text
BankCore/
├── CMakeLists.txt
├── database/
├── src/
│   └── main.cpp
├── include/
├── tests/
└── README.md
```

## What I learned

While building this project, I got practical experience with:

- Connecting a C++ program to an SQLite database
- Creating tables and executing SQL queries
- Inserting, updating and retrieving records
- Using callbacks with SQLite
- Handling user input and invalid values
- Managing account balances and transaction records

## What's next?

I want to improve this project further in its next version by working on prepared statements, better database handling and cleaner code structure.

This is one of my first projects while learning C++ and backend development.