#include "sorts.h"
#include <vector>

using namespace std;

void bubbleSort(vector<int> &arr) {
    const size_t size = arr.size(); //size_t is better than int beecause it could handle larger numbers

    for (size_t start=0; start < size-1; start++) {
        bool swapped = false;

        for (size_t index=0; index < size - start - 1; index++) {
            if (arr[index] > arr[index + 1]) {
                swap(arr[index], arr[index + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

void selectionSort(vector<int> &arr) {
    const size_t size = arr.size();

    for (size_t start=0; start < size - 1; start++) {
        size_t min_index = start;

        for (size_t index = start + 1; index < size; index++) {
            if (arr[index] < arr[min_index]) {
                min_index = index;
            }
        }

        if (min_index != start) swap(arr[start], arr[min_index]);
    }
}

void insertionSort(vector<int> &arr) {
    const size_t size = arr.size();

    for (size_t start = 1; start < size; start++) {
        int temp = arr[start];
        long long index = start - 1;

        while (index >= 0 && arr[index] > temp) {
            arr[index + 1] = arr[index];
            index--;
        }

        arr[index + 1] = temp;
    }
}
