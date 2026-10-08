/*
排列后前缀极差之和最小

按原函数恢复：重排数组，使每个非空前缀的最大值减最小值之和最小，返回最小和。学习版枚举排列，n<=9、元素绝对值<=10^9；空数组为0。

样例一：[1,2,4] -> 4，排列 [1,2,4] 的前缀极差为0、1、3。
样例二：[4,1,2] -> 4，输入顺序不应影响所有排列的最小值。
来源：10.22/10.22/10.22.cpp:199-222（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

long long calculateMinSum(vector<int> sequence)
{
    if (sequence.empty())
        return 0;
    sort(sequence.begin(), sequence.end()); // 修复：从最小排列起枚举才不会漏掉较小排列。
    long long minSum = LLONG_MAX;
    do
    {
        int minVal = sequence[0], maxVal = sequence[0];
        long long sum = 0;
        for (int x : sequence)
        {
            minVal = min(minVal, x);
            maxVal = max(maxVal, x);
            sum += 1LL * maxVal - minVal;
        }
        minSum = min(minSum, sum);
    } while (next_permutation(sequence.begin(), sequence.end()));
    return minSum;
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
    fail += check("sample1", calculateMinSum({1, 2, 4}), 4LL);
    fail += check("sample2 unsorted regression", calculateMinSum({4, 1, 2}), 4LL);
    fail += check("empty", calculateMinSum({}), 0LL);
    fail += check("equal", calculateMinSum({3, 3, 3}), 0LL);
    fail += check("large range", calculateMinSum({-1000000000, 1000000000}), 2000000000LL);
    return fail ? 1 : 0;
}

/* 收获点：保留穷举而不是假定未知原题规模。时间 O(n*n!)，空间 O(n) 输入副本。修复漏枚举和 int 累加风险。 */
