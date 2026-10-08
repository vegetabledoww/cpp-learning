/*
LeetCode 34：在排序数组中查找元素的第一个和最后一个位置

非递减数组 nums 中查找 target，返回首末下标；不存在返回 [-1,-1]，要求 O(log n)。

样例一：[5,7,7,8,8,10],8 -> [3,4]，8 连续出现两次。
样例二：[5,7,7,8,8,10],6 -> [-1,-1]，没有 6。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:57-83（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution
{
  public:
    int boundary(const vector<int> &nums, int target, bool upper)
    {
        int left = 0, right = int(nums.size()) - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target || (upper && nums[mid] == target))
                left = mid + 1;
            else
                right = mid - 1;
        }
        return left;
    }
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int start = boundary(nums, target, false);
        if (start == int(nums.size()) || nums[start] != target)
            return {-1, -1};
        // 修复：直接找第一个 >target，避免 target+1 在 INT_MAX 时溢出。
        return {start, boundary(nums, target, true) - 1};
    }
};

// 本地验证

template <class T> void show(const T &value)
{
    cout << value;
}
template <class T> void show(const vector<T> &values)
{
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i)
            cout << ',';
        show(values[i]);
    }
    cout << ']';
}
template <class T> int check(const char *name, const T &actual, const T &expected)
{
    cout << name << " expected=";
    show(expected);
    cout << " actual=";
    show(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int fail = 0;
    Solution s;
    vector<int> a = {5, 7, 7, 8, 8, 10}, b = {INT_MAX, INT_MAX}, c = {};
    fail += check("sample1", s.searchRange(a, 8), vector<int>{3, 4});
    fail += check("sample2", s.searchRange(a, 6), vector<int>{-1, -1});
    fail += check("overflow regression", s.searchRange(b, INT_MAX), vector<int>{0, 1});
    fail += check("empty", s.searchRange(c, 0), vector<int>{-1, -1});
    return fail ? 1 : 0;
}

/* 收获点：左右边界分别二分，避免通过 target+1 寻找右边界。时间 O(log n)，额外空间 O(1)。 */
