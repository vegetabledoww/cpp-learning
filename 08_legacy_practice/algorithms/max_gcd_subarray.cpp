/*
长度至少 K 的子数组最大 GCD

按原函数目标恢复的练习：正整数数组，1<=k<=n，返回所有长度至少 k 的连续子数组 GCD 的最大值。采用易读版本，建议 n<=2000。

样例一：[6,10,15],k=2 -> 5，子数组 [10,15] 的 GCD 最大。
样例二：[8,12,16],k=3 -> 4，只有全数组。
来源：9_test/9_test/9_test.cpp:298-325（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int maxGcdSubarray(const vector<int> &arr, int k)
{
    int n = arr.size(), ans = 0;
    // 扩展区间只会使 GCD 不变或减小，最优值一定可在长度 k 的窗口取得。
    for (int left = 0; left + k <= n; ++left)
    {
        int currentGcd = 0;
        for (int i = left; i < left + k; ++i)
            currentGcd = gcd(currentGcd, arr[i]);
        ans = max(ans, currentGcd);
    }
    return ans;
}

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
    fail += check("sample1 removal regression", maxGcdSubarray({6, 10, 15}, 2), 5);
    fail += check("sample2", maxGcdSubarray({8, 12, 16}, 3), 4);
    fail += check("one", maxGcdSubarray({6, 10, 15}, 1), 15);
    return fail ? 1 : 0;
}

/* 收获点：修复用 gcd(current,旧元素) 撤销窗口左端的错误；GCD 没有这样的逆运算。时间 O(n*k*log 最大值)，空间 O(1)。原笔试规模未知，不冒称满足原题性能。 */
