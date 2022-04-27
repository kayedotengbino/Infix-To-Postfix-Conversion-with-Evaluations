#include <stdio.h>
#include <stdlib.h>
#include "InfixToPostfix.h"

int main()
{
	int choice, x, y, retVal, a, b;
	stackItem infix[10];
	char postfix[10];
	Stack postfixString = newStack();
	Stack evalPostfix = newStack();
	
	do
	{
		system("cls");
		
		printf("infix to postfix conversion\n");
		printf("Infix String : ");
		scanf("%s", &infix);
		
		//Infix to Postfix Conversion
		for(x = 0, y = 0; infix[x]; x++)
		{
			//operand, add it to the postfix string
			if(isalnum(infix[x]))
				postfix[y++] = infix[x];	//	printf("alphanumeric");
			
			else
			{
				//operator
				if(theOperator(infix[x])) 	//	printf("operator");	
				{
			
					//stack is empty
					if(isEmpty(postfixString))	//	printf("pushed");	
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
		
		postfix[y++] = '\0';
		printf("Postfix String : %s", postfix);
		
		//Postfix Evaluation
		for(x = 0; postfix[x] != '\0'; x++)
		{
			//operand
			if(isalnum(postfix[x]))
				push(evalPostfix, postfix[x] - '0');
			else
			{
				//must have 2 or more operands
				a = pop(evalPostfix);
				b = pop(evalPostfix);
				
				retVal = postfixEvaluation(b, a, postfix[x]);
				push(evalPostfix, retVal);
			}
		}
		
		printf("\n\npostfix evaluation\n");
		display(evalPostfix);
		
		freeStack(evalPostfix);
		
		printf("\nTest more? (1 = Yes | 0 = No): ");
		scanf("%d", &choice);
	}
	while(choice == 1);
	
	return 0;
}
