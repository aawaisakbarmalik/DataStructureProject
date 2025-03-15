#ifndef SEARCH_LIB_BST_H
#define SEARCH_LIB_BST_H

#include <iostream>
#include <fstream>
#include <string>

typedef long int dtype;

struct Node {
    dtype data;
    int index;
    Node* left;
    Node* right;
};

typedef struct stack {
    int top;
    Node* head;
} Stack;

// Function prototypes
Node* createTree();
void printTree(Node* root);
Node* addNode(Node* root, dtype data, int index);
Node* getData(const string& filename);
void saveData(const string& filename, Node* root);
void savePreorder(ofstream& file, Node* node);  // Declare the savePreorder function
int getFirstOccurrence(dtype data, Node* root);
int getLastOccurrence(dtype data, Node* root);
void getAllOccurrences(dtype data, Node* root, int* occurrences, int& numOccurrences);
bool validateTree(Node* root);
void deleteTree(Node* root);
Stack* createStack();
void push(Stack* stack, Node* node);
Node* pop(Stack* stack);
bool isEmptyStack(Stack* stack);

#endif // SEARCH_LIB_BST_H