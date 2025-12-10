#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure of Stack
typedef struct
{
    int top;
    int size;
    int *arr;
} Stack;

// Initializing Stack with a user-given size
Stack *InitializeStack(int size)
{
    Stack *st = (Stack *)malloc(sizeof(Stack));
    st->top = -1;
    st->size = size;
    st->arr = (int *)malloc(size * sizeof(int));
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
int StackTop(Stack *s)
{
    return s->arr[s->top];
}

// Pusing a element into stack
void StackPush(Stack *s, int data)
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

// Printing all the stack's element
void PrintStack(Stack *s)
{
    for (int i = s->top; i >= 0; i--)
    {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

// Structure of Queue
typedef struct
{
    Stack *s1, *s2;
} Queue;

// Create Queue using two stack
Queue *CreateQueue(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->s1 = InitializeStack(size);
    queue->s2 = InitializeStack(size);
    return queue;
}

// Insert element into queue | O(1) | This operation can not maintain the queue property
void EnQueue(Queue *q, int data)
{
    StackPush(q->s1, data);
}

// Remove a element from Queue | O(n)
void DeQueue(Queue *q)
{
    if (IsStackEmpty(q->s1) && IsStackEmpty(q->s2))
    {
        printf("Queue is Empty.\n");
        return;
    }
    if (IsStackEmpty(q->s2))
    {
        while (!IsStackEmpty(q->s1))
        {
            StackPush(q->s2, StackTop(q->s1));
            StackPop(q->s1);
        }
    }
    StackPop(q->s2);
    if (IsStackEmpty(q->s1))
    {
        while (!IsStackEmpty(q->s2))
        {
            StackPush(q->s1, StackTop(q->s2));
            StackPop(q->s2);
        }
    }
}

// Print the entire Queue
void PrintQueue(Queue *q)
{
    if (IsStackEmpty(q->s1) && IsStackEmpty(q->s2))
    {
        printf("Queue is Empty.\n");
        return;
    }
    while (!IsStackEmpty(q->s1))
    {
        StackPush(q->s2, StackTop(q->s1));
        StackPop(q->s1);
    }
    PrintStack(q->s2);
}

int main()
{
    Queue *queue = CreateQueue(10);
    EnQueue(queue, 3);
    EnQueue(queue, 4);
    EnQueue(queue, 10);
    EnQueue(queue, 5);
    PrintQueue(queue);
    DeQueue(queue);
    EnQueue(queue, 8);
    DeQueue(queue);
    PrintQueue(queue);
    return 0;
}