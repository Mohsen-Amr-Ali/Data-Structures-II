#ifndef INC_2__QUICK_AND_MERGE_SORTS_AND_HEAPS_ADVANCED_SORTS_H
#define INC_2__QUICK_AND_MERGE_SORTS_AND_HEAPS_ADVANCED_SORTS_H

#include <vector>

void quicksort(std::vector<int> &arr, int start, int end);
int partition(std::vector<int> &arr, int start, int end);
int randomPartition(std::vector<int> &arr, int start, int end);
int generateRandomIndex(int start, int end);

void merge(std::vector<int> &leftArr, std::vector<int> &rightArr, std::vector<int> &arr);

#endif //INC_2__QUICK_AND_MERGE_SORTS_AND_HEAPS_ADVANCED_SORTS_H