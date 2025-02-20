#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Stack Structure for Operators and Values
typedef struct {
    char arr[MAX];
    int top;
} Stack;

// Stack Functions
void push(Stack *s, char c) {
    if (s->top < MAX - 1)
        s->arr[++(s->top)] = c;
}

char pop(Stack *s) {
    return (s->top >= 0) ? s->arr[(s->top)--] : '\0';
}

char peek(Stack *s) {
    return (s->top >= 0) ? s->arr[s->top] : '\0';
}

// Function to Check Operator Precedence
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Convert Infix to Postfix
void infixToPostfix(char *infix, char *postfix) {
    Stack opStack = {.top = -1};
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isdigit(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&opStack, token);
        } else if (token == ')') {
            while (peek(&opStack) != '(')
                postfix[j++] = pop(&opStack);
            pop(&opStack); // Remove '('
        } else {
            while (precedence(peek(&opStack)) >= precedence(token) && peek(&opStack) != '(')
                postfix[j++] = pop(&opStack);
            push(&opStack, token);
        }
    }

    while (opStack.top != -1)
        postfix[j++] = pop(&opStack);

    postfix[j] = '\0'; // Null-terminate string
}

// Evaluate Postfix Expression
double evaluatePostfix(char *postfix) {
    Stack valStack = {.top = -1};
    int i;

    for (i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        if (isdigit(token)) {
            push(&valStack, token - '0'); // Convert char to int
        } else {
            int b = pop(&valStack);
            int a = pop(&valStack);

            switch (token) {
                case '+': push(&valStack, a + b); break;
                case '-': push(&valStack, a - b); break;
                case '*': push(&valStack, a * b); break;
                case '/': push(&valStack, a / b); break;
                case '^': push(&valStack, pow(a, b)); break;
            }
        }
    }
    return pop(&valStack);
}

// Main Function
int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an arithmetic expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("Evaluated Result: %.2lf\n", result);

    return 0;
}

