/*
题目：柱状图中最大的矩形（LeetCode 84）

给定一个非负整数数组 heights，heights[i] 表示第 i 根柱子的高度。
每根柱子的宽度都为 1，请计算柱状图中能够组成的最大矩形面积。

示例一：
输入：heights = {2, 1, 5, 6, 2, 3}
输出：10
解释：高度为 5 和 6 的两根柱子可以组成面积为 5 * 2 = 10 的矩形。

示例二：
输入：heights = {2, 4}
输出：4
解释：既可以选择高度为 4 的一根柱子，也可以选择两根柱子组成高度为 2 的矩形。
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int>& heights)
    {
        stack<int> indexStack; // 存放柱子的下标，栈中柱子的高度保持从小到大
        int maxArea = 0;
        int n = static_cast<int>(heights.size());

        // i == n 时使用高度为 0 的虚拟柱子，让栈中剩余柱子全部完成结算。
        for (int i = 0; i <= n; i++)
        {
            int currentHeight = (i == n) ? 0 : heights[i];

            // 当前柱子更矮，说明栈顶柱子的右边界已经确定。
            while (!indexStack.empty() && heights[indexStack.top()] > currentHeight)
            {
                int height = heights[indexStack.top()];//更新高的柱子的高度
                indexStack.pop();//弹出当前柱子的下标

                // 弹栈后，新栈顶是左侧第一个比 height 矮的柱子。
                int leftBoundary = indexStack.empty() ? -1 : indexStack.top();
                int width = i - leftBoundary - 1;
                maxArea = max(maxArea, height * width);
            }

            // 虚拟柱子只用于结算，不需要存入栈中。
            if (i < n)
            {
                indexStack.push(i);//将下标入栈
            }
        }

        return maxArea;
    }
};

int main()
{
    Solution solution;

    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    cout << "示例一：期望结果 = 10，实际结果 = "
         << solution.largestRectangleArea(heights1) << '\n';

    // vector<int> heights2 = {2, 4};
    // cout << "示例二：期望结果 = 4，实际结果 = "
    //      << solution.largestRectangleArea(heights2) << '\n';

    // vector<int> singleBar = {5};
    // cout << "单根柱子：期望结果 = 5，实际结果 = "
    //      << solution.largestRectangleArea(singleBar) << '\n';

    // vector<int> increasing = {1, 2, 3, 4};
    // cout << "高度递增：期望结果 = 6，实际结果 = "
    //      << solution.largestRectangleArea(increasing) << '\n';

    // vector<int> decreasing = {4, 3, 2, 1};
    // cout << "高度递减：期望结果 = 6，实际结果 = "
    //      << solution.largestRectangleArea(decreasing) << '\n';

    // vector<int> sameHeight = {2, 2, 2};
    // cout << "高度相同：期望结果 = 6，实际结果 = "
    //      << solution.largestRectangleArea(sameHeight) << '\n';

    return 0;
}
