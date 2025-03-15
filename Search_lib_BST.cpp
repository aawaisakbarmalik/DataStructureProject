#include "search_lib_BST.h"
#include<iostream>
using namespace std;
/*
Complexity: O(1)
*/
Node* createTree() {
    return nullptr;
}

/*
Complexity: O(n), where n is the number of nodes in the tree
*/
void printTree(Node* root) {
    if (root != nullptr) {
        std::cout << root->data << " (Index: " << root->index << ")" << std::endl;
        printTree(root->left);
        printTree(root->right);
    }
}

/*
Complexity: O(h), where h is the height of the tree
*/
Node* addNode(Node* root, dtype data, int index) {
    if (root == nullptr) {
        root = new Node{ data, index, nullptr, nullptr };
    }
    else if (data <= root->data) { // Duplicates go to the left subtree
        if (root->left == nullptr) {
            root->left = new Node{ data, index, nullptr, nullptr };
        }
        else {
            addNode(root->left, data, index);
        }
    }
    else { // Greater data goes to the right subtree
        if (root->right == nullptr) {
            root->right = new Node{ data, index, nullptr, nullptr };
        }
        else {
            addNode(root->right, data, index);
        }
    }
    return root;
}

/*
Complexity: O(n*log(n)) on average, O(n^2) in worst case if data is sorted
*/
Node* getData(const std::string& filename) {
    std::ifstream file(filename);
    Node* root = createTree();
    dtype data;
    int index = 0;
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return nullptr;
    }
    while (file >> data) {
        cout << "Reading data: " << data << " at index: " << index << endl;
        root = addNode(root, data, index++);
    }
    file.close();
    return root;
}

/*
Complexity : O(n), where n is the number of nodes in the tree
*/

void savePreorder(std::ofstream& file, Node* node) {
    if (node != nullptr) {
        file << node->data << ',' << node->index << std::endl;
        savePreorder(file, node->left);
        savePreorder(file, node->right);
    }
}

/*
Complexity: O(n), where n is the number of nodes in the tree
*/
void saveData(const std::string& filename, Node* root) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }
    savePreorder(file, root);
    file.close();
}


/*
Complexity: O(h), where h is the height of the tree
*/
int getFirstOccurrence(dtype data, Node* root) {
    if (!root) {
        cout << "Reached a leaf, no data found." << endl;
        return -1;
    }
    cout << "Checking node with data: " << root->data << endl;
    if (data < root->data) {
        return getFirstOccurrence(data, root->left);
    }
    else if (data > root->data) {
        return getFirstOccurrence(data, root->right);
    }
    else {
        int leftResult = getFirstOccurrence(data, root->left);
        return (leftResult != -1) ? leftResult : root->index;
    }
}

/*
Complexity: O(h), where h is the height of the tree
*/
int getLastOccurrence(dtype data, Node* root) {
    if (!root) return -1;
    if (data < root->data) {
        return getLastOccurrence(data, root->left);
    }
    else if (data > root->data) {
        return getLastOccurrence(data, root->right);
    }
    else {
        // Attempt to find a later occurrence in the right subtree
        int rightResult = getLastOccurrence(data, root->right);
        return (rightResult != -1) ? rightResult : root->index;
    }
}

void deleteTree(Node* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

/*
Complexity: O(n), where n is the number of nodes in the tree
*/
void getAllOccurrences(dtype data, Node* root, int* occurrences, int& numOccurrences) {
    if (root) {
        getAllOccurrences(data, root->left, occurrences, numOccurrences);  // Always check left first
        if (root->data == data) {
            occurrences[numOccurrences++] = root->index;  // Store the index if data matches
        }
        getAllOccurrences(data, root->right, occurrences, numOccurrences);  // Then check right
    }
}

/*
Complexity: O(n), where n is the number of nodes in the tree
*/
bool validateTree(Node* root) {
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
        return true;  // An empty tree is trivially a valid BST.
    }

    Stack* stack = createStack();
    Node* current = root;
    Node* prev = nullptr;

    while (current != nullptr || !isEmptyStack(stack)) {
        while (current != nullptr) {
            push(stack, current);
            current = current->left;
        }

        if (!isEmptyStack(stack)) {
            current = pop(stack);

            // Check if the current node's data is in the correct order
            if (prev != nullptr && current->data < prev->data) {
                cout << "BST validation failed: Current node data " << current->data << " is less than previous node data " << prev->data << endl;
                return false;
            }

            prev = current; // Move the prev pointer to the current node
            current = current->right; // Move to the right subtree
        }
    }
    cout << "The tree is a valid BST." << endl;
    return true;
}

/*
Complexity: O(1)
*/
Stack* createStack() {
    return new Stack{ 0, nullptr };
}

/*
Complexity: O(1)
*/
void push(Stack* stack, Node* node) {
    Node* oldHead = stack->head;
    stack->head = node;
    node->right = oldHead;
    stack->top++;
}

/*
Complexity: O(1)
*/
Node* pop(Stack* stack) {
    if (isEmptyStack(stack)) return nullptr;
    Node* node = stack->head;
    stack->head = node->right;
    stack->top--;
    return node;
}

/*
Complexity: O(1)
*/
bool isEmptyStack(Stack* stack) {
    return stack->top == 0;
}
