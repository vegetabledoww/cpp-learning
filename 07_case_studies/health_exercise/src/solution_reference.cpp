// ============================================================
// 题目描述：健康运动步数统计
// ============================================================
//
// 【背景】
//   给定一组用户的运动记录，每条记录包含 userid、运动开始时间、运动结束时间、
//   该时间段内的平均速度。要求统计在连续 120 分钟内累计里程最大的用户。
//
// 【输入】
//   vector<tuple<int, int, int, int>> records，其中每个 tuple 四个 int 依次为：
//     - userid        : 用户ID
//     - start_time    : 运动开始时间（分钟）
//     - end_time      : 运动结束时间（分钟）
//     - avg_speed     : 该时间段内的平均速度
//
// 【处理规则】
//   1. 同一 userid 可能出现多条记录，且运动时间范围可能重叠。
//      当出现范围重叠时，取较大的平均速度作为该重叠段的真实速度。
//   2. 对每个用户合并后的运动区间，寻找一个长度为 120 分钟的连续窗口，
//      使得该窗口内的累计里程（里程 = 速度 × 时间）最大。
//
// 【比较规则】（按优先级从高到低）
//   1. 120 分钟内累计里程大的优先；
//   2. 若里程相同，userid 小的优先；
//   3. 若 userid 也相同，开始时间早的优先。
//
// 【返回值】
//   tuple<int, int, int>，三个参数依次为：
//     - 总里程（总步数）
//     - userid
//     - start_time
//   若无任何满足条件的记录，返回 (0, 0, 0)。
//
// 【用例1】
//   输入: records = {
//     {1, 0, 100, 5},     // 用户1，0-100分钟，速度5
//     {1, 50, 150, 8},     // 用户1，50-150分钟，速度8（与上一条重叠）
//     {2, 10, 130, 6}     // 用户2，10-130分钟，速度6
//   }
//   处理:
//     - 用户1：合并后区间为 0-150，其中 0-50 段速度5，50-150 段速度8
//     - 用户2：区间 10-130，速度6
//   分析:
//     - 用户1 在 [30, 150] 窗口内：20×5 + 100×8 = 900
//     - 用户2 在 [10, 130] 窗口内：里程为 120×6=720
//   输出: (900, 1, 30)
//
// 【用例2】
//   输入: records = {
//     {3, 0, 150, 4},     // 用户3，0-150分钟，速度4
//     {1, 20, 140, 4}     // 用户1，20-140分钟，速度4（与用户3里程相同，但userid更小）
//   }
//   处理:
//     - 用户3：区间 0-150，速度4，120分钟里程 = 120×4=480
//     - 用户1：区间 20-140，速度4，120分钟里程 = 120×4=480
//   分析:
//     - 两者里程相同（480），按规则2 userid 小的优先 → 用户1
//   输出: (480, 1, 20)
// ============================================================
#include <vector>
#include <tuple>
#include <map>
#include <iostream>
#include <algorithm>
#include <climits>
#include <set>
using namespace std;

