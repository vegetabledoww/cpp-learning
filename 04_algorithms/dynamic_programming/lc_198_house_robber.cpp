/*
题目：打家劫舍（LeetCode 198）

给定数组 nums，nums[i] 表示第 i 间房屋的现金。相邻房屋装有相连的报警器，
因此不能偷相邻的两间房屋。返回一晚能够偷到的最大金额。

示例一：
输入：nums=[1,2,3,1]
输出：4

示例二：
输入：nums=[2,7,9,3,1]
输出：12
*/

#include<iostream>
#include<vector>
using namespace std;

int rob(vector<int>&nums)
{
    int n=nums.size();
    if(nums.empty()) return 0;
    if(n==1)return nums[0];
    vector<int>dp(n);
    dp[0]=nums[0];
    dp[1]=max(nums[0],nums[1]);
    for(int i=2;i<n;i++)
    {
        dp[i]=max(dp[i-1],dp[i-2]+nums[i]);
    }
    return dp[n-1];
}
int main()
{
    vector<int>nums1={1,2,3,1};
    cout << "示例一 expected=4\n";
    cout << "actual=" << rob(nums1) << '\n';

    vector<int>nums2={2,7,9,3,1};
    cout << "示例二 expected=12\n";
    cout << "actual=" << rob(nums2) << '\n';
    return 0;
}
