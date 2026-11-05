
#include <iostream>       // For input and output operations.
#include <queue>           // For priority_queue (min-heap).
#include <vector>          // For storing Huffman tree nodes.
#include <unordered_map>  // For storing character frequencies and Huffman codes.
using namespace std;


// Structure representing a node in the Huffman tree.
struct HuffmanNode {

    char data;                  // Stores the character.
    int frequency;              // Stores the frequency of the character.
    HuffmanNode *left, *right;  // Pointers to left and right child nodes.

    // Constructor to initialize a new node.
    HuffmanNode(char data, int frequency) {

        left = right = nullptr; // Initially, both children are NULL.

        this->data = data;      // Assigns the given character to the node.
        this->frequency = frequency; // Assigns the character frequency.
    }
};


// Comparator to arrange nodes in increasing order of frequency.
struct Compare {

    bool operator()(HuffmanNode* left, HuffmanNode* right) {

        // Node with smaller frequency gets higher priority.
        return left->frequency > right->frequency;
    }
};


// Function to generate and print Huffman codes.
void printCodes(HuffmanNode* root, string code,
                unordered_map<char, string>& huffmanCodes) {

    if (!root) return; // Stops if the current node is NULL.

    // Checks whether the current node is a leaf node.
    // A leaf node contains an actual character.
    if (!root->left && !root->right) {

        // Stores the character and its generated Huffman code in the map.
        huffmanCodes[root->data] = code;

        // Prints the character and its corresponding code.
        cout << root->data << ": " << code << endl;
    }

    // Moves to the left child and adds 0 to the code.
    printCodes(root->left, code + "0", huffmanCodes);

    // Moves to the right child and adds 1 to the code.
    printCodes(root->right, code + "1", huffmanCodes);
}


// Function to build the Huffman tree and encode the input text.
void buildHuffmanTree(const string& text) {

    // Creates a map to store the frequency of each character.
    unordered_map<char, int> frequencyMap;

    // Traverses the input text character by character.
    for (char ch : text) {

        frequencyMap[ch]++; // Increments the frequency of the current character.
    }

    // Creates a min-heap to arrange nodes by their frequencies.
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Creates a leaf node for every unique character.
    for (auto pair : frequencyMap) {

        // Inserts the character and its frequency into the priority queue.
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Combines nodes until only one node (root) remains.
    while (pq.size() > 1) {

        // Gets the node with the smallest frequency.
        HuffmanNode* left = pq.top();
        pq.pop(); // Removes that node from the priority queue.

        // Gets the next smallest frequency node.
        HuffmanNode* right = pq.top();
        pq.pop(); // Removes the second node.

        // Creates a new parent node with the sum of both frequencies.
        // '\0' represents an internal node without an actual character.
        HuffmanNode* newNode = new HuffmanNode(
            '\0', left->frequency + right->frequency
        );

        newNode->left = left;   // Attaches first node as left child.
        newNode->right = right; // Attaches second node as right child.

        // Inserts the combined parent node back into the min-heap.
        pq.push(newNode);
    }

    // The remaining node is the root of the Huffman tree.
    HuffmanNode* root = pq.top();

    // Creates a map to store each character and its Huffman code.
    unordered_map<char, string> huffmanCodes;

    // Traverses the tree to generate all Huffman codes.
    // Starts with an empty code string.
    printCodes(root, "", huffmanCodes);

    // Prints the encoded version of the original text.
    cout << "\nEncoded string: ";

    // Traverses the original text character by character.
    for (char ch : text) {

        // Prints the Huffman code corresponding to each character.
        cout << huffmanCodes[ch];
    }

    cout << endl; // Moves to the next line.
}


// Main function: execution starts here.
int main() {

    string text; // Stores the input text.

    cout << "Enter text to encode using Huffman Encoding: ";

    // Reads the complete input line, including spaces.
    getline(cin, text);

    // Calls the function to build the tree and generate encoded text.
    buildHuffmanTree(text);

    return 0; // Indicates successful program termination.
}
