/*
曼哈顿距离内的最大邻域人数

恢复最终版本规则：从已给坐标中选一个人作为中心，统计距离 |dx|+|dy|<=k 的人数（包含本人），返回最大值。重合位置按不同人计数，k>=0。

样例一：[(0,0),(1,0),(3,0)],k=1 -> 2，前两个互相覆盖。
样例二：[(0,0),(0,0),(1,1)],k=0 -> 2，重合的两人都计数。
来源：huawei/huawei/huawei.cpp:499-536（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <algorithm>
using namespace std;

int maxNeighbors(const vector<pair<int, int>> &people, long long k)
{
    int ans = 0;
    for (const auto &p : people)
    {
        int count = 0;
        for (const auto &q : people)
        {
            long long distance = llabs(1LL * p.first - q.first) + llabs(1LL * p.second - q.second);
            if (distance <= k)
                ++count;
        }
        ans = max(ans, count);
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
    fail += check("sample1", maxNeighbors({{0, 0}, {1, 0}, {3, 0}}, 1), 2);
    fail += check("sample2", maxNeighbors({{0, 0}, {0, 0}, {1, 1}}, 0), 2);
    fail += check("empty", maxNeighbors({}, 1), 0);
    fail += check("sorted endpoints insufficient", maxNeighbors({{0, 0}, {1, 100}, {2, 0}}, 2), 2);
    return fail ? 1 : 0;
}

/* 收获点：保留枚举中心再扫描；只按 x 排序不能靠两个端点保证所有点都满足曼哈顿约束。时间 O(n²)，额外空间 O(1)。 */
