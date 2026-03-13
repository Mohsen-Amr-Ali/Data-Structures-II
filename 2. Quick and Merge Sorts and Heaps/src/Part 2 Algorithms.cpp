#include "../include/Part 2 Algorithms.h"

#include "../include/Advanced Sorts.h"
#include <vector>

#include "../include/Sorts.h"

using namespace std;

int quickSelect(vector<int> &arr, int start, int end, int k){
    int pivot = randomPartition(arr, start, end);

    if (pivot < k-1) { //kth element after pivot, take the right side of the array
        return quickSelect(arr, pivot + 1, end, k);
    }

    if (pivot > k-1) { //kth element before pivot, take the left side of the array
        return quickSelect(arr, start, pivot - 1, k);
    }

    return arr[pivot]; //basecase
}

void hybridSort(vector<int> &arr, int threshold) {
    int size = arr.size();
    if (size <= 1) return;
    if (size <= threshold) {
        selectionSort(arr);
        return;
    }

    int middle = size/2;

    vector<int> leftArr(arr.begin(), arr.begin() + middle);
    vector<int> rightArr(arr.begin() + middle, arr.end());

    hybridSort(leftArr, threshold);
    hybridSort(rightArr, threshold);

    merge(leftArr, rightArr, arr);
}