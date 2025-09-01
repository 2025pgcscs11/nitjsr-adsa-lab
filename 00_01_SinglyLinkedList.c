#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// structure of a node in the list
typedef struct list
{
	int data;
	struct list *next;
} node;

// Function to inserting a value in list at the end
node *insertion_back(node *head)
{
	int value;
	printf("\nEnter a Value: ");
	scanf("%d", &value);
	node *temp = (node *)malloc(sizeof(node));
	temp->data = value;
	temp->next = NULL;
	if (head == NULL)
		return temp;
	else
	{
		node *dump = head;
		while (dump->next != NULL)
		{
			dump = dump->next;
		}
		dump->next = temp;
		return head;
	}
}

// Function to delete a node from front of the list
node *deletion_front(node *head)
{
	if (head == NULL)
	{
		printf("Nothing to delete!\n");
		return NULL;
	}
	node *temp = head;
	head = head->next;
	free(temp);
	return head;
}

// Function to search a element in the list
void searching(node *head)
{
	int value, index = 0;
	printf("Enter the Searching Value: ");
	scanf("%d", &value);
	node *temp = head;
	while (temp != NULL)
	{
		if (temp->data == value)
		{
			printf("The Value %d is first found at index %d in the Linked List.\n", value, index);
			return;
		}
		temp = temp->next;
		index++;
	}
	printf("This Value is not present in the Linked List.\n");
}

// Print the whole list 
void traversal(node *head)
{
	printf("\nLinked List Traversal from Left to Right: ");
	node *temp = head;
	while (temp != NULL)
	{
		printf("%d  ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}


// Main function to control various  operation on the list using a console interface
int main()
{
	node *head = NULL;
	while (true)
	{
		int choice;
		printf("**************************************************************************************\n");
		printf("Singly Linked List is initialized & User can perform below opertions\n");
		printf("======================================================================================\n");
		printf("\n1.For Insertion.\n2.For Deletion.\n3.For Searching.\n4.For Traversal.\n5.For Exit.\n\n");
		printf("Enter Your Choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			head = insertion_back(head);
			break;
		case 2:
			head = deletion_front(head);
			break;
		case 3:
			searching(head);
			break;
		case 4:
			if (head != NULL)
				traversal(head);
			else
				printf("Nothing to print!\n");
			break;
		case 5:
			printf("!!!Program Ended!!!\n");
			exit(0);
		default:
			printf("Invalid Choice\n");
			break;
		}
		printf("*********************************!!!Operation End!!!**********************************\n\n\n");
	}
	return 0;
}
