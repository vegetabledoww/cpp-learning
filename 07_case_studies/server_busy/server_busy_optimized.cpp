/*【软件认证】服务器空闲时段（事件扫描优化版）

有 serverNum 台服务器，编号为 1 到 serverNum。
tasks[i] = [startTime, endTime, serverId] 表示一项任务在区间
[startTime, endTime) 内运行。同一台服务器可以同时运行多个任务。

返回恰好只有一台服务器空闲的全部时段。连续时段需要合并，
结果按照开始时间升序排列。

样例1：
serverNum = 3
tasks = [[1,2,1], [1,3,1], [5,6,1], [2,3,2], [5,6,3]]
结果：[[2,3], [5,6]]

样例2：
serverNum = 4
tasks = [[1,2,1], [1,2,2], [1,2,4], [2,3,1], [2,3,2], [2,3,3]]
结果：[[1,3]]
*/

#include <algorithm>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    using Interval = pair<int, int>;
    using Task = tuple<int, int, int>;

    vector<Interval> GetTimeIntervals(int serverNum, const vector<Task>& tasks)
    {
        struct Event {
            int time;
            int serverId;
            int delta;
        };

        vector<Event> events;
        events.reserve(tasks.size() * 2);

        for (const auto& [startTime, endTime, serverId] : tasks) {
            events.push_back({startTime, serverId, 1});
            events.push_back({endTime, serverId, -1});
        }

        if (events.empty()) {
            return {};
        }

        sort(events.begin(), events.end(), [](const Event& left, const Event& right) {
            if (left.time != right.time) {
                return left.time < right.time;
            }
            return left.serverId < right.serverId;
        });

        // activeTaskCount[id] 表示服务器 id 当前正在运行的任务数。
        vector<int> activeTaskCount(static_cast<size_t>(serverNum) + 1, 0);
        int busyServerCount = 0;
        vector<Interval> result;

        size_t index = 0;
        int previousTime = events.front().time;

        while (index < events.size()) {
            int currentTime = events[index].time;

            // 处理 currentTime 的事件前，busyServerCount 描述的是
            // [previousTime, currentTime) 内的忙碌服务器数量。
            if (previousTime < currentTime && busyServerCount == serverNum - 1) {
                appendOrMerge(result, previousTime, currentTime);
            }

            // 同一时间、同一服务器的开始/结束事件合并后再更新状态。
            while (index < events.size() && events[index].time == currentTime) {
                int serverId = events[index].serverId;
                size_t serverIndex = static_cast<size_t>(serverId);
                int taskCountChange = 0;

                while (index < events.size()
                       && events[index].time == currentTime
                       && events[index].serverId == serverId) {
                    taskCountChange += events[index].delta;
                    ++index;
                }

                bool wasBusy = activeTaskCount[serverIndex] > 0;
                activeTaskCount[serverIndex] += taskCountChange;
                bool isBusy = activeTaskCount[serverIndex] > 0;

                if (!wasBusy && isBusy) {
                    ++busyServerCount;
                } else if (wasBusy && !isBusy) {
                    --busyServerCount;
                }
            }

            previousTime = currentTime;
        }

        return result;
    }

private:
    static void appendOrMerge(vector<Interval>& result, int startTime, int endTime)
    {
        if (!result.empty() && result.back().second == startTime) {
            result.back().second = endTime;
        } else {
            result.emplace_back(startTime, endTime);
        }
    }
};

static void PrintResult(const vector<pair<int, int>>& intervals)
{
    cout << '[';
    for (size_t i = 0; i < intervals.size(); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << '[' << intervals[i].first << ", " << intervals[i].second << ']';
    }
    cout << ']';
}

int main()
{
    Solution solution;

    vector<Solution::Task> tasks1 = {
        {1, 2, 1}, {1, 3, 1}, {5, 6, 1}, {2, 3, 2}, {5, 6, 3}
    };
    vector<Solution::Interval> expected1 = {{2, 3}, {5, 6}};
    auto result1 = solution.GetTimeIntervals(3, tasks1);

    vector<Solution::Task> tasks2 = {
        {1, 2, 1}, {1, 2, 2}, {1, 2, 4},
        {2, 3, 1}, {2, 3, 2}, {2, 3, 3}
    };
    vector<Solution::Interval> expected2 = {{1, 3}};
    auto result2 = solution.GetTimeIntervals(4, tasks2);

    cout << "example1: " << (result1 == expected1 ? "PASS " : "FAIL ");
    PrintResult(result1);
    cout << '\n';

    cout << "example2: " << (result2 == expected2 ? "PASS " : "FAIL ");
    PrintResult(result2);
    cout << '\n';

    return result1 == expected1 && result2 == expected2 ? 0 : 1;
}
