/*
LeetCode 2105：给植物浇水 II

Alice 从左、Bob 从右浇水；每人水不足时补满，水桶初始满。奇数株中间一株由剩水多者浇，平局任意。返回总补水次数。每株需水不超过两人各自容量。

样例一：plants=[2,2,3,3], A=5,B=5 -> 1，Bob 第二株需补水。
样例二：plants=[2,2,3,3], A=3,B=4 -> 2，两人各补一次。
来源：../originals/new_function/test_function.cpp:590-634（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int minimumRefill(vector<int> &plants, int capacityA, int capacityB)
    {
        int n = plants.size(), num1 = 0, num2 = 0;
        int Alice_cur = capacityA, Bob_cur = capacityB;
        for (int i = 0; i < n / 2; ++i)
        {
            if (Alice_cur < plants[i])
            {
                ++num1;
                Alice_cur = capacityA;
            }
            Alice_cur -= plants[i];
        }
        // 偶数株时，下标 n/2 也属于 Bob；旧稿跳过了它。
        for (int i = n - 1; i >= (n + 1) / 2; --i)
        {
            if (Bob_cur < plants[i])
            {
                ++num2;
                Bob_cur = capacityB;
            }
            Bob_cur -= plants[i];
        }
        if (n % 2 && max(Alice_cur, Bob_cur) < plants[n / 2])
            ++num1;
        return num1 + num2;
    }
};

// 以下仅为本地样例验证；提交平台时保留上面的题解即可。

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
    vector<int> a = {2, 2, 3, 3}, b = {5}, c = {2, 2, 3, 2, 2};
    fail += check("sample1 regression", s.minimumRefill(a, 5, 5), 1);
    fail += check("sample2", s.minimumRefill(a, 3, 4), 2);
    fail += check("single", s.minimumRefill(b, 5, 6), 0);
    fail += check("middle refill", s.minimumRefill(c, 5, 5), 1);
    return fail ? 1 : 0;
}

/* 收获点：保留左右分别扫描的实现。修复偶数遗漏，并更正原题号 2109。时间 O(n)，空间 O(1)。 */
