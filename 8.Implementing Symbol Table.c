#include <stdio.h>
#include <string.h>

#define MAX 100  // Maximum number of symbols

// Structure to store a symbol
typedef struct {
    char name[50];   // Variable or function name
    char type[20];   // Data type (int, float, char, etc.)
    int size;        // Memory size (4 for int, 1 for char, etc.)
} Symbol;

// Symbol Table Array
Symbol table[MAX];
int count = 0;  // Number of symbols in table

// Function to check if a symbol already exists
int searchSymbol(char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            return i; // Symbol found, return its index
        }
    }
    return -1; // Not found
}

// Function to insert a new symbol
void insertSymbol(char *name, char *type, int size) {
    if (searchSymbol(name) != -1) {
        printf("Error: Symbol '%s' already exists in the table!\n", name);
        return;
    }

    strcpy(table[count].name, name);
    strcpy(table[count].type, type);
    table[count].size = size;
    count++;
    printf("Symbol '%s' added successfully.\n", name);
}

// Function to display the symbol table
void displayTable() {
    if (count == 0) {
        printf("Symbol table is empty!\n");
        return;
    }

    printf("\nSymbol Table:\n");
    printf("--------------------------------------------------\n");
    printf("| %-15s | %-10s | %-5s |\n", "Name", "Type", "Size");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("| %-15s | %-10s | %-5d |\n", table[i].name, table[i].type, table[i].size);
    }
    printf("--------------------------------------------------\n");
}

// Main function
int main() {
    int choice;
    char name[50], type[20];
    int size;

    while (1) {
        printf("\nSymbol Table Operations:\n");
        printf("1. Insert Symbol\n");
        printf("2. Search Symbol\n");
        printf("3. Display Symbol Table\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter symbol name: ");
                scanf("%s", name);
                printf("Enter data type (int, float, char, etc.): ");
                scanf("%s", type);
                printf("Enter size (bytes): ");
                scanf("%d", &size);
                insertSymbol(name, type, size);
                break;
            case 2:
                printf("Enter symbol name to search: ");
                scanf("%s", name);
                int index = searchSymbol(name);
                if (index != -1)
                    printf("Symbol '%s' found in the table at index %d.\n", name, index);
                else
                    printf("Symbol '%s' not found.\n", name);
                break;
            case 3:
                displayTable();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
