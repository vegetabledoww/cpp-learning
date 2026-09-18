/*
题目：使用 sort 和 priority_queue 处理二元排序

每个任务使用 pair<int, string> 表示：
- first 表示任务优先级；
- second 表示任务名称。

pair 默认先比较 first；如果 first 相同，再比较 second。
请分别完成以下四种处理，并观察它们的对应关系：
1. 使用 sort 按 pair 从小到大排序；
2. 使用 sort 按 pair 从大到小排序；
3. 使用小根堆按 pair 从小到大取出；
4. 使用大根堆按 pair 从大到小取出。

示例一：
输入：{{1,"jinzongquan"}, {1,"aaa"}, {2,"bbb"}}
升序输出：(1,aaa) (1,jinzongquan) (2,bbb)
降序输出：(2,bbb) (1,jinzongquan) (1,aaa)
解释：先比较优先级；优先级相同时，再比较名称的字典序。

示例二：
输入：{{3,"z"}, {2,"b"}, {2,"a"}}
升序输出：(2,a) (2,b) (3,z)
降序输出：(3,z) (2,b) (2,a)
解释：任务 (2,a) 和 (2,b) 的 first 相同，所以继续比较 second。
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Task = pair<int, string>;

void PrintTasks(const vector<Task>& tasks)
{
    for (const Task& task : tasks)
    {
        cout << '(' << task.first << ',' << task.second << ") ";
    }
    cout << '\n';
}

vector<Task> SortAscending(vector<Task> tasks)
{
    // sort 默认使用 less，较小的 pair 放在前面。
    sort(tasks.begin(), tasks.end());
    return tasks;
}

vector<Task> SortDescending(vector<Task> tasks)
{
    // greater 在 sort 中表示：较大的 pair 放在前面，因此得到降序。
    sort(tasks.begin(), tasks.end(), greater<Task>());
    return tasks;
}

vector<Task> PopFromMinHeap(const vector<Task>& tasks)
{
    // greater 在 priority_queue 中会得到小根堆，最小的 pair 位于 top。
    priority_queue<Task, vector<Task>, greater<Task>> minHeap;

    for (const Task& task : tasks)
    {
        minHeap.push(task);
    }

    vector<Task> result;
    while (!minHeap.empty())
    {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    return result;
}

vector<Task> PopFromMaxHeap(const vector<Task>& tasks)
{
    // priority_queue 默认使用 less，因此是大根堆，最大的 pair 位于 top。
    priority_queue<Task> maxHeap;

    for (const Task& task : tasks)
    {
        maxHeap.push(task);
    }

    vector<Task> result;
    while (!maxHeap.empty())
    {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return result;
}

bool CheckResult(const string& testName,
                 const vector<Task>& actual,
                 const vector<Task>& expected)
{
    cout << testName << '\n';
    cout << "期望：";
    PrintTasks(expected);
    cout << "实际：";
    PrintTasks(actual);
    cout << (actual == expected ? "结果：通过\n\n" : "结果：失败\n\n");

    return actual == expected;
}

int main()
{
    int failedCount = 0;

    vector<Task> tasks1 = {
        {1, "jinzongquan"},
        {1, "aaa"},
        {2, "bbb"}
    };
    vector<Task> ascending1 = {
        {1, "aaa"},
        {1, "jinzongquan"},
        {2, "bbb"}
    };
    vector<Task> descending1 = {
        {2, "bbb"},
        {1, "jinzongquan"},
        {1, "aaa"}
    };

    if (!CheckResult("示例一：sort 升序", SortAscending(tasks1), ascending1))
        failedCount++;
    if (!CheckResult("示例一：小根堆出队", PopFromMinHeap(tasks1), ascending1))
        failedCount++;
    if (!CheckResult("示例一：sort 降序", SortDescending(tasks1), descending1))
        failedCount++;
    if (!CheckResult("示例一：大根堆出队", PopFromMaxHeap(tasks1), descending1))
        failedCount++;

    vector<Task> tasks2 = {
        {3, "z"},
        {2, "b"},
        {2, "a"}
    };
    vector<Task> ascending2 = {
        {2, "a"},
        {2, "b"},
        {3, "z"}
    };
    vector<Task> descending2 = {
        {3, "z"},
        {2, "b"},
        {2, "a"}
    };

    if (!CheckResult("示例二：sort 升序", SortAscending(tasks2), ascending2))
        failedCount++;
    if (!CheckResult("示例二：小根堆出队", PopFromMinHeap(tasks2), ascending2))
        failedCount++;
    if (!CheckResult("示例二：sort 降序", SortDescending(tasks2), descending2))
        failedCount++;
    if (!CheckResult("示例二：大根堆出队", PopFromMaxHeap(tasks2), descending2))
        failedCount++;

    cout << "失败用例数：" << failedCount << '\n';
    return failedCount;
}

/*
什么时候使用 sort：
1. 所有数据已经准备好，需要得到完整有序结果时使用。
2. 例如：输出完整排行榜、按照两个字段整理全部记录。
3. 排序时间复杂度为 O(n log n)，排序后可以直接遍历或随机访问。

什么时候使用 priority_queue：
1. 只关心当前最大值或最小值，或者数据会不断加入时使用。
2. 例如：任务调度、反复取最高优先级任务、维护 Top-K。
3. top() 是 O(1)，push() 和 pop() 是 O(log n)，但不能直接遍历全部元素。

记忆：
1. sort 默认升序；sort + greater 是降序。
2. priority_queue 默认大根堆；priority_queue + greater 是小根堆。
3. 如果所有数据已知并且最终要全部输出，优先考虑 sort；
   如果要动态加入数据并反复取得当前最优元素，优先考虑 priority_queue。
*/
