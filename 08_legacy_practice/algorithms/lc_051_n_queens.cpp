/*
LeetCode 51：N 皇后

在 n*n 棋盘放 n 个皇后，每行、每列、两条对角线方向均不冲突；返回全部棋盘，Q 表示皇后，. 表示空位。1<=n<=9。

样例一：n=4 -> 两个解：[.Q..,...Q,Q...,..Q.] 和 [..Q.,Q...,...Q,.Q..]。
样例二：n=1 -> [[Q]]，唯一格子放皇后。
来源：../originals/new_function/test_function.cpp:325-360（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
    void backtrack(int row, int n, vector<string> &state, vector<vector<string>> &res,
                   vector<bool> &cols, vector<bool> &diags1, vector<bool> &diags2)
    {
        if (row == n)
        {
            res.push_back(state);
            return;
        }
        for (int col = 0; col < n; ++col)
        {
            int diag1 = row - col + n - 1, diag2 = row + col;
            if (!cols[col] && !diags1[diag1] && !diags2[diag2])
            {
                state[row][col] = 'Q';
                cols[col] = diags1[diag1] = diags2[diag2] = true;
                backtrack(row + 1, n, state, res, cols, diags1, diags2);
                state[row][col] = '.';
                cols[col] = diags1[diag1] = diags2[diag2] = false;
            }
        }
    }

  public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<string> state(n, string(n, '.'));
        vector<bool> cols(n), diags1(2 * n - 1), diags2(2 * n - 1);
        vector<vector<string>> res;
        backtrack(0, n, state, res, cols, diags1, diags2);
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
    fail += check(
        "sample1", s.solveNQueens(4),
        vector<vector<string>>{{".Q..", "...Q", "Q...", "..Q."}, {"..Q.", "Q...", "...Q", ".Q.."}});
    fail += check("sample2", s.solveNQueens(1), vector<vector<string>>{{"Q"}});
    fail += check("no solution", s.solveNQueens(2), vector<vector<string>>{});
    return fail ? 1 : 0;
}

/* 收获点：保留列和对角线占用表，将原三维字符串单格表示调整为平台棋盘签名。上界 O(n*n!+解数*n²)，不计输出空间 O(n²)。 */
