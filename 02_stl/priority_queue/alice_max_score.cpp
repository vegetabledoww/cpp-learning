// 题目：测试人工智能 Alice 的智力
//
// 有一组长度为偶数的数组。每一轮先由 Alice 从数组中取出一个数，
// 放入自己的系统池；随后工程师删除剩余数组中间位置的数。
// 求 Alice 系统池中所有数字之和的最大值。
//
// 示例：[1, 2, 1, 5, 1, 10]
// step 1：Alice 取 5，工程师取中间的 1，数组变为 [1, 2, 1, 10]；
// step 2：Alice 取 2，工程师取中间的 1，数组变为 [1, 10]；
// step 3：Alice 取 10，最终最大总和为 5 + 2 + 10 = 17。

#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

long long maxAliceScore(const vector<int>& nums)
{
    priority_queue<int,vector<int>,greater<int>>q;    
    int half = nums.size()/2;
    long long answer = 0;
    //只需要将中间的两个值不断地push进优先队列，然后pop出较小的即可
    for (int layer = 0; layer < half; layer++)
    {
        q.push(nums[half - layer - 1]);
        q.push(nums[half + layer]);
        q.pop();
    }
    while (!q.empty())
    {
        answer += (long long)q.top();
        q.pop();
    }
    return answer;
}

int main()
{
    vector<int> nums = {1, 2, 1, 5, 1, 10};
    cout << "Alice 能取得的最大总和：" << maxAliceScore(nums) << '\n';
    return 0;
}
//例子：{200,2,77,100}