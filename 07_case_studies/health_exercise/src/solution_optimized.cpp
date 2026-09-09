// ============================================================
// 健康运动步数统计：改进实现
//
// 整体仍然分为三步：
//   Step 1：按 userid 分组；
//   Step 2：用时间事件构造每分钟的真实速度；
//   Step 3：用前缀和枚举所有 120 分钟窗口。
//
// 相比 solution_readable.cpp，主要改进位置都用“【改进】”标出。
// 全程没有使用仿函数、Lambda 或自定义比较器。
// ============================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

const int WINDOW_SIZE = 120;

// 一条分组后的记录：(start_time, end_time, speed)
using Interval = tuple<int, int, int>;

// ------------------------------------------------------------
// 【改进 1】把答案比较单独写成普通辅助函数。
// 这样主流程只负责“算答案”，不用反复阅读一长串并列条件。
// 这只是普通函数，不是仿函数。
// ------------------------------------------------------------
bool shouldUpdateAnswer(int distance, int uid, int start_time,
                        int best_distance, int best_uid, int best_start_time) {
    if (distance != best_distance) {
        return distance > best_distance;
    }
    if (uid != best_uid) {
        return uid < best_uid;
    }
    return start_time < best_start_time;
}

// ------------------------------------------------------------
// Step 2：构造一个用户的每分钟真实速度。
//
// speed[i] 表示实际时间区间：
//   [min_time + i, min_time + i + 1)
//
// 【改进 2】不再对“每个相邻端点”重新遍历所有原始记录。
// 每条记录只产生两个事件：
//   start 时刻：该速度开始生效；
//   end   时刻：该速度停止生效。
//
// active_speeds 保存当前时间仍然生效的全部速度。
// multiset 会自动排序，所以 *active_speeds.rbegin() 就是最大速度。
// ------------------------------------------------------------
vector<int> buildMinuteSpeed(const vector<Interval>& intervals, int& min_time) {
    // events[time] 中：
    //   first  =  1，表示速度开始生效；
    //   first  = -1，表示速度停止生效；
    //   second = speed。
    map<int, vector<pair<int, int>>> events;// time -> list of (event_type, speed)
    set<int> time_points;// 收集所有时间端点

    for (const auto& interval : intervals) {
        int start_time = get<0>(interval);
        int end_time = get<1>(interval);
        int speed = get<2>(interval);

        events[start_time].push_back({1, speed});
        events[end_time].push_back({-1, speed});
        time_points.insert(start_time);
        time_points.insert(end_time);
    }

    vector<int> times(time_points.begin(), time_points.end());
    min_time = times.front();
    int max_time = times.back();

    // 初始值 0 表示该分钟没有运动记录。
    vector<int> minute_speed(max_time - min_time, 0);
    multiset<int> active_speeds;

    for (int i = 0; i + 1 < static_cast<int>(times.size()); ++i) {
        int current_time = times[i];
        int next_time = times[i + 1];

        // 区间采用左闭右开形式 [start, end)。
        // 因此到达 current_time 时，要先删除在这里结束的速度。
        for (const auto& event : events[current_time]) {
            int event_type = event.first;
            int speed = event.second;

            if (event_type == -1) {
                // multiset::erase(value) 会删除所有相同值，不能这样用。
                // find + erase(iterator) 只删除这一条结束的记录。
                auto position = active_speeds.find(speed);
                if (position != active_speeds.end()) {
                    active_speeds.erase(position);
                }
            }
        }

        // 再加入从 current_time 开始生效的速度。
        for (const auto& event : events[current_time]) {
            int event_type = event.first;
            int speed = event.second;

            if (event_type == 1) {
                active_speeds.insert(speed);
            }
        }

        int real_speed = 0;
        if (!active_speeds.empty()) {
            real_speed = *active_speeds.rbegin();
        }

        // 相邻事件之间，生效的记录不会改变，所以真实速度也不会改变。
        for (int time = current_time; time < next_time; ++time) {
            minute_speed[time - min_time] = real_speed;
        }
    }

    return minute_speed;
}

