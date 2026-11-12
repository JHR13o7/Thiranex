#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

//file whwre all student data will be saved
const string FILE_NAME = "students.txt";

class Student{
private:
    int rollNo;
    string name;
    string course;
    float marks;

public:
    //Basic Output
    void display() const;

    //Helper for validation
    bool isRollNoExists(int searchRoll);

    //Core file Operations
    void addRecord();
    void displayAll();
    void updateRecord(int searchRoll);
    void deleteRecord(int searchRoll);
    void searchRecord(int searchRoll);
};

//Formats and prints a single student's record
void Student::display() const {
    cout << left << setw(10) << rollNo
    << setw(20) << name
    << setw(15) << course
    << setw(10) << marks << endl;
}

//checks if a roll number is already in the text file
bool Student::isRollNoExists(int searchRoll) {
    ifstream inFile(FILE_NAME); //Open file in read mode

    //If the file doesn't exist yet, there are no duplicates
    if(!inFile){
        return false;
    }

    int tempRoll;
    string tempName, tempCourse;
    float tempMarks;

    //Read the file record by record untill the end
    while (inFile >> tempRoll){
        inFile.ignore(); //Clear the newline after the integer
        getline(inFile, tempName);
        getline(inFile, tempCourse);
        inFile >> tempMarks;
        inFile.ignore(); //Clear the newline after the float

        if (tempRoll == searchRoll) {
            inFile.close();
            return true; //Match Found!
        }
    }

    inFile.close();
    return false;
}

//Add a new student to the database
void Student::addRecord() {
    int newRoll;
    cout << "\nEnter Roll Number: ";
    cin >> newRoll;

    // 1. Validation check
    if(isRollNoExists(newRoll)) {
        cout << "\nError: A student with Roll Number " << newRoll << " already exists!\n";
        return; //Stop the function immediately
    }

    // 2. Gather remaining data
    rollNo = newRoll;
    cin.ignore(); //Clear newline before using getline

    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Course: ";
    getline(cin, course);
    cout << "Enter Mark: ";
    cin >> marks;

    // 3. Save to file
    ofstream outFile(FILE_NAME, ios::app);
    outFile << rollNo << "\n" << name << "\n" << course << "\n" << marks << "\n";
    outFile.close();

    cout << "\n Student Record Added Successfully!\n";
}

// Reads and prints every student in the text file
void Student::displayAll(){
    ifstream inFile(FILE_NAME);

    if (!inFile) {
        cout << "\nNo records found (Database is empty.\n)";
        return;
    }

    // Print Table Headers
    cout << "\n----------------------------------------\n";
    cout << left << setw(10) << "Roll No"
         << setw(20) << "Name"
         << setw(15) << "Course"
         << setw(10) << "Marks" << endl;
    cout << "\n----------------------------------------\n";

    //Read through the file and print each record
    while (inFile >> rollNo) {
        inFile.ignore();
        getline(inFile, name);
        getline(inFile, course);
        inFile >> marks;
        inFile.ignore();

        // Use the display method from Part 2 for each student
        display();
    }

    inFile.close();
}

void Student::searchRecord(int searchRoll) {
    ifstream inFile(FILE_NAME);
    bool found = false;

    if (!inFile) {
        cout << "\nNo Record found (database is empty). \n";
        return;
    }

    while (inFile >> rollNo) {
        inFile.ignore();
        getline(inFile, name);
        getline(inFile, course);
        inFile >> marks;
        inFile.ignore();

        if (rollNo == searchRoll) {
            found = true;
            cout << "\n--- Student Record Found ---\n";
            cout << left << setw(10) << "Roll No"
            << setw(20) << "Name"
            << setw(15) << "Course"
            << setw(10) << "Marks" << endl;
            cout << "\n----------------------------------------\n";
            display();
            break;
        }
    }

    inFile.close();

    if(!found) {
        cout << "\nRecord with Roll number "<< searchRoll << " not Found!\n";
     }
}

void Student::updateRecord(int searchRoll) {
    ifstream inFile(FILE_NAME);
    ofstream tempFile("temp.txt");
    bool found = false;

    if (!inFile) {
        cout << "\nNo records found.\n";
        return;
    }

    // Read through the original file
    while (inFile >> rollNo) {
        inFile.ignore();
        getline(inFile, name);
        getline(inFile, course);
        inFile >> marks;
        inFile.ignore();

        // If we find the student, ask for new details before writing
        if (rollNo == searchRoll) {
            found = true;
            cin.ignore();
            cout << "\nStudent Found! Enter New Details:\n";
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Course: ";
            getline(cin, course);
            cout << "Enter Marks: ";
            cin >> marks;
        }

        // Write the data (either original or updated) to the temp file
        tempFile << rollNo << "\n" << name << "\n" << course << "\n" << marks << "\n";
    }

    inFile.close();
    tempFile.close();

    // Replace the old file with the new updated file
    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (found) cout << "\nRecord Updated Successfully!\n";
    else cout << "\nRecord Not Found\n";
}

//Deletes a student's record from the database
void Student::deleteRecord(int searchRoll) {
    ifstream inFile(FILE_NAME);
    ofstream tempFile("temp.txt");
    bool found = false;

    if (!inFile) {
        cout << "\nNo records Found.\n";
        return;
    }

    // Read through the original file
    while (inFile >> rollNo) {
        inFile.ignore();
        getline(inFile, name);
        getline(inFile, course);
        inFile >> marks;
        inFile.ignore();

        // If we find the student to delete, just skip writing them to the temp file
        if(rollNo == searchRoll) {
            found = true;
            continue;
        }

        // Write all OTHER students to the temp file
        tempFile << rollNo << "\n" << name << "\n" << course << "\n" << marks << "\n";
    }

    inFile.close();
    tempFile.close();

    //Replace the old file with the new file (which is now missing the deleted student)
    remove(FILE_NAME.c_str());
    rename("temp.txt", FILE_NAME.c_str());

    if (found) cout << "\nRecord Deleted Successfully!\n";
    else cout << "\nRecord Not Found!\n";
}

int main() {
    Student s; //Create an instance of our Student Blueprint
    int choice, roll;

    do{
        //Display the interactive menu
        cout << "\n=== Student Management System===\n";
        cout << "1. Add Student Record\n";
        cout << "2. Display All Records\n";
        cout << "3. Search Student Record\n";
        cout << "4. Update Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        //Process the user's choice
        switch (choice) {
            case 1:
                s.addRecord();
                break;
            case 2:
                s.displayAll();
                break;
            case 3:
                cout << "\nEnter Roll Number to Search: ";
                cin >> roll;
                s.searchRecord(roll);
                break;
            case 4:
                cout << "\nEnter Roll Number to Update:";
                cin >> roll;
                s.updateRecord(roll);
                break;
            case 5:
                cout << "\nEnter Roll Number to Delete: ";
                cin >> roll;
                s.deleteRecord(roll);
                break;
            case 6:
                cout << "\nEXITING SYSTEM...SEE YOU LATER!\n";
                break;
            default:
            cout << "\nInvalid choice! Please select a number from 1 to 5\n";
        }
    }while (choice != 5); //Keep looping intil the use chooses to exit

    return 0; // Signals that the program ended successfully
}