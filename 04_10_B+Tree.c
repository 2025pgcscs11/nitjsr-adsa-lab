#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 3   // Max keys per node

typedef struct BPlusNode {
    int keys[ORDER];
    struct BPlusNode* children[ORDER + 1];
    int numKeys;
    bool isLeaf;
    struct BPlusNode* next; 
} BPlusNode;

typedef struct BPlusTree {
    BPlusNode* root;
} BPlusTree;

// Create Node 
BPlusNode* createNode(bool isLeaf) {
    BPlusNode* node = (BPlusNode*)malloc(sizeof(BPlusNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    node->next = NULL;
    for (int i = 0; i <= ORDER; i++) node->children[i] = NULL;
    return node;
}

// Create Tree
BPlusTree* createTree() {
    BPlusTree* tree = (BPlusTree*)malloc(sizeof(BPlusTree));
    tree->root = createNode(true);
    return tree;
}

//  Search item in the tree
BPlusNode* SearchItem(BPlusTree* tree, int key) {
    BPlusNode* cur = tree->root;
    while (!cur->isLeaf) {
        int i = 0;
        while (i < cur->numKeys && key >= cur->keys[i]) i++;
        cur = cur->children[i];
    }
    for (int i = 0; i < cur->numKeys; i++) {
        if (cur->keys[i] == key) return cur;
    }
    return NULL;
}

//  Split Child 
void splitChild(BPlusNode* parent, int index, BPlusNode* child) {
    int mid = ORDER / 2;
    BPlusNode* newNode = createNode(child->isLeaf);
    newNode->numKeys = child->numKeys - mid;

    // Copy keys/children to new node
    for (int i = 0; i < newNode->numKeys; i++) {
        newNode->keys[i] = child->keys[mid + i];
    }
    if (!child->isLeaf) {
        for (int i = 0; i <= newNode->numKeys; i++) {
            newNode->children[i] = child->children[mid + i];
        }
    }

    child->numKeys = mid;

    // Shift parent's children
    for (int i = parent->numKeys; i >= index + 1; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newNode;

    // Shift parent's keys
    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    // Promote key
    parent->keys[index] = newNode->keys[0];
    parent->numKeys++;
}

//  Insert Non-Full 
void insertNonFull(BPlusNode* node, int key) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        // Shift to make space
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && node->keys[i] > key) i--;
        i++;
        if (node->children[i]->numKeys == ORDER) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// ---------------- Insert ----------------
void InsertItem(BPlusTree* tree, int key) {
    BPlusNode* root = tree->root;
    if (root->numKeys == ORDER) {
        BPlusNode* newRoot = createNode(false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        int i = (key > newRoot->keys[0]) ? 1 : 0;
        insertNonFull(newRoot->children[i], key);
        tree->root = newRoot;
    } else {
        insertNonFull(root, key);
    }
}

// ---------------- Delete (simplified leaf deletion only) ----------------
void DeleteItem(BPlusTree* tree, int key) {
    BPlusNode* leaf = SearchItem(tree, key);
    if (!leaf) return;

    int i;
    for (i = 0; i < leaf->numKeys; i++) {
        if (leaf->keys[i] == key) break;
    }
    for (; i < leaf->numKeys - 1; i++) {
        leaf->keys[i] = leaf->keys[i + 1];
    }
    leaf->numKeys--;
}

// ---------------- DeleteTree ----------------
void freeNode(BPlusNode* node) {
    if (node == NULL) return;
    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            freeNode(node->children[i]);
        }
    }
    free(node);
}

void DeleteTree(BPlusTree* tree) {
    freeNode(tree->root);
    free(tree);
}

// ---------------- Print Tree (Level-wise) ----------------
void printTreeRecursive(BPlusNode* node, int level) {
    if (node == NULL) return;
    printf("Level %d [", level);
    for (int i = 0; i < node->numKeys; i++) {
        printf("%d ", node->keys[i]);
    }
    printf("]\n");

    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            printTreeRecursive(node->children[i], level + 1);
        }
    }
}

void printTree(BPlusTree* tree) {
    printTreeRecursive(tree->root, 0);
}

// ---------------- Main function to do operations----------------
int main() {
    BPlusTree* tree = createTree();

    InsertItem(tree, 5);
    InsertItem(tree, 15);
    InsertItem(tree, 25);
    InsertItem(tree, 35);
    InsertItem(tree, 45);

    printf("B+ Tree after insertions:\n");
    printTree(tree);

    BPlusNode* found = SearchItem(tree, 25);
    if (found) printf("Found 25 in leaf.\n");

    DeleteItem(tree, 25);
    printf("B+ Tree after deleting 25:\n");
    printTree(tree);
    
    DeleteTree(tree);
    return 0;
}
