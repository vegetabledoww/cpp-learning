/*
数字条重叠后的最短总长度

恢复练习：两个由0..3组成的数字条，允许平移但不能翻转；重叠位置的数字和必须<=3。返回覆盖两条所需的最短总长度。

样例一：12 与 21 -> 2，完全重叠时两位置和均为3。
样例二：22 与 22 -> 4，任一位置重叠都会超过3，只能分开放。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:14-45（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int minimumCombinedLength(const string &a, const string &b)
{
    int n = a.size(), m = b.size(), ans = n + m;
    for (int offset = -m; offset <= n; ++offset)
    {
        bool valid = true;
        int overlap = 0;
        for (int j = 0; j < m; ++j)
        {
            int i = offset + j;
            if (i < 0 || i >= n)
                continue;
            if (a[i] - '0' + b[j] - '0' > 3)
            {
                valid = false;
                break;
            }
            ++overlap;
        }
        if (valid)
            ans = min(ans, n + m - overlap);
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
    fail += check("sample1", minimumCombinedLength("12", "21"), 2);
    fail += check("sample2", minimumCombinedLength("22", "22"), 4);
    fail += check("partial overlap", minimumCombinedLength("111", "33"), 5);
    fail += check("contained", minimumCombinedLength("111", "2"), 3);
    fail += check("empty", minimumCombinedLength("", "12"), 2);
    return fail ? 1 : 0;
}

/* 收获点：枚举相对起点，自然覆盖左移、右移和包含关系。时间 O((n+m)*m)，额外空间 O(1)。 */
