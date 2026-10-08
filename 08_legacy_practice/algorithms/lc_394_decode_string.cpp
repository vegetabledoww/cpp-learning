/*
LeetCode 394：字符串解码

编码 k[片段] 表示将片段重复正整数 k 次，支持嵌套，普通字符为英文字母。输入保证合法，展开长度<=100000。

样例一：3[a]2[bc] -> aaabcbc，分别展开后拼接。
样例二：3[a2[c]] -> accaccacc，先展开内层 cc。
来源：../originals/pen_exam_8/pen_exam_8/_8_pen_exam.cpp:171-238（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class Solution
{
  public:
    string getDigits(string &s, size_t &ptr)
    {
        string ret = "";
        //如果当前字符为数字，则将当前字符入栈，然后继续下一个字符

        while (ptr < s.size() && isdigit(s[ptr]))
        {
            ret.push_back(s[ptr++]);
            //上述代码相当于
            /*ret.push_back(s[ptr]);
        ptr++;*/
        }
        return ret;
    }

    string getString(vector<string> &v)
    {
        string ret;
        //将储存在vector中的若干小字符串拼接为大字符串
        for (const auto &s : v)
        {
            ret += s;
        }
        return ret;
    }

    string decodeString(string s)
    {
        vector<string> stk;
        size_t ptr = 0;
        while (ptr < s.size())
        {
            char cur = s[ptr];
            if (isdigit(cur))
            {
                //获取一个数字并进站
                string digits = getDigits(s, ptr);
                stk.push_back(digits);
            }
            else if (isalpha(cur) || cur == '[')
            {
                //获取一个字母进栈
                //string(1, s[ptr++])将s[ptr++]的类型由char转换为string
                stk.push_back(string(1, s[ptr++]));
            }
            else
            {
                ++ptr;
                vector<string> sub;
                while (stk.back() != "[")
                {
                    sub.push_back(stk.back());
                    stk.pop_back();
                }
                reverse(sub.begin(), sub.end());
                //左括号出栈
                stk.pop_back();
                //此时栈顶为当前sub对应的字符串出现的次数
                int repTime = stoi(stk.back());
                stk.pop_back();
                string t, o = getString(sub);
                while (repTime--)
                    t += o;
                stk.push_back(t);
            }
        }
        return getString(stk);
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
    fail += check("sample1", s.decodeString("3[a]2[bc]"), string("aaabcbc"));
    fail += check("sample2", s.decodeString("3[a2[c]]"), string("accaccacc"));
    fail += check("multi digit", s.decodeString("10[a]"), string(10, 'a'));
    fail += check("empty", s.decodeString(""), string(""));
    return fail ? 1 : 0;
}

/* 收获点：保留字符串栈模拟；本题输入仅 ASCII，字符分类不会遇到负 char。时间保守上界 O(输入长度+展开长度*嵌套深度)，空间同阶上界。 */
