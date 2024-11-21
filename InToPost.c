#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
struct stack
{
    int top;
    int arr[MAX];
};

void initstack(struct stack* s1)
{
    s1->top = -1;
}

int isempty(struct stack* s1)
{
        return (s1->top == -1);
}

int isfull(struct stack* s1)
{
    return s1->top == MAX - 1;
}
void push(struct stack* s1,char data)
{
    if(isfull(s1))
    {
        printf("Stack is full\n");
        exit(1);
    }
    else
    {
        s1->arr[++(s1->top)] = data;
    }
}

char pop(struct stack* s1)
{
    if(isempty(s1))
    {
        printf("Stack is empty\n");
        exit(1);
    }
    else
    {
        return s1->arr[(s1->top)--];
    }
}

char peek(struct stack* s1)
{
    if(isempty(s1))
    {
        printf("Stack is empty\n");
    }
    else
    {
        return s1->arr[s1->top];
    }
}

int isoperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
    {
        return 1;
    }
}

int precedence(char ch)
{
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch == '/') return 2;
    if(ch == '^') return 3;
    return 0;
}

void infix_to_postfix(char infix[], char postfix[])
{
    
    struct stack* s1 = (struct stack*)malloc(sizeof(struct stack));
    int i = 0, j = 0;
    initstack(s1);
    char ch;

    for(i; i<strlen(infix); i++)
    {
        ch = infix[i];

        if(isalnum(ch))
        {
            postfix[j++] = ch;
        }
        else if(ch == '(')
        {
            push(s1, ch);
        }
        else if(ch == ')')
        {
            while(!isempty(s1) && peek(s1) != '(')
            {
                postfix[j++] = pop(s1);
            }
            pop(s1);
        }
        else if(isoperator(ch))
        {
            while(!isempty(s1) && precedence(peek(s1)) >= precedence(ch))
            {
                postfix[j++] = pop(s1);
            }
            push(s1, ch);
        }
    }
        while (!isempty(s1)) 
        {
            postfix[j++] = pop(s1);
        }
        postfix[j] = '\0';
}

int main()
{
    char infix[MAX], postfix[MAX];
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    infix_to_postfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    return 0;
}