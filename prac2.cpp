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

    void insertWithReplacement(int prn, int marks) {
        int index = hashFunc(prn);
        if (!table[index].isOccupied) {
            table[index].prn = prn;
            table[index].marks = marks;
            table[index].isOccupied = true;
        } else {
            int homeIndex = hashFunc(table[index].prn);
            if (homeIndex != index) {
                swap(table[index].prn, prn);
                swap(table[index].marks, marks);
                insertWithReplacement(prn, marks);
            } else {
                int i = (index + 1) % TABLE_SIZE;
                while (table[i].isOccupied) i = (i + 1) % TABLE_SIZE;
                table[i].prn = prn;
                table[i].marks = marks;
                table[i].isOccupied = true;
                int chainIndex = index;
                while (table[chainIndex].next != -1) {
                    chainIndex = table[chainIndex].next;
                }
                table[chainIndex].next = i;
            }
        }
    }

    void deleteLinear(int prn) {
        int index = hashFunc(prn);
        int start = index;
        do {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].prn == prn) {
                table[index].isDeleted = true;
                cout << "Deleted successfully.\n";
                return;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != start);
        cout << "PRN not found.\n";
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
        cout << "2. Insert using Linear Probing (Chaining With Replacement)\n";
        cout << "3. Delete using Linear Probing\n";
        // cout << "5. Insert using Quadratic Probing\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter PRN and Marks: ";
                cin >> prn >> marks;
                ht.insertLinear(prn, marks);
                break;
            case 3:
                cout << "Enter PRN to delete: ";
                cin >> prn;
                ht.deleteLinear(prn);
                break;
            case 2:
                cout << "Enter PRN and Marks: ";
                cin >> prn >> marks;
                ht.insertWithReplacement(prn, marks);
                break;
            case 4:
                ht.display();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
