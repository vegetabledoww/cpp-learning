/*
题目：滑动窗口最大值（LeetCode 239）

给定整数数组 nums 和窗口长度 k，每次将窗口向右移动一格，
按顺序返回每个长度为 k 的连续窗口中的最大值。元素可以为负数或重复。
正常输入满足 1 <= k <= nums.size()；本地补充约定：非法 k 返回空数组。

示例一：nums={1,3,-1,-3,5,3,6,7}, k=3
输出：{3,3,5,5,6,7}
解释：前两个窗口分别是 {1,3,-1}、{3,-1,-3}，最大值都是 3。

示例二：nums={9,7,5}, k=2
输出：{9,7}
解释：9 离开窗口后，第二个窗口 {7,5} 的最大值是 7。
*/
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = static_cast<int>(nums.size());
        if (k <= 0 || k > n) return {};
        vector<int> result;
        deque<int> candidates;
        for (int right = 0; right < n; right++)
        {
            // 队列存下标，便于判断候选最大值是否已经离开窗口。
            while (!candidates.empty() && candidates.front() <= right - k)
                candidates.pop_front();

            // 新元素更大或相等，而且更晚过期；旧的小元素不再可能成为答案。
            while (!candidates.empty() && nums[candidates.back()] <= nums[right])
                candidates.pop_back();
            candidates.push_back(right);

            // 队内下标递增、对应值递减，所以队头就是最大值。
            if (right >= k - 1) result.push_back(nums[candidates.front()]);
        }
        return result;
    }
};

void Print(const vector<int> &values)
{
    cout << '[';
    for (int value : values) cout << value << ' ';
    cout << ']';
}

struct TestCase
{
    vector<int> nums;
    int k;
    vector<int> expected;
};

int main()
{
    vector<TestCase> tests = {
        {{1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7}},
        {{9,7,5}, 2, {9,7}},
        {{1,2,3,4}, 2, {2,3,4}},
        {{2,2,2}, 2, {2,2}},
        {{-4,-2,-5}, 2, {-2,-2}},
        {{3,1,3,2}, 3, {3,3}},
        {{4,-1,2}, 1, {4,-1,2}},
        {{4,-1,2}, 3, {4}},
        {{7}, 1, {7}},
        {{}, 1, {}},
        {{1,2}, 3, {}},
        {{1,2}, 0, {}}};
    Solution solution;
    int failed = 0;
    for (TestCase &test : tests)
    {
        vector<int> actual = solution.maxSlidingWindow(test.nums, test.k);
        cout << "k=" << test.k << " expected=";
        Print(test.expected);
        cout << " actual=";
        Print(actual);
        bool passed = actual == test.expected;
        cout << (passed ? " PASS\n" : " FAIL\n");
        if (!passed) failed++;
    }
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：窗口和可以直接加减；窗口最大值需要保留仍有机会成为答案的候选者。
队头删除过期下标，队尾删除被新元素淘汰的下标，不要混淆两种删除理由。
每个下标入队一次、出队至多一次，总时间 O(n)，队列额外空间 O(k)，不含结果。
*/
