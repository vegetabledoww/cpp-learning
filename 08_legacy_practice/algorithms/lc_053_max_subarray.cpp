/*
LeetCode 53：最大子数组和

返回整数数组中非空连续子数组的最大和。练习扩展：空数组返回 0。测试数据的累加和在 int 范围内。

样例一：[-2,1,-3,4,-1,2,1,-5,4] -> 6，连续段 [4,-1,2,1]。
样例二：[-3,-1,-2] -> -1，只取 -1。
来源：../originals/Top_K_C++/demo.cpp:495-508（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n);
        if (!n)
            return 0;
        dp[0] = nums[0];
        for (int i = 1; i < n; i++)
        {
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
            /*dp[i] 有两种「选择」，要么与前面的相邻子数
        组连接，形成一个和更大的子数组；要么不与前面
        的子数组连接，自成一派，自己作为一个子数组。*/
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
    vector<int> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4}, b = {-3, -1, -2}, c = {};
    fail += check("sample1", s.maxSubArray(a), 6);
    fail += check("sample2", s.maxSubArray(b), -1);
    fail += check("empty", s.maxSubArray(c), 0);
    return fail ? 1 : 0;
}

/* 收获点：保留 dp[i]：以 i 结尾的最大和。时间 O(n)，空间 O(n)。 */
