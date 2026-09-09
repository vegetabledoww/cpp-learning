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
#include <utility>
using namespace std;
using ll = long long;
class Solution {
public:
    tuple<int, int, int> MaxAmountOfExercise(const vector<tuple<int, int, int, int>>& records) {
        //step1: 按用户ID分组，合并重叠区间，记录每个时间段的最大速度
        map<int, vector<tuple<int, int, int>>> user_records;//userid-->start,end,speed
        int max_distance = -1;
        int best_uid = INT_MAX;
        int best_start_time = INT_MAX;
        //1. 用map拿到所有数据
        for(auto &element : records)
        {
            int userid = get<0>(element);
            int start_time = get<1>(element);
            int end_time = get<2>(element);
            int speed = get<3>(element);
            user_records[userid].push_back({start_time, end_time, speed});
        }
        //2. 逐用户处理:合并区间
        //2.1.收集所有时间端点（即加速度不为0的点）
        set<int>time_points;
        for(const auto&[uid,intervals]: user_records)
        {
            int act_distance = 0;
            time_points.clear();
            for(const auto &iv : intervals)
            {
                time_points.insert(get<0>(iv));//start_time
                time_points.insert(get<1>(iv));//end_time
            }
        
            //2.2. 开始合并并保留同一usid的最大速度
            vector<int>times(time_points.begin(),time_points.end());
            vector<tuple<int,int,int>>segments;//存放合并后的区间
            for(size_t i = 0; i + 1 < times.size();i++)
            {
                int s = times[i], e = times[i+1];//先固定一个区间
                int best_speed = 0;
                for(const auto& iv : intervals)
                {
                    if(get<0>(iv) <= s && get<1>(iv) >= e)//覆盖当前区间，选择速度大的
                        best_speed = max(get<2>(iv),best_speed);
                   
                }
                segments.emplace_back(s,e,best_speed);//如果用push_back,要加花括号！
            }
            // Step 3: 直接用滑动窗口来解决
            //3.1 展开逐分钟对应的速度
            int min_time = times.front();
            int max_time = times.back();
            int total_minutes = max_time - min_time;
            if(total_minutes < 120) continue;//如果不存在大于120分钟的区间，则跳过
            vector<int>speed(total_minutes, 0);
            for(const auto& segment : segments)
            {
                int start_time = get<0>(segment);
                int end_time = get<1>(segment);
                int cur_speed = get<2>(segment);
                for(int i = start_time;i < end_time;i++)
                    speed[i - min_time] = cur_speed;
            }
            //3.2. 滑动窗口
            for(int i = 0;i<120;i++)
                act_distance += speed[i]; 
            for(int start = 0;start+120<=total_minutes;start++)
            {
                if(start > 0)
                {
                    act_distance -= speed[start-1];
                    act_distance += speed[start+119];
                }
                int actual_start_time = start + min_time;
                //将结果比较出来
                if( (act_distance > max_distance) ||
                    (act_distance == max_distance &&  uid < best_uid) ||
                    (act_distance == max_distance &&  uid == best_uid && actual_start_time < best_start_time)
                )
                {
                    max_distance = act_distance;
                    best_uid = uid;
                    best_start_time = actual_start_time;
                }
            }
        }
        if(max_distance == -1) return make_tuple(0,0,0);
        return make_tuple(max_distance,best_uid,best_start_time);
    }
};