### 2. Library Management System (`Library-Management-System/README.md`)

```markdown
# Library Management System

An object-oriented C++ console application that manages library inventory, member registrations, book lending workflows, and catalog searches with persistent file synchronization.

## Key Features
* **Object-Oriented Architecture:** Encapsulates data into `Book` and `Member` entity classes managed by a central `Library` controller class[cite: 2].
* **In-Memory & Persistent Storage:** Uses dynamic `std::vector` containers for fast runtime operations while automatically syncing data to `books.txt` and `members.txt` on startup and modification[cite: 2].
* **Issue & Return Tracking:** Validates book availability and member registration before issuing books, tracking borrowers via `issuedToMemberId`[cite: 2].
* **Substring Catalog Search:** Supports partial-match searching by Book Title or Author using `std::string::find()`[cite: 2].
* **Duplicate ID Validation:** Prevents duplicate Book IDs and Member IDs upon creation[cite: 2].

## How to Compile and Run
1. Open a terminal in the project directory.
2. Compile the source code:
   ```bash
   g++ LibraryManagement.cpp -o LibraryManagement.exe