/*
0/1 背包

每件物品最多取一次，重量正整数、价值非负、两个数组等长。容量 cap>=0，求不超重的最大价值。结果在 int 范围。

样例一：wgt=[1,2,3], val=[5,11,15], cap=4 -> 20，选重量 1 和 3。
样例二：wgt=[2], val=[3], cap=4 -> 3，只有一件，不能选两次。
来源：../originals/9_test/9_test/9_test.cpp:378-393（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsackDP(vector<int> &wgt, vector<int> &val, int cap)
{
    int n = wgt.size();
    // 初始化 dp 表
    vector<int> dp(cap + 1, 0);
    // 状态转移
    for (int i = 1; i <= n; i++)
    {
        for (int c = cap; c >= 1; c--) //倒序进行
        {
            if (wgt[i - 1] <= c)
            {
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
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
    vector<int> a = {1, 2, 3}, b = {5, 11, 15}, c = {2}, d = {3};
    fail += check("sample1", knapsackDP(a, b, 4), 20);
    fail += check("sample2", knapsackDP(c, d, 4), 3);
    fail += check("zero", knapsackDP(a, b, 0), 0);
    return fail ? 1 : 0;
}

/* 收获点：容量倒序使 dp[c-w] 仍代表上一轮，避免一件物品用多次。时间 O(n*cap)，空间 O(cap)。 */
