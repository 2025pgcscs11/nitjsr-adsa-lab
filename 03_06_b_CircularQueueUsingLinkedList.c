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
struct CircularQueue
{
    struct ListNode *front;
    struct ListNode *rear;
};

// Function to initialize/create a queue
struct CircularQueue *CreateQueue()
{
    struct CircularQueue *queue = (struct CircularQueue *)malloc(sizeof(struct CircularQueue));
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
bool IsEmptyQueue(struct CircularQueue *q)
{
    if (q->rear == NULL)
        return true;
    else
        return false;
}

// Function to insert element in queue
void EnQueue(struct CircularQueue *q, int data)
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
void DeQueue(struct CircularQueue *q)
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

// Function to destroy the entire queue's memory
void DestroyQueue(struct CircularQueue **q)
{
    struct ListNode *temp = NULL;
    while ((*q)->front != NULL)
    {
        temp = (*q)->front;
        (*q)->front = (*q)->front->next;
        free(temp);
    }
    (*q)->rear = NULL;
    free(*q);
    *q=NULL;
}

// Function to print the entire queue
void PrintQueue(struct CircularQueue *q)
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

// Driver Main function to control various operation on queue
int main()
{
    struct CircularQueue *queue = CreateQueue();
    if (queue != NULL)
    {
        printf("Linked List based Queue is initialized.\n");
        while (1)
        {
            int choice;
            int data;
            printf("###################################################################################################\n");
            printf("1.For Enqueue Operation.\n2.For Dequeue Operation.\n3.For Checking whether queue is empty or not.\n4.For Queue's front element.\n5.For Printing the entire Queue.\n6.For Exit.\n");
            printf("###################################################################################################\n");
            printf("Enter Choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                printf("Enter Data: ");
                scanf("%d", &data);
                EnQueue(queue, data);
                break;
            case 2:
                DeQueue(queue);
                break;
            case 3:
                if (IsEmptyQueue(queue))
                    printf("Queue is Empty/Underflow.\n");
                else
                    printf("Queue is not Empty.\n");
                break;
            case 4:
            if(!IsEmptyQueue(queue))
                printf("The front element of the Queue is : %d\n", queue->front->data);
                break;
            case 5:
                if (!IsEmptyQueue(queue))
                {
                    PrintQueue(queue);
                }
                break;
            case 6:
                DestroyQueue(&queue);
                if (queue)
                    printf("Queue is not destroyed.\n");
                else
                    printf("Queue is destroyed successfully.\n");
                exit(0);
                break;
            default:
                printf("Invalid Choice.\n");
                break;
            }
        }
    }
    return 0;
}