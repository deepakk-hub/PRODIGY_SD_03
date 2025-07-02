#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

vector<Contact> contacts;
const string FILE_NAME = "contacts.txt";

void loadContacts() {
    ifstream file(FILE_NAME);
    string line;
    contacts.clear();
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, email;
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        if (!name.empty())
            contacts.push_back({ name, phone, email });
    }
    file.close();
}

void saveContacts() {
    ofstream file(FILE_NAME);
    for (const auto& c : contacts) {
        file << c.name << "," << c.phone << "," << c.email << "\n";
    }
    file.close();
}

void addContact() {
    Contact c;
    cout << "Enter name: ";
    getline(cin, c.name);
    cout << "Enter phone: ";
    getline(cin, c.phone);
    cout << "Enter email: ";
    getline(cin, c.email);
    contacts.push_back(c);
    saveContacts();
    cout << "Contact added.\n";
}

void viewContacts() {
    cout << "\n--- Contact List ---\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". " << contacts[i].name
            << " | " << contacts[i].phone
            << " | " << contacts[i].email << "\n";
    }
    cout << "---------------------\n";
}

void editContact() {
    viewContacts();
    int index;
    cout << "Enter the contact number to edit: ";
    cin >> index;
    cin.ignore(); // clear newline from input buffer

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    Contact& c = contacts[index - 1];
    cout << "Editing contact: " << c.name << "\n";

    cout << "Enter new name (leave empty to keep current): ";
    string input;
    getline(cin, input);
    if (!input.empty()) c.name = input;

    cout << "Enter new phone (leave empty to keep current): ";
    getline(cin, input);
    if (!input.empty()) c.phone = input;

    cout << "Enter new email (leave empty to keep current): ";
    getline(cin, input);
    if (!input.empty()) c.email = input;

    saveContacts();
    cout << "Contact updated.\n";
}

void deleteContact() {
    viewContacts();
    int index;
    cout << "Enter the contact number to delete: ";
    cin >> index;
    cin.ignore(); // clear newline

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid contact number.\n";
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    saveContacts();
    cout << "Contact deleted.\n";
}

void showMenu() {
    cout << "\n--- Contact Manager ---\n";
    cout << "1. View Contacts\n";
    cout << "2. Add Contact\n";
    cout << "3. Edit Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    loadContacts();
    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // clear newline
        switch (choice) {
        case 1: viewContacts(); break;
        case 2: addContact(); break;
        case 3: editContact(); break;
        case 4: deleteContact(); break;
        case 5: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
    return 0;
}
