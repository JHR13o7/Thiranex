#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

//Blueprint for the library's physical assets
class Book {
    public:
    int id;
    string title;
    string author;
    bool isIssued;
    int issuedToMemberId;

    // Constructor to initialize a new book cleanly
    Book(int bId, string bTitle, string bAuthor) {
        id = bId;
        title = bTitle;
        author = bAuthor;
        isIssued = false;
        issuedToMemberId = -1; //-1 indicates the book is currently in the library
    }
};

// Blueprint for the library's registered users
class Member {
    public:
    int id;
    string name;

    // Constructor to initialize a new member
    Member(int mId, string mName) {
        id = mId;
        name = mName;
    }
};

class Library {
    private:
    // Dynamic arrays acting as our in-memory database
    vector<Book> books;
    vector<Member> members;

    // Helper method to find a book's exact position in the array
    int findBookIndex(int bId) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].id == bId)
                return i;
        }
        return -1; // -1 means the book was not found
    }

    //Helper method to find a member's exact position in the array
    int findMemberIndex(int mId) {
        for (size_t i = 0; i < members.size(); i++) {
            if (members[i].id == mId)
                return i;
        }
        return -1;
    }

    void saveData() {
        // Save all books
        ofstream bookFile("books.txt");
        for (const auto& b : books) {
            bookFile << b.id << "\n" << b.title << "\n" << b.author << "\n" << b.isIssued << "\n" << b.issuedToMemberId << "\n";
        }
        bookFile.close();

        // Save all members
        ofstream memberFile("members.txt");
        for (const auto& m : members) {
            memberFile << m.id << "\n" << m.name << "\n";
        }
        memberFile.close();
    }

    void loadData() {
        //load books
        ifstream bookFile("books.txt");
        if (bookFile) {
            int bId, mId;
            bool issued;
            string bTitle, bAuthor;

            while (bookFile >> bId) {
                bookFile.ignore();
                getline(bookFile, bTitle);
                getline(bookFile, bAuthor);
                bookFile >> issued >> mId;
                bookFile.ignore();

                Book newBook(bId, bTitle, bAuthor);
                newBook.isIssued = issued;
                newBook.issuedToMemberId = mId;
                books.push_back(newBook);
            }
            bookFile.close();
        }

        // Load Members
        ifstream memberFile("members.txt");
        if (memberFile) {
            int mId;
            string mName;
            while (memberFile >> mId) {
                memberFile.ignore();
                getline(memberFile, mName);
                members.push_back(Member(mId, mName));
            }
            memberFile.close();
        }
    }

    public:
    // Constructor to load data automatically
    Library(){
        loadData();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "\nEnter Book Id: ";
        cin >> id;

        // Validation: Prevent duplicate Book IDs
        if (findBookIndex(id) != -1) {
            cout << "Error: Book ID already exists!\n";
            return;
        }

        cin.ignore(); //Clear the hidden newline character from the input buffer
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);

        //Create the book using our constructor and append it to the vector
        books.push_back(Book(id, title, author));
        saveData();
        cout << "\nBook Added Successfully!\n";
    }

    void addMember() {
        int id;
        string name;

        cout << "\nEnter Member ID: ";
        cin >> id;

        //Validation: Prevent duplicate Member IDs
        if (findMemberIndex(id) != -1) {
            cout << "Error: Member ID already exists!\n";
            return;
        }

        cin.ignore();
        cout << "Enter Member Name: ";
        getline (cin, name);

        members.push_back(Member(id, name));
        saveData();
        cout << "\nMember Added Successfully!\n";
    }

    void issueBook() {
    int bId, mId;
    cout << "\nEnter Book ID to Issue: ";
    cin >> bId;

    // Validation: Verify the book exists
    int bIndex = findBookIndex(bId);
    if (bIndex == -1) {
        cout << "Error: Book not found.\n";
        return;
    }

    //Validation: Ensure book is not currently issued
    if (books[bIndex].isIssued) {
        cout << "Error: Book is already issued to Member ID" << books[bIndex].issuedToMemberId << "\n";
        return;
    }

    cout << "Enter Member ID: ";
    cin >> mId;

    //Validtion: Ensure member is registered in the system
    if (findMemberIndex(mId) == -1) {
        cout << "Error: Member not found. Please register the member first.\n";
        return;
    }

    // Update the books availability flags
    books[bIndex].isIssued = true;
    books[bIndex].issuedToMemberId = mId;
    saveData();
    cout << "\nSuccess: Book issued!\n";
    }
    
    void returnBook() {
    int bId;
    cout << "\nEnter Book ID to Return: ";
    cin >> bId;

    int bIndex = findBookIndex(bId);
    if (bIndex == -1) {
        cout << "Error: Book not found.\n";
        return;
    }

    if (!books[bIndex].isIssued) {
        cout << "Notice: This book is not currently issued.\n";
        return;
    }

    // Reset the availability flags to thr default state from Part 1
    books[bIndex].isIssued = false;
    books[bIndex].issuedToMemberId = -1;
    saveData();
    cout << "\nSuccess: Book returned to inventory!\n";
    }

    void searchCatalog() {
    if (books.empty()) {
        cout << "\nThe catalog is currently empty.\n";
        return;
    }

    int choice;
    string query;

    cout << "\n--- Search By ---\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "Selection: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter Search Term (Case-Sensitive): ";
    getline(cin, query);

    bool found = false;
    cout << "\n--------------------------------------------------------------------------\n";
    cout << left << setw(10) << "ID" << setw(30) << "Title" << setw(20) << "Author" << setw(15) << "Status" << endl;
    cout << "--------------------------------------------------------------------------\n";

    for (const auto& b : books) {
        //Checks if the query exists as a substring within the title or author
        bool matchTitle = (choice == 1 && b.title.find(query) != string::npos);
        bool matchAuthor = (choice == 2 && b.author.find(query) != string::npos);

        if (matchTitle || matchAuthor) {
            cout << left << setw(10) << b.id
            << setw(30) << b.title
            << setw(20) << b.author
            << setw(15) << (b.isIssued ? "Issued" : "Available") << endl;
            found = true; //Flag that at least one result was printed
        }
    }

    if (!found) {
        cout << "No matching records found for '" << query << "'.\n";
    }
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n=================================\n";
        cout << "    LIBRARY MANAGEMENT SYSTEM    ";
        cout << "\n=================================\n";
        cout << "1. Add New Book\n";
        cout << "2. Add New Member\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Catalog\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.addMember();
                break;
            case 3:
                lib.issueBook();
                break;
            case 4:
                lib.returnBook();
                break;
            case 5:
                lib.searchCatalog();    //Not working
                break;
            case 6:
                cout << "\nShutting down system.\n";
                break;
            default:
            cout << "\nInvalid input. Please select a valid option.\n";
        }
    }while (choice != 6);

    return 0;
}