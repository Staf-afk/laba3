#include "file.h"
#include <stdio.h>
#include <stdlib.h>

void writeStackToFile(Stack* stack, const char* filename){
    FILE* file = fopen(filename, "w");
    if (!file){
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }
    fprintf(file, "%d\n", getStackSize(stack));
    Stack* reversed = reverseStack(stack);
    Node* current = reversed->top;
    while (current != NULL){
        fprintf(file, "%d\n", current->data);
        current = current->next;
    }
    fclose(file);
    freeStack(reversed);
}

Stack* readStackFromFile(const char* filename){
    FILE* file = fopen(filename, "r");
    if (!file){
        printf("Ошибка открытия файла %s\n", filename);
        return NULL;
    }
    Stack* stack = initStack();
    int size, value;
    
    if (fscanf(file, "%d", &size) != 1){
        fclose(file);
        freeStack(stack);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        if (fscanf(file, "%d", &value) != 1){
            break;
        }
        push(stack, value);
    }
    fclose(file);
    Stack* result = reverseStack(stack);
    freeStack(stack);
    return result;
}

void appendStackToFile(Stack* stack, const char* filename, const char* label){
    FILE* file = fopen(filename, "a");
    if (!file){
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }
    
    fprintf(file, "\n%s:\n", label);
    Stack* reversed = reverseStack(stack);
    Node* current = reversed->top;
    while (current != NULL){
        fprintf(file, "%d ", current->data);
        current = current->next;
    }
    fprintf(file, "\n");
    fclose(file);
    freeStack(reversed);
}