#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
void CountingSort(int *, int);
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

// Function to sort array using Counting Sort Algorithm
void CountingSort(int *arr, int size)
{
	int k = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] >= 0)
		{
			if (arr[i] > k)
				k = arr[i];
		}
		else
		{
			printf("Counting sort can not be applied here.\n");
			return;
		}
	}
	k++;
	int c[k], b[size];
	for (int i = 0; i < k; i++)
		c[i] = 0;
	for (int i = 0; i < size; i++)
		c[arr[i]]++;
	for (int i = 1; i < k; i++)
		c[i] = c[i] + c[i - 1];
	for (int i = size - 1; i >= 0; i--)
	{
		b[c[arr[i]] - 1] = arr[i];
		c[arr[i]]--;
	}
	for (int i = 0; i < size; i++)
		arr[i] = b[i];
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
				printf("Counting Sort can not be applied here.\n");
				return 0;
			}
		}
        CountingSort(arr, size);
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
