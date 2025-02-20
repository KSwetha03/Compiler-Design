#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Stack Structure
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

// Precedence of Operators
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Convert Infix to Postfix (Shunting Yard Algorithm)
void infixToPostfix(char *infix, char *postfix) {
    Stack opStack = {.top = -1};
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isalnum(token)) {
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

// Generate Three-Address Code from Postfix Expression
void generateTAC(char *postfix) {
    Stack varStack = {.top = -1};
    int tempVar = 1;

    printf("\nThree-Address Code:\n");

    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        if (isalnum(token)) {
            push(&varStack, token);
        } else {
            char op2 = pop(&varStack);
            char op1 = pop(&varStack);

            printf("t%d = %c %c %c\n", tempVar, op1, token, op2);
            push(&varStack, 't' + tempVar); // Store temp variable as 't1', 't2', etc.
            tempVar++;
        }
    }
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an arithmetic expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    generateTAC(postfix);

    return 0;
}

