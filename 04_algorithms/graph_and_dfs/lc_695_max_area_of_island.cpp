/*
题目：岛屿的最大面积（LeetCode 695）

给定一个大小为 rows * columns 的二维整数网格 grid。
grid[row][column] 为 1 表示陆地，为 0 表示水域。
上下或左右相邻的陆地属于同一座岛屿，一座岛屿的面积就是其中陆地格子的数量。
请返回网格中面积最大的岛屿；如果网格中没有陆地，则返回 0。

示例一：
输入：
grid = {
    {0,0,1,0,0},
    {0,1,1,1,0},
    {0,0,1,0,0},
    {1,1,0,0,0}
}
输出：5
解释：中间相连的 5 个陆地格子组成最大岛屿；左下角岛屿的面积为 2。

示例二：
输入：
grid = {
    {0,0,0},
    {0,0,0}
}
输出：0
解释：网格中没有陆地，所以最大岛屿面积为 0。

约束：
1 <= rows, columns <= 50
grid[row][column] 只能是 0 或 1。
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        if (grid.empty() || grid[0].empty())
        {
            return 0;
        }

        int rows = static_cast<int>(grid.size());
        int columns = static_cast<int>(grid[0].size());
        int maxArea = 0;

        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                if (grid[row][column] == 1)
                {
                    int currentArea = dfs(grid, row, column);
                    if (currentArea > maxArea)
                    {
                        maxArea = currentArea;
                    }
                }
            }
        }

        return maxArea;
    }

private:
    int dfs(vector<vector<int>>& grid, int row, int column)
    {
        int rows = static_cast<int>(grid.size());
        int columns = static_cast<int>(grid[0].size());

        // 越界或遇到水时，这个方向不能贡献面积
        if (row < 0 || row >= rows || column < 0 || column >= columns ||
            grid[row][column] == 0)
        {
            return 0;
        }

        // 当前陆地先计入面积，再沉降为水，避免被相邻格子重复统计。
        grid[row][column] = 0;
        //需要+1的原因是只要有一个是1，则其面积为1
        return 1 + dfs(grid, row - 1, column)
                 + dfs(grid, row + 1, column)
                 + dfs(grid, row, column - 1)
                 + dfs(grid, row, column + 1);
    }
};

bool runTest(const string& testName, vector<vector<int>> grid, int expected)
{
    Solution solution;
    int actual = solution.maxAreaOfIsland(grid);

    cout << testName << "：期望结果 = " << expected
         << "，实际结果 = " << actual
         << (actual == expected ? "，通过" : "，失败") << '\n';

    return actual == expected;
}

int main()
{
    int failedCount = 0;

    vector<vector<int>> grid1 = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {0,0,1,0,0},
        {1,1,0,0,0}
    };
    if (!runTest("示例一", grid1, 5))
    {
        failedCount++;
    }

    vector<vector<int>> grid2 = {
        {0,0,0},
        {0,0,0}
    };
    if (!runTest("示例二", grid2, 0))
    {
        failedCount++;
    }

    vector<vector<int>> grid3 = {{1}};
    if (!runTest("单个陆地", grid3, 1))
    {
        failedCount++;
    }

    vector<vector<int>> grid4 = {
        {1,0,1},
        {0,1,0},
        {1,0,1}
    };
    if (!runTest("互不相邻的陆地", grid4, 1))
    {
        failedCount++;
    }

    vector<vector<int>> grid5 = {{1,1,1,1,1,1}};
    if (!runTest("一整行连续陆地", grid5, 6))
    {
        failedCount++;
    }

    cout << "失败用例数：" << failedCount << '\n';
    return failedCount;
}

/*
收获点：
1. LeetCode 200 的 DFS 只需要标记整座岛；本题让 DFS 返回每个方向贡献的面积。
2. 递归公式是：当前岛屿面积 = 1 + 上 + 下 + 左 + 右。
3. 访问陆地后立即将它改成 0，可以代替额外的 visited 数组。
4. 每个格子最多访问一次，时间复杂度为 O(rows * columns)；
   最坏情况下递归栈的空间复杂度为 O(rows * columns)。
*/
