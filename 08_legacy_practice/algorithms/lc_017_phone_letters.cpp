/*
LeetCode 17：电话号码的字母组合

给定只含数字 2..9 的字符串，按电话键盘映射返回所有字母组合；空输入返回空数组。

样例一：23 -> [ad,ae,af,bd,be,bf,cd,ce,cf]，两组字母做组合。
样例二：2 -> [a,b,c]，只有一层选择。
来源：../originals/new_function/test_function.cpp:222-257（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
    vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    void backtrack(const string &digits, int start, string cur)
    {
        if (start == int(digits.size()))
        {
            res.push_back(cur);
            return;
        }
        // 每层只处理一个数字；不需要再遍历后面所有数字。
        for (char c : mapping[digits[start] - '0'])
        {
            cur.push_back(c);
            backtrack(digits, start + 1, cur);
            cur.pop_back();
        }
    }

  public:
    vector<string> letterCombinations(string digits)
    {
        res.clear(); // 同一 Solution 重复调用不能残留上次结果。
        if (!digits.empty())
            backtrack(digits, 0, "");
        return res;
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
    fail += check("sample1", s.letterCombinations("23"),
                  vector<string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"});
    fail += check("sample2 reuse", s.letterCombinations("2"), vector<string>{"a", "b", "c"});
    fail += check("empty reuse", s.letterCombinations(""), vector<string>{});
    return fail ? 1 : 0;
}

/* 收获点：回溯选择、递归、撤销。时间 O(n*4^n)，含输出空间 O(n*4^n)，递归深度 O(n)。 */
