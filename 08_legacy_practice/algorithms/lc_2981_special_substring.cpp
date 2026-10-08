/*
LeetCode 2981：找出出现至少三次的最长特殊子字符串 I

特殊子串只含一种字母；返回出现至少三次的最长长度，允许重叠，无解返回 -1。输入小写英文字母。

样例一：aaaa -> 2，aa 在下标 0、1、2 各出现一次。
样例二：abcdef -> -1，没有任何字母出现三次。
来源：../originals/new_function/test_function.cpp:740-763（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int maximumLength(string s)
    {
        vector<int> groups[26]; //二维数组
        int cnt = 0, n = s.length();
        for (int i = 0; i < n; i++)
        {
            cnt++;
            if (i + 1 == n || s[i] != s[i + 1])
            {
                groups[s[i] - 'a'].push_back(cnt);
                cnt = 0;
            }
        }

        int ans = 0;
        for (auto &a : groups)
        {
            if (a.empty())
                continue;
            sort(a.rbegin(), a.rend());
            a.push_back(0);
            a.push_back(0);
            ans = max({ans, a[0] - 2, min(a[0] - 1, a[1]), a[2]});
        }
        return ans ? ans : -1;
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
    fail += check("sample1", s.maximumLength("aaaa"), 2);
    fail += check("sample2", s.maximumLength("abcdef"), -1);
    fail += check("three groups", s.maximumLength("abcaba"), 1);
    fail += check("two groups", s.maximumLength("aaaabaaa"), 3);
    fail += check("empty", s.maximumLength(""), -1);
    return fail ? 1 : 0;
}

/* 收获点：分组长度降序后考虑：单组贡献三次、两组贡献三次、三组各一次。时间 O(n log n)，空间 O(n)。 */
