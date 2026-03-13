#include "sorts.h"
#include <vector>
#include <cstdlib>

using namespace std;

//####################### O(n^2) Algorithms #######################\\

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

//####################### O(nlog(n)) Algorithms #######################\\

//======= Quick Sort
void quicksort(vector<int> &arr, int start, int end) {
    if (end <= start) return; //base case beta3etna

    int pivot = randomPartition(arr, start, end);

    quicksort(arr, start, pivot-1); //sort left hand side (less than the pivot)
    quicksort(arr, pivot+1, end); //sort right hand side (more than the pivot)
}

int partition(vector<int> &arr, int start, int end) {
    int pivot = arr[end];
    int i = start -1; //the index i starts before the array

    for (int j = start; j <= end-1; j++) { //we end before the end of the array because the pivot is there
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // this for loop ensures all elements to the left of the pivot are less than it,
    // and all elements to the right of the pivot are more than it.
    // Now we need to actually swap our pivot into its correct position
    i++;
    swap(arr[end], arr[i]);

    return i; //the correct sorted location of our pivot
}

int randomPartition(vector<int> &arr, int start, int end) { //wrapper function to choose pivot randomly
    int RandomPivot = generateRandomIndex(start, end);
    swap(arr[end], arr[RandomPivot]);

    int pivot = partition(arr, start, end);
    return pivot;
}

int generateRandomIndex(int start, int end) {
    return start + (rand() % (end - start + 1));
}