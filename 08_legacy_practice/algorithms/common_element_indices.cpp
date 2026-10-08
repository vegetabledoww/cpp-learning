/*
共同元素的下标映射

给两个整数数组，返回每个共同数值及其在两个数组中的最后出现下标。此重复值规则沿用原稿的覆盖赋值行为，原业务是否需要全部配对需另确认。结果用 map 按数值升序展示。

样例一：a=[1,2,3],b=[3,1] -> {1:[0,1],3:[2,0]}。
样例二：a=[1,1],b=[1,2,1] -> {1:[1,2]}，保留最后下标。
来源：new_function/test_function.cpp:393-410（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

map<int, vector<int>> findCommonElements(const vector<int> &a, const vector<int> &b)
{
    unordered_map<int, int> elementIndexMap;
    for (int i = 0; i < int(a.size()); ++i)
        elementIndexMap[a[i]] = i;
    map<int, vector<int>> indexMap;
    for (int j = 0; j < int(b.size()); ++j)
        if (elementIndexMap.count(b[j]))
            indexMap[b[j]] = {elementIndexMap[b[j]], j};
    return indexMap;
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
    auto a = findCommonElements({1, 2, 3}, {3, 1});
    fail += check("sample1 key1", a.at(1), vector<int>{0, 1});
    fail += check("sample1 key3", a.at(3), vector<int>{2, 0});
    fail += check("sample1 count", int(a.size()), 2);
    auto b = findCommonElements({1, 1}, {1, 2, 1});
    fail += check("sample2", b.at(1), vector<int>{1, 2});
    fail += check("empty", findCommonElements({}, {1}).empty(), true);
    return fail ? 1 : 0;
}

/* 收获点：保留 hash 记录下标，返回有序 map 便于观察；明确定义重复值覆盖规则。期望时间 O(n+m log u)，空间 O(n+u)，u 为共同值数量。 */
