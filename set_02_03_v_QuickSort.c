#include <stdio.h>
#include <stdbool.h>

void PrintArray(int *, int);
int Parition(int*,int,int);
void Swap(int*,int*);
void QuickSort(int *, int,int);
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

// Function to sort array using Quick Sort Algorithm
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(int *arr, int low, int high)
{
	int pivot = arr[low];
	int start = low + 1;
	int end = high;
	do
	{
		while (arr[start] <= pivot)
		{
			start++;
		}
		while (arr[end] > pivot)
		{
			end--;
		}
		if (start < end)
			Swap(&arr[start], &arr[end]);
	} while (start < end);
	Swap(&arr[low], &arr[end]);
	return end;
}

void QuickSort(int *arr, int start, int end)
{
	if (start < end)
	{
		int loc = Partition(arr, start, end);
		QuickSort(arr, start, loc - 1);
		QuickSort(arr, loc + 1, end);
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
       QuickSort(arr,0,size-1);
        printf("-----After Sorting-----\n");
        PrintArray(arr,size);
    }
    else printf("The array is Sorted.\n");
    return 0;
}