#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void PrintArray(int *, int);
bool IsSortedArray(int *, int);
void merge(int*,int,int,int);
void MergeSortUsingIteration(int*,int);

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

// Merge Function
void merge(int *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// Bottom-Up Merge Sort
void MergeSortUsingIteration(int* arr, int size)
{
    for (int curr_size = 1; curr_size < size; curr_size *= 2)
    {
        for (int left_start = 0; left_start < size - 1; left_start += 2 * curr_size)
        {
            int mid = left_start + curr_size - 1;
            int right_end = (left_start + 2 * curr_size - 1 < size - 1)
                                ? (left_start + 2 * curr_size - 1)
                                : (size - 1);

            if (mid < right_end)
                merge(arr, left_start, mid, right_end);
        }
    }
}

// Main Function
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
        MergeSortUsingIteration(arr, size);
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
