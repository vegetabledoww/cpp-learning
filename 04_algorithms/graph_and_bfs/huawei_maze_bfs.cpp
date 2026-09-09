/*
题目：限时穿越辐射迷宫

给定一个 N x N 的矩阵 maze，maze[i][j] 表示该位置的辐射值。人物从左上角
(0,0) 出发，每次可以向上、下、左、右移动一格，最多移动 K 步到达右下角。
只有辐射值不超过防护能力 protection 的位置才能进入。求完成穿越所需的
最小防护能力。题目保证 K 足以让人物在防护能力足够时到达终点。

示例一：
输入：maze={{1,3},{2,4}}，K=2
输出：4

示例二：
输入：maze={{1,9,1},{2,8,2},{3,4,5}}，K=4
输出：5
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

// BFS 检查能否在 K 时间内到达右下角
bool canReach(const vector<vector<int>>& maze, int N, int K, int protection) {
    if (maze[0][0] > protection) {
        return false;
    }

    vector<vector<bool>> visited(N, vector<bool>(N, false));
    queue<pair<int, int>> q; // (x, y)
    q.push({0, 0});
    visited[0][0] = true;
    int time = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            pair<int,int>p = q.front();
            q.pop();

            // 如果到达右下角且时间不超过 K
            if (p.first == N - 1 && p.second == N - 1) {
                return true;
            }

            // 四个方向移动
            vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            for (auto [dx, dy] : directions) {
                int nx = p.first + dx, ny = p.second + dy;
                if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny]) {
                    if (maze[nx][ny] <= protection) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        }
        // 每次 BFS 循环后增加时间
        if (++time > K) break;
    }
    return false;
}

int minProtectionLevel(const vector<vector<int>>& maze, int N, int K) {
    int low = INT_MAX, high = INT_MIN;
    // 找到最小和最大辐射值
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            low = min(low, maze[i][j]);
            high = max(high, maze[i][j]);
        }
    }

    // 二分搜索
    int result = high;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canReach(maze, N, K, mid)) {
            result = mid; // 找到可行的保护能力，尝试更小的
            high = mid - 1;
        } else {
            low = mid + 1; // 不可行，增加保护能力
        }
    }
    return result;
}

int main() {
    vector<vector<int>> maze1={{1,3},{2,4}};
    cout << "示例一 expected=4\n";
    cout << "actual=" << minProtectionLevel(maze1,2,2) << '\n';

    vector<vector<int>> maze2={{1,9,1},{2,8,2},{3,4,5}};
    cout << "示例二 expected=5\n";
    cout << "actual=" << minProtectionLevel(maze2,3,4) << '\n';
    return 0;
}
