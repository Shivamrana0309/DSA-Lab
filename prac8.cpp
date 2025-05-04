#include <iostream>
#include <vector>
#include <unordered_map>
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

Node* buildTreeHelper(const vector<int>& pre, const vector<int>& in, int &preIdx,
                      int inStart, int inEnd, unordered_map<int,int>& inMap) {
    if (inStart > inEnd) return nullptr;
    int rootVal = pre[preIdx++];
    Node* root = new Node(rootVal);
    int idx = inMap[rootVal];
    root->left  = buildTreeHelper(pre, in, preIdx, inStart, idx - 1, inMap);
    root->right = buildTreeHelper(pre, in, preIdx, idx + 1, inEnd,   inMap);
    return root;
}

Node* buildTree(const vector<int>& pre, const vector<int>& in) {
    unordered_map<int,int> inMap;
    for (int i = 0; i < (int)in.size(); ++i) inMap[in[i]] = i;
    int preIdx = 0;
    return buildTreeHelper(pre, in, preIdx, 0, in.size() - 1, inMap);
}

bool isEqual(Node* a, Node* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    if (a->data != b->data) return false;
    return isEqual(a->left, b->left) && isEqual(a->right, b->right);
}

int main() {
    Node *bst = nullptr, *tree2 = nullptr;
    int n, val, choice;

    cout << "Enter number of nodes for BST: ";
    cin >> n;
    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        bst = insert(bst, val);
    }

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert node into BST\n";
        cout << "2. Construct tree from inorder & preorder\n";
        cout << "3. Check equality of BST and constructed tree\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                bst = insert(bst, val);
                break;
            case 2: {
                int m;
                cout << "Enter number of nodes: ";
                cin >> m;
                vector<int> pre(m), in(m);
                cout << "Enter preorder:\n";
                for (int i = 0; i < m; ++i) cin >> pre[i];
                cout << "Enter inorder:\n";
                for (int i = 0; i < m; ++i) cin >> in[i];
                tree2 = buildTree(pre, in);
                cout << "Tree constructed.\n";
                break;
            }
            case 3:
                if (isEqual(bst, tree2))
                    cout << "Trees are equal\n";
                else
                    cout << "Trees are not equal\n";
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}
