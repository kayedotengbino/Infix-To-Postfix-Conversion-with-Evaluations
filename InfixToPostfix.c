#include <stdio.h>
#include <stdlib.h>
#include "InfixToPostfix.h"

Stack newStack()
{
	Stack s = (Stack)malloc(sizeof(STACK_HEAD));
	s->count = 0;
	s->top = NULL;
	
	return s;
}

Nodeptr createNode(char item)
{
	Nodeptr ptr = (Nodeptr)malloc(sizeof(STACK_NODE));
	ptr->data = item;
	ptr->next = NULL;
	
	return ptr;
}

stackItem topStack(Stack s)
{
	return s->top->data;
}

stackItem pop(Stack s)
{
	Nodeptr ptr = s->top;
	stackItem item = ptr->data;
	
	s->top = ptr->next;
	ptr = NULL;
	free(ptr);
	s->count--;
	
	return item;
}

int theOperator(char item)
{
	return (item == '+' || item == '-' || item == '*' || item == '/');
}

int isEmpty(Stack s)
{
	return s->top == NULL, s->count == 0;
}

void push(Stack s, stackItem item)
{
	Nodeptr ptr = createNode(item);
	
	ptr->next = s->top;
	s->top = ptr;
	s->count++;
}

int precedence(char item)
{
	int val = 0;
	
	switch(item)
	{
		case '+': 
		case '-': 
			val = 1;
			break;
		case '*': 
		case '/': 
			val = 2;
			break;
		default: 
			val = 0;
			break;
	}
	
	return val;
}

int postfixEvaluation(int a, int b, int postfix)
{
	int result = 0;
	
	switch(postfix)
	{
		case '+':
			result = a + b;
			break;
		case '-':
			result = a - b;
			break;
		case '*':
			result = a * b;
			break;
		case '/':
			result = a / b;
			break;
	}
	
	return result;
}

void display(Stack s)
{
    Nodeptr ptr = s->top;
    
	if (!isEmpty(s))
    {
        printf("Result : ");
        while (ptr != NULL)
        {
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
    }
    printf("\n");
}

void freeStack(Stack s)
{
	Nodeptr ptr = s->top;
	Nodeptr temp = ptr;
	
	while(ptr != NULL)
	{
		ptr = ptr->next;
		ptr = NULL;
		free(temp);
	}
	
	s->top = ptr;
	s->count = 0;
}
