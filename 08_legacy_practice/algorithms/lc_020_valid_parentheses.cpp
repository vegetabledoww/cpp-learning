/*
LeetCode 20：有效的括号

输入只含 ()[]{}。判断是否正确嵌套且全部配对，空串有效。

样例一：()[]{} -> true，三对均匹配。
样例二：([)] -> false，嵌套顺序错误。
来源：../originals/new_function/test_function.cpp:553-580（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution
{
  public:
    bool isValid(string s)
    {
        int n = s.size();
        if (n % 2 == 1)
        {
            return false;
        }

        unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
        stack<char> stk;
        for (char ch : s)
        {
            if (pairs.count(ch))
            {
                if (stk.empty() || stk.top() != pairs[ch])
                {
                    return false;
                }
                stk.pop();
            }
            else
            {
                stk.push(ch);
            }
        }
        return stk.empty();
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
    fail += check("sample1", s.isValid("()[]{}"), true);
    fail += check("sample2", s.isValid("([)]"), false);
    fail += check("empty", s.isValid(""), true);
    fail += check("unfinished", s.isValid("(("), false);
    return fail ? 1 : 0;
}

/* 收获点：左括号入栈，右括号只能与栈顶配对。时间 O(n)，空间 O(n)。 */
