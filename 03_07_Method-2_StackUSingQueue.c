#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure of node in Linked List
struct ListNode
{
    int data;
    struct ListNode *next;
};

// Structure of Circular Queue
typedef struct
{
    struct ListNode *front;
    struct ListNode *rear;
} Queue;

// Function to initialize/create a queue
Queue *CreateQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (!queue)
    {
        printf("Memory Error\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Check whether the queue is empty or not
bool IsEmptyQueue(Queue *q)
{
    if (q->rear == NULL)
        return true;
    else
        return false;
}

// Function to insert element in queue
void EnQueue(Queue *q, int data)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!newNode)
    {
        printf("Memmory Error.\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;
    if (q->rear)
        q->rear->next = newNode;
    q->rear = newNode;
    if (q->front == NULL)
        q->front = q->rear;
}

// Function to remove element from queue
void DeQueue(Queue *q)
{
    if (IsEmptyQueue(q))
    {
        printf("Queue is Empty.\n");
    }
    else
    {
        struct ListNode *temp = q->front;
        q->front = q->front->next;
        if (q->front == NULL)
            q->rear = NULL;
        free(temp);
    }
}

// Function to print the entire queue
void PrintQueue(Queue *q)
{
    printf("Queue's contents are : ");
    struct ListNode *temp = q->front;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Structure of Stack
typedef struct
{
    Queue *q1, *q2;
} Stack;

// Create Stack
Stack *CreateStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->q1 = CreateQueue(stack->q1);
    stack->q2 = CreateQueue(stack->q2);
    return stack;
}

// Pushing a element into stack | O(n)
void PushStack(Stack *s, int data)
{
    EnQueue(s->q1, data);
}

// Popping a element from stack | O(1)
void PopStack(Stack *s)
{
    if (IsEmptyQueue(s->q1))
    {
        printf("Stack is empty\n");
        return;
    }
    while (s->q1->front->next)
    {
        EnQueue(s->q2, s->q1->front->data);
        DeQueue(s->q1);
    }
    DeQueue(s->q1);
    Queue *temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

// Print Entire Stack
void PrintStack(Stack *s)
{
    PrintQueue(s->q1);
}

int main()
{
    Stack *stack = CreateStack();
    PushStack(stack, 3);
    PushStack(stack, 5);
    PrintStack(stack);
    PopStack(stack);
    PrintStack(stack);
    return 0;
}