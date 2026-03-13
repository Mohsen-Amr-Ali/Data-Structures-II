#ifndef ASSIGNMENT2_SORTS_H
#define ASSIGNMENT2_SORTS_H

#include <vector>
#include <algorithm>

// Function Prototypes
void bubbleSort(std::vector<int> &arr);
void selectionSort(std::vector<int> &arr);
void insertionSort(std::vector<int> &arr);


void quicksort(std::vector<int> &arr, int start, int end);
int partition(std::vector<int> &arr, int start, int end);
int randomPartition(std::vector<int> &arr, int start, int end);
int generateRandomIndex(int start, int end);

#endif //ASSIGNMENT2_SORTS_H