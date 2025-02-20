#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char expr[MAX];
    char temp[5];
} SubExpr;

SubExpr subexpressions[MAX];
int subCount = 0;

// Function to check if a subexpression exists
char* findSubexpression(char* expr) {
    for (int i = 0; i < subCount; i++) {
        if (strcmp(subexpressions[i].expr, expr) == 0)
            return subexpressions[i].temp;
    }
    return NULL;
}

// Function to add a new subexpression
void addSubexpression(char* expr) {
    snprintf(subexpressions[subCount].temp, 5, "t%d", subCount + 1);
    strcpy(subexpressions[subCount].expr, expr);
    subCount++;
}

// Function to optimize expressions
void optimizeExpression(char expressions[MAX][MAX], int n) {
    printf("\nOptimized Code:\n");

    for (int i = 0; i < n; i++) {
        char var, expr[MAX], sub[MAX];

        sscanf(expressions[i], "%c = %[^\n]", &var, expr);

        char* existingTemp = findSubexpression(expr);
        if (existingTemp) {
            printf("%c = %s\n", var, existingTemp);
        } else {
            addSubexpression(expr);
            printf("%s = %s\n", subexpressions[subCount - 1].temp, expr);
            printf("%c = %s\n", var, subexpressions[subCount - 1].temp);
        }
    }
}

int main() {
    int n;
    char expressions[MAX][MAX];

    printf("Enter number of expressions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter expressions (format: a = b + c):\n");
    for (int i = 0; i < n; i++) {
        fgets(expressions[i], MAX, stdin);
        expressions[i][strcspn(expressions[i], "\n")] = '\0';
    }

    optimizeExpression(expressions, n);

    return 0;
}
