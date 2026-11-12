# Student Management System

A console-based C++ application designed to manage student academic records efficiently using object-oriented programming, persistent text file handling, and a menu-driven interface.

## Key Features
* **Complete CRUD Operations:** Add, view, search, update, and delete student records (Roll Number, Name, Course, and Marks)[cite: 1].
* **Duplicate Prevention:** Automatically checks existing records via `isRollNoExists()` to prevent duplicate roll numbers from being saved[cite: 1].
* **Persistent Storage:** Stores records in `students.txt` using `<fstream>` (`ifstream` and `ofstream` with `ios::app`)[cite: 1].
* **Non-Destructive Updates & Deletions:** Uses a temporary file swap (`temp.txt`) to modify or remove specific entries safely without corrupting the database[cite: 1].
* **Formatted Console Output:** Utilizes `<iomanip>` (`setw`, `left`) to render clean, aligned tables in the terminal[cite: 1].

## How to Compile and Run
1. Open a terminal in the project directory.
2. Compile the source code:
   ```bash
   g++ StudentManagement.cpp -o StudentManagement.exe