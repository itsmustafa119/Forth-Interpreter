#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>





#define MAX_SIZE 300

typedef struct {
    double array[MAX_SIZE];
    int top;
} Stack;



char* strdup_custom(const char* str) {
    size_t len = strlen(str) + 1;  // +1 for the null terminator
    char* copy = (char*)malloc(len);
    if (copy != NULL) {
        memcpy(copy, str, len);
    }
    return copy;
}


// start of HashMAP functions and structures

#define MAX_SIZE_HASHMAP 100

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *table[MAX_SIZE_HASHMAP];
} HashMap;

// Simple hash function
unsigned int hash(const char *key) {
    unsigned int hashValue = 0;
    while (*key) {
        hashValue = (hashValue << 5) + *key++;
    }
    return hashValue % MAX_SIZE;
}
// Insert key-value pair into the hash map
void insert(HashMap *map, const char *key, const char *value) {
    unsigned int index = hash(key);
    map->table[index] = malloc(sizeof(KeyValuePair)); // Allocate memory for the key-value pair
    map->table[index]->key = strdup_custom(key);            // Allocate memory and copy the key
    map->table[index]->value = strdup_custom(value);        // Allocate memory and copy the value
}

// Find a value by its key
char *get(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    if (map->table[index] != NULL && strcmp(map->table[index]->key, key) == 0) {
        return map->table[index]->value;
    }
    return NULL;  // Key not found
}
// Free the memory used by the hash map
void freeHashMap(HashMap *map) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (map->table[i] != NULL) {
            free(map->table[i]->key);    // Free the key
            free(map->table[i]->value);  // Free the value
            free(map->table[i]);         // Free the KeyValuePair structure
        }
    }
}
// end of HashMAP functions and structures
void initializationStack(Stack *stack) {
    stack->top = -1;
}







bool isFull(Stack *stack) {
    if (stack->top == MAX_SIZE -1) {
        return true;
    }
    return false;
}

bool isEmpty(Stack *stack) {
    if (stack->top == -1 ) {
        return true;
    }
    return false;
}

void push(Stack *stack, double number) {
    if(isFull(stack)) {
        printf("Stack overflow");
    }
    stack->array[++stack->top] = number;
}

double pop(Stack *stack) {
    if(isEmpty(stack)) {

        printf("Stack underflow");
        return -1;

    }
    return stack->array[stack->top--];
}
void printStack(Stack *stack) {
    for(int i = stack->top ; i > -1; i--) {
        printf("%0.1f ", stack->array[i]);
    }
}
bool isNumeric(const char *token, double *value) {
    char *endptr;
    *value = strtod(token, &endptr);

    if (token == endptr)
        return false;

    if (*endptr != '\0')
        return false;

    return true;
}
char *doubleToString(double value) {            //Converts double number to String. 
    int len = snprintf(NULL, 0, "%g", value);
    char *str = malloc(len + 1);
    if (str != NULL) {
        snprintf(str, len + 1, "%g", value);
    }
    return str;
}

