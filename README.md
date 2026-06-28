Bank Management System (C Programming)

Overview
This is a simple console-based Bank Management System developed using C programming. It simulates basic banking operations like creating an account, depositing money, withdrawing money, checking balance, and transferring money between accounts. The project focuses on using file handling to store and manage data permanently without using a database.

Features

* Create a new bank account with an auto-generated account number
* Deposit money into an existing account
* Withdraw money with proper balance validation
* Check account balance
* Transfer money between two accounts
* Data is stored and updated using file handling

Technologies Used

* C programming language
* File handling
* Structures
* Functions and modular programming
* Random number generation
* Temporary file handling for safe updates

What I Learned
This project helped me understand how data can be stored and managed using files in C. It improved my logical thinking, problem-solving skills, and ability to break a problem into smaller functions. It also gave me an understanding of how basic real-world systems work behind the scenes.

How to Run
gcc main.c -o bank
./bank

How It Works

* A user first creates an account and gets a unique account number
* The user can then perform banking operations using that account number
* All data is stored in a text file so it remains even after the program stops running
* Updates like deposit, withdraw, and transfer are handled using a temporary file to ensure safe data modification

Future Improvements

* Add login or PIN-based authentication system
* Maintain transaction history
* Improve input validation and error handling
* Replace file storage with a database system
* Develop a graphical user interface version

Author
Akshaya V

Repository
https://github.com/Akshaya-V199/Bank-Management-System-C
