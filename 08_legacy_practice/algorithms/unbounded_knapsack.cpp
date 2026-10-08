/*
完全背包

每类物品可取任意次，重量为正整数、价值非负；wgt 与 val 等长。容量 cap>=0，求总重量不超过 cap 的最大价值。结果在 int 范围。

样例一：wgt=[2,3], val=[3,4], cap=6 -> 9，选三个重量 2。
样例二：wgt=[5], val=[10], cap=4 -> 0，一件也装不下。
来源：../originals/new_function/test_function.cpp:363-381（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int unboundedKnapsackDP(vector<int> &wgt, vector<int> &val, int cap)
{
    int n = wgt.size();
    // 初始化 dp 表
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));
    // 状态转移
    for (int i = 1; i <= n; i++)
    {
        for (int c = 1; c <= cap; c++)
        {
            if (wgt[i - 1] > c)
            {
                // 若超过背包容量，则不选物品 i
                dp[i][c] = dp[i - 1][c];
            }
            else
            {
                // 不选和选物品 i 这两种方案的较大值
                dp[i][c] = max(dp[i - 1][c], dp[i][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[n][cap];
}

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
    vector<int> a = {2, 3}, b = {3, 4}, c = {5}, d = {10};
    fail += check("sample1", unboundedKnapsackDP(a, b, 6), 9);
    fail += check("sample2", unboundedKnapsackDP(c, d, 4), 0);
    fail += check("zero capacity", unboundedKnapsackDP(a, b, 0), 0);
    return fail ? 1 : 0;
}

/* 收获点：与 0/1 背包比较：选当前物品后仍取 dp[i]，所以可重复选。时间、空间 O(n*cap)。 */
