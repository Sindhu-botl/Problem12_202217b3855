#include <stdio.h>
#include <stdlib.h>

// Node structure to define the structure of the node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Function to create a new node
Node* newNode(int val) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = val;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to insert nodes into the binary tree
Node* insert(Node* root, int data) {
    // If tree is empty, new node becomes the root
    if (root == NULL) {
        root = newNode(data);
        return root;
    }
    
    // Otherwise, recur down the tree
    if (data <= root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    
    return root;
}

// Function to find the deepest rightmost node in the binary tree
Node* findDeepestRightmostNode(Node* root, Node** deepestNode) {
    if (root == NULL)
        return NULL;
    
    if (!root->left && !root->right) {
        *deepestNode = root;
        return NULL;
    }
    
    root->right = findDeepestRightmostNode(root->right, deepestNode);
    if (!root->right) {
        root->left = NULL; // Remove reference to the node being replaced
    }
    
    return root;
}

// Function to delete a given node from the binary tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return root;
    
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to print inorder traversal of the binary tree
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Driver program to test above functions
int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal before deletion: ");
    inorder(root);
    printf("\n");

    int key = 50; // Node to be deleted

    Node* deepestNode = NULL;
    root = findDeepestRightmostNode(root, &deepestNode);

    if (deepestNode) {
        printf("Deepest rightmost node: %d\n", deepestNode->data);
        root = deleteNode(root, key);

        // Replace key with deepest rightmost node's data
        if (root) {
            root->data = deepestNode->data;
        }
        free(deepestNode);
    }

    printf("Inorder traversal after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}