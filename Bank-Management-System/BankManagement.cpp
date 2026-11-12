#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <string>

using namespace std;

//Global logging function
// Append to a standard text file so it doesn't mess up our binary data alignments.
void logTransaction(int accNo, const char* type, double amount) {
    ofstream logFile("transaction_log.txt", ios::app);
    if (!logFile) return;

    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt) - 1] = '\0'; // Remove the default newline character from ctime

    logFile << accNo << " | " << dt << " | " << type << " | Rs." << amount << "\n";
    logFile.close();
}

class BankAccount {
    private:
        int accountNumber;
        char name[50];
        double balance;
        char pin[5];

    public:
        void createAccount();
        void showAccount() const;
        void deposit(double amount);
        void withdraw(double amount);
        int getAccountNumber() const;
        bool verifyPIN(const char* enteredPIN) const;
};

void BankAccount::createAccount() {
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "Set a 4-digit PIN: ";
    cin >> setw(5) >> pin;
    cout << "Enter Initial Balance (Min 500): Rs.";
    cin >> balance;
    cout << "\nAccount Created Successfully!\n";
}

void BankAccount::showAccount() const {
    cout << "\nAccount Number : " << accountNumber;
    cout << "\nAccount Holder : " << name;
    cout << "\nBalance        : Rs." << balance << "\n";
}

void BankAccount::deposit(double amount) {
    balance += amount;
    logTransaction(accountNumber, "Deposit", amount);
}

void BankAccount::withdraw(double amount) {
    if (balance - amount >= 500) {
        balance -= amount;
        cout << "\nWithdrawal Successful! New Balance: Rs." << balance << "\n";
        logTransaction(accountNumber, "Withdrawal", amount);
    } else {
        cout << "\nInsufficient Balance. Minimum Rs.500 must br maintained.\n";
    }
}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

bool BankAccount::verifyPIN(const char* enteredPIN) const {
    return strcmp(pin, enteredPIN) == 0;
}

//Appends a single new binary object to the end of the file
void  writeAccountToFile(){
    BankAccount ac;
    ofstream outFile("bank_records.dat", ios::binary | ios::app);
    ac.createAccount();
    // reinterpret_cast converts our object into a raw byte stream for storage
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
    outFile.close();
}

// Scans binary file for an account, verifies PIN, shows balance
void displayBalance(int n) {
    BankAccount ac;
    bool found = false;
    ifstream inFile("bank_records.dat", ios::binary);
    if (!inFile) {
        cout << "No records exist.\n";
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        if (ac.getAccountNumber() == n) {
            char enteredPIN[5];
            cout << "Enter PIN: ";
            cin >> enteredPIN;

            if (ac.verifyPIN(enteredPIN)) {
                ac.showAccount();
            } else {
                cout << "\nIncorrect PIN. Access Denied.\n";
            }
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "\nAccount number does not exist.\n";
}

//Scans the text log for a specific account number
void showTransactionHistory(int targetAccNo) {
    ifstream logFile("transaction_log.txt");
    if (!logFile) {
        cout << "\nNo transaction history found.\n";
        return;
    }

    cout << "\n--- Transaction History for Account " << targetAccNo << " ---\n";
    bool found = false;
    int fileAccNo;
    string line;

    while (logFile >> fileAccNo) {
        getline(logFile, line);
        if (fileAccNo == targetAccNo) {
            cout << line << "\n";
            found = true;
        }
    }
    logFile.close();
    if(!found) cout << "No transactions recorded yet.\n";
    cout <<"---------------------------------------\n";
}
 
void processTransaction(int n, int option) {
    bool found = false;
    BankAccount ac;
    //Open in Both IN and OUT mode simultaneously
    fstream File("bank_records.dat", ios::binary | ios::in | ios::out);

    if (!File) {
        cout << "No records exist.\n";
        return;
    }

    while (File.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount)) && !found) {
        if (ac.getAccountNumber() == n) {
            char enteredPIN[5];
            cout << "Enter PIN: ";
            cin >> enteredPIN;

            if (!ac.verifyPIN(enteredPIN)) {
                cout << "\nIncorrect PIN. Transaction Cancelled.\n";
                File.close();
                return;
            }

            ac.showAccount();
            double amount;
            if (option == 1) {
                cout << "\nEnter amount to deposit: Rs.";
                cin >> amount;
                ac.deposit(amount); //Automatically calls logTransaction
            } else if (option == 2) {
                cout << "\nEnter amount to withdraw: Rs.";
                cin >> amount;
                ac.withdraw(amount); //Automatically calla logTransaction
            }

            //The Magic Step:
            // Move the write pointer (seekp) back by exactly one object size.
            // ios::cur means "start from the current position".
            long pos = (-1) * static_cast<long>(sizeof(ac));
            File.seekp(pos, ios::cur);

            // Overwrite the old data with the updated object
            File.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));

            cout << "\nRecord Updated.\n";
            found = true;
        }
    }
    File.close();
    if (!found) cout << "\nAccount number does not exist.\n";
}

int main(){
    int choice;
    int num;

    do{
        cout << "\n====================================\n";
        cout << "      BANK MANAGEMENT SYSTEM";
        cout << "\n====================================\n";
        cout << "1. Open New Account\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Balance Enquiry\n";
        cout << "5. Transaction History\n";
        cout << "6. Exit\n";
        cout << "Select Option (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                writeAccountToFile();
                break;
            case 2:
                cout << "\nEnter Account Number: ";
                cin >> num;
                processTransaction(num, 1);
                break;
            case 3:
                cout << "\nEnter Account Number: ";
                cin >> num;
                processTransaction(num,2);
                break;
            case 4:
                cout << "\nEnter Account Number: ";
                cin >> num;
                displayBalance(num);
                break;
            case 5:
                cout << "\nEnter Account Number: ";
                cin >> num;
                // Basic security to view logs
                displayBalance(num);
                showTransactionHistory(num);
                break;
            case 6:
                cout << "\nExiting System...See ya Later!\n";
                break;
            default:
                cout << "\nInvalid Option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}