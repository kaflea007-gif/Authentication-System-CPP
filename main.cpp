
// Assignment 2 - Authentication System
// Name: Kafle Anish
// Student ID: 20253720
// Course: Object-Oriented Programming II

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// User class
class User {
public:
    string username;
    string password;

    // Constructor
    User(const string& u, const string& p)
        : username(u), password(p) {}

    // Converts user information into one line
    string toLine() const {
        return username + "," + password;
    }

    // Creates a user from a line in the file
    static User fromLine(const string& line) {
        size_t pos = line.find(',');

        if (pos == string::npos) {
            return User("", "");
        }

        string u = line.substr(0, pos);
        string p = line.substr(pos + 1);

        return User(u, p);
    }
};

// AuthSystem class
class AuthSystem {
private:
    string filename;

public:
    // Constructor
    AuthSystem(const string& fname)
        : filename(fname) {}

    // Saves a new user in the file
    void signup(const User& user) {
        ofstream fout(filename, ios::app);

        if (!fout.is_open()) {
            cout << "Could not open the file.\n";
            return;
        }

        fout << user.toLine() << "\n";
        fout.close();

        cout << "Signup successful!\n";
    }

    // Checks username and password
    bool login(const string& name, const string& pass) {
        ifstream fin(filename);

        if (!fin.is_open()) {
            return false;
        }

        string line;

        while (getline(fin, line)) {
            if (line.empty()) {
                continue;
            }

            User user = User::fromLine(line);

            if (user.username == name && user.password == pass) {
                fin.close();
                return true;
            }
        }

        fin.close();
        return false;
    }
};

int main() {
    AuthSystem auth("users.txt");

    int choice;

    do {
          cout << "\n1. Signup\n2. Login\n3. Quit\nChoose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string username, password;

            cout << "Enter username: ";
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            User newUser(username, password);
            auth.signup(newUser);
        }
        else if (choice == 2) {
            string username, password;

            cout << "Enter username: ";
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            if (auth.login(username, password)) {
                cout << "Welcome, " << username << "\n";
            }
            else {
                cout << "Login failed.\n";
            }
        }
        else if (choice == 3) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}
