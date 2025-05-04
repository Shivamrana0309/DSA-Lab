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

int height(Node* root) {
    if (!root) return 0;
    int L = height(root->left);
    int R = height(root->right);
    return 1 + (L > R ? L : R);
}

Node* cloneAndErase(Node* root) {
    if (!root) return nullptr;
    Node* L = cloneAndErase(root->left);
    Node* R = cloneAndErase(root->right);
    Node* C = new Node(root->data);
    delete root;
    C->left = L;
    C->right = R;
    return C;
}

void mirror(Node* root) {
    if (!root) return;
    Node* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    mirror(root->left);
    mirror(root->right);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main() {
    Node* root = nullptr;
    int n, val, choice;

    cout << "Enter number of initial nodes: ";
    cin >> n;
    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        root = insert(root, val);
    }

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert a node\n";
        cout << "2. Find height of tree\n";
        cout << "3. Clone tree and erase original\n";
        cout << "4. Create mirror image of tree\n";
        cout << "5. Display traversals\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Value to insert: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "Height of tree: " << height(root) << "\n";
                break;
            case 3:
                root = cloneAndErase(root);
                cout << "Original tree erased; cloned tree created.\n";
                break;
            case 4:
                mirror(root);
                cout << "Tree has been mirrored.\n";
                break;
            case 5:
                cout << "Inorder: ";
                inorder(root);
                cout << "\nPreorder: ";
                preorder(root);
                cout << "\nPostorder: ";
                postorder(root);
                cout << "\n";
                break;
            case 6:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}
