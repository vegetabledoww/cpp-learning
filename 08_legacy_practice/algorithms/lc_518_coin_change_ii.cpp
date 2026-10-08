/*
LeetCode 518：零钱兑换 II

coins 中是互不相同的正面额，每种不限数量，返回凑出 amount>=0 的组合数；不同顺序视为同一种。题目保证最终答案<=INT_MAX。

样例一：amount=5,coins=[1,2,5] -> 4，5；2+2+1；2+1+1+1；五个1。
样例二：amount=3,coins=[2] -> 0，奇数无法凑出。
来源：new_function/test_function.cpp:831-843（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution
{
  public:
    int change(int amount, vector<int> &coins)
    {
        vector<int> dp(amount + 1);
        dp[0] = 1;
        for (int coin : coins)
            for (int i = coin; i <= amount; ++i)
            {
                // 中间金额的方案数也可能溢出，即使最终目标不可达。
                // 计数只做非负加法；超过 int 的状态封顶，不影响承诺范围内的最终答案。
                if (dp[i] > INT_MAX - dp[i - coin])
                    dp[i] = INT_MAX;
                else
                    dp[i] += dp[i - coin];
            }
        return dp[amount];
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
    vector<int> a = {1, 2, 5}, b = {2};
    fail += check("sample1", s.change(5, a), 4);
    fail += check("sample2", s.change(3, b), 0);
    fail += check("zero amount", s.change(0, a), 1);
    vector<int> even;
    for (int i = 2; i <= 200; i += 2)
        even.push_back(i);
    fail += check("intermediate overflow regression", s.change(4999, even), 0);
    return fail ? 1 : 0;
}

/* 收获点：先硬币后金额，避免将排列重复计数。时间 O(amount*币种数)，空间 O(amount)。 */
