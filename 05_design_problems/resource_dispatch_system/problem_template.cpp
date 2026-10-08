/*
题目：资源请求分发系统（根据现有代码整理）

系统中有若干台机器，capacities[i] 表示下标为 i 的机器初始可用容量。
requests 中的请求按顺序到达。对每个请求 request，需要按照下面的规则分配：

1. 只能选择剩余容量大于或等于 request 的机器；
2. 在所有可选机器中，优先选择剩余容量最小的机器；
3. 如果多台机器的剩余容量相同，选择下标最小的机器；
4. 分配成功后，该机器的剩余容量减去 request，并记录机器下标；
5. 如果没有机器能够满足请求，记录 -1，机器状态保持不变。

请实现 DispatchRequests，返回每个请求对应的机器下标。

输入约定：
- capacities 中的容量是非负 int；
- requests 中的请求量是正 int；
- 机器数量不超过 INT_MAX；
- 容量和请求不要求是 32 的倍数。

示例一：
capacities = {32, 256, 192, 64}
requests   = {128, 64, 64, 512}
输出       = {2, 2, 3, -1}

解释：
- 128 分给容量为 192 的机器 2，机器 2 剩余 64；
- 此时机器 2 和机器 3 都剩余 64，选择下标更小的机器 2；
- 下一个 64 分给机器 3；
- 最后没有机器能够满足 512。

示例二：
capacities = {100, 100, 150}
requests   = {60, 30, 80}
输出       = {0, 0, 1}

解释：第一次在两台容量为 100 的机器中选择下标 0；机器 0 剩余 40，
仍是能够满足 30 的最小容量；最后 80 分给机器 1。

示例三：
capacities = {50, 80}
requests   = {100, 50, 30}
输出       = {-1, 0, 1}

解释：100 分配失败且不改变状态；随后 50 分给机器 0，30 分给机器 1。
*/

#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> DispatchRequests(const vector<int> &capacities,
                                 const vector<int> &requests)
    {
        // TODO：在这里完成资源分发逻辑。
        // 开始实现后，可以删除下面两行；它们只用于消除空骨架的未使用参数警告。
        (void)capacities;
        (void)requests;
        return {};
    }
};

/*
手敲提示：
1. 用 set<pair<int, int>> 保存（剩余容量，机器下标）。
2. 对每个请求，用 lower_bound 找第一台容量足够的机器。
3. 分配成功时，先删除旧 pair，再扣减容量并插回 set。
*/
