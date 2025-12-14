#ifndef SORT_H
#define SORT_H

void insertionSort(int* arr, int size);                  //pryamoe sort

void mergeSort(int* arr, int left, int right);           //sliyanie sort
void merge(int* arr, int left, int mid, int right);

void copyArray(int* dest, const int* src, int size);
void printArray(const int* arr, int size);

#endif