
#include <iostream>  // For input and output (cin, cout).
#include <queue>     // For priority_queue (min-heap).
#include <vector>    // For storing characters and frequencies.
#include <string>    // For storing Huffman codes.
using namespace std;

// Structure representing a node in the Huffman tree.
struct Node {
    char ch;          // Stores the character.
    int freq;         // Stores the frequency of the character.
    Node *left, *right; // Pointers to left and right child nodes.

    // Constructor to initialize a new node.
    Node(char c, int f) {
        ch = c;                  // Assigns character.
        freq = f;                // Assigns frequency.
        left = right = nullptr;  // Initially, both children are NULL.
    }
};

// Comparator to make priority_queue work as a min-heap.
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // Node with smaller frequency gets higher priority.
    }
};

// Function to generate and print Huffman codes.
void printCodes(Node* root, string code) {

    if (!root)               // Checks whether the node is NULL.
        return;              // Stops if no node exists.

    // Checks whether the current node is a leaf node.
    if (!root->left && !root->right) {
        cout << root->ch << ": "
             << (code.empty() ? "0" : code) << "\n";
        // Prints character and its Huffman code.
        // If only one character exists, assigns code 0.
        return;
    }

    // Moving left adds 0 to the code.
    printCodes(root->left, code + "0");

    // Moving right adds 1 to the code.
    printCodes(root->right, code + "1");
}

// Function to construct Huffman tree and generate codes.
void huffman(char chars[], int freq[], int n) {

    // Creates a min-heap to store nodes based on frequency.
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Creates a separate node for every character and inserts it into the heap.
    for (int i = 0; i < n; i++)
        pq.push(new Node(chars[i], freq[i]));

    // Continues until only one node (root) remains.
    while (pq.size() > 1) {

        Node* left = pq.top(); // Gets the node with minimum frequency.
        pq.pop();              // Removes it from the priority queue.

        Node* right = pq.top();// Gets the next minimum frequency node.
        pq.pop();              // Removes it from the priority queue.

        // Creates a parent node with the sum of both frequencies.
        Node* parent = new Node('$', left->freq + right->freq);

        parent->left = left;   // Makes first minimum node the left child.
        parent->right = right;// Makes second minimum node the right child.

        pq.push(parent);       // Inserts the parent node back into the heap.
    }

    // The remaining node is the root of the Huffman tree.
    if (!pq.empty())
        printCodes(pq.top(), ""); // Generates codes starting with an empty string.
}

// Main function: execution starts here.
int main() {

    int n;
    cout << "Enter number of characters: ";
    cin >> n; // Takes the number of characters as input.

    // Validates the number of characters.
    if (n <= 0) {
        cout << "Invalid number of characters.\n";
        return 0; // Terminates the program.
    }

    vector<char> chars(n); // Stores input characters.
    vector<int> freq(n);   // Stores corresponding frequencies.

    // Takes characters and their frequencies from the user.
    for (int i = 0; i < n; i++) {

        cout << "Enter character and frequency: ";
        cin >> chars[i] >> freq[i];

        // Frequency must be greater than zero.
        if (freq[i] <= 0) {
            cout << "Frequency must be positive.\n";
            return 0; // Terminates if frequency is invalid.
        }
    }

    cout << "Huffman Codes:\n";

    // Calls Huffman function to construct the tree and print codes.
    huffman(chars.data(), freq.data(), n);

    return 0; // Indicates successful program termination.
}



/*
EXAMPLE:

Input:
Number of characters = 3

Character    Frequency
A            5
B            2
C            1

Huffman tree construction:

Step 1:
Select two minimum frequencies:
C = 1 and B = 2

Combine them:
1 + 2 = 3

Step 2:
Remaining frequencies:
A = 5 and Combined Node = 3

Combine them:
3 + 5 = 8

Step 3:
Generate codes by traversing the tree.
Left side = 0
Right side = 1

Huffman Codes:
C = 00
B = 01
A = 1

Explanation:
- Always select the two nodes having minimum frequencies.
- Combine their frequencies and create a parent node.
- Repeat until only one root node remains.
- Traverse the tree to generate Huffman codes.
*/