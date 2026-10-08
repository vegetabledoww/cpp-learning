/*
分数背包

每件物品只能取一次，但可切分；切分价值按重量成比例。正重量、非负价值，数组等长，容量>=0。返回最大价值（double）。

样例一：wgt=[10,20,30],val=[60,100,120],cap=50 -> 240，取前两件和第三件的2/3。
样例二：wgt=[4],val=[10],cap=2 -> 5，取半件。
来源：new_function/test_function.cpp:434-472（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Item
{
    int w, v;
};
bool higherDensity(const Item &a, const Item &b)
{
    return 1LL * a.v * b.w > 1LL * b.v * a.w; // 在乘法前提升，比较单位重量价值。
}
double fractionalKnapsack(const vector<int> &wgt, const vector<int> &val, int cap)
{
    vector<Item> items;
    for (size_t i = 0; i < wgt.size(); ++i)
        items.push_back({wgt[i], val[i]});
    sort(items.begin(), items.end(), higherDensity);
    double res = 0;
    for (const auto &item : items)
    {
        if (item.w <= cap)
        {
            res += item.v;
            cap -= item.w;
        }
        else
        {
            res += double(item.v) / item.w * cap;
            break;
        }
    }
    return res;
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
    double a = fractionalKnapsack({10, 20, 30}, {60, 100, 120}, 50),
           b = fractionalKnapsack({4}, {10}, 2);
    cout << "sample1 expected=240 actual=" << a << '\n';
    cout << "sample2 expected=5 actual=" << b << '\n';
    fail += check("sample1 tolerance", abs(a - 240) < 1e-9, true);
    fail += check("sample2 tolerance", abs(b - 5) < 1e-9, true);
    fail += check("zero", fractionalKnapsack({4}, {10}, 0), 0.0);
    fail += check("equal density", fractionalKnapsack({2, 4}, {4, 8}, 3), 6.0);
    return fail ? 1 : 0;
}

/* 收获点：只有可分割时按价值密度贪心才成立；不可用于 0/1 背包。时间 O(n log n)，空间 O(n)。 */
