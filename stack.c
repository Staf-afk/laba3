#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* initStack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack* stack, int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;
    
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int pop(Stack* stack){
    if (isEmpty(stack)){
        return -1;
    }
    
    Node* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    
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
    return stack->size;
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
    printf("Стек: ");
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    freeStack(reversed);
}

int getElementAt(Stack* stack, int index){
    if (index < 0 || index >= stack->size){
        return -1;
    }
    
    Node* current = stack->top;
    for (int i = 0; i < index && current != NULL; i++){
        current = current->next;
    }
    return (current != NULL) ? current->data : -1;
}

void insertAt(Stack* stack, int index, int value){
    if (index < 0 || index > stack->size) {
        return;
    }
    if (index == 0){
        push(stack, value);
        return;
    }
    
    Stack* temp = initStack();
    for (int i = 0; i < index; i++){
        push(temp, pop(stack));
    }
    push(stack, value);
    
    while (!isEmpty(temp)){
        push(stack, pop(temp));
    }
    freeStack(temp);
}

void removeAt(Stack* stack, int index){
    if (index < 0 || index >= stack->size){
        return;
    }
    
    Stack* temp = initStack();
    for (int i = 0; i < index; i++){
        push(temp, pop(stack));
    }
    pop(stack);
    
    while (!isEmpty(temp)){
        push(stack, pop(temp));
    }
    freeStack(temp);
}

void insertionSortStack(Stack* stack){
    if (isEmpty(stack) || stack->size == 1){
        return;
    }
    Stack* sorted = initStack();
    
    while (!isEmpty(stack)){
        int current = pop(stack);
        
        while (!isEmpty(sorted) && peek(sorted) > current){
            push(stack, pop(sorted));
        }
        push(sorted, current);
    }
    
    while (!isEmpty(sorted)){
        push(stack, pop(sorted));
    }
    
    freeStack(sorted);
}

Stack* mergeStacks(Stack* left, Stack* right) {
    Stack* result = initStack();
    Stack* temp = initStack();
    
    while (!isEmpty(left) && !isEmpty(right)) {
        if (peek(left) <= peek(right)) {
            push(temp, pop(left));
        } else {
            push(temp, pop(right));
        }
    }
    
    while (!isEmpty(left)) {
        push(temp, pop(left));
    }
    while (!isEmpty(right)) {
        push(temp, pop(right));
    }
    while (!isEmpty(temp)) {
        push(result, pop(temp));
    }
    
    freeStack(temp);
    return result;
}

Stack* mergeSortStack(Stack* stack) {
    if (isEmpty(stack) || stack->size == 1) {
        return copyStack(stack);
    }
    
    int mid = stack->size / 2;
    
    Stack* left = initStack();
    Stack* right = initStack();
    
    for (int i = 0; i < mid; i++) {
        push(left, pop(stack));
    }
    
    while (!isEmpty(stack)) {
        push(right, pop(stack));
    }
    
    Stack* sortedLeft = mergeSortStack(left);
    Stack* sortedRight = mergeSortStack(right);
    
    Stack* result = mergeStacks(sortedLeft, sortedRight);
    
    freeStack(left);
    freeStack(right);
    freeStack(sortedLeft);
    freeStack(sortedRight);
    
    return result;
}