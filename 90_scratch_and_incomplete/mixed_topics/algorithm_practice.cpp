/*
题目：基础算法综合练习

本文件包含四个独立练习：快速排序、二叉树层序遍历、搜索旋转排序数组、
最长公共子序列。main 函数分别为每个算法准备两组测试。

1. quickSort(nums)：将整数数组按升序原地排序。
2. levelOrder(root)：按照从上到下、从左到右的顺序返回二叉树每一层的节点值。
3. searchRotatedArray(nums,target)：nums 是元素互不相同的升序数组经过一次旋转
   得到的数组；返回 target 的下标，找不到时返回 -1，要求 O(log n) 时间。
4. longestCommonSubsequence(text1,text2)：返回两个字符串的最长公共子序列长度。

示例一：
快速排序 [3,1,2] -> [1,2,3]
层序遍历 [1,2,3] -> [[1],[2,3]]
旋转数组 [4,5,6,7,0,1,2] 中查找 0 -> 4
最长公共子序列 "abcde" 与 "ace" -> 3

示例二：
快速排序 [5,5,-1] -> [-1,5,5]
空树层序遍历 -> []
旋转数组 [4,5,6,7,0,1,2] 中查找 3 -> -1
最长公共子序列 "abc" 与 "def" -> 0
*/

#include "tree_node.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// 快速排序算法
void swapElements(vector<int> &nums, int left, int right)
{
    int temp = nums[left];
    nums[left] = nums[right];
    nums[right] = temp;
}

int partitionArray(vector<int> &nums, int left, int right)
{
    int i = left, j = right;
    while (i < j)
    {
        while (i < j && nums[j] >= nums[left])
        {
            j--;
        }
        while (i < j && nums[i] <= nums[left])
        {
            i++;
        }
        swapElements(nums, i, j);
    }
    swapElements(nums, i, left);
    return i;
}

void quickSort(vector<int> &nums, int left, int right)
{
    if (left >= right)
        return;
    int pivotIndex = partitionArray(nums, left, right);
    quickSort(nums, pivotIndex + 1, right);
    quickSort(nums, left, pivotIndex - 1);
}

void quickSort(vector<int> &nums)
{
    quickSort(nums,0,static_cast<int>(nums.size())-1);
}

// 二叉树的层序遍历
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> res;
    if (!root)
        return res;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int sz = static_cast<int>(q.size());
        vector<int> level;
        for (int i = 0; i < sz; i++)
        {
            TreeNode *cur = q.front();
            q.pop();
            level.push_back(cur->val);
            if (cur->left)
                q.push(cur->left);
            if (cur->right)
                q.push(cur->right);
        }
        res.push_back(level);
    }
    return res;
}

// 搜索旋转的排序数组  leetcode33  二分查找  o(logn)时间复杂度
int searchRotatedArray(const vector<int> &nums, int target)
{
    int n = static_cast<int>(nums.size());
    if (!n)
        return -1;
    if (n == 1)
        return nums[0] == target ? 0 : -1;
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = l + (r-l)/2;
        if (nums[mid] == target)
            return mid;
        // 只能在有序一侧采用缩小搜索范围，无序一侧不行（相当于分两段找）
        if (nums[mid] >= nums[0]) // 左侧有序
        {
            if (nums[0] <= target && target < nums[mid])
                r = mid - 1;
            else
                l = mid + 1;
        }
        else // mid右侧有序
        {
            if (nums[mid] < target && target <= nums[n - 1])
                l = mid + 1;
            else
                r = mid - 1;
        }
    }
    return -1;
}

// leetcode 1143题  最长公共子序列
int longestCommonSubsequence(const string &text1, const string &text2)
{
    int m = static_cast<int>(text1.length());
    int n = static_cast<int>(text2.length());
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++)
    {
        char c1 = text1[i - 1];
        for (int j = 1; j <= n; j++)
        {
            char c2 = text2[j - 1];
            if (c1 == c2)
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
     return dp[m][n];
}

void printVector(const vector<int> &values)
{
    cout << '[';
    for (size_t i=0;i<values.size();i++)
    {
        cout << values[i];
        if (i+1<values.size()) cout << ',';
    }
    cout << "]\n";
}

void printLevels(const vector<vector<int>> &levels)
{
    cout << '[';
    for (size_t i=0;i<levels.size();i++)
    {
        cout << '[';
        for (size_t j=0;j<levels[i].size();j++)
        {
            cout << levels[i][j];
            if (j+1<levels[i].size()) cout << ',';
        }
        cout << ']';
        if (i+1<levels.size()) cout << ',';
    }
    cout << "]\n";
}

int main()
{
    vector<int> nums1={3,1,2};
    quickSort(nums1);
    cout << "快速排序示例一 expected=[1,2,3]\nactual=";
    printVector(nums1);

    vector<int> nums2={5,5,-1};
    quickSort(nums2);
    cout << "快速排序示例二 expected=[-1,5,5]\nactual=";
    printVector(nums2);

    TreeNode left(2),right(3),root(1,&left,&right);
    cout << "层序遍历示例一 expected=[[1],[2,3]]\nactual=";
    printLevels(levelOrder(&root));
    cout << "层序遍历示例二 expected=[]\nactual=";
    printLevels(levelOrder(nullptr));

    vector<int> rotated={4,5,6,7,0,1,2};
    cout << "旋转数组示例一 expected=4\nactual=" << searchRotatedArray(rotated,0) << '\n';
    cout << "旋转数组示例二 expected=-1\nactual=" << searchRotatedArray(rotated,3) << '\n';

    cout << "最长公共子序列示例一 expected=3\nactual="
         << longestCommonSubsequence("abcde","ace") << '\n';
    cout << "最长公共子序列示例二 expected=0\nactual="
         << longestCommonSubsequence("abc","def") << '\n';
    return 0;
}
