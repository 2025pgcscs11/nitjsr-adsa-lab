#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
int partition(int *, int, int, int);
int getMaxBit(int *, int);
void RadixExchangeSort(int *, int, int, int);
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

// Function to partition array by the given bit position
int partition(int *arr, int low, int high, int bit)
{
    int i = low, j = high;
    while (i <= j)
    {
        while (i <= j && ((arr[i] >> bit) & 1) == 0)
        {
            i++;
        }
        while (i <= j && ((arr[j] >> bit) & 1) == 1)
        {
            j--;
        }
        if (i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

// Recursive Radix Exchange Sort
void RadixExchangeSort(int *arr, int low, int high, int bit)
{
    if (low >= high || bit < 0)
        return;

    int mid = partition(arr, low, high, bit);

    RadixExchangeSort(arr, low, mid - 1, bit - 1);
    RadixExchangeSort(arr, mid, high, bit - 1);
}

//  function to find the most significant bit position
int getMaxBit(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    int bit = 0;
    while (max > 0)
    {
        max >>= 1;
        bit++;
    }
    return bit - 1;
}

int main()
{
    int size;
    bool isSort;
    printf("Enter the size of the array: ", size);
    scanf("%d", &size);
    int arr[size];
    printf("Enter the element of the array(Non-Negative Integer): ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    PrintArray(arr, size);
    isSort = IsSortedArray(arr, size);
    if (!isSort)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] < 0)
            {
                printf("Radix Exchange Sort can not be applied here.\n");
                return 0;
            }
        }
        int maxBit = getMaxBit(arr, size);
        RadixExchangeSort(arr, 0, size - 1, maxBit);
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