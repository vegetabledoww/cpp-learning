/*
LeetCode 5：最长回文子串

返回最长连续回文子串，有多个时任一个均可；空输入返回空字符串。

样例一：babad -> bab 或 aba，两者都是最长回文。
样例二：cbbd -> bb，偶数长度中心在两个 b 之间。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:545-570（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
  public:
    string palindrome(const string &s, int l, int r)
    {
        //防止数组越界
        while (l >= 0 && r < int(s.length()) && s[l] == s[r])
        {
            //双指针，向两边展开
            l--;
            r++;
        }
        //返回以s[l]和s[r]为中心的最长回文子串
        return s.substr(l + 1, r - l - 1);
    }
    string longestPalindrome(string s)
    {
        string res = "";
        for (int i = 0; i < int(s.length()); i++)
        {
            //以s[i]为中心的最长回文子串
            string s1 = palindrome(s, i, i); //
            //以s[i+1]为中心的最长回文子串
            string s2 = palindrome(s, i, i + 1);
            res = res.length() > s1.length() ? res : s1;
            res = res.length() > s2.length() ? res : s2;
        }
        return res;
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
    auto a = s.longestPalindrome("babad");
    fail += check("sample1 either palindrome", a == "bab" || a == "aba", true);
    fail += check("sample2", s.longestPalindrome("cbbd"), string("bb"));
    fail += check("empty", s.longestPalindrome(""), string(""));
    fail += check("all same", s.longestPalindrome("aaaa"), string("aaaa"));
    return fail ? 1 : 0;
}

/* 收获点：保留奇偶双中心展开，辅助函数按引用读原串。时间 O(n²)，生成候选子串需 O(n) 空间。 */
