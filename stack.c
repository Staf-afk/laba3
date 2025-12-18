#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* initStack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;
    
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack){
    if (isEmpty(stack)){
        return -1;
    }
    
    Node* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    
    return value;
}

int peek(Stack* stack){
    if (isEmpty(stack)){
        return -1;
    }
    return stack->top->data;
}

int isEmpty(Stack* stack){
    return stack->top == NULL;
}

void freeStack(Stack* stack){
    while (!isEmpty(stack)){
        pop(stack);
    }
    free(stack);
}

int getStackSize(Stack* stack){
    int count = 0;
    Node* current = stack->top;
    while (current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

Stack* copyStack(Stack* stack){
    Stack* copy = initStack();
    if (isEmpty(stack)) return copy;
    Stack* temp = initStack();
    Node* current = stack->top;
    while (current != NULL){
        push(temp, current->data);
        current = current->next;
    }
    while (!isEmpty(temp)){
        int value = pop(temp);
        push(copy, value);
    }
    freeStack(temp);
    return copy;
}

Stack* reverseStack(Stack* stack){
    Stack* reversed = initStack();
    Stack* copy = copyStack(stack);
    
    while (!isEmpty(copy)){
        push(reversed, pop(copy));
    }
    
    freeStack(copy);
    return reversed;
}

void printStack(Stack* stack){
    if (isEmpty(stack)){
        printf("Стек пуст\n");
        return;
    }
    
    Stack* reversed = reverseStack(stack);
    Node* current = reversed->top;
    
    printf("Стек (сверху вниз): ");
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    freeStack(reversed);
}