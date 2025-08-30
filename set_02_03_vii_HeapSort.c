#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// structure of the heap node
struct Heap
{
    int *array;
    int count;
    int capacity;
    int heap_type;
};

void PrintArray(int *, int);
struct Heap *CreateHeap(int, int);
int Parent(struct Heap *, int);
int LeftChild(struct Heap *, int);
int RightChild(struct Heap *, int);
int GetMaximum(struct Heap *);
void PercolateDown(struct Heap *, int);
int DeleteMax(struct Heap *);
void BuildHeap(struct Heap *, int *, int);
void ResizeHeap(struct Heap *);
void Insert(struct Heap *, int);
void DestroyHeap(struct Heap *);
void HeapSort(int *, int);
bool IsSortedArray(int *, int);

// Function to Print the entire array
void PrintArray(int *arr, int size)
{
    printf("The elements of the array are: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to check whether the array is sorted in ascending or descending order or not
bool IsSortedArray(int *arr, int size)
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

// Initialize heap
struct Heap *CreateHeap(int capacity, int heap_type)
{
    struct Heap *h = (struct Heap *)malloc(sizeof(struct Heap));
    if (h == NULL)
    {
        printf("Memory Error.\n");
        return NULL;
    }
    h->heap_type = heap_type;
    h->count = 0;
    h->capacity = capacity;
    h->array = (int *)malloc(sizeof(int) * h->capacity);
    if (h->array == NULL)
    {
        printf("Memory Error.\n");
        return NULL;
    }
    return h;
}

// Return parent of a node
int Parent(struct Heap *h, int i)
{
    if (i <= 0 || i >= h->count)
        return -1;
    return (i - 1) / 2;
}

// Return left child of a node
int LeftChild(struct Heap *h, int i)
{
    int left = 2 * i + 1;
    if (left >= h->count)
        return -1;
    return left;
}

// Return right child of a node
int RightChild(struct Heap *h, int i)
{
    int right = 2 * i + 2;
    if (right >= h->count)
        return -1;
    return right;
}

// Return maximum element
int GetMaximum(struct Heap *h)
{
    if (h->count == 0)
        return -1;
    return h->array[0];
}

// Heapify the element at loction i
void PercolateDown(struct Heap *h, int i)
{
    int l, r, max, temp;
    l = LeftChild(h, i);
    r = RightChild(h, i);
    if (l != -1 && h->array[l] > h->array[i])
        max = l;
    else
        max = i;
    if (r != -1 && h->array[r] > h->array[max])
        max = r;
    if (max != i)
    {
        temp = h->array[i];
        h->array[i] = h->array[max];
        h->array[max] = temp;
        PercolateDown(h, max);
    }
}

// Delete  root element of a heap
int DeleteMax(struct Heap *h)
{
    int data;
    if (h->count == 0)
        return -1;
    data = h->array[0];
    h->array[0] = h->array[h->count - 1];
    h->count--;
    PercolateDown(h, 0);
    return data;
}

// Resize the heap size to double
void ResizeHeap(struct Heap *h)
{
    int *array_old = h->array;
    h->array = (int *)malloc(sizeof(int) * h->capacity * 2);
    if (h->array == NULL)
    {
        printf("Memmory Error.\n");
        return;
    }
    for (int i = 0; i < h->capacity; i++)
        h->array[i] = array_old[i];
    h->capacity *= 2;
    free(array_old);
}

// Insert data in the heap
void Insert(struct Heap *h, int data)
{
    int i;
    if (h->count == h->capacity)
        ResizeHeap(h);
    h->count++;
    i = h->count - 1;
    while (i > 0 && data > h->array[(i - 1) / 2])
    {
        h->array[i] = h->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->array[i] = data;
}

// Destroy  the heap
void DestroyHeap(struct Heap *h)
{
    if (h == NULL)
        return;
    free(h->array);
    free(h);
    h = NULL;
}

// Build a max heap from a array
void BuildHeap(struct Heap *h, int *arr, int size)
{
    if (h == NULL)
        return;
    while (size > h->capacity)
        ResizeHeap(h);
    for (int i = 0; i < size; i++)
        h->array[i] = arr[i];
    h->count = size;
    for (int i = (size - 1) / 2; i >= 0; i--)
        PercolateDown(h, i);
}

// Heap sort function
void HeapSort(int *arr, int size)
{
    struct Heap *h = CreateHeap(size, 1);
    int old_size, i, temp;
    BuildHeap(h, arr, size);
    old_size = h->count;
    for (int i = size - 1; i > 0; i--)
    {
        temp = h->array[0];
        h->array[0] = h->array[h->count - 1];
        h->array[h->count - 1] = temp;
        h->count--;
        PercolateDown(h, 0);
    }
    h->count = old_size;
    for (int i = 0; i < size; i++)
        arr[i] = h->array[i];
    DestroyHeap(h);
}

int main()
{
    int size;
    bool isSort;
    printf("Enter the size of the array: ", size);
    scanf("%d", &size);
    int arr[size];
    printf("Enter the element of the array(Integer): ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    PrintArray(arr, size);
    isSort = IsSortedArray(arr, size);
    if (!isSort)
    {
        HeapSort(arr, size);
        if (IsSortedArray(arr, size))
        {
            printf("<===============After Sorting===============>\n");
            PrintArray(arr, size);
        }
        else
            printf("The Sorting algorithm is failed!\n");
    }
    else
        printf("The array is Sorted.\n");
    return 0;
}