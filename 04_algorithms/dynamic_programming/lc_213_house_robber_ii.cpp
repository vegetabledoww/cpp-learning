/*
题目：打家劫舍 II（LeetCode 213）

给定数组 nums，房屋围成一圈，所以第一间和最后一间也相邻。不能偷任何
两间相邻房屋，返回一晚能够偷到的最大金额。

示例一：
输入：nums=[2,3,2]
输出：3

示例二：
输入：nums=[1,2,3,1]
输出：4
*/

#include<iostream>
#include<vector>
using namespace std;

int rob2(vector<int>&nums)
{
    int n=nums.size();
    if(nums.empty())return 0;
    if(n==1)return nums[0];
    if(n==2)return max(nums[0],nums[1]);

    vector<int>dp1(n-1);//偷首家
    dp1[0]=nums[0];
    dp1[1]=max(nums[0],nums[1]);
    for (int i = 2; i <= n-2; i++)
    {
        dp1[i]=max(dp1[i-1],dp1[i-2]+nums[i]);
    }
    
    vector<int>dp2(n);//偷末家
    dp2[1]=nums[1];
    dp2[2]=max(nums[1],nums[2]);
    for (int i = 3; i <= n-1; i++)
    {
        dp2[i]=max(dp2[i-1],dp2[i-2]+nums[i]);
    }
    return max(dp1[n-2],dp2[n-1]);
}

int main()
{
    vector<int>nums1={2,3,2};
    cout << "示例一 expected=3\n";
    cout << "actual=" << rob2(nums1) << '\n';

    vector<int>nums2={1,2,3,1};
    cout << "示例二 expected=4\n";
    cout << "actual=" << rob2(nums2) << '\n';
    return 0;
}
