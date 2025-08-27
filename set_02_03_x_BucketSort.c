#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LL
{
    float data;
    struct LL *next;
    struct LL *prev;
} node;

node *LinkedListInsert(node *list, float d)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->data = d;

    if (list == NULL)
        list = new_node;
    else
    {
        node *temp = list;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = new_node;
        new_node->prev = temp;
    }

    return list;
}

void ShowLinkedList(node *list)
{
    node *temp = list;
    while (temp != NULL)
    {
        printf("%0.2f->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

node *DeleteStart(node *list, float *d)
{
    node *temp = list;
    list = list->next;

    if (list != NULL && list->prev != NULL)
        list->prev = NULL;

    *d = temp->data;
    free(temp);

    return list;
}

// Function to sort array using Quick Sort Algorithm
void Swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

node *LinkedListInsertionSort(node *list)
{
    if (list != NULL)
    {
        node *ahead = list->next;

        while (ahead != NULL)
        {
            node *rev = ahead;

            while (rev->prev != NULL && rev->prev->data > rev->data)
            {
                Swap(&(rev->data), &(rev->prev->data));
                rev = rev->prev;
            }
            ahead = ahead->next;
        }
        return list;
    }
    return NULL;
}

void BucketSort(float *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < 0 || arr[i] >= 1)
        {
            printf("Bucket Sort can not be applied here.\n");
            return;
        }
    }
    node *bins[size];
    for (int i = 0; i < size; i++)
        bins[i] = NULL;
    int pos = 0;
    for (int i = 0; i < size; i++)
    {
        pos = size * arr[i];
        bins[pos] = LinkedListInsert(bins[pos], arr[i]);
    }

    for (int i = 0; i < size; i++)
        bins[i] = LinkedListInsertionSort(bins[i]);
    pos = 0;
    float temp;
    for (int i = 0; i < size; i++)
    {
        while (bins[i] != NULL)
        {
            bins[i] = DeleteStart(bins[i], &temp);
            arr[pos] = temp;
            pos++;
        }
    }
}

// Function to check whether the array is sorted in ascending or descending order or not
bool IsSortedArray(float *arr, int size)
{
    if (size <= 1)
        return true;

    bool ascending = true, descending = true;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[i - 1])
            ascending = false;
        if (arr[i] > arr[i - 1])
            descending = false;
    }
    return ascending || descending;
}

// Function to Print the entire array
void PrintArray(float *arr, int size)
{
    printf("The elements of the array are: ");
    for (int i = 0; i < size; i++)
    {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int size;
    bool isSort;
    printf("Enter the size of the array: ", size);
    scanf("%d", &size);
    float arr[size];
    printf("Enter the element of the array[0,1)] : ");
    for (int i = 0; i < size; i++)
    {
        scanf("%f", &arr[i]);
    }
    PrintArray(arr, size);
    isSort = IsSortedArray(arr, size);
    if (!isSort)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] < 0 || arr[i] >= 1)
            {
                printf("Bucket Sort can not be applied here.\n");
                return 0;
            }
        }
        BucketSort(arr, size);
        if (IsSortedArray(arr, size))
        {
            printf("<===============After Sorting===============>");
            PrintArray(arr, size);
        }
        else
            printf("The Sorting algorithm is failed!\n");
    }
    else
        printf("The Array is sorted.\n");

    return 0;
}
