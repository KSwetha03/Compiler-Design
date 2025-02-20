#include <stdio.h>
#include <string.h>

#define MAX 10

// Function to find the longest common prefix
void findCommonPrefix(char *productions[], int n, char *prefix) {
    int minLen = strlen(productions[0]);

    // Find the minimum length string
    for (int i = 1; i < n; i++) {
        if (strlen(productions[i]) < minLen)
            minLen = strlen(productions[i]);
    }

    int i;
    for (i = 0; i < minLen; i++) {
        char ch = productions[0][i];
        for (int j = 1; j < n; j++) {
            if (productions[j][i] != ch) {
                prefix[i] = '\0';
                return;
            }
        }
        prefix[i] = ch;
    }
    prefix[i] = '\0';
}

// Function to eliminate left factoring
void eliminateLeftFactoring(char *nonTerminal, char *productions[], int numProductions) {
    char prefix[20];
    findCommonPrefix(productions, numProductions, prefix);

    int prefixLen = strlen(prefix);
    if (prefixLen == 0) {
        printf("No left factoring needed.\n");
        return;
    }

    printf("Eliminated Left Factoring Grammar:\n");
    printf("%s -> %sX\n", nonTerminal, prefix);
    printf("X -> ");

    // Print the new productions for X
    for (int i = 0; i < numProductions; i++) {
        if (strlen(productions[i]) > prefixLen) {
            printf("%s", productions[i] + prefixLen);
        } else {
            printf("ε");  // Empty production
        }
        if (i != numProductions - 1) printf(" | ");
    }
    printf("\n");
}

// Main function
int main() {
    char *nonTerminal = "A";
    char *productions[] = {"abD", "abcD", "abE", "abcE"};  // Input grammar
    int numProductions = 4;

    eliminateLeftFactoring(nonTerminal, productions, numProductions);

    return 0;
}
