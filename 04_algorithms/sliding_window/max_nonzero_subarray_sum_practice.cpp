/*
题目：长度不超过 num 的非零连续子数组最大和（手敲练习）

给定一个非负整数数组 locs 和一个正整数 num，locs 中可能包含 0。
请选出一个非空连续子数组，要求其中不包含 0，且长度不超过 num，
返回所有符合条件的子数组中的最大元素和。

如果 locs 为空，或数组中没有非零元素，返回 0。
补充约定：num <= 0 时返回 0。
元素和可能超过 int 的范围，返回值和求和变量应使用 long long。

示例 1：
输入：locs = {1, 2, 3, 4, 1, 0, 8, 2, 6, 4}, num = 4
输出：20
解释：选择 {8, 2, 6, 4}，长度为 4，元素和为 20。

示例 2：
输入：locs = {5, 0, 2, 3, 0, 4, 4, 4}, num = 2
输出：8
解释：选择两个连续的 4，长度为 2，元素和为 8；不能跨过 0。

练习方式：只需填写下面的成员函数，main 已提供测试。
当前返回 -1 只是未完成标记，运行时所有测试失败是正常的。
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution
{
public:
    long long GetMaxNonZeroSubarraySum(const vector<int> &locs, int num)
    {
        int n = locs.size();
        long long answer = 0;
        int left = 0;
        long long max_sum = 0;
        for (int right = 0; right < n; right++)
        {
            answer += locs[right];
            if(locs[right] == 0)
            {
                left = right + 1;
                answer = 0;//清零重启
                continue;
            }
            while (right - left >= num)
            {
                answer -= locs[left];
                left++;
            }
            max_sum = max(max_sum, answer);
        }
        return max_sum;
    }
};

struct TestCase
{
    string name;
    vector<int> locs;
    int num;
    long long expected;
};

int main()
{
    Solution solution;
    vector<TestCase> testCases = {
        {"example 1", {1, 2, 3, 4, 1, 0, 8, 2, 6, 4}, 4, 20},
        {"example 2", {5, 0, 2, 3, 0, 4, 4, 4}, 2, 8},
        {"all zeros", {0, 0, 0}, 2, 0},
        {"num exceeds segment length", {1, 2, 0, 4}, 10, 4},
        {"num equals one", {1, 9, 2, 0, 8}, 1, 9},
        {"empty input", {}, 3, 0},
        {"invalid num", {1, 2, 3}, 0, 0},
        {"zeros separate segments", {0, 5, 0, 0, 6, 0}, 3, 6},
        {"sum exceeds int", {1000000000, 1000000000, 1000000000}, 3,
         3000000000LL}};

    int failed = 0;
    for (const TestCase &test : testCases)
    {
        long long actual = solution.GetMaxNonZeroSubarraySum(test.locs, test.num);
        bool passed = actual == test.expected;

        cout << test.name << ": " << (passed ? "PASS" : "FAIL")
             << ", expected=" << test.expected
             << ", actual=" << actual << '\n';

        if (!passed)
        {
            failed++;
        }
    }

    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
练习后复盘（完成代码后自己填写）：
1. 你如何保证子数组不包含 0？
2. 你如何保证长度不超过 num？
3. 时间复杂度和额外空间复杂度分别是多少？
*/
