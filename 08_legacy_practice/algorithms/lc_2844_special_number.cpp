/*
LeetCode 2844：生成特殊数字的最少操作

每次删除十进制字符串的一个字符，求使剩余数能被 25 整除的最少删除次数。删空按 0 处理，输入非空、无前导零。

样例一：2245047 -> 2，删除末尾 47 得到 22450。
样例二：2908305 -> 3，保留结尾 25 可得到 2925。
来源：../originals/Top_K_C++/demo.cpp:446-477（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
  public:
    int minimumOperations(string num)
    {
        int n = num.length();
        bool find0 = false, find5 = false;
        for (int i = n - 1; i >= 0; i--)
        {
            if ((num[i] == '0' || num[i] == '5') && find0)
            {
                return n - i - 2;
            }
            if ((num[i] == '2' || num[i] == '7') && find5)
            {
                return n - i - 2;
            }
            if (num[i] == '0')
            {
                find0 = true;
                continue;
            }
            if (num[i] == '5')
            {
                find5 = true;
                continue;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (num[i] == '0')
                return n - 1;
        }
        return n;
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
    fail += check("sample1", s.minimumOperations("2245047"), 2);
    fail += check("sample2", s.minimumOperations("2908305"), 3);
    fail += check("zero", s.minimumOperations("10"), 1);
    fail += check("erase all", s.minimumOperations("1"), 1);
    return fail ? 1 : 0;
}

/* 收获点：末两位只可能为 00、25、50、75，另外处理仅剩 0。时间 O(n)，额外空间 O(1)。 */
