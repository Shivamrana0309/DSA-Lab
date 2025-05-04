#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

int longestPathNodes(Node* root) {
    if (!root) return 0;
    int L = longestPathNodes(root->left);
    int R = longestPathNodes(root->right);
    return 1 + (L > R ? L : R);
}

bool searchWithCount(Node* root, int key, int &comparisons) {
    Node* cur = root;
    while (cur) {
        comparisons++;
        if (cur->data == key) return true;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }
    return false;
}

int main() {
    Node* root = nullptr;
    int choice, val, key, comps;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert value\n";
        cout << "2. Longest path node count\n";
        cout << "3. Search value\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "Number of nodes in longest path from root: "
                     << longestPathNodes(root) << "\n";
                break;
            case 3:
                comps = 0;
                cout << "Enter value to search: ";
                cin >> key;
                if (searchWithCount(root, key, comps))
                    cout << "Value found. Comparisons required: " << comps << "\n";
                else
                    cout << "Value not found. Comparisons made: " << comps << "\n";
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}
