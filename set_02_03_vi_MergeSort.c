#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
void MergeSort(int *,int, int);
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

// Function to sort array using Merge Sort Algorithm
void MergeSort(int *arr, int start, int end)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	MergeSort(arr, start, mid);
	MergeSort(arr, mid + 1, end);
	int index = 0;
	int left = start, right = mid + 1;
	int temp[end - start + 1];
	while (left <= mid && right <= end)
	{
		if (arr[left] <= arr[right])
		{
			temp[index++] = arr[left++];
		}
		else
		{
			temp[index++] = arr[right++];
		}
	}

	while (left <= mid)
	{
		temp[index++] = arr[left++];
	}
	while (right <= end)
	{
		temp[index++] = arr[right++];
	}
	for (int i = 0; i < (end - start + 1); i++)
	{
		arr[start + i] = temp[i];
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
        MergeSort(arr,0,size-1);
        printf("-----After Sorting-----\n");
        PrintArray(arr,size);
    }
    else printf("The array is Sorted.\n");
    return 0;
}