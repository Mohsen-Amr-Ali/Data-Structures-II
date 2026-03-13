#include "../include/Part 2 Algorithms.h"

#include "../include/Advanced Sorts.h"
#include <vector>

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