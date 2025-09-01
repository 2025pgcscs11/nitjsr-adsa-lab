#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
void SelectionSort(int *, int);
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

// Function to sort array using Selection Sort Algorithm
void SelectionSort(int *arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		int temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
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
        SelectionSort(arr,size);
        printf("-----After Sorting-----\n");
        PrintArray(arr,size);
    }
    else printf("The array is Sorted.\n");
    return 0;
}