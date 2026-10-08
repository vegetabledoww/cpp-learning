/*
LeetCode 125：验证回文串

仅保留 ASCII 英文字母和数字并忽略大小写后，判断是否回文。空过滤结果也是回文。

样例一：A man, a plan, a canal: Panama -> true，过滤后正反相同。
样例二：race a car -> false，过滤后 raceacar 不是回文。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:306-331（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
  public:
    bool isPalindrome(string s)
    {
        string sb;
        for (char c : s)
        {
            if (c >= 'A' && c <= 'Z')
                c = c - 'A' + 'a';
            if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
                sb += c;
        }
        int left = 0, right = int(sb.size()) - 1;
        while (left < right)
        {
            if (sb[left++] != sb[right--])
                return false;
        }
        return true;
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
    fail += check("sample1", s.isPalindrome("A man, a plan, a canal: Panama"), true);
    fail += check("sample2", s.isPalindrome("race a car"), false);
    fail += check("only punctuation", s.isPalindrome(" ,."), true);
    fail += check("digit and letter", s.isPalindrome("0P"), false);
    return fail ? 1 : 0;
}

/* 收获点：保留过滤再双指针；明确 ASCII 约定，避免误解 isalnum 返回值及 char 符号。时间 O(n)，空间 O(n)。 */
