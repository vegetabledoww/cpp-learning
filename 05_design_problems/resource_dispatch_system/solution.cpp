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

解释：128 分给机器 2 后，它和机器 3 都剩余 64；下一个请求按照
下标规则继续选择机器 2。第三个请求选择机器 3，最后的 512 分配失败。

示例二：
capacities = {100, 100, 150}
requests   = {60, 30, 80}
输出       = {0, 0, 1}

解释：第一次在相同容量中选择下标 0；它剩余 40，仍是满足 30 的
最小容量；最后 80 分给机器 1。

示例三：
capacities = {50, 80}
requests   = {100, 50, 30}
输出       = {-1, 0, 1}

解释：100 分配失败且不改变状态；随后两个请求仍可正常分配。
*/

#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> DispatchRequests(const vector<int> &capacities,
                                 const vector<int> &requests)
    {
        // pair 的 first 是剩余容量，second 是机器下标。
        // set 默认先按 first 排序，容量相同再按 second 排序，
        // 正好对应“最小足够容量优先，下标小者优先”。
        set<pair<int, int>> machines;
        for (size_t i = 0; i < capacities.size(); ++i)
        {
            machines.emplace(capacities[i], static_cast<int>(i));
        }

        vector<int> result;
        result.reserve(requests.size());

        for (int request : requests)
        {
            // -1 小于任何合法机器下标，因此会找到容量至少为 request
            // 的第一台机器；如果容量相同，就是其中下标最小的一台。
            auto position = machines.lower_bound({request, -1});
            if (position == machines.end())
            {
                result.push_back(-1);
                continue; // 分配失败，set 中的机器状态完全不变。
            }

            int remainingCapacity = position->first;
            int machineIndex = position->second;

            // set 元素是排序依据，不能原地修改。先删除旧状态，
            // 再扣除本次请求，把机器的新状态重新放回有序集合。
            machines.erase(position);
            remainingCapacity -= request;
            machines.emplace(remainingCapacity, machineIndex);
            result.push_back(machineIndex);
        }

        return result;
    }
};

void PrintVector(const vector<int> &values)
{
    cout << '{';
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        cout << values[i];
    }
    cout << '}';
}

int CheckResult(const char *name,
                const vector<int> &actual,
                const vector<int> &expected)
{
    cout << name << " expected=";
    PrintVector(expected);
    cout << " actual=";
    PrintVector(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    Solution solution;
    int failed = 0;

    failed += CheckResult(
        "原始样例与容量并列",
        solution.DispatchRequests({32, 256, 192, 64}, {128, 64, 64, 512}),
        {2, 2, 3, -1});

    failed += CheckResult(
        "重复选择当前最小足够容量",
        solution.DispatchRequests({100, 100, 150}, {60, 30, 80}),
        {0, 0, 1});

    failed += CheckResult(
        "失败请求不改变机器状态",
        solution.DispatchRequests({50, 80}, {100, 50, 30}),
        {-1, 0, 1});

    failed += CheckResult(
        "容量不必是32的倍数",
        solution.DispatchRequests({7, 10}, {6, 3, 8}),
        {0, 1, -1});

    failed += CheckResult(
        "没有机器",
        solution.DispatchRequests({}, {1, 2}),
        {-1, -1});

    failed += CheckResult(
        "没有请求",
        solution.DispatchRequests({10}, {}),
        {});

    cout << "failed=" << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. set<pair<int, int>> 可以直接维护“第一关键字容量、第二关键字下标”的顺序。
2. lower_bound({request, -1}) 能一次找到容量最小且足够的机器，并自动处理并列。
3. set 中的值决定排序位置，状态变化时要先删除旧值，再插入新值。
4. 设机器数为 N、请求数为 M：总时间复杂度为 O((N+M)logN)，
   额外空间复杂度为 O(N)。
*/
