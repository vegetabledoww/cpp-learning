/*
按出现次数过滤数组

恢复练习：删除所有总出现次数位于闭区间 [l,r] 的数值，剩余元素保留原顺序。保证 0<=l<=r。

样例一：[1,2,2,3,3,3],l=2,r=2 -> [1,3,3,3]，只删出现两次的 2。
样例二：[1,1,2],l=1,r=2 -> []，所有值的频次都命中。
来源：10.22/10.22/10.22.cpp:154-194（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> filterByFrequency(const vector<int> &nums, int l, int r)
{
    unordered_map<int, int> countMap;
    for (int x : nums)
        ++countMap[x];
    vector<int> result;
    for (int x : nums)
        if (countMap[x] < l || countMap[x] > r)
            result.push_back(x);
    return result;
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
    fail += check("sample1", filterByFrequency({1, 2, 2, 3, 3, 3}, 2, 2), vector<int>{1, 3, 3, 3});
    fail += check("sample2", filterByFrequency({1, 1, 2}, 1, 2), vector<int>{});
    fail += check("empty", filterByFrequency({}, 1, 2), vector<int>{});
    fail += check("preserve order", filterByFrequency({3, 1, 3, 2}, 1, 1), vector<int>{3, 3});
    return fail ? 1 : 0;
}

/* 收获点：先统计完整频率再过滤，不能一边累计一边决定删除。期望时间 O(n)，空间 O(n)。 */
