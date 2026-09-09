/*
题目：零钱兑换（LeetCode 322）

给定不同面额的硬币数组 coins 和总金额 amount，每种硬币可以使用任意次。
返回凑成总金额所需的最少硬币数量；如果无法凑成，则返回 -1。

示例一：
输入：coins=[1,2,5]，amount=11
输出：3

示例二：
输入：coins=[2]，amount=3
输出：-1
*/

#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        //     vector<int> dp(amount+1, amount+1);//因为求得是最小值，所以初始化的很大
        //     dp[0] = 0;//初始化
        //     for(const auto &coin : coins){
        //         for(int j = coin; j <= amount; ++j){//完全背包正序遍历
        //             dp[j] = min(dp[j], dp[j-coin]+1);
        //         }
        //     }
        //     return dp[amount] == amount+1 ? -1 : dp[amount];
        // }
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int &coin : coins)
        {
            for (int i = coin; i <= amount; ++i)
            {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
        return dp.back() == amount + 1 ? -1 : dp.back();
    }
};

int main()
{
    Solution s;
    vector<int>coins1={1,2,5};
    cout << "示例一 expected=3\n";
    cout << "actual=" << s.coinChange(coins1,11) << '\n';

    vector<int>coins2={2};
    cout << "示例二 expected=-1\n";
    cout << "actual=" << s.coinChange(coins2,3) << '\n';
    return 0;
}
