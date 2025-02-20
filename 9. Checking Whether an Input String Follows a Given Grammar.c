
#include <stdio.h>
#include <string.h>

char input[100];  // Input string
int pos = 0;      // Current position in the string

// Function to parse based on grammar S -> aSb | ε
int S() {
    if (input[pos] == 'a') {  // Match 'a'
        pos++;
        if (S()) {  // Recursive call
            if (input[pos] == 'b') {  // Match 'b'
                pos++;
                return 1;  // Successfully parsed "aSb"
            }
        }
        return 0;  // Parsing failed
    }
    return 1;  // Empty string (ε) is valid
}

// Function to check if the input string is valid
void checkGrammar() {
    pos = 0;  // Reset position
    if (S() && input[pos] == '\0') {
        printf("The string follows the grammar.\n");
    } else {
        printf("The string does NOT follow the grammar.\n");
    }
}

// Main function
int main() {
    printf("Enter a string: ");
    scanf("%s", input);

    checkGrammar();
    return 0;
}
