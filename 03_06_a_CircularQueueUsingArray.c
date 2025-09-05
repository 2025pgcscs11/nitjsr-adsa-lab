#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// structure of Circular Queue
struct CircularQueue
{
    int front, rear;
    int capacity;
    int *array;
};

// Function to initialize/create a queue
struct CircularQueue *CreateQueue(int capacity)
{
    struct CircularQueue *queue = (struct CircularQueue *)malloc(sizeof(struct CircularQueue));
    if (!queue)
    {
        printf("Memory Error\n");
        return NULL;
    }
    queue->capacity = capacity;
    queue->front = -1;
    queue->rear = -1;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    if (!queue->array)
    {
        printf("Memory Error\n");
        return NULL;
    }
    return queue;
}

// Check whether the queue is empty or not
bool IsEmptyQueue(struct CircularQueue *q)
{
    if (q->rear == -1)
        return true;
    else
        return false;
}

// Check whether the queue is full or not
bool IsFullQueue(struct CircularQueue *q)
{
    if ((q->rear + 1) % q->capacity == q->front)
        return true;
    else
        return false;
}

// Function to insert element in queue
void EnQueue(struct CircularQueue *q, int data)
{
    if (IsFullQueue(q))
    {
        printf("Queue is Full.\n");
    }
    else
    {
        q->rear = (q->rear + 1) % q->capacity;
        q->array[q->rear] = data;
        if (q->front == -1)
            q->front = 0;
    }
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
        if (q->front == q->rear)
            q->front = q->rear = -1;
        else
            q->front = (q->front + 1) % q->capacity;
    }
}

// Function to destroy the entire queue's memory
void DestroyQueue(struct CircularQueue **q)
{
    if (*q)
    {
        free((*q)->array);
        free(*q);
        *q = NULL;
    }
}

// Function to print the entire queue
void PrintQueue(struct CircularQueue *q)
{
    printf("Queue's contents are : ");
    for (int i = q->front; i <= q->rear; i++)
    {
        printf("%d ", q->array[i]);
    }
    printf("\n");
}

// Driver Main function to control various operation on queue
int main()
{
    int capacity;
    printf("Enter the capacity of the Queue: ");
    scanf("%d", &capacity);
    struct CircularQueue *queue = CreateQueue(capacity);
    if (queue != NULL)
    {
        while (1)
        {
            int choice;
            int data;
            printf("###################################################################################################\n");
            printf("1.For Enqueue Operation.\n2.For Dequeue Operation.\n3.For Checking whether queue is empty or not.\n4.For Checking whether queue is full or not.\n5.For Queue's front element.\n6.For Printing the entire Queue.\n7.For Exit.\n");
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
                if (IsFullQueue(queue))
                    printf("Queue is Full/Overflow.\n");
                else
                    printf("Queue is not Full.\n");
                break;
            case 5:
                if (!IsEmptyQueue(queue))
                    printf("The front element of the Queue is : %d\n", queue->array[queue->front]);
                else
                    printf("Queue is Empty/Underflow.\n");
                break;
            case 6:
                if (!IsEmptyQueue(queue))
                {
                    PrintQueue(queue);
                }
                break;
            case 7:
                DestroyQueue(&queue);
                if (queue != NULL)
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