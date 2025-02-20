#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];  // Input expression
int pos = 0;      // Current position in input

// Function Prototypes
void E();
void EPrime();
void T();
void TPrime();
void F();

// Function to match a character in input
void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        printf("Syntax Error at position %d: Expected '%c'\n", pos, expected);
        exit(0);
    }
}

// Recursive Descent Parsing Functions

// E -> T E'
void E() {
    T();
    EPrime();
}

// E' -> + T E' | ε
void EPrime() {
    if (input[pos] == '+') {  // Match '+'
        match('+');
        T();
        EPrime();
    }
}

// T -> F T'
void T() {
    F();
    TPrime();
}

// T' -> * F T' | ε
void TPrime() {
    if (input[pos] == '*') {  // Match '*'
        match('*');
        F();
        TPrime();
    }
}

// F -> (E) | id
void F() {
    if (input[pos] == '(') {  // Match '('
        match('(');
        E();
        match(')');  // Match ')'
    } else if (isalnum(input[pos])) {  // Match 'id' (identifier)
        match(input[pos]);  // Consume single character identifier
    } else {
        printf("Syntax Error at position %d: Unexpected character '%c'\n", pos, input[pos]);
        exit(0);
    }
}

// Main function
int main() {
    printf("Enter an arithmetic expression: ");
    scanf("%s", input);

    E();  // Start parsing from the root (E)

    // If parsing ends at the last character, it's valid
    if (input[pos] == '\0') {
        printf("The input string is a valid expression.\n");
    } else {
        printf("Syntax Error at position %d: Unexpected trailing characters.\n", pos);
    }

    return 0;
}
