#ifndef STACK_H
#define STACK_H

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Stack{
    Node* top;
}Stack;

Stack* initStack();
void push(Stack* stack, int value);
int pop(Stack* stack);
int peek(Stack* stack);
int isEmpty(Stack* stack);
void freeStack(Stack* stack);
int getStackSize(Stack* stack);
void printStack(Stack* stack);
Stack* copyStack(Stack* stack);
Stack* reverseStack(Stack* stack);

#endif