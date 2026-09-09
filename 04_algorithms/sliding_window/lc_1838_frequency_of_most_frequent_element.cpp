/*
题目：最高频元素的频数（LeetCode 1838）

元素的频数是该元素在数组中出现的次数。
给定一个整数数组 nums 和一个整数 k。一次操作可以选择 nums 中的一个元素，
并将该元素增加 1。最多执行 k 次操作，返回数组中最高频元素的最大可能频数。

示例一：
输入：nums = {1, 2, 4}，k = 5
输出：3
解释：把 1 增加 3 次，把 2 增加 2 次，数组变成 {4, 4, 4}。

示例二：
输入：nums = {1, 4, 8, 13}，k = 5
输出：2
解释：可以把 1 增加 3 次，数组变成 {4, 4, 8, 13}。
     无法在 5 次操作内让三个元素相同。
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxFrequency(vector<int>& nums, int k)
    {
        if (nums.empty())
            return 0;
        // 排序后，窗口内所有元素都只需要增加到最右边的 nums[right]。
        sort(nums.begin(), nums.end());
        int n = static_cast<int>(nums.size());
        // prefix[i] 表示 nums[0] 到 nums[i - 1] 的元素之和。
        vector<long long> prefix(n + 1, 0);//定义一个前缀和数组
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];
        int left = 0;
        int answer = 1;
        //滑动窗口经典格式
        for (int right = 0; right < n; right++)
        {
            // 把窗口内所有元素增加到 nums[right] 所需要的操作次数：
            // 目标总和 - 窗口原来的总和。
            long long windowSum = prefix[right + 1] - prefix[left];
            //cost：将窗口内的所有数，搞到最大时，需要的操作步数
            long long cost = 1LL * nums[right] * (right - left + 1) - windowSum;

            // 操作次数超过 k 时，缩小窗口，直到当前窗口重新合法。
            while (cost > k)
            {
                left++;
                windowSum = prefix[right + 1] - prefix[left];
                cost = 1LL * nums[right] * (right - left + 1) - windowSum;
            }
            //跳出while的话，则证明符合条件，此时该窗口内的所有元素都相等，
            //也即：这个虚拟窗口的size即为answer
            answer = max(answer, right - left + 1);
        }

        return answer;
    }
};

int main()
{
    Solution solution;

    vector<int> nums1 = {1, 2, 4};
    cout << "示例一：期望结果 = 3，实际结果 = "
         << solution.maxFrequency(nums1, 5) << '\n';

    vector<int> nums2 = {1, 4, 8, 13};
    cout << "示例二：期望结果 = 2，实际结果 = "
         << solution.maxFrequency(nums2, 5) << '\n';

    vector<int> nums3 = {3, 9, 6};
    cout << "补充测试：期望结果 = 1，实际结果 = "
         << solution.maxFrequency(nums3, 2) << '\n';

    return 0;
}

/*
收获点：
1. 排序后，可以把 nums[right] 作为当前窗口要变成的目标值。
2. 前缀和可以在 O(1) 时间内计算窗口 [left, right] 的元素总和。
3. cost = 目标总和 - 原窗口总和；cost > k 时向右移动 left。
4. 每个下标最多被 left 和 right 各访问一次，窗口部分为 O(n)；
   加上排序后，总时间复杂度为 O(n log n)，空间复杂度为 O(n)。
*/
