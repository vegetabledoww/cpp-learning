/*
题目：周期定时器系统

给定多个定时器的周期，实现定时器的启动、停止和系统时间推进功能。
启动定时器后，它第一次超时的时间为“当前系统时间 + 定时器周期”，
以后每经过一个周期再次超时。

RunTimerSystem(nowTime) 返回当前时间推进到 nowTime 期间产生的全部事件，
事件格式为 {超时时间, 定时器ID}，先按时间升序排列，同一时刻按 ID 升序排列。

接口说明：
1. TimerSystem(timers)
   创建定时器系统。timers[i] 表示 i 号定时器的周期。
   系统初始时间为 0，所有定时器初始时都未启动。

2. TimerStart(timerId)
   启动指定定时器，第一次超时时间为“当前系统时间 + 对应周期”。
   如果该定时器已经启动，再次调用会从当前系统时间重新计时。
   timerId 合法时返回 true，否则返回 false。

3. TimerStop(timerId)
   停止指定定时器。停止后不再产生新的超时事件，已经返回的事件不受影响。
   timerId 合法时返回 true，否则返回 false。

4. RunTimerSystem(nowTime)
   将系统时间推进到 nowTime，返回推进过程中所有已启动定时器产生的超时事件。
   返回值中的 pair<int, int> 表示 {超时时间, 定时器ID}。
   调用结束后，系统当前时间更新为 nowTime。

题目保证所有周期大于 0，并且 nowTime 按非递减顺序给出。

示例一：
输入：
TimerSystem timerSystem({3, 5});
timerSystem.TimerStart(0);
timerSystem.TimerStart(1);
timerSystem.RunTimerSystem(10);
输出：{{3, 0}, {5, 1}, {6, 0}, {9, 0}, {10, 1}}
解释：0 号定时器每 3 个时间单位超时，1 号定时器每 5 个时间单位超时。

示例二：
输入：
TimerSystem timerSystem({2, 4});
timerSystem.TimerStart(0);
timerSystem.RunTimerSystem(3);
timerSystem.TimerStop(0);
timerSystem.TimerStart(1);
timerSystem.RunTimerSystem(8);
输出：
第一次运行返回 {{2, 0}}
第二次运行返回 {{7, 1}}
解释：第一次运行后当前时间为 3。此时停止 0 号定时器，并启动 1 号定时器，
     所以 1 号定时器第一次超时的时间是 3 + 4 = 7。
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class TimerSystem
{
private:
    int currentTime;//当前系统时间
    vector<int>periods;//每个定时器的周期
    vector<bool>active;//每个定时器是否启动
    vector<int>nextTimeout;//每个定时器的下一次超时时间

public:
    TimerSystem(const vector<int> &timers)
        : currentTime(0), periods(timers)
    {
        int n = static_cast<int>(periods.size());
        active.resize(n, false);
        nextTimeout.resize(n, 0);
    }

    bool TimerStart(int timerId)
    {
        if (timerId < 0 || timerId >= static_cast<int>(periods.size()))
        {
            return false;
        }

        active[timerId] = true;//定时器启动
        nextTimeout[timerId] = currentTime + periods[timerId];//下一次的超时时间
        return true;
    }

    bool TimerStop(int timerId)
    {
        if (timerId < 0 || timerId >= static_cast<int>(periods.size()))
        {
            return false;
        }
        active[timerId] = false;//关闭定时器
        return true;
    }

    vector<pair<int,int>> RunTimerSystem(int nowTime)
    {
        vector<pair<int,int>>events;
        for (int timerId = 0; timerId < static_cast<int>(periods.size()); timerId++)
        {
            if (!active[timerId])//定时器关闭了
            {
                continue;
            }

            while (nextTimeout[timerId] <= nowTime)
            {
                events.push_back({nextTimeout[timerId], timerId});
                nextTimeout[timerId] += periods[timerId];
            }
        }

        //pair默认先比较first，再比较second，正好符合题目的排序规则
        sort(events.begin(), events.end());
        currentTime = nowTime;//推进系统时间
        return events;
    }
};

int main()
{
    TimerSystem timerSystem({3, 5});
    timerSystem.TimerStart(0);
    timerSystem.TimerStart(1);

    vector<pair<int,int>>events = timerSystem.RunTimerSystem(10);
    cout << "expected=(3,0) (5,1) (6,0) (9,0) (10,1)\n";
    cout << "actual=";
    for (const auto &event : events)
    {
        cout << '(' << event.first << ',' << event.second << ") ";
    }
    cout << '\n';
    return 0;
}
