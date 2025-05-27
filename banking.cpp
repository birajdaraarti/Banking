#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Transaction class
class Transaction {
private:
    string type;
    double amount;
    string timestamp;

public:
    Transaction(const string& type, double amount) : type(type), amount(amount) {
        time_t now = time(0);
        timestamp = ctime(&now);
        timestamp.pop_back(); // Remove newline
    }

    void displayTransaction() const {
        cout << left << setw(20) << type << ": $" << fixed << setprecision(2) << amount 
             << " (Time: " << timestamp << ")" << endl;
    }
};

// BankAccount class
class BankAccount {
private:
    double balance;
    vector<Transaction> transactionHistory;

public:
    BankAccount(double initialDeposit = 0) : balance(initialDeposit) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.emplace_back("Deposit", amount);
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactionHistory.emplace_back("Withdrawal", amount); // ✅ Fixed here
            cout << "Withdrawn: $" << amount << endl;
        } else {
            cout << "Insufficient funds or invalid amount!" << endl;
        }
    }

    void transfer(BankAccount& receiver, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactionHistory.emplace_back("Transfer to recipient", amount);
            receiver.receiveTransfer(amount);
            cout << "Transferred: $" << amount << endl;
        } else {
            cout << "Transfer failed: Insufficient funds or invalid amount!" << endl;
        }
    }

    void receiveTransfer(double amount) {
        balance += amount;
        transactionHistory.emplace_back("Received transfer", amount);
    }

    void displayBalance() const {
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void displayTransactionHistory() const {
        cout << "\nTransaction History:\n";
        if (transactionHistory.empty()) {
            cout << "No transactions yet!\n";
            return;
        }
        for (const auto& transaction : transactionHistory) {
            transaction.displayTransaction();
        }
    }
};

// Customer class
class Customer {
private:
    string name;
    BankAccount account;

public:
    Customer(const string& name, double initialDeposit = 0) : name(name), account(initialDeposit) {}

    void displayCustomerDetails() const {
        cout << "\nCustomer Name: " << name << endl;
        account.displayBalance();
    }

    BankAccount& getAccount() {
        return account;
    }
};

// BankService class
class BankService {
public:
    void runDemo() {
        Customer customer1("Alice", 500);
        Customer customer2("Bob", 300);

        customer1.displayCustomerDetails();
        customer2.displayCustomerDetails();

        cout << "\n--- Performing Transactions ---\n";
        customer1.getAccount().deposit(200);
        customer1.getAccount().withdraw(100);
        customer1.getAccount().transfer(customer2.getAccount(), 150);

        cout << "\n--- Final Balances ---\n";
        customer1.displayCustomerDetails();
        customer2.displayCustomerDetails();

        cout << "\n--- Alice's Transactions ---\n";
        customer1.getAccount().displayTransactionHistory();

        cout << "\n--- Bob's Transactions ---\n";
        customer2.getAccount().displayTransactionHistory();
    }
};

// Main function
int main() {
    BankService service;
    service.runDemo();
    return 0;
}