// ------------------------------------------------------------
// Step 3：寻找一个用户的最佳 120 分钟窗口。
// 返回值：(最大里程, 实际开始时间)。
// 若不存在完整的 120 分钟范围，则返回 (-1, INT_MAX)。
//
// 【改进 3】使用前缀和简化窗口计算：
//   [left, right) 的里程 = prefix[right] - prefix[left]
// 每个窗口只需要一次减法，不再手动处理移出和移入的元素。
// ------------------------------------------------------------
pair<int, int> findBestWindow(const vector<int>& minute_speed, int min_time) {
    int total_minutes = static_cast<int>(minute_speed.size());
    if (total_minutes < WINDOW_SIZE) {
        return {-1, INT_MAX};
    }

    vector<int> prefix(total_minutes + 1, 0);
    for (int i = 0; i < total_minutes; ++i) {
        prefix[i + 1] = prefix[i] + minute_speed[i];
    }

    int best_distance = -1;
    int best_start_time = INT_MAX;

    for (int left = 0; left + WINDOW_SIZE <= total_minutes; ++left) {
        int right = left + WINDOW_SIZE;
        int distance = prefix[right] - prefix[left];
        int actual_start_time = min_time + left;

        // 同一用户里程相同时，保留更早的窗口。
        if (distance > best_distance ||
            (distance == best_distance && actual_start_time < best_start_time)) {
            best_distance = distance;
            best_start_time = actual_start_time;
        }
    }

    return {best_distance, best_start_time};
}

class Solution {
public:
    tuple<int, int, int> MaxAmountOfExercise(
        const vector<tuple<int, int, int, int>>& records) {

        // Step 1：按 userid 分组。
        map<int, vector<Interval>> user_records;

        for (const auto& record : records) {
            int uid = get<0>(record);
            int start_time = get<1>(record);
            int end_time = get<2>(record);
            int speed = get<3>(record);

            // 【改进 4】空区间没有任何有效分钟，直接忽略。
            if (start_time >= end_time) {
                continue;
            }

            user_records[uid].push_back({start_time, end_time, speed});
        }

        int best_distance = -1;
        int best_uid = INT_MAX;
        int best_start_time = INT_MAX;

        for (const auto& user_data : user_records) {
            int uid = user_data.first;
            const vector<Interval>& intervals = user_data.second;

            int min_time = 0;
            vector<int> minute_speed = buildMinuteSpeed(intervals, min_time);
            pair<int, int> user_answer = findBestWindow(minute_speed, min_time);

            int distance = user_answer.first;
            int start_time = user_answer.second;

            if (distance == -1) {
                continue;
            }

            if (shouldUpdateAnswer(distance, uid, start_time,
                                   best_distance, best_uid, best_start_time)) {
                best_distance = distance;
                best_uid = uid;
                best_start_time = start_time;
            }
        }

        if (best_distance == -1) {
            return make_tuple(0, 0, 0);
        }

        return make_tuple(best_distance, best_uid, best_start_time);
    }
};

// 使用下面的命令可以运行文件内的简单测试：
// g++ -std=c++17 -DLOCAL_TEST solution_optimized.cpp -o health_exercise.exe
#ifdef LOCAL_TEST
void printResult(const tuple<int, int, int>& result) {
    cout << '(' << get<0>(result) << ", "
         << get<1>(result) << ", "
         << get<2>(result) << ")\n";
}

int main() {
    Solution solution;

    vector<tuple<int, int, int, int>> records1 = {
        {1, 0, 100, 5},
        {1, 50, 150, 8},
        {2, 10, 130, 6}
    };
    printResult(solution.MaxAmountOfExercise(records1)); // (900, 1, 30)

    vector<tuple<int, int, int, int>> records2 = {
        {3, 0, 150, 4},
        {1, 20, 140, 4}
    };
    printResult(solution.MaxAmountOfExercise(records2)); // (480, 1, 20)

    return 0;
}
#endif
