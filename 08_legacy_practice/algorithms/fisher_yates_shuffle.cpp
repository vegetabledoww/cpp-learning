/*
Fisher–Yates 洗牌

原地随机排列数组。每步 i 从 n-1 降到1，只在 [0,i] 均匀选择 j 与 i 交换。随机输出不固定，测试验证元素守恒和给定选择序列的结果。

样例一：[1,2,3]，从 i=2 到1依次选择 j=0,0 -> [2,3,1]。
样例二：[1,2]，i=1选择 j=0 -> [2,1]；选择 j=1 -> [1,2]。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:420-446; Char/main.cpp:66-95（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <set>
using namespace std;

void fisherYates(vector<int> &arr, mt19937 &gen)
{
    for (int i = int(arr.size()) - 1; i >= 1; --i)
    {
        uniform_int_distribution<int> choose(0, i);
        swap(arr[i], arr[choose(gen)]);
    }
}
vector<int> chosenShuffle(vector<int> arr, const vector<int> &choices)
{
    size_t p = 0;
    for (int i = int(arr.size()) - 1; i >= 1; --i)
        swap(arr[i], arr[choices[p++]]);
    return arr;
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
    fail += check("sample1", chosenShuffle({1, 2, 3}, {0, 0}), vector<int>{2, 3, 1});
    fail += check("sample2", chosenShuffle({1, 2}, {0}), vector<int>{2, 1});
    set<vector<int>> results;
    for (int a = 0; a < 3; ++a)
        for (int b = 0; b < 2; ++b)
            results.insert(chosenShuffle({1, 2, 3}, {a, b}));
    fail += check("all six equiprobable choice paths", int(results.size()), 6);
    mt19937 gen(2026);
    vector<int> a = {1, 2, 2, 3};
    fisherYates(a, gen);
    sort(a.begin(), a.end());
    fail += check("multiset preserved", a, vector<int>{1, 2, 2, 3});
    vector<int> empty;
    fisherYates(empty, gen);
    fail += check("empty", empty, vector<int>{});
    return fail ? 1 : 0;
}

/* 收获点：修复原 i>=2 漏掉最后一次交换、从全数组选取和取模偏差。mt19937 是伪随机；normal_distribution 第二参数是标准差，不是方差。洗牌时间 O(n)，额外空间 O(1)。 */
