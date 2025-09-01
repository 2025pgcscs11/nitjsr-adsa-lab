#include <stdio.h>

int main()
{
	int row_size, col_size, row, col, value;
	printf("Enter the row size of the 2D array: ");
	scanf("%d", &row_size);
	printf("Enter the column size of the 2D array: ");
	scanf("%d", &col_size);

	int arr[row_size][col_size];
	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			arr[i][j] = 0;
		}
	}
	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			printf("%d  ", arr[i][j]);
		}
		printf("\n");
	}
	while (1)
	{
		printf("Enter Row(1- %d): ", row_size);
		scanf("%d", &row);
		if (row <= 0 || row > row_size)
			printf("Invalid Row\n");
		else
			break;
	}
	while (1)
	{
		printf("Enter Column(1- %d): ", col_size);
		scanf("%d", &col);
		if (col <= 0 || col > col_size)
			printf("Invalid Column\n");
		else
			break;
	}
	printf("Enter Value: ");
	scanf("%d", &value);
	arr[row - 1][col - 1] = value;
	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			printf("%d  ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
