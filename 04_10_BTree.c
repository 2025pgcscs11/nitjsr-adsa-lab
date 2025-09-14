#include <stdio.h>
#include <stdlib.h>

#define T 3 // Minimum degree

// ------------------- BTree Node -------------------
typedef struct BTreeNode
{
    int keys[2 * T - 1];
    struct BTreeNode *children[2 * T];
    int n;
    int leaf;
} BTreeNode;

typedef struct BTree
{
    BTreeNode *root;
} BTree;

// ------------------- Create Tree Node -------------------
BTreeNode *createNode(int leaf)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; i++)
        node->children[i] = NULL;
    return node;
}

// Create Tree
BTree *createTree()
{
    BTree *tree = (BTree *)malloc(sizeof(BTree));
    tree->root = createNode(1);
    return tree;
}

// ------------------- Search Item on the tree-------------------
BTreeNode *SearchItem(BTreeNode *node, int key, int *pos)
{
    int i = 0;
    while (i < node->n && key > node->keys[i])
        i++;

    if (i < node->n && key == node->keys[i])
    {
        *pos = i;
        return node;
    }

    if (node->leaf)
        return NULL;

    return SearchItem(node->children[i], key, pos);
}

// ------------------- Split Child -------------------
void splitChild(BTreeNode *parent, int i, BTreeNode *y)
{
    BTreeNode *z = createNode(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    if (!y->leaf)
    {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[T - 1];
    parent->n++;
}

// ------------------- Insert Non-Full -------------------
void insertNonFull(BTreeNode *node, int key)
{
    int i = node->n - 1;

    if (node->leaf)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->children[i]->n == 2 * T - 1)
        {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void InsertItem(BTree *tree, int key)
{
    BTreeNode *r = tree->root;
    if (r->n == 2 * T - 1)
    {
        BTreeNode *s = createNode(0);
        tree->root = s;
        s->children[0] = r;
        splitChild(s, 0, r);
        insertNonFull(s, key);
    }
    else
    {
        insertNonFull(r, key);
    }
}

// ------------------- Deletion Helpers -------------------
int getPred(BTreeNode *node, int idx)
{
    BTreeNode *cur = node->children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}

int getSucc(BTreeNode *node, int idx)
{
    BTreeNode *cur = node->children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void borrowFromPrev(BTreeNode *node, int idx)
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; i--)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[idx - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    node->keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n++;
    sibling->n--;
}

void borrowFromNext(BTreeNode *node, int idx)
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    child->keys[child->n] = node->keys[idx];

    if (!child->leaf)
        child->children[child->n + 1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; i++)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->n++;
    sibling->n--;
}

void merge(BTreeNode *node, int idx)
{
    BTreeNode *child = node->children[idx];
    BTreeNode *sibling = node->children[idx + 1];

    child->keys[T - 1] = node->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + T] = sibling->keys[i];

    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; i++)
            child->children[i + T] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->n; i++)
        node->keys[i - 1] = node->keys[i];

    for (int i = idx + 2; i <= node->n; i++)
        node->children[i - 1] = node->children[i];

    child->n += sibling->n + 1;
    node->n--;

    free(sibling);
}

// ------------------- Delete Key -------------------
void deleteFromNode(BTreeNode *node, int key);

void fill(BTreeNode *node, int idx)
{
    if (idx != 0 && node->children[idx - 1]->n >= T)
        borrowFromPrev(node, idx);
    else if (idx != node->n && node->children[idx + 1]->n >= T)
        borrowFromNext(node, idx);
    else
    {
        if (idx != node->n)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

void deleteFromNode(BTreeNode *node, int key)
{
    int idx = 0;
    while (idx < node->n && key > node->keys[idx])
        idx++;

    if (idx < node->n && node->keys[idx] == key)
    {
        if (node->leaf)
        {
            for (int i = idx + 1; i < node->n; i++)
                node->keys[i - 1] = node->keys[i];
            node->n--;
        }
        else
        {
            if (node->children[idx]->n >= T)
            {
                int pred = getPred(node, idx);
                node->keys[idx] = pred;
                deleteFromNode(node->children[idx], pred);
            }
            else if (node->children[idx + 1]->n >= T)
            {
                int succ = getSucc(node, idx);
                node->keys[idx] = succ;
                deleteFromNode(node->children[idx + 1], succ);
            }
            else
            {
                merge(node, idx);
                deleteFromNode(node->children[idx], key);
            }
        }
    }
    else
    {
        if (node->leaf)
        {
            return; // key not found
        }

        int flag = (idx == node->n);
        if (node->children[idx]->n < T)
            fill(node, idx);

        if (flag && idx > node->n)
            deleteFromNode(node->children[idx - 1], key);
        else
            deleteFromNode(node->children[idx], key);
    }
}

void DeleteItem(BTree *tree, int key)
{
    if (!tree->root)
        return;

    deleteFromNode(tree->root, key);

    if (tree->root->n == 0)
    {
        BTreeNode *tmp = tree->root;
        if (tree->root->leaf)
            tree->root = NULL;
        else
            tree->root = tree->root->children[0];
        free(tmp);
    }
}

// ------------------- Delete Tree -------------------
void freeSubtree(BTreeNode *node)
{
    if (node)
    {
        if (!node->leaf)
        {
            for (int i = 0; i <= node->n; i++)
                freeSubtree(node->children[i]);
        }
        free(node);
    }
}

void DeleteTree(BTree *tree)
{
    if (tree->root)
        freeSubtree(tree->root);
    free(tree);
}

// ------------------- Print Tree -------------------
void printTree(BTreeNode *node, int level)
{
    if (node)
    {
        printf("Level %d [", level);
        for (int i = 0; i < node->n; i++)
            printf(" %d", node->keys[i]);
        printf(" ]\n");

        if (!node->leaf)
        {
            for (int i = 0; i <= node->n; i++)
                printTree(node->children[i], level + 1);
        }
    }
}

// -------------------Main function to do the operations -------------------
int main()
{
    BTree *tree = createTree();

    InsertItem(tree, 10);
    InsertItem(tree, 20);
    InsertItem(tree, 5);
    InsertItem(tree, 6);
    InsertItem(tree, 12);
    InsertItem(tree, 30);
    InsertItem(tree, 7);
    InsertItem(tree, 17);

    printf("B-Tree after insertion:\n");
    printTree(tree->root, 0);

    int pos;
    BTreeNode *found = SearchItem(tree->root, 6, &pos);
    if (found)
        printf("Found key %d at position %d\n", found->keys[pos], pos);

    DeleteItem(tree, 10);
    printf("\nB-Tree after deleting 10:\n");
    printTree(tree->root, 0);

    DeleteItem(tree, 6);
    printf("\nB-Tree after deleting 6:\n");
    printTree(tree->root, 0);


    DeleteTree(tree);
    return 0;
}
