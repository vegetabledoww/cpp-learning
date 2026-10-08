/*
LeetCode 2965：找出缺失和重复的数字

n*n 方阵包含 1..n²，其中恰有一个数出现两次、一个数缺失。返回 [重复数,缺失数]，n>=2。

样例一：[[1,3],[2,2]] -> [2,4]，2 重复、4 未出现。
样例二：[[9,1,7],[8,9,2],[3,4,6]] -> [9,5]。
来源：../originals/new_function/test_function.cpp:765-782（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>> &grid)
    {
        int n = grid.size(), a = 0, b = 0;
        vector<int> ans(n * n, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ans[grid[i][j] - 1]++;
            }
        }
        for (int i = 0; i < n * n; i++)
        {
            if (ans[i] == 2)
                a = i;
            if (ans[i] == 0)
                b = i;
            else
                continue;
        }
        return {a + 1, b + 1};
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
    vector<vector<int>> a = {{1, 3}, {2, 2}}, b = {{9, 1, 7}, {8, 9, 2}, {3, 4, 6}},
                        c = {{4, 2}, {3, 4}};
    fail += check("sample1", s.findMissingAndRepeatedValues(a), vector<int>{2, 4});
    fail += check("sample2", s.findMissingAndRepeatedValues(b), vector<int>{9, 5});
    fail += check("missing one", s.findMissingAndRepeatedValues(c), vector<int>{4, 1});
    return fail ? 1 : 0;
}

/* 收获点：计数下标比数值小 1，返回时加回 1。时间、空间 O(n²)。 */
