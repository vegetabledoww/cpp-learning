/*
LeetCode 32：最长有效括号

输入只含 '(' 和 ')'，返回最长连续、正确配对的括号子串长度。

样例一：(() -> 2，末尾 () 有效。
样例二：)()()) -> 4，中间 ()() 有效。
来源：../originals/new_function/test_function.cpp:784-808（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int longestValidParentheses(string s)
    {
        int maxans = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < int(s.length()); i++)
        {
            if (s[i] == '(')
            {
                stk.push(i);
            }
            else
            {
                stk.pop();
                if (stk.empty())
                {
                    stk.push(i);
                }
                else
                {
                    maxans = max(maxans, i - stk.top());
                }
            }
        }
        return maxans;
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
    fail += check("sample1", s.longestValidParentheses("(()"), 2);
    fail += check("sample2", s.longestValidParentheses(")()())"), 4);
    fail += check("empty", s.longestValidParentheses(""), 0);
    fail += check("nested", s.longestValidParentheses("()(())"), 6);
    return fail ? 1 : 0;
}

/* 收获点：栈存下标，-1 是第一段起点之前的位置。时间 O(n)，空间 O(n)。 */
