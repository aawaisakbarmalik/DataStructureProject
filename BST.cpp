#include "search_lib_BST.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    
    string inputFilename = "myData_CS2001.csv";
    string outputFilename = "output.csv";

    Node* root = getData(inputFilename);
    if (root == nullptr) {
        cout << "Failed to load data from file." << endl;
        return -1;
    }

    cout << "BST Preorder Traversal:" << endl;
    printTree(root);

   
    saveData(outputFilename, root);
    cout << "Data has been saved to " << outputFilename << endl;

   
    cout << "Starting BST validation..." << endl;
    if (validateTree(root)) {
        cout << "The tree is a valid BST." << endl;
    }
    else {
        cout << "The tree is not a valid BST." << endl;
    }
       cout << "BST validation complete." << endl;

       cout << "Searching for occurrences..." << endl;
    dtype searchData = 915;  
       cout << "First occurrence of " << searchData << ": " << getFirstOccurrence(searchData, root) << endl;
       cout << "Last occurrence of " << searchData << ": " << getLastOccurrence(searchData, root) << endl;
    return 0;
}
