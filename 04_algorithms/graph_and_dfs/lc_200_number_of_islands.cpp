/*
题目：岛屿数量（LeetCode 200）

给定一个由字符 '1'（陆地）和 '0'（水）组成的二维网格 grid。
上下或左右相邻的陆地属于同一座岛屿，网格的四条边都被水包围。
请返回网格中的岛屿数量。

示例一：
输入：
grid = {
    {'1','1','1','1','0'},
    {'1','1','0','1','0'},
    {'1','1','0','0','0'},
    {'0','0','0','0','0'}
}
输出：1
解释：所有陆地通过上下左右相连，因此只有一座岛屿。

示例二：
输入：
grid = {
    {'1','1','0','0','0'},
    {'1','1','0','0','0'},
    {'0','0','1','0','0'},
    {'0','0','0','1','1'}
}
输出：3
解释：左上角、中间和右下角分别形成一座岛屿。
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numIslands(vector<vector<char>>& grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;

        int rows = static_cast<int>(grid.size());
        int columns = static_cast<int>(grid[0].size());
        int islandCount = 0;

        for (int row = 0; row < rows; row++)
        {
            for (int column = 0; column < columns; column++)
            {
                if (grid[row][column] == '1')
                {
                    // 发现一座新岛屿，再用 DFS 标记这座岛屿的全部陆地。
                    islandCount++;
                    dfs(grid, row, column);
                }
            }
        }

        return islandCount;
    }

private:
    //深度搜索就是先写清楚边界条件，然后再进行递归
    void dfs(vector<vector<char>>& grid, int row, int column)
    {
        int rows = static_cast<int>(grid.size());
        int columns = static_cast<int>(grid[0].size());

        // 越界或者遇到水，说明当前方向不能继续搜索。
        if (row < 0 || row >= rows || column < 0 || column >= columns ||
            grid[row][column] == '0')
        {
            return;
        }

        // 先标记为已访问，避免相邻陆地之间反复递归。
        grid[row][column] = '0';//单元陆地沉降

        dfs(grid, row - 1, column); // 上
        dfs(grid, row + 1, column); // 下
        dfs(grid, row, column - 1); // 左
        dfs(grid, row, column + 1); // 右
    }
};

int main()
{
    Solution solution;

    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    cout << "示例一：期望结果 = 1，实际结果 = "
         << solution.numIslands(grid1) << '\n';

    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "示例二：期望结果 = 3，实际结果 = "
         << solution.numIslands(grid2) << '\n';

    vector<vector<char>> grid3 = {{'0'}};
    cout << "全是水：期望结果 = 0，实际结果 = "
         << solution.numIslands(grid3) << '\n';

    return 0;
}

/*
收获点：
1. 二维网格可以看成图，每个陆地格子是一个节点，上下左右相邻关系是边。
2. 主函数每遇到一块未访问陆地，岛屿数量加 1，再用 DFS 遍历整座岛。
3. DFS 必须先判断边界，并在继续递归前标记当前格子，避免重复访问。
4. 每个格子最多访问一次，时间复杂度为 O(rows * columns)；
   最坏情况下递归栈的空间复杂度为 O(rows * columns)。
*/
