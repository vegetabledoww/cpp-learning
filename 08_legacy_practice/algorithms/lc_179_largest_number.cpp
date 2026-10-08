/*
LeetCode 179：最大数

给定非空非负整数数组，排列并拼接成最大数字，结果以字符串返回；全零返回单个 0。

样例一：[10,2] -> 210，因为 210 大于 102。
样例二：[3,30,34,5,9] -> 9534330，按拼接后的大小比较。
来源：../originals/new_function/test_function.cpp:510-524（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool largerConcat(int x, int y)
{
    return to_string(x) + to_string(y) > to_string(y) + to_string(x);
}
class Solution
{
  public:
    string largestNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end(), largerConcat);
        if (nums[0] == 0)
            return "0";
        string ret;
        for (int x : nums)
            ret += to_string(x);
        return ret;
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
    vector<int> a = {10, 2}, b = {3, 30, 34, 5, 9}, c = {0, 0}, d = {12, 121};
    fail += check("sample1", s.largestNumber(a), string("210"));
    fail += check("sample2", s.largestNumber(b), string("9534330"));
    fail += check("zeros", s.largestNumber(c), string("0"));
    fail += check("prefix tie", s.largestNumber(d), string("12121"));
    return fail ? 1 : 0;
}

/* 收获点：原拼接比较规则保留，改为具名比较函数。时间 O(n log n * L)，L 为数字位数上限；输出 O(nL)。 */
