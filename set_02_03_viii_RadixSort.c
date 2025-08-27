#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
void RadixSort(int *, int);
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

// Function to sort array using Radix Sort Algorithm
void RadixSort(int *arr, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] >= 0)
        {
            if (arr[i] > max)
                max = arr[i];
        }
        else
        {
            printf("Radix Sort can not be applied here.\n");
            return;
        }
    }

    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        int count[10] = {0};
        int b[size];
        for (int i = 0; i < size; i++)
            count[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        for (int i = size - 1; i >= 0; i--)
        {
            int digit = (arr[i] / exp) % 10;
            b[count[digit] - 1] = arr[i];
            count[digit]--;
        }
        for (int i = 0; i < size; i++)
            arr[i] = b[i];
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
			if (arr[i] >= 0)
			{
				printf("Radix Sort can not be applied here.\n");
				return 0;
			}
		}
        RadixSort(arr, size);
        printf("-----After Sorting-----\n");
        if(IsSortedArray(arr,size)){
            PrintArray(arr, size);
        }
        else{
            printf("The Sorting Algorithm is failed.\n");
        }
    }
    else
        printf("The array is Sorted.\n");
    return 0;
}
