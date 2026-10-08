/*
区间异或与有界整数异或最大值

按旧稿恢复的小规模练习：每个查询 [l,r,m] 下标从1开始，先求 a[l..r] 异或值 x，再求 max(x XOR k),0<=k<=m；所有查询的最大值再异或得到结果。元素非负int，0<=m<=100000，区间合法。

样例一：a=[1,2,3],query=[1,2,2] -> 3，x=3，k=0最大。
样例二：a=[1,2,3],queries=[[1,2,2],[2,3,2]] -> 0，两项最大值均为3，3 XOR 3=0。
来源：mi/mi/mi.cpp:8-44（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int answerQueries(const vector<int> &a, const vector<vector<int>> &queries)
{
    vector<int> prefix(a.size() + 1);
    for (size_t i = 0; i < a.size(); ++i)
        prefix[i + 1] = prefix[i] ^ a[i];
    int totalXor = 0;
    for (const auto &q : queries)
    {
        int value = prefix[q[1]] ^ prefix[q[0] - 1], maxVal = 0;
        for (int k = 0; k <= q[2]; ++k)
            maxVal = max(maxVal, value ^ k);
        totalXor ^= maxVal;
    }
    return totalXor;
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
    fail += check("sample1", answerQueries({1, 2, 3}, {{1, 2, 2}}), 3);
    fail += check("sample2", answerQueries({1, 2, 3}, {{1, 2, 2}, {2, 3, 2}}), 0);
    fail += check("m zero", answerQueries({7}, {{1, 1, 0}}), 7);
    fail += check("no query", answerQueries({}, {}), 0);
    return fail ? 1 : 0;
}

/* 收获点：保留枚举 k，区间异或使用前缀快速取得。时间 O(n+查询数+各m之和)，空间 O(n)。原 m 上界未知，本版明确只承诺小规模练习。 */
