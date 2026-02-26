#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/valarray_after.h>

#include "sorts.h"

using namespace std;
using namespace chrono;

vector<int> generateRandomVector(const size_t size) {
    vector<int> v;  v.reserve(size);
    for (int i = 0; i < size; ++i) {
        v.push_back(rand() % 1000000000); // Random numbers 0-999,999,999
    }
    return v;
}

int main() {
    srand(time(0));

    ofstream logFile("sorting_data.csv");
    logFile << "Size,Algorithm,Time\n";

    for (int n = 500; n<=1'000'000; n*=2) {
        cout << "Testing Size: " << n << endl;

        vector<int> baseData = generateRandomVector(n);

        //======= Bubble sort =======//
        vector<int> data = baseData;
        auto start = high_resolution_clock::now();
        bubbleSort(data);
        auto stop  = high_resolution_clock::now();
        auto duration = duration_cast<chrono::microseconds>(stop - start);
        logFile << n << ",BubbleSort," << duration.count() << "\n";

        //======= Selection sort =======//
        data = baseData;
        start = high_resolution_clock::now();
        selectionSort(data);
        stop  = high_resolution_clock::now();
        duration = duration_cast<chrono::microseconds>(stop - start);
        logFile << n << ",SelectionSort," << duration.count() << "\n";

        //======= Insertion sort =======//
        data = baseData;
        start = high_resolution_clock::now();
        insertionSort(data);
        stop  = high_resolution_clock::now();
        duration = duration_cast<chrono::microseconds>(stop - start);
        logFile << n << ",InsertionSort," << duration.count() << "\n";
    }

    logFile.close();
    cout << "Benchmarks finished. Data written to sorting_data.csv." << endl;

    cout << "Launching Python graph generator..." << endl;

    system("venv\\Scripts\\python.exe plot_graph.py");

    return 0;
}


