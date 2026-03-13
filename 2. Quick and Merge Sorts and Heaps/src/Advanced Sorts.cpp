#include "../include/Advanced Sorts.h"

#include <vector>
#include <cstdlib>

using namespace std;

//####################### O(nlog(n)) Algorithms #######################\\

//=========== Quick Sort ===========\\

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

//=========== Merge Sort ===========\\