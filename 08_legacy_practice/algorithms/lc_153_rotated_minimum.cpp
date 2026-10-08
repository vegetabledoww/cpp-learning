/*
LeetCode 153：寻找旋转排序数组中的最小值

非空、互不相同的升序数组经过旋转，返回最小值。要求 O(log n)。

样例一：[3,4,5,1,2] -> 1，旋转分界处最小。
样例二：[11,13,15,17] -> 11，未旋转也适用。
来源：../originals/_top_k_8/_top_k_8/_top_k_8.cpp:264-275（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    int findMin(vector<int> &nums)
    {
        int low = 0, high = nums.size() - 1;
        while (low < high) // 相遇时就是答案；继续推进会越界
        {
            int pivot = low + (high - low) / 2;
            if (nums[pivot] < nums[high])
                high = pivot;
            else
                low = pivot + 1;
        }
        return nums[low];
    }
};

// 以下仅为本地样例验证；提交平台时保留上面的题解即可。

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
    vector<int> a = {3, 4, 5, 1, 2}, b = {11, 13, 15, 17}, c = {7}, d = {2, 1};
    fail += check("sample1", s.findMin(a), 1);
    fail += check("sample2", s.findMin(b), 11);
    fail += check("single regression", s.findMin(c), 7);
    fail += check("two", s.findMin(d), 1);
    return fail ? 1 : 0;
}

/* 收获点：修正题号及 low<=high 的越界。时间 O(log n)，空间 O(1)。 */
