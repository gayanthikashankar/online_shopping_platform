# Library Management System

A C++ object-oriented programming project that implements a simple library management system to track books and borrowers.

## Overview

This project demonstrates fundamental OOP concepts in C++ including inheritance, polymorphism, file handling, and both traditional arrays and container usage. The system allows for managing a collection of books and borrowers (students and faculty) with different borrowing privileges.

## Features

- Add and manage books and borrowers
- Borrow and return books
- Process returned books using a queue system
- Search for books by author
- Track recently added books using a traditional array
- Automatic ID generation for books
- Inheritance hierarchy with polymorphic functions
- Persistent data storage using file I/O
- Different borrowing limits for students and faculty

## Project Structure

- **Book.h/cpp**: Definition and implementation of the Book class
- **Person.h/cpp**: Base Person class and derived Student and Faculty classes
- **Library.h/cpp**: Core library management functionality
- **main.cpp**: User interface and program entry point

## Data Files

- **books.txt**: Stores information about books
- **borrowers.txt**: Stores information about borrowers

## How to Build and Run

1. Make sure you have a C++ compiler installed (supporting C++11 or later)
2. Compile the program:
   ```
   g++ -std=c++11 main.cpp book.cpp person.cpp library.cpp -o library
   ```
3. Run the program:
   ```
   ./library
   ```

## Usage

The program provides a menu-driven interface with the following options:
1. Add a new book
2. Display all books
3. Display available books
4. Add a new borrower
5. Display all borrowers
6. Borrow a book
7. Return a book
8. Process returned books
9. Search books by author
10. Display recently added books
0. Exit

## Implementation Details

### Array Implementation
- Fixed-size array of borrowers (max 50)
- Array of recently added books (max 10)
- Demonstrates traditional array manipulation and management


## Sample Workflow

1. Add several books to the library
2. Add student and faculty borrowers
3. Allow borrowers to check out books 
4. Return books to the queue
5. Process returns to make books available again
6. Search for books by a specific author
7. View the recently added books 
# ap_cpp_project