class Solution {
public:
    tuple<int, int, int> MaxAmountOfExercise(const vector<tuple<int, int, int, int>>& records) {
        // Step 1: 按 userid 分组
        map<int, vector<tuple<int, int, int>>> user_raw; // uid -> {(start, end, speed)}
        for (const auto& r : records) {
            user_raw[get<0>(r)].emplace_back(get<1>(r), get<2>(r), get<3>(r));
        }

        int max_distance = -1;
        int best_uid = INT_MAX;
        int best_start_time = INT_MAX;

        // Step 2: 逐个用户处理
        for (auto& [uid, intervals] : user_raw) {
            // 2.1 收集所有时间端点
            set<int> time_points;
            for (const auto& iv : intervals) {
                time_points.insert(get<0>(iv)); // start
                time_points.insert(get<1>(iv)); // end
            }
            if (time_points.size() < 2) continue;

            // 2.2 相邻端点构成小段，对每个小段求最大速度
            vector<int> times(time_points.begin(), time_points.end());
            vector<tuple<int, int, int>> segments; // (start, end, speed)
            for (int i = 0; i + 1 < (int)times.size(); ++i) {
                int start = times[i];
                int end = times[i + 1];
                int best_speed = 0;

                // 找出所有覆盖 [start, end) 的原始记录，保留最大速度
                for (const auto& iv : intervals) {
                    if (get<0>(iv) <= start && get<1>(iv) >= end) {
                        best_speed = max(best_speed, get<2>(iv));
                    }
                }
                segments.emplace_back(start, end, best_speed);
            }

            // Step 3: 在原有分段结果的基础上，构造每分钟速度数组
            int min_time = times.front();
            int max_time = times.back();
            int total_minutes = max_time - min_time;
            if (total_minutes < 120) continue;

            // 【修改点1】speed[i] 表示 [min_time+i, min_time+i+1) 的真实速度。
            vector<int> speed(total_minutes, 0);

            // 【修改点2】segments 已经处理好了重叠关系，这里只负责按分钟展开。
            for (const auto& segment : segments) {
                int start = get<0>(segment);
                int end = get<1>(segment);
                int segment_speed = get<2>(segment);
                for (int time = start; time < end; ++time) {
                    speed[time - min_time] = segment_speed;
                }
            }

            // 3.1 先计算第一个 120 分钟窗口
            int window_distance = 0;
            for (int i = 0; i < 120; ++i) {
                window_distance += speed[i];
            }

            // 3.2 普通滑动窗口：每次向右移动一分钟
            for (int start = 0; start + 120 <= total_minutes; ++start) {
                // 【修改点3】窗口右移一分钟时，只需要移出左侧一分钟，
                // 再加入右侧新进入的一分钟，不需要重新累加 120 次。
                if (start > 0) {
                    window_distance -= speed[start - 1];
                    window_distance += speed[start + 119];
                }

                int actual_start_time = min_time + start;// 计算实际的开始时间

                // 更新答案（里程 > uid > start_time 三级比较）
                if (window_distance > max_distance ||
                    (window_distance == max_distance && uid < best_uid) ||
                    (window_distance == max_distance && uid == best_uid &&
                     actual_start_time < best_start_time)) {
                    max_distance = window_distance;
                    best_uid = uid;
                    best_start_time = actual_start_time;
                }
            }
        }

        if (max_distance == -1)
            return make_tuple(0, 0, 0); // 无有效记录
        return make_tuple(max_distance, best_uid, best_start_time);
    }
};

int main() {
    Solution solution;

    // 测试案例1：基本测试
    cout << "=== 测试案例1 ===" << endl;
    vector<tuple<int, int, int, int>> records1 = {
            {1, 0, 100, 5},    // 用户1，0-100分钟，速度5
            {1, 50, 150, 8},   // 用户1，50-150分钟，速度8 (与上面重叠)
            {2, 10, 130, 6}    // 用户2，10-130分钟，速度6
    };

    auto result1 = solution.MaxAmountOfExercise(records1);
    cout << "结果: 总步数=" << get<0>(result1)
         << ", 用户ID=" << get<1>(result1)
         << ", 开始时间=" << get<2>(result1) << endl;

    // 测试案例2：多个用户竞争
    cout << "\n=== 测试案例2 ===" << endl;
    vector<tuple<int, int, int, int>> records2 = {
            {1, 0, 200, 3},    // 用户1，0-200分钟，速度3
            {2, 50, 170, 4},   // 用户2，50-170分钟，速度4
            {3, 100, 220, 5}   // 用户3，100-220分钟，速度5
    };

    auto result2 = solution.MaxAmountOfExercise(records2);
    cout << "结果: 总步数=" << get<0>(result2)
         << ", 用户ID=" << get<1>(result2)
         << ", 开始时间=" << get<2>(result2) << endl;

    // 测试案例3：相同距离，比较用户ID
    cout << "\n=== 测试案例3 ===" << endl;
    vector<tuple<int, int, int, int>> records3 = {
            {3, 0, 150, 4},    // 用户3，0-150分钟，速度4
            {1, 20, 140, 4}    // 用户1，20-140分钟，速度4 (相同距离，但用户ID更小)
    };

    auto result3 = solution.MaxAmountOfExercise(records3);
    cout << "结果: 总步数=" << get<0>(result3)
         << ", 用户ID=" << get<1>(result3)
         << ", 开始时间=" << get<2>(result3) << endl;

    return 0;
}
