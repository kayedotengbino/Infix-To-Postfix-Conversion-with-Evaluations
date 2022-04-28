#include <stdio.h>
#include <stdlib.h>
#include "InfixToPostfix.h"

int main()
{
	int choice, x, y, retVal, a, b, flag, spaces;
	stackItem infix[10];
	char postfix[10];
	Stack postfixString = newStack();
	Stack evalPostfix = newStack();
	
	do
	{
		flag = 0;
		
		system("cls");
		
		printf("infix to postfix conversion\n");
		printf("Infix String : ");
		scanf(" %[^\n]s", &infix);
		
		//Infix to Postfix Conversion
		for(x = 0, y = 0; infix[x]; x++)
		{
			if(infix[x] == ' ')
			{
				printf("\nCould not convert strings that contains space(s) in between.");
				flag = 1;
				break;
			}
			//operand, add it to the postfix string
			else if(isalnum(infix[x]))
				postfix[y++] = infix[x];	//	printf("alphanumeric");
			else
			{
				//operator
				if(theOperator(infix[x])) 	//	printf("operator");	
				{
			
					//stack is empty
					if(isEmpty(postfixString)) 	//	printf("pushed");	
						push(postfixString, infix[x]);
						
					//non-empty stack
					else
					{
						//char is higher precedence
						if(precedence(topStack(postfixString)) < precedence(infix[x]))
							push(postfixString, infix[x]);	
						
						//top is higher precedence
						else
						{
							while(!isEmpty(postfixString) && precedence(topStack(postfixString)) >= precedence(infix[x]))
							{
								postfix[y++] = topStack(postfixString);
								pop(postfixString);
							}
							push(postfixString, infix[x]);	
						}
					}
				} 
					
			}
		}
		
		//unscanned characters
		while(!isEmpty(postfixString))
		{
			postfix[y++] = topStack(postfixString);
			pop(postfixString);
		}
		
		if(flag != 1)
		{
			postfix[y++] = '\0';
			printf("Postfix String : %s", postfix);
		}
		
		//Postfix Evaluation
		for(x = 0; postfix[x] != '\0'; x++)
		{
			//operand
			if(isdigit(postfix[x]))
				push(evalPostfix, postfix[x] - '0');
			else if(isalnum(postfix[x]) || postfix[x] == ' ')
			{
				printf("\nCould not evaluate strings that contains non-integer.");
				flag = 1;
				break;
			}
			else
			{
				//must have 2 or more operands
				a = pop(evalPostfix);
				b = pop(evalPostfix);
					
				retVal = postfixEvaluation(b, a, postfix[x]);
				push(evalPostfix, retVal);
			}
		}

		if(flag != 1)
		{
			printf("\n\npostfix evaluation\n");
			display(evalPostfix);	
		}
		
		freeStack(evalPostfix);
		
		printf("\nTest more? (1 = Yes | 0 = No): ");
		scanf("%d", &choice);
	}
	while(choice == 1);
	
	return 0;
}
