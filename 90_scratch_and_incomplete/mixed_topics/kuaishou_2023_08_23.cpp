/*
题目一：括号匹配计数

给定一个只包含 ()、[]、{} 的字符串。如果括号完全合法，返回匹配成功的
括号对数；只要存在不匹配或未闭合的括号，就返回 0。

示例一：输入 "([]{})"，输出 3
示例二：输入 "([)]"，输出 0

题目二：矩阵中的最长下降路径

给定一个整数矩阵，每次只能向上、下、左、右移动到严格更小的数字，返回
一条路径最多能够经过的格子数量。
题目保证矩阵非空，并且行数、列数都不超过 100。

示例一：输入螺旋排列的 5x5 矩阵，输出 25
示例二：输入 {{4,3},{2,1}}，输出 3
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// 8.23快手
int kuohao_nums(const string &v)
{
    stack<char> stk;
    int ans = 0;
    for (size_t i = 0; i < v.length(); i++)
    {
        if (v[i] == '(' || v[i] == '[' || v[i] == '{')
        {
            stk.push(v[i]);
            continue;
        }
        if (stk.empty())
        {
            ans = 0;
            break;
        }
        if (v[i] == '}')
        {

            if (stk.top() == '{')
            {
                ans++;
                stk.pop();
            }
            else
            {
                ans = 0;
                break;
            }
        }

        if (v[i] == ')')
        {
            if (stk.top() == '(')
            {
                ans++;
                stk.pop();
            }
            else
            {
                ans = 0;
                break;
            }
        }

        if (v[i] == ']')
        {
            if (stk.top() == '[')
            {
                ans++;
                stk.pop();
            }
            else
            {
                ans = 0;
                break;
            }
        }
    }
    if (!stk.empty())
        ans = 0;
    return ans;
}

// 第二题    二维动态规划
int r = 0, c = 0, res = 0;
int a[105][105], dp[105][105];
int go[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1}; // 上、右、下、左
int dfs(int x, int y)
{
    if (dp[x][y] > 0)
        return dp[x][y]; // 如果已经检查过
    dp[x][y] = 1;        // 标记为1，表示检查过
    for (int i = 0; i < 4; i++)
    {
        int xx = x + go[i][0], yy = y + go[i][1];
        if (xx >= 0 && xx < r && yy >= 0 && yy < c && a[xx][yy] < a[x][y])
        {
            dp[x][y] = max(dp[x][y], dfs(xx, yy) + 1);
        }
    }
    return dp[x][y];
}

int LongestDescendingPath(const vector<vector<int>> &matrix)
{
    if (matrix.empty() || matrix[0].empty())
    {
        return 0;
    }

    r=static_cast<int>(matrix.size());
    c=static_cast<int>(matrix[0].size());
    res=0;
    memset(dp,0,sizeof(dp));

    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            a[i][j]=matrix[i][j];
        }
    }

    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            res=max(res,dfs(i,j));
        }
    }
    return res;
}

int main()
{
    string brackets1="([]{})";
    string brackets2="([)]";
    cout << "括号示例一 expected=3\nactual=" << kuohao_nums(brackets1) << '\n';
    cout << "括号示例二 expected=0\nactual=" << kuohao_nums(brackets2) << '\n';

    vector<vector<int>> matrix1={
        {1,2,3,4,5},
        {16,17,18,19,6},
        {15,24,25,20,7},
        {14,23,22,21,8},
        {13,12,11,10,9}
    };
    cout << "路径示例一 expected=25\nactual="
         << LongestDescendingPath(matrix1) << '\n';

    vector<vector<int>> matrix2={{4,3},{2,1}};
    cout << "路径示例二 expected=3\nactual="
         << LongestDescendingPath(matrix2) << '\n';
    return 0;
}
