#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct Node {
    string key;
    string meaning;
    int height;
    Node* left;
    Node* right;
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(const string& key, const string& meaning) {
    Node* node = new Node();
    node->key = key;
    node->meaning = meaning;
    node->height = 1;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = maxInt(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maxInt(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = maxInt(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maxInt(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* insertNode(Node* node, const string& key, const string& meaning) {
    if (!node) return newNode(key, meaning);
    if (key < node->key)
        node->left = insertNode(node->left, key, meaning);
    else if (key > node->key)
        node->right = insertNode(node->right, key, meaning);
    else {
        cout << "Keyword already exists. Meaning updated.\n";
        node->meaning = meaning;
        return node;
    }
    node->height = 1 + maxInt(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, const string& key) {
    if (!root) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((!root->left) || (!root->right)) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (!root) return root;
    root->height = 1 + maxInt(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* searchNode(Node* root, const string& key, int& comparisons) {
    if (!root) return nullptr;
    comparisons++;
    if (key == root->key)
        return root;
    else if (key < root->key)
        return searchNode(root->left, key, comparisons);
    else
        return searchNode(root->right, key, comparisons);
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " : " << root->meaning << "\n";
        inorder(root->right);
    }
}

void reverseInorder(Node* root) {
    if (root) {
        reverseInorder(root->right);
        cout << root->key << " : " << root->meaning << "\n";
        reverseInorder(root->left);
    }
}

Node* updateNode(Node* root, const string& key, const string& newMeaning) {
    int comp = 0;
    Node* node = searchNode(root, key, comp);
    if (node) {
        node->meaning = newMeaning;
        cout << "Meaning updated.\n";
    } else {
        cout << "Keyword not found, update failed.\n";
    }
    return root;
}

Node* rootNode = nullptr;

void safeInput(string& str, const string& label) {
    cout << label;
    getline(cin, str);
    while (str.empty()) {
        cout << "Input cannot be empty. Please re-enter: ";
        getline(cin, str);
    }
}

void inputDictionary() {
    int n;
    cout << "Enter number of entries: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {
        string key, meaning;
        safeInput(key, "Enter keyword: ");
        safeInput(meaning, "Enter meaning: ");
        rootNode = insertNode(rootNode, key, meaning);
    }
}

void addKeyword() {
    string key, meaning;
    safeInput(key, "Enter keyword: ");
    safeInput(meaning, "Enter meaning: ");
    rootNode = insertNode(rootNode, key, meaning);
}

void deleteKeyword() {
    string key;
    safeInput(key, "Enter keyword to delete: ");
    rootNode = deleteNode(rootNode, key);
    cout << "Keyword deleted (if it existed).\n";
}

void updateKeyword() {
    string key, meaning;
    safeInput(key, "Enter keyword to update: ");
    safeInput(meaning, "Enter new meaning: ");
    rootNode = updateNode(rootNode, key, meaning);
}

void displayAscending() {
    cout << "Dictionary in ascending order:\n";
    inorder(rootNode);
}

void displayDescending() {
    cout << "Dictionary in descending order:\n";
    reverseInorder(rootNode);
}

void findKeyword() {
    string key;
    safeInput(key, "Enter keyword to find: ");
    int comparisons = 0;
    Node* result = searchNode(rootNode, key, comparisons);
    if (result)
        cout << "Found: " << result->key << " : " << result->meaning << "\n";
    else
        cout << "Keyword not found.\n";
    cout << "Comparisons made: " << comparisons << "\n";
    cout << "Maximum comparisons required are O(log n) for a height balanced tree.\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n----- Dictionary Menu -----\n";
        cout << "1. Input Dictionary\n";
        cout << "2. Add Keyword\n";
        cout << "3. Delete Keyword\n";
        cout << "4. Update Keyword\n";
        cout << "5. Display in Ascending Order\n";
        cout << "6. Display in Descending Order\n";
        cout << "7. Find Keyword\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                inputDictionary();
                break;
            case 2:
                addKeyword();
                break;
            case 3:
                deleteKeyword();
                break;
            case 4:
                updateKeyword();
                break;
            case 5:
                displayAscending();
                break;
            case 6:
                displayDescending();
                break;
            case 7:
                findKeyword();
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
    return 0;
}