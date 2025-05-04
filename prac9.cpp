#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    bool lthread, rthread;
    Node(int x)
        : data(x), left(nullptr), right(nullptr), lthread(false), rthread(false) {}
};

Node* insertBST(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->data)  root->left  = insertBST(root->left,  key);
    else                   root->right = insertBST(root->right, key);
    return root;
}

void storeInorderBST(Node* root, vector<Node*>& nodes) {
    if (!root) return;
    if (root->left)  storeInorderBST(root->left,  nodes);
    nodes.push_back(root);
    if (root->right) storeInorderBST(root->right, nodes);
}

void convertToThreaded(Node* root) {
    vector<Node*> nodes;
    storeInorderBST(root, nodes);
    int n = nodes.size();
    for (int i = 0; i < n; ++i) {
        Node* curr = nodes[i];
        if (!curr->left) {
            curr->lthread = true;
            curr->left = (i > 0 ? nodes[i-1] : nullptr);
        } else curr->lthread = false;
        if (!curr->right) {
            curr->rthread = true;
            curr->right = (i < n-1 ? nodes[i+1] : nullptr);
        } else curr->rthread = false;
    }
}

Node* insertThreaded(Node* root, int key) {
    if (!root) {
        Node* node = new Node(key);
        node->lthread = node->rthread = true;
        return node;
    }
    Node *ptr = root, *parent = nullptr;
    while (ptr) {
        if (key == ptr->data) return root;
        parent = ptr;
        if (key < ptr->data) {
            if (!ptr->lthread) ptr = ptr->left;
            else break;
        } else {
            if (!ptr->rthread) ptr = ptr->right;
            else break;
        }
    }
    Node* node = new Node(key);
    node->lthread = node->rthread = true;
    if (key < parent->data) {
        node->left = parent->left;
        node->right = parent;
        parent->lthread = false;
        parent->left = node;
    } else {
        node->left = parent;
        node->right = parent->right;
        parent->rthread = false;
        parent->right = node;
    }
    return root;
}

Node* leftmost(Node* root) {
    if (!root) return nullptr;
    while (!root->lthread) root = root->left;
    return root;
}

void inorder(Node* root) {
    for (Node* cur = leftmost(root); cur; ) {
        cout << cur->data << " ";
        if (cur->rthread) cur = cur->right;
        else              cur = leftmost(cur->right);
    }
    cout << "\n";
}

void preorder(Node* root) {
    Node* cur = root;
    while (cur) {
        cout << cur->data << " ";
        if (!cur->lthread)       cur = cur->left;
        else if (!cur->rthread)  cur = cur->right;
        else {
            while (cur && cur->rthread) cur = cur->right;
            if (cur) cur = cur->right;
        }
    }
    cout << "\n";
}

int main() {
    Node* bst   = nullptr;
    Node* troot = nullptr;
    int n, val, choice;

    cout << "Enter number of nodes for BST: ";
    cin  >> n;
    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        bst = insertBST(bst, val);
    }

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Convert BST to Threaded BST\n";
        cout << "2. Insert new node into Threaded BST\n";
        cout << "3. Inorder traversal\n";
        cout << "4. Preorder traversal\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin  >> choice;

        switch (choice) {
            case 1:
                convertToThreaded(bst);
                troot = bst;
                cout << "Conversion done\n";
                break;
            case 2:
                cout << "Enter value to insert: ";
                cin  >> val;
                if (!troot) {
                    convertToThreaded(bst);
                    troot = bst;
                }
                troot = insertThreaded(troot, val);
                break;
            case 3:
                if (troot) inorder(troot);
                else       cout << "Threaded tree not created\n";
                break;
            case 4:
                if (troot) preorder(troot);
                else       cout << "Threaded tree not created\n";
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}
