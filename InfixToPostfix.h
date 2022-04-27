typedef char stackItem;
typedef struct node* Nodeptr;

typedef struct
{
	int count;
	Nodeptr top;
}STACK_HEAD;

typedef STACK_HEAD* Stack;

typedef struct node
{
	stackItem data;
	Nodeptr next;
}STACK_NODE;

Stack newStack();
stackItem topStack(Stack s);
stackItem pop(Stack s);
int theOperator(char item);
int isEmpty(Stack s);
void push(Stack s, stackItem item);
int precedence(char item);
int evaluatePostfixString(int a, int b, int postfix);
void display(Stack s);

//additional function since program can be done on x times, depending on user
void freeStack(Stack s);
