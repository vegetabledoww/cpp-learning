/*
缩短木棍得到最大三角形周长

三根正整数长度木棍，允许缩短为正整数，不允许增长；求能构成非退化三角形的最大周长。每根长度<=10^9。

样例一：[2,3,10] -> 9，把最长缩为4，周长2+3+4。
样例二：[3,4,5] -> 12，已经满足三角形不等式。
来源：10.22/10.22/10.22.cpp:107-127（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

long long maxPerimeter(array<int, 3> sticks)
{
    sort(sticks.begin(), sticks.end());
    long long a = sticks[0], b = sticks[1], c = sticks[2];
    c = min(c, a + b - 1);
    return a + b + c;
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
    fail += check("sample1", maxPerimeter({2, 3, 10}), 9LL);
    fail += check("sample2", maxPerimeter({3, 4, 5}), 12LL);
    fail += check("minimum lengths", maxPerimeter({1, 1, 100}), 3LL);
    fail +=
        check("wide perimeter", maxPerimeter({1000000000, 1000000000, 1000000000}), 3000000000LL);
    return fail ? 1 : 0;
}

/* 收获点：保留只缩短最长边的思路，用 c=min(c,a+b-1) 代替逐次减1。正整数边长保证边界。时间、空间 O(1)。 */
