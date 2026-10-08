/*
剪绳子：答案二分

给定非负整数绳长，剪出至少 target 段同样长的正整数绳子（target>=1），返回最大段长；无解返回 0。剩余零头可丢弃。

样例一：[802,743,457,539],target=11 -> 200，分别可剪 4、3、2、2 段。
样例二：[1,1,1],target=4 -> 0，连长度 1 都不够。
来源：huawei/huawei/huawei.cpp:48-87（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canCut(const vector<int> &lens, int target, int length)
{
    long long count = 0;
    for (int x : lens)
    {
        count += x / length;
        if (count >= target)
            return true;
    }
    return false;
}
int maxLength(const vector<int> &lens, int target)
{
    if (lens.empty())
        return 0;
    int left = 1, right = *max_element(lens.begin(), lens.end()), result = 0;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (canCut(lens, target, mid))
        {
            result = mid;
            if (mid == right)
                break; // 也避免最大绳长 INT_MAX 时 mid+1 溢出。
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
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
    fail += check("sample1", maxLength({802, 743, 457, 539}, 11), 200);
    fail += check("sample2", maxLength({1, 1, 1}, 4), 0);
    fail += check("empty", maxLength({}, 1), 0);
    fail += check("exact", maxLength({10}, 1), 10);
    return fail ? 1 : 0;
}

/* 收获点：长度越大，可剪数量越少，满足二分单调性。计数用 long long。时间 O(n log 最大绳长)，空间 O(1)。 */
