#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure of the Binary Tree node
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} Node;

// Structure of Stack
typedef struct
{
    int top;
    int size;
    Node **arr;
} Stack;

// Initializing Stack with a user-given size
Stack *InitializeStack(int size)
{
    Stack *st = (Stack *)malloc(sizeof(Stack));
    st->top = -1;
    st->size = size;
    st->arr = (Node **)malloc(size * sizeof(Node *));
    return st;
}

// Checking whether the stack is empty or not
bool IsStackEmpty(Stack *s)
{
    if (s->top == -1)
        return true;
    else
        return false;
}

// Checking whether the stack is full or not
bool IsStackFull(Stack *s)
{
    if (s->top == s->size - 1)
        return true;
    else
        return false;
}

// Fetching the top value of stack
Node *StackTop(Stack *s)
{
    return s->arr[s->top];
}

// Pusing a element into stack
void StackPush(Stack *s, Node *data)
{
    if (s->top < s->size - 1)
        s->arr[++s->top] = data;
    else
        printf("Stack is Full.");
}

// Popping a element from the stack
void StackPop(Stack *s)
{
    if (s->top > -1)
        s->top--;
    else
        printf("Stack is Empty.");
}

// Function to destroy the entire Stack's memeory
void DestroyStack(Stack **s)
{
    if (*s)
    {
        free((*s)->arr);
        free(*s);
        *s = NULL;
    }
}

// Insert a element into Binary Tree (Assuming Binary Search tree)
Node *InsertElement(Node *root, int value)
{
    Node *ptr = (Node *)malloc(sizeof(Node));
    if (ptr == NULL)
    {
        printf("Memory Error.\n");
        return NULL;
    }
    ptr->data = value;
    ptr->right = ptr->left = NULL;

    if (root == NULL)
    {
        root = ptr;
    }
    else
    {
        if (value <= root->data)
        {
            root->left = InsertElement(root->left, value);
        }
        else
        {
            root->right = InsertElement(root->right, value);
        }
    }
    return root;
}

// Preorder Traversal Algorithm using Recursion
void PreorderTraversalRecursive(Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    PreorderTraversalRecursive(root->left);
    PreorderTraversalRecursive(root->right);
}

// Preorder Traversal Algorithm using Iteration
void PreorderTraversalIterative(Node *root)
{
    Stack *stack = InitializeStack(100);
    while (1)
    {
        while (root)
        {
            printf("%d ", root->data);
            StackPush(stack, root);
            root = root->left;
        }
        if (IsStackEmpty(stack))
            break;
        root = StackTop(stack);
        StackPop(stack);
        root = root->right;
    }
    DestroyStack(&stack);
}

int main()
{
    Node *root = NULL;
    root = InsertElement(root, 4);
    root = InsertElement(root, 2);
    root = InsertElement(root, 7);
    root = InsertElement(root, 5);
    root = InsertElement(root, 3);
    root = InsertElement(root, 1);
    PreorderTraversalIterative(root);
    return 0;
}