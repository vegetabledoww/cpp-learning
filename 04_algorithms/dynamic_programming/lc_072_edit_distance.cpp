/*
题目：编辑距离（LeetCode 72）

给定两个字符串 word1 和 word2，每次可以插入、删除或替换一个字符。
返回将 word1 转换成 word2 所需的最少操作次数。

示例一：
输入：word1="horse"，word2="ros"
输出：3

示例二：
输入：word1="intention"，word2="execution"
输出：5
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
int minDistance(string &s, string &t)
{
    int n = s.length(), m = t.length();
    // 状态[i,j]对应的子问题：将s的前i个字符更改为t的前j个字符所需的最少编辑步数
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // 状态转移：首行首列
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = j;
    }
    // 状态转移，其余行和列
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1]) // 此时不用修改
                dp[i][j] = dp[i - 1][j - 1];
            else
                // 三个状态分别对应增、删、改
                dp[i][j] =
                    min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) +
                    1;
        }
    }
    return dp[n][m];
}

int main()
{
    string word1="horse", word2="ros";
    cout << "示例一 expected=3\n";
    cout << "actual=" << minDistance(word1,word2) << '\n';

    string word3="intention", word4="execution";
    cout << "示例二 expected=5\n";
    cout << "actual=" << minDistance(word3,word4) << '\n';
    return 0;
}
