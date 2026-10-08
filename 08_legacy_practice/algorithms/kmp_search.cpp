/*
KMP：首次子串匹配

返回 pattern 在 text 中首次出现的零基下标，找不到返回 -1；空模式串约定返回 0。

样例一：BBCABCDABABCDABCDABDE, ABCDABD -> 13，从下标 13 匹配。
样例二：aaaaa, bba -> -1，没有匹配。
来源：../originals/new_function/test_function.cpp:847-883（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void getNext(string pattern, vector<int> &next)
{
    int m = pattern.length();
    next.resize(m);
    int i = 0, j = -1;
    if (m == 0)
        return; // 空模式没有 next[0]
    next[0] = -1;
    while (i < m - 1)
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

// KMP 匹配函数    文本串      模式串
int kmpSearch(string text, string pattern)
{
    int n = text.length(), m = pattern.length();
    vector<int> next(m);
    getNext(pattern, next);
    int i = 0, j = 0;
    while (i < n && j < m)
    {
        if (j == -1 || text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == m)
    {
        return i - j;
    }
    return -1;
}

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
    fail += check("sample1", kmpSearch("BBCABCDABABCDABCDABDE", "ABCDABD"), 13);
    fail += check("sample2", kmpSearch("aaaaa", "bba"), -1);
    fail += check("empty pattern", kmpSearch("abc", ""), 0);
    fail += check("fallback", kmpSearch("ababababca", "ababca"), 4);
    fail += check("empty text", kmpSearch("", "a"), -1);
    return fail ? 1 : 0;
}

/* 收获点：保留 next[0]=-1 的回退版本。修复空模式越界。时间 O(n+m)，空间 O(m)。 */
