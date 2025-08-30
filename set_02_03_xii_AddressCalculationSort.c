#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
bool IsSortedArray(int *, int);
void AddressCalculationSort(int*,int);

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
}

// Address Calculation Sort
void AddressCalculationSort(int *arr, int size)
{
    int min = arr[0], max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min)
            min = arr[i];
        if (arr[i] > max)
            max = arr[i];
    }

    int range = max - min + 1;
    int bucket[range];
    for (int i = 0; i < range; i++) bucket[i] = 0;
    for (int i = 0; i < size; i++)
    {
        bucket[arr[i] - min]++;
    }
    int index = 0;
    for (int i = 0; i < range; i++)
    {
        while (bucket[i] > 0)
        {
            arr[index++] = i + min;
            bucket[i]--;
        }
    }
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
                printf("Address Calculation Sort can not be applied here.\n");
                return 0;
            }
        }
        AddressCalculationSort(arr, size);
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
