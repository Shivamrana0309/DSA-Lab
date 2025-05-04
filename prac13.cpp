#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f): ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, const string& str, unordered_map<char,string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = str;
    }
    buildCodes(root->left,  str + "0", codes);
    buildCodes(root->right, str + "1", codes);
}

int main() {
    int n;
    cout << "Enter number of unique characters: ";
    cin >> n;

    vector<char> chars(n);
    vector<int> freq(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter character and its frequency: ";
        cin >> chars[i] >> freq[i];
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < n; ++i) {
        pq.push(new Node(chars[i], freq[i]));
    }

    while (pq.size() > 1) {
        Node* left  = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left  = left;
        parent->right = right;
        pq.push(parent);
    }

    Node* root = pq.top();
    unordered_map<char,string> codes;
    buildCodes(root, "", codes);

    cout << "\nHuffman Codes:\n";
    for (char c : chars) {
        cout << c << " : " << codes[c] << "\n";
    }

    cin.ignore();
    string text;
    cout << "\nEnter string to encode: ";
    getline(cin, text);

    string encoded;
    for (char c : text) {
        encoded += codes[c];
    }
    cout << "Encoded bit sequence: " << encoded << "\n";

    string bits;
    cout << "\nEnter bit sequence to decode: ";
    cin >> bits;

    string decoded;
    Node* curr = root;
    for (char b : bits) {
        curr = (b == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }
    cout << "Decoded string: " << decoded << "\n";

    return 0;
}
