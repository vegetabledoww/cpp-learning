/*
LeetCode 2380：二进制字符串重新安排顺序需要的时间

每秒同时把所有 01 替换为 10，返回直到没有 01 所需秒数。输入二进制字符串；本版保留逐轮模拟，适合长度<=1000。

样例一：0110101 -> 4，经过四轮所有 1 到左侧。
样例二：11100 -> 0，初始没有 01。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:79-108（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

class Solution
{
  public:
    int secondsToRemoveOccurrences(string s)
    {
        int seconds = 0;
        while (true)
        {
            bool changed = false;
            for (size_t i = 0; i + 1 < s.size(); ++i)
                if (s[i] == '0' && s[i + 1] == '1')
                {
                    swap(s[i], s[i + 1]);
                    ++i;
                    changed = true; // 跳过刚换过的位置，模拟同时变化。
                }
            if (!changed)
                return seconds;
            ++seconds;
        }
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
    fail += check("sample1", s.secondsToRemoveOccurrences("0110101"), 4);
    fail += check("sample2", s.secondsToRemoveOccurrences("11100"), 0);
    fail += check("first position regression", s.secondsToRemoveOccurrences("001"), 2);
    fail += check("empty extension", s.secondsToRemoveOccurrences(""), 0);
    return fail ? 1 : 0;
}

/* 收获点：修复旧循环重置 i=0 后又自增导致漏检首位置，以及空串 size()-1 下溢。时间 O(n²)，空间 O(n)（输入副本）。 */
