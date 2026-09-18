/*
题目：长度不超过 num 的非零连续子数组最大和

给定一个非负整数数组 locs 和一个正整数 num，locs 中可能包含 0。
请选出一个非空连续子数组，要求子数组中不包含 0，并且长度不超过 num，
返回所有符合条件的子数组中的最大元素和。

如果 locs 为空，或者数组中不存在非零元素，则返回 0。
元素和可能超过 int 的范围，因此函数返回 long long。

示例 1：
输入：locs = {1, 2, 3, 4, 1, 0, 8, 2, 6, 4}, num = 4
输出：20
解释：长度为 4 的非零连续子数组有 {1, 2, 3, 4}、{2, 3, 4, 1}、
     {8, 2, 6, 4}，其中最大的元素和为 8 + 2 + 6 + 4 = 20。

示例 2：
输入：locs = {5, 0, 2, 3, 0, 4, 4, 4}, num = 2
输出：8
解释：子数组不能跨过 0，并且长度最多为 2。
     选择任意两个连续的 4，元素和为 8，是所有合法子数组中的最大值。
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 解法一：不创建分组，直接在原数组上维护滑动窗口。
class Solution
{
public:
    // 使用滑动窗口寻找长度不超过 num、且不包含 0 的连续子数组最大和。
    // locs 只读，所以使用 const 引用；窗口和使用 long long 防止 int 相加溢出。
    long long GetMaxNonZeroSubarraySum(const vector<int> &locs, int num)
    {
        if (locs.empty() || num <= 0)
        {
            return 0;
        }

        int left = 0;
        long long windowSum = 0;
        long long answer = 0;
        //两个限制：1.num的长度 2. 0
        for (int right = 0; right < static_cast<int>(locs.size()); right++)
        {
            if (locs[right] == 0)
            {
                // 合法子数组不能包含 0，因此下一个窗口从 0 的右侧重新开始。
                left = right + 1;
                windowSum = 0;
                continue;
            }

            windowSum += locs[right];

            // 窗口长度超过 num 时移动左边界，直到长度重新合法。
            while (right - left + 1 > num)
            {
                windowSum -= locs[left];
                left++;
            }

            // 元素均为非负数。对同一个 right，合法窗口越长，和不会越小。
            if (windowSum > answer)
            {
                answer = windowSum;
            }
        }

        return answer;
    }
};

// 解法二：先按照 0 拆成二维数组，再分别处理每个非零分组。
class SolutionByGroups
{
public:
    long long GetMaxNonZeroSubarraySum(const vector<int> &locs, int num)
    {
        if (locs.empty() || num <= 0)
        {
            return 0;
        }

        vector<vector<int>> groups;
        vector<int> currentGroup;

        // 第一步：0 是分隔符，将两个 0 之间的非零元素保存成一行。
        for (int value : locs)
        {
            if (value == 0)
            {
                if (!currentGroup.empty())
                {
                    groups.push_back(currentGroup);
                    currentGroup.clear();
                }
            }
            else
            {
                currentGroup.push_back(value);
            }
        }

        // 数组末尾没有 0 时，最后一组需要单独放入二维数组。
        if (!currentGroup.empty())
        {
            groups.push_back(currentGroup);
        }

        long long answer = 0;

        // 第二步：每一行都不含 0，分别寻找长度不超过 num 的最大和。
        for (const vector<int> &group : groups)
        {
            long long windowSum = 0;

            for (int i = 0; i < static_cast<int>(group.size()); i++)
            {
                windowSum += group[i];

                // 加入新元素后只保留最近 num 个元素。
                if (i >= num)
                {
                    windowSum -= group[i - num];
                }

                if (windowSum > answer)
                {
                    answer = windowSum;
                }
            }
        }

        return answer;
    }
};

struct TestCase
{
    string name;
    vector<int> locs;
    int num;
    long long expected;
};

// 运行题面样例和边界测试，并通过返回值表示是否全部通过。
int main()
{
    Solution directSolution;
    SolutionByGroups groupedSolution;
    vector<TestCase> testCases = {
        {"example 1", {1, 2, 3, 4, 1, 0, 8, 2, 6, 4}, 4, 20},
        {"example 2", {5, 0, 2, 3, 0, 4, 4, 4}, 2, 8},
        {"all zeros", {0, 0, 0}, 2, 0},
        {"num exceeds segment length", {1, 2, 0, 4}, 10, 4},
        {"num equals one", {1, 9, 2, 0, 8}, 1, 9},
        {"empty input", {}, 3, 0},
        {"invalid num", {1, 2, 3}, 0, 0},
        {"sum exceeds int", {1000000000, 1000000000, 1000000000}, 3,
         3000000000LL}};

    int failed = 0;
    for (const TestCase &test : testCases)
    {
        long long directActual =
            directSolution.GetMaxNonZeroSubarraySum(test.locs, test.num);
        long long groupedActual =
            groupedSolution.GetMaxNonZeroSubarraySum(test.locs, test.num);
        bool passed = directActual == test.expected &&
                      groupedActual == test.expected;

        cout << test.name << ": " << (passed ? "PASS" : "FAIL")
             << ", expected=" << test.expected
             << ", direct=" << directActual
             << ", grouped=" << groupedActual << '\n';

        if (!passed)
        {
            failed++;
        }
    }

    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. 0 相当于分隔符：遇到 0 时清空窗口，并从它的右侧重新开始。
2. right 负责扩大窗口；窗口长度超过 num 后，left 负责缩小窗口。
3. 因为数组元素非负，所以对同一个右端点，最长的合法窗口一定不劣于更短窗口。
4. 二维数组解法先按 0 分组，再逐行计算，逻辑更直观，但需要 O(n) 额外空间。
5. 两种解法的时间复杂度都是 O(n)；直接滑动窗口的额外空间复杂度为 O(1)。
*/
