/*
三数递增 K 次后的最大乘积

恢复练习：三个非负整数，每次任选一个加1，恰好做 k 次，返回最大乘积。学习范围每个初值和 k 都不超过1000。

样例一：[1,2,3],k=2 -> 18，两次都补到较小者，可得到 [3,2,3]。
样例二：[0,0,0],k=3 -> 1，三个数各补一次。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:494-513（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

long long maximizeProduct(array<int, 3> values, int k)
{
    while (k--)
    {
        auto it = min_element(values.begin(), values.end());
        ++*it;
    }
    return 1LL * values[0] * values[1] * values[2];
}
long long bruteProduct(array<int, 3> values, int k)
{
    long long best = 0;
    for (int a = 0; a <= k; ++a)
        for (int b = 0; b <= k - a; ++b)
            best = max(best, 1LL * (values[0] + a) * (values[1] + b) * (values[2] + k - a - b));
    return best;
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
    fail += check("sample1", maximizeProduct({1, 2, 3}, 2), 18LL);
    fail += check("sample2", maximizeProduct({0, 0, 0}, 3), 1LL);
    fail += check("zero operations", maximizeProduct({1, 2, 3}, 0), 6LL);
    bool ok = true;
    for (int a = 0; a <= 3; ++a)
        for (int b = 0; b <= 3; ++b)
            for (int c = 0; c <= 3; ++c)
                for (int k = 0; k <= 6; ++k)
                    if (maximizeProduct({a, b, c}, k) != bruteProduct({a, b, c}, k))
                        ok = false;
    fail += check("448 inputs vs allocations", ok, true);
    return fail ? 1 : 0;
}

/* 收获点：非负数中补小值可以使乘积更大，乘法前提升 long long。时间 O(k)，空间 O(1)。枚举分配测试覆盖多个0及并列最小值。 */
