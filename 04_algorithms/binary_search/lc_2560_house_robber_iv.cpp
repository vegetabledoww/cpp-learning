/*
题目：打家劫舍 IV（LeetCode 2560）

给定数组 nums，nums[i] 表示第 i 间房屋的现金。不能偷相邻房屋，并且必须
至少偷 k 间。窃贼的能力值是所偷房屋中的最大金额，返回可能的最小能力值。

示例一：
输入：nums=[2,3,5,9]，k=2
输出：5

示例二：
输入：nums=[2,7,9,3,1]，k=2
输出：2
*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
bool check(vector<int> &nums, int k, int mx)
{
    int f0 = 0, f1 = 0;
    for (int x : nums)
    {
        if (x > mx)
        {
            f0 = f1;
        }
        else
        {
            int tmp = f1;
            f1 = max(f1, f0 + 1);
            f0 = tmp;
        }
    }
    return f1 >= k;
}

// 二分查找
int minCapability(vector<int> &nums, int k)
{
    int right = *max_element(nums.begin(), nums.end());
    int left = 0;
    while (left + 1 < right)
    {
        int mid = (left + right) / 2;
        (check(nums, k, mid) ? right : left) = mid;
    }
    return right;
}

int main()
{
    vector<int> nums1={2,3,5,9};
    cout << "示例一 expected=5\n";
    cout << "actual=" << minCapability(nums1,2) << '\n';

    vector<int> nums2={2,7,9,3,1};
    cout << "示例二 expected=2\n";
    cout << "actual=" << minCapability(nums2,2) << '\n';
    return 0;
}

