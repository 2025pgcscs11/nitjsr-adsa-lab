#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node Structure of AVL Tree
typedef struct AVLTreeNode
{
    struct AVLTreeNode *left;
    int data;
    struct AVLTreeNode *right;
    int height;
} Node;

// Initialize AVL Tree
Node *CreateTree()
{
    return NULL;
}

// Function that return height of a node
int Height(Node *root)
{
    if (!root)
        return -1;
    else
        return root->height;
}

// Max element returning function
int max(int a, int b)
{
    return a >= b ? a : b;
}

// Single Rotation  LL
Node *LLRotation(Node *root)
{
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = 1 + max(Height(root->left), Height(root->right));
    temp->height = 1 + max(Height(temp->left), root->height);
    return temp;
}

// Single Rotation RR
Node *RRRotation(Node *root)
{
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = 1 + max(Height(root->right), Height(root->left));
    temp->height = 1 + max(Height(temp->right), root->height);
    return temp;
}

// Double Rotation LR
Node *LRRotation(Node *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// Double Rotation RL
Node *RLRotation(Node *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

// Insert a element into Binary Search Tree
Node *InsertItem(Node *root, int value)
{
    Node *ptr = (Node *)malloc(sizeof(Node));
    if (ptr == NULL)
    {
        printf("Memory Error.\n");
        return NULL;
    }
    ptr->data = value;
    ptr->height = 0;
    ptr->right = ptr->left = NULL;

    if (root == NULL)
    {
        root = ptr;
    }
    else if (value < root->data)
    {
        root->left = InsertItem(root->left, value);
        if (Height(root->left) - Height(root->right) == 2)
        {
            if (value < root->left->data)
                root = LLRotation(root);
            else
                root = LRRotation(root);
        }
    }
    else if (value > root->data)
    {
        root->right = InsertItem(root->right, value);
        if (Height(root->right) - Height(root->left) == 2)
        {
            if (value > root->right->data)
                root = RRRotation(root);
            else
                root = RLRotation(root);
        }
    }

    root->height = 1 + max(Height(root->left), Height(root->right));
    return root;
}

// Search a value in the tree
bool SearchItem(Node *root, int value)
{
    if (root == NULL)
        return false;
    else if (root->data == value)
        return true;
    else
        return SearchItem(root->left, value) || SearchItem(root->right, value);
}

// Delete node of the tree
void DeleteItem(Node **root)
{
    if (*root == NULL)
        return;
    DeleteItem(&((*root)->left));
    DeleteItem(&((*root)->right));
    free(*root);
    *root = NULL;
}

// Print Preorder Traversal of the tree
void PreOrderTraversal(Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

int main()
{
    Node *root = NULL;
    root = CreateTree();
    root = InsertItem(root, 3);
    root = InsertItem(root, 5);
    root = InsertItem(root, 1);
    root = InsertItem(root, 2);
    root = InsertItem(root, 8);
    PreOrderTraversal(root);
    printf("\n");
    // After When 9 is inserted the order changes to maintain the balance
    root = InsertItem(root, 9);
    PreOrderTraversal(root);
    printf("\n");
    if (SearchItem(root, 4))
        printf("Search item is found.\n");
    else
        printf("Search item is not found.\n");
    DeleteItem(&root);
    if (root == NULL)
        printf("The AVL Tree is deleted.\n");
    return 0;
}