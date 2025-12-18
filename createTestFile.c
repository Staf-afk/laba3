#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const char *filename = "numbers100.txt";
    const int count = 100;
    
    FILE *file = fopen(filename, "w");
    if (!file) return 1;
    
    srand(time(NULL));
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", rand() % 1000000);
    }
    
    fclose(file);
    printf("Создан файл %s с %d числами (по одному на строку)\n", filename, count);
    
    return 0;
}