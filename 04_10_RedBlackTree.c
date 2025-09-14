#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    RED,
    BLACK
} Color;

// Structure of the node
typedef struct RBNode
{
    int data;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

// Structure of the Red-Black Tree
typedef struct RBTree
{
    RBNode *root;
    RBNode *NIL;
} RBTree;

// It create a Node and return the pointer
RBNode *createNode(RBTree *tree, int data)
{
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;
    node->left = node->right = tree->NIL;
    node->parent = tree->NIL;
    return node;
}

// Create empty tree
RBTree *createTree()
{
    RBTree *tree = (RBTree *)malloc(sizeof(RBTree));
    tree->NIL = (RBNode *)malloc(sizeof(RBNode));
    tree->NIL->color = BLACK;
    tree->NIL->left = tree->NIL->right = tree->NIL->parent = NULL;
    tree->root = tree->NIL;
    return tree;
}

// Left Rotation Function
void leftRotate(RBTree *tree, RBNode *x)
{
    RBNode *y = x->right;
    x->right = y->left;
    if (y->left != tree->NIL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == tree->NIL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right Rotation Function
void rightRotate(RBTree *tree, RBNode *y)
{
    RBNode *x = y->left;
    y->left = x->right;
    if (x->right != tree->NIL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == tree->NIL)
        tree->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

// ----------- Insertion ------------

// Function to fix the balance of the Red-Black Tree
void insertFixup(RBTree *tree, RBNode *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBNode *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        }
        else
        {
            RBNode *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// Inserting a new value
void InsertItem(RBTree *tree, int data)
{
    RBNode *z = createNode(tree, data);
    RBNode *y = tree->NIL;
    RBNode *x = tree->root;

    while (x != tree->NIL)
    {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == tree->NIL)
        tree->root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFixup(tree, z);
}

// ----------- Search ------------
RBNode *SearchItem(RBTree *tree, int key)
{
    RBNode *current = tree->root;
    while (current != tree->NIL && current->data != key)
    {
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return current == tree->NIL ? NULL : current;
}

// ----------- Deletion ------------
void transplant(RBTree *tree, RBNode *u, RBNode *v)
{
    if (u->parent == tree->NIL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// Return minimum value of the tree
RBNode *treeMinimum(RBTree *tree, RBNode *x)
{
    while (x->left != tree->NIL)
        x = x->left;
    return x;
}

// After delete a item,it fixes the balance of the Red-Black Tree
void deleteFixup(RBTree *tree, RBNode *x)
{
    while (x != tree->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            RBNode *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        }
        else
        {
            RBNode *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

// Delete a item by its key
void DeleteItem(RBTree *tree, int key)
{
    RBNode *z = SearchItem(tree, key);
    if (z == NULL)
        return;

    RBNode *y = z;
    RBNode *x;
    Color yOriginalColor = y->color;

    if (z->left == tree->NIL)
    {
        x = z->right;
        transplant(tree, z, z->right);
    }
    else if (z->right == tree->NIL)
    {
        x = z->left;
        transplant(tree, z, z->left);
    }
    else
    {
        y = treeMinimum(tree, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else
        {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (yOriginalColor == BLACK)
        deleteFixup(tree, x);
}

// ----------- Delete Entire Tree ------------
void freeSubtree(RBTree *tree, RBNode *node)
{
    if (node != tree->NIL)
    {
        freeSubtree(tree, node->left);
        freeSubtree(tree, node->right);
        free(node);
    }
}

void DeleteTree(RBTree *tree)
{
    freeSubtree(tree, tree->root);
    free(tree->NIL);
    free(tree);
}

// Print Inorder Traversal of the Tree
void inorderTraversal(RBTree *tree, RBNode *node)
{
    if (node != tree->NIL)
    {
        inorderTraversal(tree, node->left);
        printf("%d(%s) ", node->data, node->color == RED ? "R" : "B");
        inorderTraversal(tree, node->right);
    }
}

void printTree(RBTree *tree)
{
    printf("Inorder Traversal: ");
    inorderTraversal(tree, tree->root);
    printf("\n");
}

// ----------- Main function to Check the operations------------
int main()
{
    RBTree *tree = createTree();

    InsertItem(tree, 10);
    InsertItem(tree, 20);

    printTree(tree);

    InsertItem(tree, 30);

    printTree(tree);

    InsertItem(tree, 15);
    printTree(tree);

    RBNode *found = SearchItem(tree, 15);
    if (found)
        printf("Found: %d\n", found->data);
    else
        printf("Not found\n");

    DeleteItem(tree, 20);

    printTree(tree);

    found = SearchItem(tree, 20);
    if (found)
        printf("Found: %d\n", found->data);
    else
        printf("Not found\n");

    DeleteTree(tree);
    return 0;
}
