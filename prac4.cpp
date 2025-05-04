#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int TABLE_SIZE = 100;

class HashTable {
    vector<list<string>> table;

public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    int hashFunc(const string& word) {
        int hash = 0;
        for (char c : word)
            hash = (hash * 31 + c) % TABLE_SIZE;
        return hash;
    }

    void insert(const string& word) {
        int index = hashFunc(word);
        table[index].push_back(word);
    }

    bool search(const string& word) {
        int index = hashFunc(word);
        for (const auto& w : table[index]) {
            if (w == word) return true;
        }
        return false;
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Unable to open dictionary file.\n";
            return;
        }
        string word;
        while (file >> word) {
            insert(word);
        }
        file.close();
    }
};

int main() {
    HashTable dict;
    int choice;
    string input;

    cout << "Loading dictionary into hash table...\n";
    dict.loadFromFile("dictionary.txt");
    cout << "Dictionary loaded.\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Check if word is correctly spelled\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word to check: ";
                cin >> input;
                if (dict.search(input))
                    cout << "'" << input << "' is spelled correctly.\n";
                else
                    cout << "'" << input << "' is not found in the dictionary.\n";
                break;
            case 2:
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
