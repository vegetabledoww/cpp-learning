/*
修改至多一个数后的最长严格递增连续段

根据原暴力草稿的范围恢复：整数数组元素都在 [0,100000]，可将至多一个元素改成该范围中的任意整数，求最长严格递增连续段长度。注意不是子序列。

样例一：[1,2,5,4,5] -> 5，将第三项5改成3。
样例二：[2,2,2] -> 2，最多改变一个数，不能让三项严格递增。
来源：huawei/huawei/huawei.cpp:319-425（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findLongest(const vector<int> &heights)
{
    int n = heights.size();
    if (n == 0)
        return 0;
    vector<int> left(n, 1), right(n, 1);
    for (int i = 1; i < n; ++i)
        if (heights[i] > heights[i - 1])
            left[i] = left[i - 1] + 1;
    for (int i = n - 2; i >= 0; --i)
        if (heights[i] < heights[i + 1])
            right[i] = right[i + 1] + 1;
    int ans = *max_element(left.begin(), left.end());
    for (int i = 0; i < n; ++i)
    {
        if (i > 0 && heights[i - 1] < 100000)
            ans = max(ans, left[i - 1] + 1);
        if (i + 1 < n && heights[i + 1] > 0)
            ans = max(ans, right[i + 1] + 1);
        // 必须存在夹在两邻居之间的整数，差值至少为2。
        if (i > 0 && i + 1 < n && heights[i + 1] - heights[i - 1] >= 2)
            ans = max(ans, left[i - 1] + 1 + right[i + 1]);
    }
    return ans;
}
int bruteLongest(vector<int> a)
{
    int best = 0;
    for (int i = 0; i < int(a.size()); ++i)
    {
        int original = a[i];
        // 对测试中原值0..2，候选0..3足以覆盖所有可实现的大小关系。
        for (int value = 0; value <= 3; ++value)
        {
            a[i] = value;
            int length = 0;
            for (int j = 0; j < int(a.size()); ++j)
            {
                length = (j > 0 && a[j] > a[j - 1]) ? length + 1 : 1;
                best = max(best, length);
            }
        }
        a[i] = original;
    }
    return best;
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
    fail += check("sample1", findLongest({1, 2, 5, 4, 5}), 5);
    fail += check("sample2", findLongest({2, 2, 2}), 2);
    fail += check("lower boundary", findLongest({0, 0}), 2);
    fail += check("upper boundary", findLongest({100000, 100000}), 2);
    fail += check("empty", findLongest({}), 0);
    bool ok = true;
    for (int code = 0; code < 243; ++code)
    {
        int x = code;
        vector<int> a(5);
        for (int &v : a)
        {
            v = x % 3;
            x /= 3;
        }
        if (findLongest(a) != bruteLongest(a))
            ok = false;
    }
    fail += check("243 arrays vs brute changes", ok, true);
    return fail ? 1 : 0;
}

/* 收获点：修复旧优化版把前缀最大值当成连续递增长度的错误。前后连续长度连接，注意整数间隙及允许修改范围。时间 O(n)，空间 O(n)。 */
