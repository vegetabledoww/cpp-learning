/*
LeetCode 2144：打折购买糖果的最小开销

购买两颗糖，可免费拿一颗价格不超过这两颗中较便宜者的糖；求拿到所有糖的最小开销。价格正整数，总价在 int 范围。

样例一：[1,2,3] -> 5，买3和2，免费1。
样例二：[3,3,3,1] -> 7，买两颗3送一颗3，另买1。
来源：huawei/huawei/huawei.cpp:98-123（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int minimumCost(vector<int> &cost)
    {
        sort(cost.rbegin(), cost.rend());
        int sum = 0;
        for (size_t i = 0; i < cost.size(); ++i)
            if (i % 3 != 2)
                sum += cost[i];
        return sum;
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
    vector<int> a = {1, 2, 3}, b = {3, 3, 3, 1}, c = {5}, d = {};
    fail += check("sample1", s.minimumCost(a), 5);
    fail += check("sample2 tail regression", s.minimumCost(b), 7);
    fail += check("single", s.minimumCost(c), 5);
    fail += check("empty extension", s.minimumCost(d), 0);
    return fail ? 1 : 0;
}

/* 收获点：从贵到便宜，每三项免掉第三项。修复旧稿末组越界及尾部重复计费。时间 O(n log n)，排序栈空间 O(log n)。 */
