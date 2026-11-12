### 3. Bank Management Application (`Bank-Management-System/README.md`)

```markdown
# Bank Management Application

A C++ console application simulating core banking operations using object-oriented encapsulation, binary file handling for in-place record updates, and plain-text transaction audit logging.

## Key Features
* **Account Management & Security:** Creates customer accounts with a 4-digit PIN verification check required for balance inquiries, transactions, and history lookups[cite: 4].
* **In-Place Binary File Updates:** Stores fixed-size `BankAccount` objects in `bank_records.dat` (`ios::binary`) and uses `fstream::seekp()` to overwrite updated balances directly in place without rewriting the entire file[cite: 4].
* **Minimum Balance Enforcement:** Ensures withdrawals maintain a minimum account balance of ₹500[cite: 4].
* **Timestamped Audit Log:** Automatically appends every deposit and withdrawal with the system date and time (`<ctime>`) to `transaction_log.txt`[cite: 4].

## How to Compile and Run
1. Open a terminal in the project directory.
2. Compile the source code:
   ```bash
   g++ BankManagement.cpp -o BankManagement.exe