bool lineProcessing(char * tokens[50], Stack *stack, HashMap *map, char line[100], bool recursiveCall) {
    int index = 0;
    double number, operand1, operand2, operand3 = 0;
    char outputLine[1024] = "";  // Initialize outputLine as an empty string.

    while(tokens[index] != NULL) {
        if(isNumeric(tokens[index], &number)) {

            number = strtod(tokens[index], NULL);
            push(stack, number);
        }
        else {
            char *definition = get(map, tokens[index]);
            char *definitionCopy = NULL;
            if(definition != NULL){
                definitionCopy = malloc(strlen(definition) + 1);
                strcpy(definitionCopy, definition);
            }
            if(definitionCopy != NULL){
                char *defTokens[50] = {NULL};
                int defIndex = 0;
                char *defToken = strtok(definitionCopy, " ");
                while(defToken != NULL) {
                    defTokens[defIndex] = malloc(strlen(defToken) + 1);
                    strcpy(defTokens[defIndex], defToken);
                    defToken = strtok(NULL, " ");
                    defIndex++;

                }
                defTokens[defIndex] = NULL; // Null-terminate the array of tokens.
                // Recursively process the definition tokens.
                lineProcessing(defTokens, stack, map, line, recursiveCall);
                recursiveCall = true;

                // Free the allocated memory for definition tokens.
                for (int i = 0; i < defIndex; i++) {
                    free(defTokens[i]);
                    defTokens[i] = NULL;
                }
            }
            else if(strcmp(tokens[index], "exit") == 0) {

                return false;
            }
            else if(strcmp(tokens[index], "+") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                push(stack, operand1 + operand2);
            }
            else if(strcmp(tokens[index], "-") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                push(stack, operand1 - operand2);
            }
            else if(strcmp(tokens[index], "*") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                push(stack, operand1 * operand2);
            }
            else if(strcmp(tokens[index], "/") == 0) {

                operand1 = pop(stack);
                operand2 = pop(stack);
                push(stack, operand2 / operand1);
            }
            else if(strcmp(tokens[index], "dup") == 0) {

                operand1 = pop(stack);
                push(stack, operand1);
                push(stack, operand1);
            }
            else if(strcmp(tokens[index], "drop") == 0) {
                pop(stack);
            }
            else if(strcmp(tokens[index], "swap") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                push(stack, operand1);
                push(stack, operand2);
            }
            else if(strcmp(tokens[index], "over") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                push(stack, operand2);
                push(stack, operand1);
                push(stack, operand2);
            }
            else if(strcmp(tokens[index], "rot") == 0 ) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                operand3 = pop(stack);
                push(stack, operand2);
                push(stack, operand1);
                push(stack, operand3);
            }
            else if(strcmp(tokens[index], "mod") == 0) {
                
                operand1 = pop(stack);
                operand2 = pop(stack);
                push(stack, (double)((int)operand2 % (int)operand1));
            }
            else if( strcmp(tokens[index], "if") == 0) {
                operand1 = pop(stack);
                
                if(operand1 == 0) {
                    while(strcmp(tokens[index], "then") != 0) {
                        if(strcmp(tokens[index], "else") == 0) {
                            index++;
                            int elseBodyIndex = 0;
                            char* elseBody[50] = {NULL};
                            while(strcmp(tokens[index], "then") != 0) {
                                elseBody[elseBodyIndex] = malloc(strlen(tokens[index]) + 1);
                                strcpy(elseBody[elseBodyIndex], tokens[index]);
                                elseBodyIndex++;
                                index++;
                            }
                            lineProcessing(elseBody, stack, map, line, recursiveCall);
                            recursiveCall = true;
                            for (int i = 0; i < elseBodyIndex; i++) {
                                free(elseBody[i]);
                                elseBody[i] = NULL;
                            }
                            break;
                        }
                        index++;
                    }
                    index++;
                }
                else {
                    int ifBodyIndex = 0;
                    char* ifBody[50] = {NULL};
                    index++;
                    while(strcmp(tokens[index], "else") != 0 && strcmp(tokens[index], "then") != 0) {
                        ifBody[ifBodyIndex] = malloc(strlen(tokens[index]) + 1);
                        strcpy(ifBody[ifBodyIndex], tokens[index]);
                        ifBodyIndex++;
                        index++;
                    }
                    lineProcessing(ifBody, stack, map, line, recursiveCall);
                    recursiveCall = true;
                    for (int i = 0; i < ifBodyIndex; i++) {
                        free(ifBody[i]);
                        ifBody[i] = NULL;
                    }
                    index++;  // Skip the "then"
                    
                }


            }
            else if(strcmp(tokens[index], "do") == 0) {
                operand1 = pop(stack); //start of the loop
                operand2 = pop(stack); //end of the loop
                int loopBodyIndex = 0;
                char* loopBody[50] = {NULL};
                index++;
                index++;
                while(strcmp(tokens[index], "loop") != 0) {
                    loopBody[loopBodyIndex] = malloc(strlen(tokens[index]) + 1);
                    strcpy(loopBody[loopBodyIndex], tokens[index]);
                    loopBodyIndex++;
                    index++;
                }
                for(int i = (int)operand1; i < (int)operand2; i++) {
                    push(stack, (double)i);
                    lineProcessing(loopBody, stack, map, line, recursiveCall);
                }
                recursiveCall = true;
                for (int i = 0; i < loopBodyIndex; i++) {
                    free(loopBody[i]);
                    loopBody[i] = NULL;
                }
                index++;
            }
            else if(strcmp(tokens[index], ":") == 0) {
                index++;
                char *wordName = tokens[index];
                index++;
                char definition[512] = "";
                while(strcmp(tokens[index], ";") != 0) {
                    strncat(definition, tokens[index], sizeof(definition) - strlen(definition) - 1);
                    strncat(definition, " ", sizeof(definition) - strlen(definition) - 1);
                    index++;
                }
                insert(map, wordName, definition);
            }
            else if(strcmp(tokens[index], ".") == 0) {
                char * stringNumber = doubleToString(pop(stack));
                strncat(outputLine, " ", sizeof(outputLine) - strlen(outputLine) - 1);
                strncat(outputLine, stringNumber, sizeof(outputLine) - strlen(outputLine) - 1);
                free(stringNumber);
            }
            else if(strcmp(tokens[index], "emit") == 0) {
                operand1 = pop(stack);
                int x = (int)operand1;
                char y = (char)x;

                char str[2];        //converting character to string.
                str[0] = y;
                str[1] = '\0';

                strncat(outputLine, str, sizeof(outputLine) - strlen(outputLine) - 1);
            }
            else if(strcmp(tokens[index], "cr") == 0) {
                strncat(outputLine, "\n", sizeof(outputLine) - strlen(outputLine) - 1);
            }
            else if(strcmp(tokens[index], ".\"") == 0) {
                
                index++;
                while(strcmp(tokens[index], "\"") != 0) {
                    strncat(outputLine, tokens[index], sizeof(outputLine) - strlen(outputLine) - 1);
                    strncat(outputLine, " ", sizeof(outputLine) - strlen(outputLine) - 1);
                    index++;
                } 
            }
            else if(strcmp(tokens[index], "=") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                if(operand1 == operand2) {
                    push(stack, -1);
                }
                else {
                    push(stack, 0);
                }
            }
            else if(strcmp(tokens[index], "<") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                if(operand2 < operand1) {
                    push(stack, -1);
                }
                else {
                    push(stack, 0);
                }
            }
            else if(strcmp(tokens[index], ">") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                if(operand2 > operand1) {
                    push(stack, -1);
                }
                else {
                    push(stack, 0);
                }
            }
            else if(strcmp(tokens[index], "and") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                operand3 = (double)((int)operand1 & (int)operand2);
                push(stack, operand3);
            }
            else if(strcmp(tokens[index], "or") == 0) {
                operand1 = pop(stack);
                operand2 = pop(stack);
                operand3 = (double)((int)operand1 | (int)operand2);
                push(stack, operand3);
            }
            else if(strcmp(tokens[index], "invert") == 0) {
                operand1 = pop(stack);
                operand3 = (double)(~(int)operand1);
                push(stack, operand3);
            }
        }
        index++;
        
    }
    if(!recursiveCall) {
    printf("\033[A\r%s %s  ok\n", line, outputLine);      //Printing the transparent message ending with ok.
    }
    return true;
}
int main() {
    Stack stack = {0};
    HashMap map = {0};
    char line[100] = "";
    char tempLine[100] = "";        //temprorary line variable to store the original line because the line variable will be tokenized.
    char *tokens[50] = {NULL};
    int index = 0;
    initializationStack(&stack);
    while(true) {

        
        printStack(&stack);
        printf("<- top\n");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';       // For removing the last nextline
        strcpy(tempLine, line);
        char *token = strtok(line, " ");
        while(token != NULL) {
            tokens[index] = malloc(strlen(token) + 1);
            strcpy(tokens[index], token);
            token = strtok(NULL, " ");
            index++;
        }

        
        if(!lineProcessing(tokens, &stack, &map, tempLine, false)){
            break;
        };


        for (int i = 0; i < index; i++) {
            free(tokens[i]);
            tokens[i] = NULL;   // clear the tokens array.
        }

        line[0] = '\0';             //clearing the line variable.
        tempLine[0] = '\0';       //clearing the tempLine variable.
        index = 0;


    }



}