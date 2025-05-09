# Library Management System

A lightweight and functional library management system implemented in C. This system is designed to allow librarians to manage books and users, while students can search for and request books from the library. The program uses file-based storage to keep track of books, users, and pending requests.

## Key Features

### User Roles
- **Librarians**:
  - Add, delete, edit, and view books in the library.
  - Manage book borrowing requests (approve/reject).
  - Create user accounts for students and other librarians.
- **Students**:
  - View available books and submit borrowing requests.
  - Return borrowed books.

### Functionality Overview
- **Book Management**: Add, edit, delete, and view a list of books with information such as title, author, subject, and availability.  
- **Request Management**: Tracks borrowing requests and allows librarians to approve or reject them.  
- **Persistent Storage**: Automatically saves all data to text files (`books.txt`, `users.txt`, and `requests.txt`).

---

## How to Compile and Run

1. **Prerequisites**: Make sure you have GCC installed on your system.
2. **Compilation**:
   ```bash
   gcc main.c -o library_system
