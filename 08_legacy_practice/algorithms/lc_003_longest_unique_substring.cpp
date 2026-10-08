/*
LeetCode 3：无重复字符的最长子串

返回字符串中不含重复字符的最长连续子串长度。这里按 char 字节处理，不作 Unicode 字符切分。

样例一：abcabcbb -> 3，abc 无重复。
样例二：bbbbb -> 1，只能保留一个 b。
来源：../originals/_top_k_8/_top_k_8/_top_k_8.cpp:450-471（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_map<char, int> mp;
        int left = 0, right = 0;
        int res = 0;
        while (right < int(s.length()))
        {
            //窗口右移
            char c = s[right];
            right++;
            mp[c]++;
            //证明此字符已经存在
            while (mp[c] > 1)
            {
                //窗口左移
                char d = s[left];
                left++;
                mp[d]--;
            }
            res = max(res, right - left);
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
    fail += check("sample1", s.lengthOfLongestSubstring("abcabcbb"), 3);
    fail += check("sample2", s.lengthOfLongestSubstring("bbbbb"), 1);
    fail += check("empty", s.lengthOfLongestSubstring(""), 0);
    fail += check("shrink repeatedly", s.lengthOfLongestSubstring("abba"), 2);
    return fail ? 1 : 0;
}

/* 收获点：计数重复时收缩左边界。时间 O(n)，空间 O(字符集大小)。 */
