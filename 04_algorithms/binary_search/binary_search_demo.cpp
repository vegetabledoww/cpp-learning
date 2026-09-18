/*
题目：基础二分查找与重复元素边界

给定一个按非递减顺序排列的整数数组 nums 和一个目标值 target，请完成：
1. 使用迭代二分查找 target；找到时返回它的下标，否则返回 -1。
2. 使用递归二分查找完成相同功能。
3. 当 target 重复出现时，返回它第一次出现的下标。
4. 当 target 重复出现时，返回它最后一次出现的下标。

普通二分查找只要求返回任意一个等于 target 的位置。
查找第一次和最后一次出现位置时，必须继续收缩搜索区间。

示例一：
输入：nums = {1,3,5,7,9}，target = 7
输出：普通二分下标 = 3，第一次出现下标 = 3，最后一次出现下标 = 3
解释：数组下标从 0 开始，7 位于下标 3，并且只出现一次。

示例二：
输入：nums = {1,2,2,2,3}，target = 2
输出：第一次出现下标 = 1，最后一次出现下标 = 3
解释：普通二分可以返回下标 1、2、3 中的任意一个；边界查找必须返回 1 和 3。

要求：
- 输入数组已经按非递减顺序排列；
- 数组可以为空；
- 所有查找函数的时间复杂度应为 O(log n)。
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int binarySearch(const vector<int>& nums, int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left <= right)
    {
        // 这种写法避免直接计算 left + right 可能产生的整数溢出。
        int mid = left + (right - left) / 2;

        if (nums[mid] == target)
        {
            return mid;
        }
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

int binarySearchRecursive(const vector<int>& nums,
                          int target,
                          int left,
                          int right)
{
    // 区间为空，说明目标值不存在。
    if (left > right)
    {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (nums[mid] == target)
    {
        return mid;
    }
    if (nums[mid] < target)
    {
        return binarySearchRecursive(nums, target, mid + 1, right);
    }
    return binarySearchRecursive(nums, target, left, mid - 1);
}

int findFirst(const vector<int>& nums, int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    int answer = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target)
        {
            answer = mid;
            // 已经找到一个 target，但左侧可能还有，所以继续搜索左半部分。
            right = mid - 1;
        }
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return answer;
}

int findLast(const vector<int>& nums, int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    int answer = -1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target)
        {
            answer = mid;
            // 已经找到一个 target，但右侧可能还有，所以继续搜索右半部分。
            left = mid + 1;
        }
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return answer;
}

bool checkResult(const string& testName, int actual, int expected)
{
    cout << testName
         << "：期望结果 = " << expected
         << "，实际结果 = " << actual
         << (actual == expected ? "，通过" : "，失败") << '\n';

    return actual == expected;
}

int main()
{
    int failedCount = 0;

    vector<int> nums1 = {1,3,5,7,9};
    if (!checkResult("示例一：迭代二分", binarySearch(nums1, 7), 3))
        failedCount++;
    if (!checkResult("示例一：递归二分",
                     binarySearchRecursive(nums1, 7, 0,
                                           static_cast<int>(nums1.size()) - 1),
                     3))
        failedCount++;

    vector<int> nums2 = {1,2,2,2,3};
    if (!checkResult("示例二：第一次出现", findFirst(nums2, 2), 1))
        failedCount++;
    if (!checkResult("示例二：最后一次出现", findLast(nums2, 2), 3))
        failedCount++;

    if (!checkResult("目标值不存在", binarySearch(nums1, 8), -1))
        failedCount++;
    if (!checkResult("查找第一个元素", binarySearch(nums1, 1), 0))
        failedCount++;
    if (!checkResult("查找最后一个元素", binarySearch(nums1, 9), 4))
        failedCount++;

    vector<int> emptyNums;
    if (!checkResult("空数组：迭代二分", binarySearch(emptyNums, 1), -1))
        failedCount++;
    if (!checkResult("空数组：递归二分",
                     binarySearchRecursive(emptyNums, 1, 0,
                                           static_cast<int>(emptyNums.size()) - 1),
                     -1))
        failedCount++;
    if (!checkResult("空数组：第一次出现", findFirst(emptyNums, 1), -1))
        failedCount++;
    if (!checkResult("空数组：最后一次出现", findLast(emptyNums, 1), -1))
        failedCount++;

    cout << "失败用例数：" << failedCount << '\n';
    return failedCount;
}

/*
收获点：
1. 二分查找的前提是搜索区间具有单调性，本题中的数组必须有序。
2. 使用闭区间 [left, right] 时，循环条件固定为 left <= right。
3. 查找第一次出现位置：找到 target 后记录答案，再令 right = mid - 1。
4. 查找最后一次出现位置：找到 target 后记录答案，再令 left = mid + 1。
5. 四种查找的时间复杂度都是 O(log n)。迭代版本额外空间复杂度为 O(1)；
   递归版本需要 O(log n) 的递归栈空间。
*/
