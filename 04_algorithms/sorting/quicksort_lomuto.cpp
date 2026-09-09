/*
题目：Lomuto 分区快速排序

给定一个整数数组，请使用 Lomuto 分区方案实现快速排序，将数组按升序排列。
分区时选择当前区间最右侧元素作为基准值。

示例一：
输入：[10,7,8,9,1,5,3,2,4,6]
输出：[1,2,3,4,5,6,7,8,9,10]

示例二：
输入：[3,-1,3,0]
输出：[-1,0,3,3]
*/

#include <iostream>
#include <vector>
using namespace std;
// 分区函数（Lomuto方案）
int partition(vector<int>& arr, int low, int high) {
    // 选择最右边的元素作为基准
    int pivot = arr[high];
    
    // 指向小于基准区域的最后一个元素
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        // 如果当前元素小于等于基准
        if (arr[j] <= pivot) {
            i++;
            // 将当前元素交换到小于基准的区域
            swap(arr[i], arr[j]);
        }
    }
    
    // 将基准元素交换到正确位置 (i+1)
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 快速排序主函数
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi 是分区操作返回的基准索引
        int pi = partition(arr, low, high);
        
        // 递归排序基准左边和右边的子数组
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 重载函数，提供更简洁的接口
void quickSort(vector<int>& arr) {
    quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
}

// 打印数组的辅助函数
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// 测试代码
int main() {
    vector<int> arr1={10,7,8,9,1,5,3,2,4,6};
    quickSort(arr1);
    cout << "示例一 expected=1 2 3 4 5 6 7 8 9 10\nactual=";
    printArray(arr1);

    vector<int> arr2={3,-1,3,0};
    quickSort(arr2);
    cout << "示例二 expected=-1 0 3 3\nactual=";
    printArray(arr2);
    
    return 0;
}
