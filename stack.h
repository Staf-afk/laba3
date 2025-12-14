#ifndef STACK_H
#define STACK_H

typedef struct Node{
    int data;
    struct Node* next;
}Node;              //узел

typedef struct Stack{
    Node* top;
    int size;
}Stack;

Stack* initStack();
void push(Stack* stack, int value);
int pop(Stack* stack);
int isEmpty(Stack* stack);
void freeStack(Stack* stack);
int getStackSize(Stack* stack);
int* stackToArray(Stack* stack);
Stack* arrayToStack(int* arr, int size);
void printStack(Stack* stack);

#endif