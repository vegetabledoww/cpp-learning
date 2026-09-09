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

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

using namespace std;

class TimerSystem
{
private:
    // TODO：设计并添加需要维护的成员变量

public:
    map<int,int>per_times;//定时器ID-->周期
    int now_time = 0;
    unordered_map<int,int>table;//已启动的定时器ID-->上一次计时位置
    TimerSystem(const vector<int> &timers)
    {
        // TODO：初始化定时器系统
        for (size_t i = 0; i < timers.size(); i++)
        {
            per_times[i] = timers[i];
        }
        
    }

    bool TimerStart(int timerId)
    {
        // TODO：启动或重新启动指定定时器
        if(timerId >= 0 && timerId < static_cast<int>(per_times.size()))
        {
            table[timerId] = now_time;
            return true;
        }
        return false;
    }

    bool TimerStop(int timerId)
    {
        // TODO：停止指定定时器
        if(timerId >= 0 && timerId < static_cast<int>(per_times.size()))
        {
            if(table.find(timerId) != table.end())//证明查到了，确有这个定时器
            {
                table.erase(timerId);//将其在table中删除
                return true;
            }
        }
        return false;
    }

    vector<pair<int, int>> RunTimerSystem(int nowTime)
    {
        // TODO：推进系统时间并返回全部超时事件
        vector<pair<int,int>>answer;
        for(auto &ele : table)
        {
            int timerId = ele.first;
            int &time = ele.second;//带上引用，修改time的话，ele.second也会跟这变
            int period = per_times[timerId];
            while (time + period <= nowTime)
            {
                time += period;
                answer.emplace_back(time,timerId);
            }
        }
        sort(answer.begin(),answer.end());
        now_time = nowTime;//推进系统时间
        return answer;
    }
};

int main()
{
    // 测试示例一：两个定时器同时运行
    TimerSystem timerSystem1({3, 5});
    timerSystem1.TimerStart(0);
    timerSystem1.TimerStart(1);

    vector<pair<int, int>> events1 = timerSystem1.RunTimerSystem(10);
    cout << "example 1\n";
    cout << "expected=(3,0) (5,1) (6,0) (9,0) (10,1)\n";
    cout << "actual=";
    for (const auto &event : events1)
    {
        cout << '(' << event.first << ',' << event.second << ") ";
    }
    cout << "\n\n";

    // 测试示例二：推进时间后停止一个定时器，再启动另一个定时器
    TimerSystem timerSystem2({2, 4});
    timerSystem2.TimerStart(0);

    vector<pair<int, int>> firstEvents = timerSystem2.RunTimerSystem(3);
    cout << "example 2 - first run\n";
    cout << "expected=(2,0)\n";
    cout << "actual=";
    for (const auto &event : firstEvents)
    {
        cout << '(' << event.first << ',' << event.second << ") ";
    }
    cout << '\n';

    timerSystem2.TimerStop(0);
    timerSystem2.TimerStart(1);

    vector<pair<int, int>> secondEvents = timerSystem2.RunTimerSystem(8);
    cout << "example 2 - second run\n";
    cout << "expected=(7,1)\n";
    cout << "actual=";
    for (const auto &event : secondEvents)
    {
        cout << '(' << event.first << ',' << event.second << ") ";
    }
    cout << '\n';

    return 0;
}
