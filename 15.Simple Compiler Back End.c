#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char op[10], arg1[10], arg2[10], result[10];
} TAC;

TAC code[MAX];
int codeCount = 0;
int tempVar = 1;

// Generate a new temporary variable
void newTemp(char *temp) {
    sprintf(temp, "t%d", tempVar++);
}

// Generate Three-Address Code
void generateTAC(char op[], char arg1[], char arg2[], char result[]) {
    strcpy(code[codeCount].op, op);
    strcpy(code[codeCount].arg1, arg1);
    strcpy(code[codeCount].arg2, arg2);
    strcpy(code[codeCount].result, result);
    codeCount++;
}

// Parse and generate TAC from infix expression (Assume single-letter variables)
void parseExpression(char *expr) {
    char operandStack[MAX][10];
    int operandTop = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isalnum(expr[i])) {  // If operand, push to stack
            char temp[2] = {expr[i], '\0'};
            strcpy(operandStack[++operandTop], temp);
        } else {  // Operator
            char op2[10], op1[10], result[10];
            strcpy(op2, operandStack[operandTop--]);
            strcpy(op1, operandStack[operandTop--]);
            newTemp(result);
            generateTAC((char[]){expr[i], '\0'}, op1, op2, result);
            strcpy(operandStack[++operandTop], result);
        }
    }
}

// Generate Assembly Code from TAC
void generateAssembly() {
    printf("\nGenerated Assembly Code:\n");
    for (int i = 0; i < codeCount; i++) {
        printf("MOV R1, %s\n", code[i].arg1);
        if (strcmp(code[i].op, "+") == 0)
            printf("ADD R1, %s\n", code[i].arg2);
        else if (strcmp(code[i].op, "-") == 0)
            printf("SUB R1, %s\n", code[i].arg2);
        else if (strcmp(code[i].op, "*") == 0)
            printf("MUL R1, %s\n", code[i].arg2);
        else if (strcmp(code[i].op, "/") == 0)
            printf("DIV R1, %s\n", code[i].arg2);
        printf("MOV %s, R1\n", code[i].result);
    }
}

int main() {
    char expression[MAX];

    printf("Enter a postfix expression: ");
    scanf("%s", expression);

    parseExpression(expression);

    printf("\nGenerated Three-Address Code:\n");
    for (int i = 0; i < codeCount; i++)
        printf("%s = %s %s %s\n", code[i].result, code[i].arg1, code[i].op, code[i].arg2);

    generateAssembly();

    return 0;
}
