/*
LeetCode 438：找到字符串中所有字母异位词

返回 s 中所有与 p 字母频次相同的连续子串起点，按下标升序。练习约定：p 为空返回空数组。

样例一：s=cbaebabacd,p=abc -> [0,6]，cba 和 bac 是异位词。
样例二：s=abab,p=ab -> [0,1,2]，允许重叠。
来源：../originals/new_function/test_function.cpp:121-156（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution
{
  public:
    vector<int> findAnagrams(string s, string p)
    {
        if (p.empty())
            return {};
        unordered_map<int, int> need, window;
        for (char c : p)
            need[c]++;
        int left = 0, right = 0;
        int valid = 0;
        vector<int> res;
        while (right < int(s.size()))
        {
            char c = s[right];
            right++;
            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                    valid++;
            }
            while (right - left >= int(p.size()))
            {
                if (int(need.size()) == valid)
                {
                    res.push_back(left);
                }
                char d = s[left];
                left++;
                if (need.count(d))
                {
                    if (window[d] == need[d])
                    {
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
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
    fail += check("sample1", s.findAnagrams("cbaebabacd", "abc"), vector<int>{0, 6});
    fail += check("sample2", s.findAnagrams("abab", "ab"), vector<int>{0, 1, 2});
    fail += check("empty pattern", s.findAnagrams("abc", ""), vector<int>{});
    fail += check("repeats", s.findAnagrams("baa", "aa"), vector<int>{1});
    return fail ? 1 : 0;
}

/* 收获点：保留 need/window/valid，修复空模式时窗口循环越界。时间 O(n+m)，空间 O(字符集大小)。 */
