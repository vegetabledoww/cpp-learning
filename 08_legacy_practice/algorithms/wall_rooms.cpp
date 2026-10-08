/*
墙壁位掩码：统计房间面积

根据旧稿恢复的练习：矩形网格每格用 8/4/2/1 表示北/东/南/西墙，1 表示有墙。相邻格共享墙一致，不能越过网格边界。返回各连通房间格数，降序排列。

样例一：[[9,12],[3,6]] -> [4]，外圈有墙、内部连通。
样例二：[[15,15]] -> [1,1]，两格之间有墙。
来源：10.22/10.22/10.22.cpp:1-71; huawei/huawei/huawei.cpp:180-235（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dfs(const vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y)
{
    visited[x][y] = true;
    int size = 1;
    const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1}, mask[] = {8, 4, 2, 1};
    int n = grid.size(), m = grid[0].size();
    for (int d = 0; d < 4; ++d)
    {
        int nx = x + dx[d], ny = y + dy[d];
        // 检查当前格朝该方向的墙；不是邻格的同方向墙。
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && !(grid[x][y] & mask[d]))
            size += dfs(grid, visited, nx, ny);
    }
    return size;
}
vector<int> findRoomSizes(const vector<vector<int>> &grid)
{
    if (grid.empty() || grid[0].empty())
        return {};
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m));
    vector<int> res;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!visited[i][j])
                res.push_back(dfs(grid, visited, i, j));
    sort(res.rbegin(), res.rend());
    return res;
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
    fail += check("sample1", findRoomSizes({{9, 12}, {3, 6}}), vector<int>{4});
    fail += check("sample2", findRoomSizes({{15, 15}}), vector<int>{1, 1});
    fail += check("single", findRoomSizes({{15}}), vector<int>{1});
    fail += check("empty", findRoomSizes({}), vector<int>{});
    fail += check("different rooms", findRoomSizes({{11, 14, 15}}), vector<int>{2, 1});
    return fail ? 1 : 0;
}

/* 收获点：合并两个旧文件的同题片段，修复 void DFS 返回面积及墙方向错误。时间 O(nm+R log R)，空间 O(nm)，R 为房间数。大网格可改显式栈避免递归过深。 */
