/*
LeetCode 8：字符串转换整数 atoi

跳过前导空格，读取可选正负号，再读取连续十进制数字；无数字返回0，超出32位有符号范围则截为 INT_MIN/INT_MAX。

样例一："   -42" -> -42，空格后是负号和数字。
样例二："4193 with words" -> 4193，遇非数字停止。
来源：9_test/9_test/9_test.cpp:77-105（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

class Solution
{
  public:
    int myAtoi(string s)
    {
        size_t i = 0;
        while (i < s.size() && s[i] == ' ')
            ++i;
        int sign = 1;
        if (i < s.size() && (s[i] == '+' || s[i] == '-'))
        {
            if (s[i] == '-')
                sign = -1;
            ++i;
        }
        long long value = 0, limit = sign == 1 ? INT_MAX : -(1LL * INT_MIN);
        while (i < s.size() && s[i] >= '0' && s[i] <= '9')
        {
            int digit = s[i++] - '0';
            if (value > (limit - digit) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;
            value = value * 10 + digit;
        }
        return int(sign * value);
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
    fail += check("sample1", s.myAtoi("   -42"), -42);
    fail += check("sample2", s.myAtoi("4193 with words"), 4193);
    fail += check("positive overflow", s.myAtoi("999999999999999999999"), INT_MAX);
    fail += check("negative boundary", s.myAtoi("-2147483648"), INT_MIN);
    fail += check("negative overflow", s.myAtoi("-2147483649"), INT_MIN);
    fail += check("sign only", s.myAtoi("+"), 0);
    fail += check("empty", s.myAtoi(""), 0);
    return fail ? 1 : 0;
}

/* 收获点：修复先溢出再判断 s<0 的错误，带符号整数溢出不是合法检测手段。乘10前判断阈值。时间 O(n)，额外空间 O(1)，传值副本 O(n)。 */
