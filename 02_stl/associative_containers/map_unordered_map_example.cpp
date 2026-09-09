// ============================================================
// std::map 与 std::unordered_map 入门示例
//
// map 可以理解为一张“键 -> 值”的对应表：
//   userid -> 用户名
//   userid -> 该用户的全部运动记录
//   time   -> 该时刻发生的全部事件
//
// map 的两个重要特点：
//   1. key 不能重复；
//   2. 遍历 map 时，元素会按照 key 从小到大排列。
//
// unordered_map 与 map 一样，也是“唯一 key -> value”的对应表，
// 但是 unordered_map 不会按照 key 排序。
// ============================================================

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// 示例一：map 的增、改、查、删和遍历。
void basicExample() {
    cout << "========== 示例一：map 的基本操作 ==========\n";

    // map<key的类型, value的类型>
    // 这里表示：用户ID -> 用户名。
    map<int, string> user_names;

    // 1. 增加元素。
    // 写法一：使用 []。
    user_names[2] = "Li Si";
    user_names[1] = "Zhang San";

    // 写法二：使用 insert。
    user_names.insert({3, "Wang Wu"});

    // 虽然插入顺序是 2、1、3，但是遍历结果会按照 key 输出 1、2、3。
    cout << "插入后的内容：\n";
    for (const auto& item : user_names) {
        // map 中的一个 item 是 pair：
        // item.first  是 key，item.second 是 value。
        cout << "userid = " << item.first
             << ", name = " << item.second << '\n';
    }

    // 2. 修改元素。
    // key=2 已经存在，所以这句修改它的 value。
    user_names[2] = "New Li Si";
    cout << "\n修改后，userid=2 的名字：" << user_names[2] << '\n';

    // 3. 查找元素。
    // find(key) 找到时返回对应位置，找不到时返回 end()。
    int target_uid = 3;
    auto position = user_names.find(target_uid);
    if (position != user_names.end()) {
        cout << "找到了 userid=" << target_uid
             << "，名字是 " << position->second << '\n';
    } else {
        cout << "没有找到 userid=" << target_uid << '\n';
    }

    // 【容易踩坑】不要随便使用 [] 判断一个 key 是否存在。
    // 当 key=100 不存在时，下面这句会自动创建：
    //   100 -> 空字符串
    cout << "\n访问 user_names[100] 之前，元素数量："
         << user_names.size() << '\n';
    cout << "user_names[100] = \"" << user_names[100] << "\"\n";
    cout << "访问 user_names[100] 之后，元素数量："
         << user_names.size() << '\n';

    // 如果只想查找而不想创建，应该使用 find。
    int another_uid = 200;
    if (user_names.find(another_uid) == user_names.end()) {
        cout << "userid=200 不存在，而且 find 不会创建它。\n";
    }

    // 4. 删除元素。
    // erase(key) 删除指定 key，并返回成功删除的元素数量。
    int removed_count = static_cast<int>(user_names.erase(1));
    cout << "\n删除 userid=1 的数量：" << removed_count << '\n';
    cout << "删除后还剩 " << user_names.size() << " 个元素。\n\n";
}

// 示例二：对应健康运动题目的 Step 1——按 userid 分组。
void groupRecordsByUser() {
    cout << "========== 示例二：按 userid 分组 ==========\n";

    // 一条原始记录：(userid, start_time, end_time, speed)
    vector<tuple<int, int, int, int>> records = {
        {2, 10, 130, 6},
        {1, 0, 100, 5},
        {1, 50, 150, 8}
    };

    // key   是 userid。
    // value 是该用户的全部 (start_time, end_time, speed) 记录。
    map<int, vector<tuple<int, int, int>>> user_records;

    for (const auto& record : records) {
        int uid = get<0>(record);
        int start_time = get<1>(record);
        int end_time = get<2>(record);
        int speed = get<3>(record);

        // 如果 uid 不存在，user_records[uid] 会先自动创建一个空 vector；
        // 然后 emplace_back 直接在 vector 内部构造 tuple。
        // 相比 push_back({start_time, end_time, speed})，这里不需要先写出
        // 一个临时 tuple，参数含义也更加直观。
        user_records[uid].emplace_back(start_time, end_time, speed);
    }

    // map 会按照 uid 从小到大遍历，所以先输出用户1，再输出用户2。
    for (const auto& user : user_records) {
        int uid = user.first;
        const vector<tuple<int, int, int>>& intervals = user.second;

        cout << "用户 " << uid << " 有 " << intervals.size() << " 条记录：\n";

        for (const auto& interval : intervals) {
            cout << "  [" << get<0>(interval)
                 << ", " << get<1>(interval)
                 << ")，速度 " << get<2>(interval) << '\n';
        }
    }

    cout << '\n';
}

