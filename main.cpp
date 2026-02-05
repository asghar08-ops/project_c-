#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct User {
    string name;
    int pin;
    double balance;
};

class ATM {
private:
    User currentUser;
    vector<string> transactions;

    void saveUsers(const vector<User>& users) {
        ofstream file("users.txt");
        for (const auto& u : users) {
            file << u.name << " " << u.pin << " " << u.balance << endl;
        }
    }

    vector<User> loadUsers() {
        vector<User> users;
        ifstream file("users.txt");
        string name;
        int pin;
        double balance;
        while (file >> name >> pin >> balance) {
            users.push_back({name, pin, balance});
        }
        return users;
    }

    void saveTransaction(string msg) {
        ofstream file("transactions.txt", ios::app);
        file << currentUser.name << ": " << msg << endl;
        file.close();
        transactions.push_back(msg);
    }

    void loadTransactions() {
        ifstream file("transactions.txt");
        string line;
        while (getline(file, line)) {
            transactions.push_back(line);
        }
    }

public:
    void registerUser() {
        vector<User> users = loadUsers();
        cout << "\n--- Registration ---\n";
        cout << "Enter your name: ";
        cin >> currentUser.name;
        cout << "Set 4-digit PIN: ";
        cin >> currentUser.pin;
        cout << "Initial deposit: ";
        cin >> currentUser.balance;
        users.push_back(currentUser);
        saveUsers(users);
        cout << "Registration successful!\n";
        saveTransaction("Account created with balance Rs. " + to_string(currentUser.balance));
    }

    bool login() {
        vector<User> users = loadUsers();
        string name;
        int pin;
        cout << "\n--- Login ---\n";
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter PIN: ";
        cin >> pin;

        for (auto &u : users) {
            if (u.name == name && u.pin == pin) {
                currentUser = u;
                loadTransactions();
                cout << "Login successful! Welcome " << currentUser.name << endl;
                return true;
            }
        }
        cout << "Incorrect credentials!\n";
        return false;
    }

    void updateBalance() {
        vector<User> users = loadUsers();
        for (auto &u : users) {
            if (u.name == currentUser.name) {
                u.balance = currentUser.balance;
                break;
            }
        }
        saveUsers(users);
    }

    void checkBalance() {
        cout << "\nCurrent Balance: Rs. " << currentUser.balance << endl;
    }

    void deposit() {
        double amount;
        cout << "\nEnter amount to deposit: ";
        cin >> amount;
        if (amount > 0) {
            currentUser.balance += amount;
            updateBalance();
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
        if (amount > 0 && amount <= currentUser.balance) {
            currentUser.balance -= amount;
            updateBalance();
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
    int option;

    cout << "==== Welcome to ATM Simulation ====\n";
    cout << "1. Register\n2. Login\nChoose option: ";
    cin >> option;

    if (option == 1) {
        atm.registerUser();
        atm.menu();
    } else if (option == 2) {
        if (atm.login()) {
            atm.menu();
        }
    } else {
        cout << "Invalid option!\n";
    }

    return 0;
}
