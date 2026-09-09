// 股票的最佳买卖时机(1,2,3,4)系列题目（多维动态规划）
#include <vector>
#include <iostream>
using namespace std;

int maxProfit1(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2));
    // 两个初始状态
    dp[0][0] = 0;          // 第0天 没持有股票
    dp[0][1] = -prices[0]; // 第0天 持有股票
    // 解释两个状态：
    // dp[i][0]
    // i表示第i天
    // 0 表示没持有股票，1表示持有股票
    for (int i = 1; i < n; ++i)
    {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = max(dp[i - 1][1], -prices[i]);
    }
    return dp[n - 1][0];
}

int maxProfit2(vector<int> &prices)
{
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i < n; i++)
    {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return dp[n - 1][0];
}

int maxProfit3(vector<int> &prices)
{
    int k_max=2,n=prices.size();
    vector<vector<vector<int>>>dp(n,vector<vector<int>>(k_max+1,vector<int>(2)));
    for (int i = 0; i < n; i++)
    {
        for(int k=k_max;k>=1;k--)
        {
            if(i-1==-1)
            {
                dp[i][k][0]=0;
                dp[i][k][1]=-prices[0];
                continue;
            }
            dp[i][k][0]=max(dp[i-1][k][0],dp[i-1][k][1]+prices[i]);//卖
            dp[i][k][1]=max(dp[i-1][k][1],dp[i-1][k-1][0]-prices[i]);//买
        }
    }
    return dp[n-1][k_max][0];
}

    int maxProfit4(int k, vector<int>& prices) 
    {
        int n=prices.size();
        vector<vector<vector<int>>>dp(n,vector<vector<int>>(k+1,vector<int>(2)));
        for(int i=0;i<n;i++)
        {
            for(int j=k;j>=1;j--)
            {
                if(i-1==-1)
                {
                    dp[i][j][0]=0;
                    dp[i][j][1]=-prices[i];
                    continue;
                }
                dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]+prices[i]);
                dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j-1][0]-prices[i]);
            }
        }
        return dp[n-1][k][0];
    }

int main(int argc, char const *argv[])
{
    vector<int> nums = {3,3,5,0,0,3,1,4};
    cout << maxProfit3(nums);
    return 0;
}