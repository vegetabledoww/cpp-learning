/*
十字翻转：把小网格变为全零

恢复练习：每次选择一格，翻转它及上下左右相邻格的0/1，返回变全零的最少次数，不可达为-1。限定矩形网格总格数<=16，以状态 BFS 验证最短路。

样例一：[[0,0],[0,1]] -> 3，翻转左上、右上、左下。
样例二：[[1,0]] -> -1，每次都同时翻两格，无法仅消掉一个1。
来源：10.22/10.22/10.22.cpp:234-288（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int minOperations(const vector<vector<int>> &grid)
{
    if (grid.empty() || grid[0].empty())
        return 0;
    int n = grid.size(), m = grid[0].size(), bits = n * m, start = 0;
    vector<int> mask(bits), distance(1 << bits, -1);
    int dx[] = {0, -1, 1, 0, 0}, dy[] = {0, 0, 0, -1, 1};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            if (grid[i][j])
                start |= 1 << (i * m + j);
            for (int d = 0; d < 5; ++d)
            {
                int x = i + dx[d], y = j + dy[d];
                if (x >= 0 && x < n && y >= 0 && y < m)
                    mask[i * m + j] |= 1 << (x * m + y);
            }
        }
    queue<int> q;
    q.push(start);
    distance[start] = 0;
    while (!q.empty())
    {
        int state = q.front();
        q.pop();
        if (state == 0)
            return distance[state];
        for (int flip : mask)
        {
            int next = state ^ flip;
            if (distance[next] == -1)
            {
                distance[next] = distance[state] + 1;
                q.push(next);
            }
        }
    }
    return -1;
}

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
    fail += check("sample1", minOperations({{0, 0}, {0, 1}}), 3);
    fail += check("sample2 unreachable", minOperations({{1, 0}}), -1);
    fail += check("already zero", minOperations({{0}}), 0);
    fail += check("single", minOperations({{1}}), 1);
    fail += check("empty", minOperations({}), 0);
    return fail ? 1 : 0;
}

/* 收获点：旧稿遇1就翻会循环，也不能保证最少操作，因此必须替换为有限状态最短路。时间 O(B*2^B)，空间 O(2^B)，B为格数。原题大规模解法需补规模后决定。 */
