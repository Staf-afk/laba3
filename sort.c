#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void insertionSortStack(Stack* stack){
    if (isEmpty(stack) || getStackSize(stack) == 1){
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

static Stack* mergeStacks(Stack* left, Stack* right) {
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

Stack* mergeSortStack(Stack* stack){
    if (isEmpty(stack) || getStackSize(stack) == 1){
        return copyStack(stack);
    }

    int mid = getStackSize(stack) / 2;
    Stack* left = initStack();
    Stack* right = initStack();
    
    for (int i = 0; i < mid; i++){
        push(left, pop(stack));
    }
    while (!isEmpty(stack)){
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

void compareStackSortingMethods(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Стек пуст! Сначала введите числа.\n");
        return;
    }
    Stack* stack1 = copyStack(stack);
    Stack* stack2 = copyStack(stack);
    
    clock_t start, end;
    double insertionTime, mergeTime;
    start = clock();
    insertionSortStack(stack1);
    end = clock();
    insertionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    start = clock();
    Stack* sorted = mergeSortStack(stack2);
    end = clock();
    mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\n=== Сравнение методов сортировки стеков ===\n");
    printf("Размер данных: %d элементов\n", getStackSize(stack));
    printf("Время сортировки прямым включением: %.6f секунд\n", insertionTime);
    printf("Время сортировки слиянием: %.6f секунд\n", mergeTime);
    
    if (insertionTime < mergeTime){
        printf("Сортировка прямым включением быстрее на %.6f секунд\n", 
               mergeTime - insertionTime);
    } 
    else{
        printf("Сортировка слиянием быстрее на %.6f секунд\n", 
               insertionTime - mergeTime);
    }
    freeStack(stack1);
    freeStack(stack2);
    freeStack(sorted);
}

void runStackPerformanceTests(){
    printf("\n=== Тестирование производительности сортировки стеков ===\n");
    printf("Размер\tВставка\t\tСлияние\t\tРазница\n");
    printf("------\t--------\t--------\t--------\n");
    
    int sizes[] = {100, 500, 1000, 5000, 10000};
    int numTests = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));
    
    for (int i = 0; i < numTests; i++){
        int size = sizes[i];
        
        Stack* stack = initStack();
        
        for (int j = 0; j < size; j++) {
            push(stack, rand() % 10000);
        }
        
        Stack* stack1 = copyStack(stack);
        Stack* stack2 = copyStack(stack);
        clock_t start = clock();
        insertionSortStack(stack1);
        clock_t end = clock();
        double insertionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        start = clock();
        Stack* sorted = mergeSortStack(stack2);
        end = clock();
        double mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("%d\t%.6f\t%.6f\t%.6f\n", size, insertionTime, mergeTime, insertionTime - mergeTime);
        freeStack(stack);
        freeStack(stack1);
        freeStack(stack2);
        freeStack(sorted);
    }
    
    printf("\n=== Анализ результатов ===\n");
    printf("1. На малых объемах данных (<1000 элементов):\n");
    printf("   - Оба метода работают быстро\n");
    printf("   - Сортировка прямым включением часто быстрее из-за меньших накладных расходов\n\n");
    
    printf("2. На средних объемах данных (1000-10000 элементов):\n");
    printf("   - Сортировка слиянием начинает показывать преимущество\n");
    printf("   - O(n log n) vs O(n?) начинает иметь значение\n\n");
    
    printf("3. На больших объемах данных (>10000 элементов):\n");
    printf("   - Сортировка слиянием значительно быстрее\n");
    printf("   - Прямое включение становится непрактичным\n\n");
    
    printf("4. График будет показывать:\n");
    printf("   - Медленный рост времени для сортировки слиянием\n");
    printf("   - Квадратичный рост для сортировки прямым включением\n");
}