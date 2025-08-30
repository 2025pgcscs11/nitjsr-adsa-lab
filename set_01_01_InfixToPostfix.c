#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	int top;
	int size;
	char *arr;
} Stack;

// Initializing Stack with a user-given size
Stack *InitializeStack(int size)
{
	Stack *st = (Stack *)malloc(sizeof(Stack));
	st->top = -1;
	st->size = size;
	st->arr = (char *)malloc(size * sizeof(char));
	return st;
}

// Checking whether the stack is empty or not
bool IsStackEmpty(Stack *s)
{
	if (s->top == -1)
		return true;
	else
		return false;
}

// Checking whether the stack is full or not
bool IsStackFull(Stack *s)
{
	if (s->top == s->size - 1)
		return true;
	else
		false;
}

// Fetching the top value of stack
char StackTop(Stack *s)
{
	return s->arr[s->top];
}

// Pusing a element into stack
void StackPush(Stack *s, char data)
{
	if (s->top < s->size - 1)
		s->arr[++s->top] = data;
	else
		printf("Stack is Full.");
}

// Popping a element from the stack
void StackPop(Stack *s)
{
	if (s->top > -1)
		s->top--;
	else
		printf("Stack is Empty.");
}

// Printing all the stack's element
void PrintStack(Stack *s)
{
	for (int i = s->top; i >= 0; i--)
	{
		printf("%c ", s->arr[i]);
	}
	printf("\n");
}

// Checking whether a character is operator or not
bool IsOperator(char ch)
{
	if (ch == '/' || ch == '*' || ch == '+' || ch == '-')
		return true;
	else
		return false;
}

// Ordering custom operators with value according to precedence
int PrecedenceValue(char ch)
{
	if (ch == '/')
		return 4;
	else if (ch == '*')
		return 3;
	else if (ch == '+')
		return 2;
	else if (ch == '-')
		return 1;
	else
		return -1;
}

// Function Converting a Infix Expression into Postfix Expression
void ConvertInfixToPostfix(char *str, char *res)
{
	int index = 0;
	Stack *st = InitializeStack(strlen(str));

	while (*str != '\0')
	{
		if (!IsOperator(*str) && *str != '(' && *str != ')')
		{
			res[index++] = *str;
		}
		else if (*str == '(')
		{
			StackPush(st, *str);
		}
		else if (*str == ')')
		{
			while (StackTop(st) != '(')
			{
				res[index++] = StackTop(st);
				StackPop(st);
			}
			StackPop(st);
		}
		else
		{
			while (!IsStackEmpty(st) && PrecedenceValue(*str) < PrecedenceValue(StackTop(st)))
			{
				res[index++] = StackTop(st);
				StackPop(st);
			}
			StackPush(st, *str);
		}
		str++;
	}
	while (!IsStackEmpty(st))
	{
		res[index++] = StackTop(st);
		StackPop(st);
	}
	res[index] = '\0';
}

int main()
{
	char str[100];
	printf("Enter the Infix Expression: ");
	scanf("%s", str);
	char res[strlen(str)];
	ConvertInfixToPostfix(str, res);
	printf("The Postfix Conversion of the Infix Expression %s is %s\n", str, res);
	return 0;
}