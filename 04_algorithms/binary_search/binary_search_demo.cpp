#include <iostream>
#include <vector>
using namespace std;

/**
 * Binary Search Algorithm (Iterative Version)
 * @param arr Sorted array
 * @param target Target value to search for
 * @return Index of target value, returns -1 if not found
 */
int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Prevent overflow
        
        if (arr[mid] == target) {
            return mid;  // Found target
        } else if (arr[mid] < target) {
            left = mid + 1;  // Target in right half
        } else {
            right = mid - 1;  // Target in left half
        }
    }
    
    return -1;  // Target not found
}

/**
 * Binary Search Algorithm (Recursive Version)
 * @param arr Sorted array
 * @param target Target value to search for
 * @param left Left boundary
 * @param right Right boundary
 * @return Index of target value, returns -1 if not found
 */
int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;  // Target not found
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;  // Found target
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);  // Search in right half
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1);  // Search in left half
    }
}

/**
 * Find the first occurrence of target value
 */
int findFirst(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching in left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

/**
 * Find the last occurrence of target value
 */
int findLast(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching in right half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

/**
 * Print array
 */
void printArray(const vector<int>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    // Test Case 1: Basic Binary Search
    vector<int> arr1 = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int target1 = 7;
    
    cout << "=== Test Case 1: Basic Binary Search ===" << endl;
    cout << "Array: ";
    printArray(arr1);
    cout << "Target: " << target1 << endl;
    
    int result1 = binarySearch(arr1, target1);
    if (result1 != -1) {
        cout << "Iterative version: Found target at index " << result1 << endl;
    } else {
        cout << "Iterative version: Target not found" << endl;
    }
    
    int result2 = binarySearchRecursive(arr1, target1, 0, arr1.size() - 1);
    if (result2 != -1) {
        cout << "Recursive version: Found target at index " << result2 << endl;
    } else {
        cout << "Recursive version: Target not found" << endl;
    }
    
    // Test Case 2: Search for non-existent value
    int target2 = 8;
    cout << "\n=== Test Case 2: Search for Non-existent Value ===" << endl;
    cout << "Target: " << target2 << endl;
    int result3 = binarySearch(arr1, target2);
    if (result3 != -1) {
        cout << "Found target at index " << result3 << endl;
    } else {
        cout << "Target not found" << endl;
    }
    
    // Test Case 3: Search for duplicate elements
    vector<int> arr2 = {1, 2, 2, 2, 3, 4, 5, 5, 5, 6};
    int target3 = 2;
    
    cout << "\n=== Test Case 3: Search for Duplicate Elements ===" << endl;
    cout << "Array: ";
    printArray(arr2);
    cout << "Target: " << target3 << endl;
    
    int first = findFirst(arr2, target3);
    int last = findLast(arr2, target3);
    
    if (first != -1) {
        cout << "First occurrence at index: " << first << endl;
        cout << "Last occurrence at index: " << last << endl;
        cout << "Total occurrences: " << (last - first + 1) << endl;
    } else {
        cout << "Target not found" << endl;
    }
    
    // Test Case 4: Boundary cases
    cout << "\n=== Test Case 4: Boundary Cases ===" << endl;
    cout << "Search for first element: " << arr1[0] << endl;
    cout << "Result index: " << binarySearch(arr1, arr1[0]) << endl;
    
    cout << "Search for last element: " << arr1[arr1.size()-1] << endl;
    cout << "Result index: " << binarySearch(arr1, arr1[arr1.size()-1]) << endl;
    
    return 0;
}