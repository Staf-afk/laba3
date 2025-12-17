#include "stack.h"
#include "sort.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "numbers.txt"

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMenu() {
    printf("\n=== Меню ===\n"
        "1. Ввести последовательность чисел\n"
        "2. Показать текущий стек\n"
        "3. Сортировать прямым включением\n"
        "4. Сортировать слиянием\n"
        "5. Сравнить методы сортировки\n"
        "6. Запустить тесты производительности\n"
        "7. Прочитать из файла\n"
        "8. Выход\n"
        "Выберите опцию: ");
}

void processInput(Stack** stack){
    printf("Введите последовательность чисел через пробел: ");
    char input[10000];
    clearInputBuffer();
    fgets(input, sizeof(input), stdin);
    if (*stack != NULL) {
        freeStack(*stack);
    }
    *stack = initStack();
    char* token = strtok(input, " \t\n");
    int count = 0;
    
    while (token != NULL) {
        int valid = 1;
        for (int i = 0; token[i] != '\0'; i++) {
            if (!isdigit(token[i]) && !(i == 0 && token[i] == '-')) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            int num = atoi(token);
            push(*stack, num);
            count++;
        }
        token = strtok(NULL, " \t\n");
    }
    
    if (isEmpty(*stack)){
        printf("Не было введено корректных чисел.\n");
        freeStack(*stack);
        *stack = NULL;
    }
    else{
        printf("Введено %d чисел\n", count);
        
        writeStackToFile(*stack, FILENAME);
        printf("Исходный ряд записан в файл '%s'\n", FILENAME);
    }
}

void sortWithInsertion(Stack* stack){
    if (stack == NULL || isEmpty(stack)){
        printf("Стек пуст! Сначала введите числа.\n");
        return;
    }
    
    printf("Исходный стек: ");
    printStack(stack);
    Stack* copy = copyStack(stack);
    insertionSortStack(copy);
    
    printf("Отсортированный стек (прямое включение): ");
    printStack(copy);
    appendStackToFile(copy, FILENAME, "Сортировка прямым включением");
    printf("Отсортированный ряд записан в файл '%s'\n", FILENAME);
    
    freeStack(copy);
}

void sortWithMerge(Stack* stack){
    if (stack == NULL || isEmpty(stack)){
        printf("Стек пуст! Сначала введите числа.\n");
        return;
    }
    printf("Исходный стек: ");
    printStack(stack);
    Stack* sorted = mergeSortStack(stack);
    printf("Отсортированный стек (слияние): ");
    printStack(sorted);
    appendStackToFile(sorted, FILENAME, "Сортировка слиянием");
    printf("Отсортированный ряд записан в файл '%s'\n", FILENAME);
    
    freeStack(sorted);
}

void readFromFile(){
    Stack* stack = readStackFromFile(FILENAME);
    if(stack != NULL){
        printf("Прочитано из файла '%s':\n", FILENAME);
        printStack(stack);
        freeStack(stack);
    } 
    else{
        printf("Файл '%s' не найден или пуст\n", FILENAME);
    }
}

int main(){
    Stack* stack = NULL;
    int choice;
    printf("=== Программа сортировки последовательностей ===\n");
    printf("Используемые методы: прямое включение и слияние\n");
    
    while(1){
        printMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Попробуйте снова.\n");
            clearInputBuffer();
            continue;
        }
        
        switch(choice){
            case 1:
                processInput(&stack);
                break;
                
            case 2:
                if (stack != NULL && !isEmpty(stack)){
                    printStack(stack);
                }
                else{
                    printf("Стек пуст! Сначала введите числа.\n");
                }
                break;
                
            case 3:
                sortWithInsertion(stack);
                break;
                
            case 4:
                sortWithMerge(stack);
                break;
                
            case 5:
                if (stack != NULL && !isEmpty(stack)){
                    compareStackSortingMethods(stack);
                }
                else{
                    printf("Стек пуст! Сначала введите числа.\n");
                }
                break;
                
            case 6:
                runStackPerformanceTests();
                break;
                
            case 7:
                readFromFile();
                break;
                
            case 8:
                printf("Завершение программы...\n");
                if (stack != NULL){
                    freeStack(stack);
                }
                return 0;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
        
        if (choice != 8){
            printf("\nНажмите Enter для продолжения...");
            clearInputBuffer();
        }
    }
}