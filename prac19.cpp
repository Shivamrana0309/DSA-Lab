#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

int n;
vector<int> p;
vector<int> q;
vector<vector<int>> e;
vector<vector<int>> w;
vector<vector<int>> rootTable;

void computeOptimalBST() {
    cout << "Enter number of keys (n): ";
    cin >> n;

    p.resize(n + 1);
    q.resize(n + 1);
    cout << "Enter " << n << " probabilities p[1.." << n << "]:\n";
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    cout << "Enter " << (n+1) << " probabilities q[0.." << n << "]:\n";
    for (int i = 0; i <= n; i++) {
        cin >> q[i];
    }

    e.assign(n + 1, vector<int>(n + 1, 0));
    w.assign(n + 1, vector<int>(n + 1, 0));
    rootTable.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= n; i++) {
        e[i][i] = q[i];
        w[i][i] = q[i];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            e[i][j] = numeric_limits<int>::max();
            for (int r = i + 1; r <= j; r++) {
                int t = e[i][r - 1] + e[r][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    rootTable[i][j] = r;
                }
            }
        }
    }
}

void printOptimalBSTStructure(int i, int j, int parent, bool isLeft) {
    if (i == j) {
        if (parent == -1)
            cout << "d" << j << " is root\n";
        else
            cout << "d" << j << " is " << (isLeft ? "left" : "right")
                 << " child of k" << parent << "\n";
        return;
    }
    int r = rootTable[i][j];
    if (parent == -1)
        cout << "k" << r << " is root\n";
    else
        cout << "k" << r << " is " << (isLeft ? "left" : "right")
             << " child of k" << parent << "\n";

    printOptimalBSTStructure(i, r - 1, r, true);
    printOptimalBSTStructure(r, j,     r, false);
}

void displayOptimalCost() {
    cout << "Optimal cost = " << e[0][n] << "\n";
}

void optimalBSTMenu() {
    computeOptimalBST();
    int choice;
    while (true) {
        cout << "\n--- OBST Menu ---\n";
        cout << "1. Display optimal cost\n";
        cout << "2. Display optimal BST structure\n";
        cout << "0. Back to main menu\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayOptimalCost();
                break;
            case 2:
                printOptimalBSTStructure(0, n, -1, true);
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice\n";
        }
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Build Optimal BST\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                optimalBSTMenu();
                break;
            case 0:
                exit(0);
            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}
