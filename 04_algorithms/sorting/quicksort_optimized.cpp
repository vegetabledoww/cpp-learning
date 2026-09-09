/*
题目：优化版三路快速排序

给定一个数组，将其按升序排列。使用三路分区把当前区间分成“小于基准”、
“等于基准”和“大于基准”三部分；小区间改用插入排序，并优先递归较短区间，
从而改善重复元素较多时的效率和递归栈深度。

示例一：
输入：[10,7,8,9,1,5,3,2,4,6]
输出：[1,2,3,4,5,6,7,8,9,10]

示例二：
输入：[4,2,4,1,4,2]
输出：[1,2,2,4,4,4]
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Insertion sort for small ranges (enhances performance)
template <typename T>
static void insertionSort(vector<T>& a, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        T key = a[i];
        int j = i - 1;
        while (j >= left && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

// 3-way Quick Sort with tail-recursion elimination
template <typename T>
static void quickSort3way(vector<T>& a, int left, int right) {
    const int INSERTION_SORT_THRESHOLD = 16;
    while (left < right) {
        if (right - left + 1 <= INSERTION_SORT_THRESHOLD) {
            insertionSort(a, left, right);
            break;
        }

        T pivot = a[left + (right - left) / 2];
        int lt = left, i = left, gt = right;
        while (i <= gt) {
            if (a[i] < pivot) swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else ++i;
        }

        // Now: [left, lt-1] < pivot, [lt, gt] == pivot, [gt+1, right] > pivot
        // Recurse on smaller part first to minimize stack depth
        if (lt - left < right - gt) {
            quickSort3way(a, left, lt - 1);
            left = gt + 1; // tail-call optimization: sort the right part in the next loop iteration
        } else {
            quickSort3way(a, gt + 1, right);
            right = lt - 1;
        }
    }
}

// Read integers from file (unchanged behavior)
vector<int> readFromFile(const string& filename) {
    vector<int> data;
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return data;
    }
    int num;
    while (inFile >> num) {
        data.push_back(num);
    }
    inFile.close();
    return data;
}

// Write integers to file
void writeToFile(const string& filename, const vector<int>& data) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open file " << filename << " for writing" << endl;
        return;
    }
    for (size_t i = 0; i < data.size(); i++) {
        outFile << data[i];
        if (i < data.size() - 1) outFile << " ";
    }
    outFile << endl;
    outFile.close();
}

template <typename T>
static void printArray(const vector<T>& arr, const string& message) {
    cout << message;
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    vector<int> data1={10,7,8,9,1,5,3,2,4,6};
    quickSort3way(data1,0,static_cast<int>(data1.size())-1);
    cout << "示例一 expected=1 2 3 4 5 6 7 8 9 10\n";
    printArray(data1,"actual=");

    vector<int> data2={4,2,4,1,4,2};
    quickSort3way(data2,0,static_cast<int>(data2.size())-1);
    cout << "示例二 expected=1 2 2 4 4 4\n";
    printArray(data2,"actual=");

    return 0;
}
