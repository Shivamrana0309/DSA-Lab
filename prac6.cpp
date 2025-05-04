#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    TreeNode* insert(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        if (val < node->val) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return node;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;
        if (key < root->val) root->left = deleteNode(root->left, key);
        else if (key > root->val) root->right = deleteNode(root->right, key);
        else {
            if (!root->left) return root->right;
            if (!root->right) return root->left;
            TreeNode* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
        return root;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    void preorder(TreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(TreeNode* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->val << " ";
    }

    void inorderIterative(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* curr = root;
        while (curr || !s.empty()) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top(); s.pop();
            cout << curr->val << " ";
            curr = curr->right;
        }
    }

    void preorderIterative(TreeNode* root) {
        if (!root) return;
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode* node = s.top(); s.pop();
            cout << node->val << " ";
            if (node->right) s.push(node->right);
            if (node->left) s.push(node->left);
        }
    }

    void postorderIterative(TreeNode* root) {
        if (!root) return;
        stack<TreeNode*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            TreeNode* node = s1.top(); s1.pop();
            s2.push(node);
            if (node->left) s1.push(node->left);
            if (node->right) s1.push(node->right);
        }
        while (!s2.empty()) {
            cout << s2.top()->val << " ";
            s2.pop();
        }
    }
};

int main() {
    BinaryTree bt;
    int choice, val, n;
    vector<int> preorder, inorder;

    while (true) {
        cout << "\nMenu:\n1. Insert\n2. Delete\n3. Recursive Traversals (Inorder, Preorder, Postorder)\n4. Iterative Traversals (Inorder, Preorder, Postorder)\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: "; cin >> val;
                bt.root = bt.insert(bt.root, val);
                break;
            case 2:
                cout << "Enter value to delete: "; cin >> val;
                bt.root = bt.deleteNode(bt.root, val);
                break;
            case 3:
                cout << "Inorder: "; bt.inorder(bt.root); cout << "\n";
                cout << "Preorder: "; bt.preorder(bt.root); cout << "\n";
                cout << "Postorder: "; bt.postorder(bt.root); cout << "\n";
                break;
            case 4:
                cout << "Inorder: "; bt.inorderIterative(bt.root); cout << "\n";
                cout << "Preorder: "; bt.preorderIterative(bt.root); cout << "\n";
                cout << "Postorder: "; bt.postorderIterative(bt.root); cout << "\n";
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}