#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
void InsertionSort(int *, int);
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

// Function to sort array using Insertion Sort Algorithm
void InsertionSort(int *arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int v = arr[i];
		int j = i;
		while (arr[j - 1] > v && j >= 1)
		{
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = v;
	}
}



int main(){
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
    if(!isSort) {
        InsertionSort(arr,size);
        printf("-----After Sorting-----\n");
        PrintArray(arr,size);
    }
    else printf("The array is Sorted.\n");
    return 0;
}