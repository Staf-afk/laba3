#ifndef FILE_H
#define FILE_H

#include "stack.h"

void writeStackToFile(Stack* stack, const char* filename);
Stack* readStackFromFile(const char* filename);
void appendStackToFile(Stack* stack, const char* filename, const char* label);

#endif