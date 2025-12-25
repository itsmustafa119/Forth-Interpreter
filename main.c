#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>





#define MAX_SIZE 300

typedef struct {
    double array[MAX_SIZE];
    int top;
} Stack;


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

bool lineProcessing(char * tokens[50], Stack *stack, char* line){
    int index = 0;
    double number, operand1, operand2, operand3 = 0;
    char *outputLine = NULL;
    while(tokens[index] != NULL) {
        if(isNumeric(tokens[index], &number)) {
            number = strtod(tokens[index], NULL);
            push(stack, number);
        }
        else {
            if(strcmp(tokens[index], "exit") == 0) {

                return false;
            }
            else if(strcmp(tokens[index], "+") == 0) {
                push(stack, pop(stack) + pop(stack));
            }
            else if(strcmp(tokens[index], "-") == 0) {
                push(stack, (pop(stack) - pop(stack)) * (-1));
            }
            else if(strcmp(tokens[index], "*") == 0) {
                push(stack, pop(stack) * pop(stack));
            }
            else if(strcmp(tokens[index], "/") == 0) {
                operand2 = pop(stack);
                push(stack, pop(stack) / operand2);
                
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
            else if(strcmp(tokens[index], ".") == 0) {
                char * stringNumber = doubleToString(pop(stack));
                strcat(outputLine, " ");
                strcat(outputLine, stringNumber);
            }
            else if(strcmp(tokens[index], "emit") == 0) {
                operand1 = pop(stack);
                int x = (int)operand1;
                char y = (char)x;

                char str[3];        //converting character to string.
                str[0] = ' ';
                str[1] = y;
                str[2] = '\0';

                strcat(outputLine, str);
            }
            else{

            }
        }
        index++;
    }
    strcat(outputLine, "\0");
    printf("\033[A\r%s %s ok\n", line, outputLine);      //Printing the transparent message ending with ok.
    return true;
}
int main() {
    Stack stack;
    char line[100];
    char *tokens[50];

    int index = 0;
    initializationStack(&stack);
    while(true) {

        
        printStack(&stack);
        printf("<- top\n");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';       // For removing the last nextline

        char *token = strtok(line, " ");
        while(token != NULL) {
            tokens[index] = malloc(strlen(token) + 1);
            strcpy(tokens[index++], token);
            token = strtok(NULL, " ");
            
        }
        

        if(!lineProcessing(tokens, &stack, line)){
            break;
        };


        for (int i = 0; i < index; i++) {
            free(tokens[i]);
            tokens[i] = NULL;   // clear the tokens array.
        }

        line[0] = '\0';             //clearing the line variable.
        index = 0;

    }



}