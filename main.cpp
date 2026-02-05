#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class ATM {
private:
    int pin;
    double balance;
    vector<string> transactions;

public:
    ATM() {
        loadAccount();
        loadTransactions();
    }

    void loadAccount() {
        ifstream file("account.txt");
        if (file.is_open()) {
            file >> pin >> balance;
            file.close();
        } else {
            pin = 1234;
            balance = 10000;
            saveAccount();
        }
    }

    void saveAccount() {
        ofstream file("account.txt");
        file << pin << " " << balance;
        file.close();
    }

    void loadTransactions() {
        ifstream file("transactions.txt");
        string line;
        while (getline(file, line)) {
            transactions.push_back(line);
        }
        file.close();
    }

    void saveTransaction(string msg) {
        ofstream file("transactions.txt", ios::app);
        file << msg << endl;
        file.close();
        transactions.push_back(msg);
    }

    bool authenticate() {
        int inputPin;
        cout << "\nEnter PIN: ";
        cin >> inputPin;
        return inputPin == pin;
    }

    void checkBalance() {
        cout << "\nCurrent Balance: Rs. " << balance << endl;
    }

    void deposit() {
        double amount;
        cout << "\nEnter amount to deposit: ";
        cin >> amount;
        if (amount > 0) {
            balance += amount;
            saveAccount();
            saveTransaction("Deposited: Rs. " + to_string(amount));
            cout << "Deposit successful!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw() {
        double amount;
        cout << "\nEnter amount to withdraw: ";
        cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            saveAccount();
            saveTransaction("Withdrawn: Rs. " + to_string(amount));
            cout << "Please collect your cash.\n";
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    void showTransactions() {
        cout << "\nTransaction History:\n";
        for (string t : transactions) {
            cout << "- " << t << endl;
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- ATM MENU ---\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Transaction History\n";
            cout << "5. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: checkBalance(); break;
                case 2: deposit(); break;
                case 3: withdraw(); break;
                case 4: showTransactions(); break;
                case 5: cout << "Thank you for using ATM!\n"; break;
                default: cout << "Invalid option!\n";
            }
        } while (choice != 5);
    }
};

int main() {
    ATM atm;

    cout << "==== Welcome to ATM Simulation ====\n";

    if (atm.authenticate()) {
        atm.menu();
    } else {
        cout << "Incorrect PIN! Access denied.\n";
    }

    return 0;
}
