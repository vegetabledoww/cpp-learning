/*
LeetCode 300：最长递增子序列

返回严格递增子序列的最大长度；子序列不要求连续。空输入返回 0。

样例一：[10,9,2,5,3,7,101,18] -> 4，例如 [2,3,7,101]。
样例二：[7,7,7] -> 1，相等不能延长。
来源：../originals/Top_K_C++/demo.cpp:531-544（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int lengthOfLIS(vector<int> &nums)
    {
        if (nums.empty())
            return 0; // 修复：空数组不能解引用 max_element
        vector<int> dp(nums.size(), 1);
        for (int i = 0; i < int(nums.size()); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
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
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18}, b = {7, 7, 7}, c = {};
    fail += check("sample1", s.lengthOfLIS(a), 4);
    fail += check("sample2", s.lengthOfLIS(b), 1);
    fail += check("empty", s.lengthOfLIS(c), 0);
    return fail ? 1 : 0;
}

/* 收获点：保留二重循环 DP。时间 O(n²)，空间 O(n)。 */
