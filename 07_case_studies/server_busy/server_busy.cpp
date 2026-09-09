/*【软件认证】服务器空闲时段

现有serverNum台服务器，编号依次为1 ~ serverNum。tasks表示一组任务，tasks[i] = [startTime, endTime, serverId]，依次表示一个任务的开始时刻、结束时刻、服务器编号。任务按指定的时段在指定的服务器上运行，一台服务器在同一时刻可以并行的运行任意多个任务。当一台服务器没有运行任何任务时，称该服务器在该时段空闲。请你统计恰好有且只有一台服务器空闲的时段，并返回排序后的时段列表（如果没有，则返回空列表 []）。要求：

连续的时段需要合并，如：[1,2]和[2,3]合并为[1,3]。
按照每个时段的开始时刻升序排序。
若无满足要求的时段，输出空列表。
输入
第一个参数是 serverNum，表示服务器个数，2 <= serverNum <= 10000
第二个参数是tasks，1 <= tasks.length <= 10000
> 0 < startTime < endTime < 10^9， 1 <= serverId <= serverNum

输出
一个列表，表示排序后的空闲时段，每个元素的格式为：[startTime, endTime]。

样例1
复制输入：
3
[[1, 2, 1], [1, 3, 1], [5, 6, 1], [2, 3, 2], [5, 6, 3]]
复制输出：
[[2, 3], [5, 6]]
解释：
如下图所示：

1 号服务器总共分配了 3 项任务，2/3 号服务器各分配了 1 项任务，
时段 [1, 2]： 1 号服务器在工作，2/3号服务器空闲，
时段 [2, 3]： 1 号和 2 号服务器在工作，3 号服务器空闲，
时段 [3, 5]： 3 台服务器都空闲，
时段 [5, 6]： 1 号和 3 号服务器在工作，2 号服务器空闲，
故满足要求的时段为 [2, 3] 和 [5, 6]。

样例2
复制输入：
4
[[1, 2, 1], [1, 2, 2], [1, 2, 4], [2, 3, 1], [2, 3, 2], [2, 3, 3]]
复制输出：
[[1, 3]]
解释：
1/2 号服务器各分配了 2 项任务，3/4 号服务器各分配了 1 项任务，
时段 [1, 2]： 1/2/4 号服务器在工作，3 号服务器空闲，
时段 [2, 3]： 1/2/3 号服务器在工作，4 号服务器空闲，
故满足要求的时段为 [1, 2] 和 [2, 3]，合并后为 [1, 3]


*/
#include <vector>
#include <tuple>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

class Solution {
public:
    using pii = pair<int, int>;
    using tiii = tuple<int, int, int>;

    // 可以使用std::get访问tuple中的成员，比如std::get<0>(obj)可访问obj中第一个成员
    vector<pair<int, int>> GetTimeIntervals(int serverNum, const vector<tuple<int, int, int>> &tasks) {
        vector<tiii> tmpTasks = tasks;
        //step1. 二元排序
        sort(tmpTasks.begin(), tmpTasks.end(), [](const tiii &a, const tiii &b) { // 排个序，方便合并
            if (get<0>(a) == get<0>(b)) {
                return get<1>(a) < get<1>(b);
            }
            return get<0>(a) < get<0>(b);
        });
        //step2. 合并区间
        unordered_map<int, vector<pii>> ranges(serverNum); // 记录服务器对应的区间
        for (auto task: tmpTasks) {
            addToRanges(ranges, task);
        }
        //step3. 得到差分数组
        map<int, int> diff; //time->deta,即时间t到来时，忙碌服务器数量要变化多少
        for (int i = 0; i < serverNum; ++i) {
            for (auto p: ranges[i + 1]) {//服务器编号从1开始，所以加一
                diff[p.first] += 1;
                diff[p.second] -= 1;
            }
        }
        //step4. 得出结果
        vector<pii> res;//开始时间 ： 结束时间（存储答案）
        int busy = 0; // 记录忙碌服务器数
        int last = 0; // 上一区间的结尾
        for (auto d: diff) {
            if (busy == serverNum - 1) {//此时空闲数为1，满足题意
                if (res.empty() || res.back().second < last) { //存在空档
                    res.emplace_back(last, d.first);
                } else { // 紧密相连
                    res.back().second = max(res.back().second, d.first);//选择结束时间最大的
                }
            }
            busy += d.second;//d.second即忙碌服务器变化数量
            last = d.first;//本区间处理完毕，将本区间的结束时间作为与下一区间开始时间，以作为判断重叠的依据
        }
        return res;
    }

private:
    // 合并区间
    static void addToRanges(unordered_map<int, vector<pii>> &ranges, tuple<int, int, int>& task) {
        int s = std::get<0>(task);  // 区间起点
        int e = std::get<1>(task);  // 区间终点
        int id = std::get<2>(task); // 服务器id
        if (ranges[id].empty() || ranges[id].back().second < s) { // 与前一个区间没有重叠部分
            ranges[id].emplace_back(s, e);
        } else {    // 有重叠部分
            ranges[id].back().second = max(ranges[id].back().second, e);
        }
    }
};