/*
LeetCode 70：爬楼梯

每次上 1 或 2 级，求恰好上 n 级的方法数，1 <= n <= 45。

样例一：n=2 -> 2，1+1 或 2。
样例二：n=3 -> 3，1+1+1、1+2、2+1。
来源：../originals/_top_k_8/_top_k_8/_top_k_8.cpp:214-227（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    int climbStairs(int n)
    {
        //base case
        if (n <= 2)
            return n;
        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i < n + 1; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp.back();
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
    fail += check("sample1", s.climbStairs(2), 2);
    fail += check("sample2", s.climbStairs(3), 3);
    fail += check("single", s.climbStairs(1), 1);
    fail += check("upper bound", s.climbStairs(45), 1836311903);
    return fail ? 1 : 0;
}

/* 收获点：最后一步来自 n-1 或 n-2。时间 O(n)，空间 O(n)。 */
