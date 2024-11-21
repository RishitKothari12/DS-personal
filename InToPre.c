#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct stack {
    int top;
    char arr[MAX];
};

void initstack(struct stack* s1) {
    s1->top = -1;
}

int isempty(struct stack* s1) {
    return (s1->top == -1);
}

int isfull(struct stack* s1) {
    return s1->top == MAX - 1;
}

void push(struct stack* s1, char data) {
    if (isfull(s1)) {
        printf("Stack is full\n");
        exit(1);
    } else {
        s1->arr[++(s1->top)] = data;
    }
}

char pop(struct stack* s1) {
    if (isempty(s1)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s1->arr[(s1->top)--];
}

char peek(struct stack* s1) {
    if (isempty(s1)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s1->arr[s1->top];
}

int isoperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;  // Higher precedence for exponentiation
    return 0;
}

void reverse_expression(char expr[]) {
    int len = strlen(expr);
    for (int i = 0; i < len / 2; i++) {
        char temp = expr[i];
        expr[i] = expr[len - i - 1];
        expr[len - i - 1] = temp;
    }
}

void infix_to_prefix(char infix[], char prefix[]) {
    struct stack* s1 = (struct stack*)malloc(sizeof(struct stack));
    initstack(s1);

    // Step 1: Reverse the infix expression and adjust parentheses
    reverse_expression(infix);
    for (int i = 0; i < strlen(infix); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    // Step 2: Convert the reversed infix expression to postfix
    char postfix[MAX];
    int i = 0, j = 0;
    char ch;
    for (i = 0; i < strlen(infix); i++) {
        ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(s1, ch);
        } else if (ch == ')') {
            while (!isempty(s1) && peek(s1) != '(') {
                postfix[j++] = pop(s1);
            }
            pop(s1);  // Remove '(' from stack
        } else if (isoperator(ch)) {
            while (!isempty(s1) && precedence(peek(s1)) >= precedence(ch)) {
                postfix[j++] = pop(s1);
            }
            push(s1, ch);
        }
    }
    while (!isempty(s1)) {
        postfix[j++] = pop(s1);
    }
    postfix[j] = '\0';

    // Step 3: Reverse the postfix expression to get prefix
    strcpy(prefix, postfix);
    reverse_expression(prefix);

    free(s1);  // Free allocated memory
}

int main() {
    char infix[MAX], prefix[MAX];
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    infix_to_prefix(infix, prefix);
    printf("Prefix Expression: %s\n", prefix);

    return 0;
}
