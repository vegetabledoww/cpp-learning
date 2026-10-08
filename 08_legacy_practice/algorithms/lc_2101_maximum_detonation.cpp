/*
LeetCode 2101：引爆最多的炸弹

bombs[i]=[x,y,r]。从一个炸弹开始，引爆中心落在其半径范围内（含边界）的其它炸弹，并继续传播。求最多引爆数。坐标绝对值和半径<=100000，数量<=100。

样例一：[[2,1,3],[6,1,4]] -> 2，第二个半径4恰好覆盖第一个。
样例二：[[1,1,5],[10,10,5]] -> 1，相距过远。
来源：Top_K_C++/demo.cpp:374-419（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int maximumDetonation(vector<vector<int>> &bombs)
    {
        int n = bombs.size();
        // 覆盖关系有方向，使用发起炸弹半径的平方，并包含圆周边界。
        //有向图
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                long long dx = 1LL * bombs[i][0] - bombs[j][0];
                long long dy = 1LL * bombs[i][1] - bombs[j][1];
                long long radius = bombs[i][2]; // 乘法前先提升，避免 int 平方溢出。
                if (i != j && radius * radius >= dx * dx + dy * dy)
                {
                    mp[i].push_back(j);
                }
            }
        }
        //在此开始，用BFS
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            int cnt = 1;
            vector<bool> visited(n);
            queue<int> q;
            q.push(i);
            visited[i] = 1;
            while (!q.empty())
            {
                int cidx = q.front();
                q.pop();
                for (const int nidx : mp[cidx])
                {
                    if (visited[nidx])
                        continue;
                    cnt++;
                    q.push(nidx);
                    visited[nidx] = 1;
                }
                res = max(res, cnt);
            }
        }
        return res;
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
    vector<vector<int>> a = {{2, 1, 3}, {6, 1, 4}}, b = {{1, 1, 5}, {10, 10, 5}},
                        c = {{0, 0, 1}, {2, 0, 10}},
                        d = {{100000, 100000, 1}, {-100000, -100000, 1}};
    fail += check("sample1 boundary", s.maximumDetonation(a), 2);
    fail += check("sample2", s.maximumDetonation(b), 1);
    fail += check("different radii regression", s.maximumDetonation(c), 2);
    fail += check("large square", s.maximumDetonation(d), 1);
    return fail ? 1 : 0;
}

/* 收获点：修复原半径相乘及严格大于号；逐个起点 BFS。时间 O(n³)，空间 O(n²)。 */
