#include <stdio.h>
#include <string.h>

void eliminateLeftRecursion(char *nonTerminal, char *productions[], int numProductions) {
    char alpha[10][20], beta[10][20];
    int alphaCount = 0, betaCount = 0;

    // Separating left-recursive and non-left-recursive productions
    for (int i = 0; i < numProductions; i++) {
        if (productions[i][0] == nonTerminal[0]) { // Left recursion: A -> Aα
            strcpy(alpha[alphaCount++], productions[i] + 1);
        } else { // Non-left recursion: A -> β
            strcpy(beta[betaCount++], productions[i]);
        }
    }

    // If there is left recursion, rewrite the rules
    if (alphaCount > 0) {
        printf("Eliminated Left Recursion Grammar:\n");
        printf("%s -> ", nonTerminal);
        for (int i = 0; i < betaCount; i++) {
            printf("%s%s' ", beta[i], nonTerminal);
            if (i != betaCount - 1) printf("| ");
        }
        printf("\n");

        printf("%s' -> ", nonTerminal);
        for (int i = 0; i < alphaCount; i++) {
            printf("%s%s' ", alpha[i], nonTerminal);
            if (i != alphaCount - 1) printf("| ");
        }
        printf("| ε\n");
    } else {
        printf("No left recursion detected.\n");
    }
}

int main() {
    char *nonTerminal = "A";
    char *productions[] = {"Aa", "Ab", "c"};  // Given grammar A -> Aa | Ab | c
    int numProductions = 3;

    eliminateLeftRecursion(nonTerminal, productions, numProductions);

    return 0;
}
