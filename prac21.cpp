#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

struct Student {
    int roll;
    string name;
    string div;
    string address;
};

void addStudent() {
    Student s;
    cout << "Enter roll number: ";
    cin >> s.roll;
    cout << "Enter name: ";
    cin >> s.name;
    cout << "Enter division: ";
    cin >> s.div;
    cin.ignore();
    cout << "Enter address: ";
    getline(cin, s.address);
    ofstream file("students.txt", ios::app);
    file << s.roll << "|" << s.name << "|" << s.div << "|" << s.address << "\n";
    file.close();
}

void deleteStudent() {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;
    ifstream fin("students.txt");
    ofstream fout("temp.txt");
    string line;
    bool found = false;
    while(getline(fin, line)) {
        stringstream ss(line);
        string field;
        getline(ss, field, '|');
        int r = stoi(field);
        if(r == roll) {
            found = true;
            continue;
        }
        fout << line << "\n";
    }
    fin.close();
    fout.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if(found)
        cout << "Student record deleted.\n";
    else
        cout << "Record not found.\n";
}

void insertStudent() {
    vector<Student> students;
    ifstream fin("students.txt");
    string line;
    while(getline(fin, line)) {
        stringstream ss(line);
        Student s;
        string field;
        getline(ss, field, '|');
        s.roll = stoi(field);
        getline(ss, s.name, '|');
        getline(ss, s.div, '|');
        getline(ss, s.address);
        students.push_back(s);
    }
    fin.close();
    int pos;
    cout << "Enter position to insert (starting from 1): ";
    cin >> pos;
    Student s;
    cout << "Enter roll number: ";
    cin >> s.roll;
    cout << "Enter name: ";
    cin >> s.name;
    cout << "Enter division: ";
    cin >> s.div;
    cin.ignore();
    cout << "Enter address: ";
    getline(cin, s.address);
    if(pos <= 0 || pos > students.size() + 1) {
        cout << "Invalid position.\n";
        return;
    }
    students.insert(students.begin() + pos - 1, s);
    ofstream fout("students.txt");
    for(auto &st : students) {
        fout << st.roll << "|" << st.name << "|" << st.div << "|" << st.address << "\n";
    }
    fout.close();
    cout << "Student record inserted.\n";
}

void searchStudent() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;
    ifstream fin("students.txt");
    string line;
    bool found = false;
    while(getline(fin, line)) {
        stringstream ss(line);
        Student s;
        string field;
        getline(ss, field, '|');
        s.roll = stoi(field);
        getline(ss, s.name, '|');
        getline(ss, s.div, '|');
        getline(ss, s.address);
        if(s.roll == roll) {
            cout << "Roll: " << s.roll << "\nName: " << s.name << "\nDivision: " << s.div << "\nAddress: " << s.address << "\n";
            found = true;
        }
    }
    fin.close();
    if(!found)
        cout << "Record not found.\n";
}

int main() {
    int choice;
    while(true) {
        cout << "\nMenu:\n1. Add student\n2. Delete student\n3. Insert student\n4. Search student\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                insertStudent();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
