#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// Employee structure
struct Employee {
    int empID;
    string name;
    string designation;
    float salary;

    void input() {
        cout << "Enter Employee ID: ";
        cin >> empID;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Designation: ";
        getline(cin, designation);
        cout << "Enter Salary: ";
        cin >> salary;
    }

    void display() const {
        cout << "Employee ID: " << empID << "\n"
             << "Name: " << name << "\n"
             << "Designation: " << designation << "\n"
             << "Salary: " << salary << "\n";
    }

    string toLine() const {
        return to_string(empID) + " " + name + " " + designation + " " + to_string(salary);
    }

    static bool fromLine(const string& line, Employee& emp) {
        istringstream iss(line);
        if (!(iss >> emp.empID >> emp.name >> emp.designation >> emp.salary)) {
            return false;
        }
        return true;
    }
};

// Build an index of employee IDs and their position in the file
map<int, streampos> buildIndex(const string& filename) {
    map<int, streampos> index;
    ifstream file(filename);
    string line;
    streampos pos;

    while (file) {
        pos = file.tellg();
        getline(file, line);
        Employee emp;
        if (Employee::fromLine(line, emp)) {
            index[emp.empID] = pos;
        }
    }

    return index;
}

// Add an employee to the file
void addEmployee(const string& filename) {
    Employee emp;
    emp.input();

    ofstream file(filename, ios::app);
    if (file) {
        file << emp.toLine() << "\n";
        cout << "Employee added successfully.\n";
    } else {
        cout << "Error: Could not open file for writing.\n";
    }
}

// Display an employee by ID
void displayEmployee(const string& filename) {
    int id;
    cout << "Enter Employee ID to search: ";
    cin >> id;

    ifstream file(filename);
    string line;
    Employee emp;
    bool found = false;

    while (getline(file, line)) {
        if (Employee::fromLine(line, emp) && emp.empID == id) {
            cout << "\nEmployee Found:\n";
            emp.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << id << " not found.\n";
    }
}

// Delete an employee by ID
void deleteEmployee(const string& filename) {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    string line;
    Employee emp;
    bool deleted = false;

    while (getline(inFile, line)) {
        if (Employee::fromLine(line, emp)) {
            if (emp.empID == id) {
                deleted = true;
                continue;
            }
            outFile << emp.toLine() << "\n";
        }
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (deleted) {
        cout << "Employee deleted successfully.\n";
    } else {
        cout << "Employee with ID " << id << " not found.\n";
    }
}

// Main menu
void showMenu(const string& filename) {
    int choice;

    do {
        cout << "\n--- Employee Management System ---\n"
             << "1. Add Employee\n"
             << "2. Display Employee\n"
             << "3. Delete Employee\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(filename); break;
            case 2: displayEmployee(filename); break;
            case 3: deleteEmployee(filename); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 4);
}

int main() {
    const string filename = "employee.txt";
    showMenu(filename);
    return 0;
}
