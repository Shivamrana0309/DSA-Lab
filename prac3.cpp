#include <iostream>
#include <vector>
using namespace std;

const int TABLE_SIZE = 10;

struct Student {
    int prn;
    int marks;
    bool isOccupied;
    bool isDeleted;
    int next;
    Student() : prn(-1), marks(0), isOccupied(false), isDeleted(false), next(-1) {}
};

class HashTable {
    vector<Student> table;

public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    int hashFunc(int prn) {
        return prn % TABLE_SIZE;
    }

    void insertLinear(int prn, int marks) {
        int index = hashFunc(prn);
        int start = index;
        do {
            if (!table[index].isOccupied || table[index].isDeleted) {
                table[index].prn = prn;
                table[index].marks = marks;
                table[index].isOccupied = true;
                table[index].isDeleted = false;
                table[index].next = -1;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != start);
        cout << "Hash table is full.\n";
    }

    void insertQuadratic(int prn, int marks) {
        int index = hashFunc(prn);
        int i = 0;
        while (table[(index + i * i) % TABLE_SIZE].isOccupied) {
            i++;
            if (i == TABLE_SIZE) {
                cout << "Hash table is full.\n";
                return;
            }
        }
        int pos = (index + i * i) % TABLE_SIZE;
        table[pos].prn = prn;
        table[pos].marks = marks;
        table[pos].isOccupied = true;
    }

    void display() {
        cout << "Index\tPRN\tMarks\tNext\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied && !table[i].isDeleted)
                cout << i << "\t" << table[i].prn << "\t" << table[i].marks << "\t" << table[i].next << "\n";
            else
                cout << i << "\t---\t---\t---\n";
        }
    }
};

int main() {
    HashTable ht;
    int choice, prn, marks;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert using Linear Probing\n";
        
        // cout << "3. Insert using Linear Probing (Chaining Without Replacement)\n";
        // cout << "2. Insert using Linear Probing (Chaining With Replacement)\n";
        // cout << "3. Delete using Linear Probing\n";
        cout << "2. Insert using Quadratic Probing\n";
        cout << "3. Display Hash Table\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter PRN and Marks: ";
                cin >> prn >> marks;
                ht.insertLinear(prn, marks);
                break;
            case 2:
                cout << "Enter PRN and Marks: ";
                cin >> prn >> marks;
                ht.insertQuadratic(prn, marks);
                break;
            case 3:
                ht.display();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
