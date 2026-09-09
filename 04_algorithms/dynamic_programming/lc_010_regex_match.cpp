/*
题目：正则表达式匹配（LeetCode 10）

给定字符串 s 和模式 p，实现支持 '.' 和 '*' 的完整字符串匹配：
'.' 可以匹配任意单个字符；'*' 可以让它前面的元素出现零次或多次。
必须匹配整个字符串，而不是其中一部分。

示例一：
输入：s="aa"，p="a"
输出：false

示例二：
输入：s="aab"，p="c*a*b"
输出：true
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int m = s.size();
        int n = p.size();

        auto matches = [&](int i, int j)
        {
            if (i == 0)
            {
                return false;
            }
            if (p[j - 1] == '.')
            {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (p[j - 1] == '*')
                {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1))
                    {
                        f[i][j] |= f[i - 1][j];
                    }
                }
                else
                {
                    if (matches(i, j))
                    {
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }
};

int main()
{
    Solution solution;
    cout << boolalpha;
    cout << "示例一 expected=false\n";
    cout << "actual=" << solution.isMatch("aa","a") << '\n';
    cout << "示例二 expected=true\n";
    cout << "actual=" << solution.isMatch("aab","c*a*b") << '\n';
    return 0;
}