// 示例三：对应健康运动题目的 Step 2——按时间保存事件。
void groupEventsByTime() {
    cout << "========== 示例三：按时间保存事件 ==========\n";

    // key   是时间。
    // value 是这个时间发生的全部 (事件类型, 速度)。
    // 事件类型  1：一条运动记录开始；
    // 事件类型 -1：一条运动记录结束。
    map<int, vector<pair<int, int>>> events;

    int start_time = 0;
    int end_time = 100;
    int speed = 5;

    events[start_time].push_back({1, speed});
    events[end_time].push_back({-1, speed});

    // 同一时刻可以有多个事件，所以 value 使用 vector。
    // 例如时间100：速度5的记录结束，同时速度8的记录开始。
    events[100].push_back({1, 8});
    events[150].push_back({-1, 8});

    for (const auto& time_and_events : events) {
        int time = time_and_events.first;
        const vector<pair<int, int>>& event_list = time_and_events.second;

        cout << "时间 " << time << "：\n";
        for (const auto& event : event_list) {
            int event_type = event.first;
            int event_speed = event.second;

            if (event_type == 1) {
                cout << "  速度 " << event_speed << " 开始生效\n";
            } else {
                cout << "  速度 " << event_speed << " 停止生效\n";
            }
        }
    }
}

// 示例四：对比 map 和 unordered_map。
void compareMapAndUnorderedMap() {
    cout << "\n========== 示例四：map 与 unordered_map 对比 ==========\n";

    map<int, string> ordered_users;
    unordered_map<int, string> unordered_users;

    // 故意不按大小顺序插入相同的数据。
    ordered_users[20] = "User 20";
    ordered_users[3] = "User 3";
    ordered_users[11] = "User 11";

    unordered_users[20] = "User 20";
    unordered_users[3] = "User 3";
    unordered_users[11] = "User 11";

    // map 内部会按照 key 排序，所以输出顺序一定是 3、11、20。
    cout << "map 的遍历结果（一定按 key 从小到大）：\n";
    for (const auto& item : ordered_users) {
        cout << "  " << item.first << " -> " << item.second << '\n';
    }

    // unordered_map 使用哈希表保存数据。
    // 它的遍历顺序没有保证，不应该依赖下面的实际输出顺序。
    cout << "unordered_map 的遍历结果（顺序不确定）：\n";
    for (const auto& item : unordered_users) {
        cout << "  " << item.first << " -> " << item.second << '\n';
    }

    // 两者最常用的增、改、查、删写法基本相同。
    unordered_users[5] = "User 5";               // 增加或修改
    auto position = unordered_users.find(11);    // 查找
    if (position != unordered_users.end()) {
        cout << "unordered_map 找到 key=11："
             << position->second << '\n';
    }
    unordered_users.erase(20);                   // 删除

    // map 因为 key 有序，所以能直接完成“找第一个不小于目标的 key”。
    auto lower_position = ordered_users.lower_bound(10);
    if (lower_position != ordered_users.end()) {
        cout << "map 中第一个不小于10的 key是："
             << lower_position->first << '\n';
    }

    // unordered_map 没有顺序，因此没有 lower_bound 和 upper_bound。
}

int main() {
    basicExample();
    groupRecordsByUser();
    groupEventsByTime();
    compareMapAndUnorderedMap();
    return 0;
}
