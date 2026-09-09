/*
题目：最小价格差的商品对数量

给定一个整数数组 prices，prices[i] 表示第 i 件商品的价格。
任取两件不同的商品 i 和 j（i < j），它们的价格差定义为：

    abs(prices[i] - prices[j])

请找出所有商品对中的最小价格差，并返回达到该最小价格差的商品对数量。
不同下标视为不同商品，即使它们的价格相同，也需要分别统计。

如果商品数量少于 2，返回 0。

数据范围：
- 0 <= prices.size() <= 2000
- 0 <= prices[i] <= 1000000000

示例 1：
输入：prices = {1, 3, 8, 10, 15}
输出：2
解释：最小价格差是 2，对应商品对 (1, 3) 和 (8, 10)。

示例 2：
输入：prices = {8, 8, 8, 12}
输出：3
解释：最小价格差是 0，三个价格为 8 的商品可以组成 3 个不同的商品对。
*/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution
{
public:
    int GetMinPriceDiff(const vector<int> &prices)
    {
        int n = static_cast<int>(prices.size());
        if (n < 2)
        {
            return 0;
        }

        //key是价格差，value是该价格差对应的商品对数量
        map<int,int>diffCount;//价格差-->数量
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int difference = abs(prices[j] - prices[i]);
                diffCount[difference]++;
            }
        }
        //map自动按照key进行排序
        return diffCount.begin()->second;
        
        // //取出所有出现过的价格差，排序后第一个就是最小价格差
        // vector<int>differences;
        // for (const auto &item : diffCount)
        // {
        //     differences.push_back(item.first);
        // }
        // sort(differences.begin(), differences.end());

        // int minDifference = differences[0];
        //return diffCount[minDifference];
    }
};

int main()
{
    Solution solution;

    vector<int>prices1 = {1, 3, 8, 10, 15};
    cout << "Example 1, expected=2, actual="
         << solution.GetMinPriceDiff(prices1) << '\n';

    vector<int>prices2 = {8, 8, 8, 12};
    cout << "Example 2, expected=3, actual="
         << solution.GetMinPriceDiff(prices2) << '\n';

    return 0;
}
