// ============================================================
// std::pair 基础用法示例
//
// pair 用来把两个相关的值组合成一个对象：
//   first  保存第一个值；
//   second 保存第二个值。
//
// 常见用途：
//   1. 函数一次返回两个结果；
//   2. 表示坐标、区间、事件等二元数据；
//   3. 配合 vector 进行二级排序；
//   4. map 中的每个元素本身就是一个 pair。
// ============================================================

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// ------------------------------------------------------------
// 示例一：创建、读取和修改 pair。
// ------------------------------------------------------------
void basicExample() {
    cout << "========== 示例一：pair 的基本操作 ==========\n";

    // pair<第一个值的类型, 第二个值的类型>
    pair<int, string> user1 = {1, "Zhang San"};

    // 也可以使用 make_pair 创建。
    pair<int, string> user2 = make_pair(2, "Li Si");

    cout << "user1: " << user1.first << ", " << user1.second << '\n';
    cout << "user2: " << user2.first << ", " << user2.second << '\n';

    // pair 中的两个值可以分别修改。
    user1.first = 10;
    user1.second = "New Zhang San";

    cout << "修改后的user1: "
         << user1.first << ", " << user1.second << "\n\n";
}

// ------------------------------------------------------------
// 示例二：使用 pair 让函数返回两个结果。
//
// 返回值：
//   first  = 商；
//   second = 余数。
// ------------------------------------------------------------
pair<int, int> divideWithRemainder(int number, int divisor) {
    int quotient = number / divisor;
    int remainder = number % divisor;

    return {quotient, remainder};
}

void returnTwoValuesExample() {
    cout << "========== 示例二：函数返回两个结果 ==========\n";

    pair<int, int> result = divideWithRemainder(17, 5);

    cout << "17 / 5 的商：" << result.first << '\n';
    cout << "17 / 5 的余数：" << result.second << '\n';

    // C++17 还支持结构化绑定，可以给 first 和 second 起更明确的名字。
    // 这只是另一种接收 pair 的写法，不是必须使用。
    auto [quotient, remainder] = divideWithRemainder(23, 4);
    cout << "23 / 4 的商：" << quotient
         << "，余数：" << remainder << "\n\n";
}

// ------------------------------------------------------------
// 示例三：pair 自带比较规则。
//
// 比较两个 pair 时：
//   1. 先比较 first；
//   2. first 相同，再比较 second。
// ------------------------------------------------------------
void comparisonExample() {
    cout << "========== 示例三：pair 的比较规则 ==========\n";

    pair<int, int> a = {1, 100};
    pair<int, int> b = {2, 10};
    pair<int, int> c = {1, 200};

    cout << boolalpha;
    cout << "(1,100) < (2,10)：" << (a < b) << '\n';
    cout << "(1,100) < (1,200)：" << (a < c) << '\n';
    cout << "(1,100) == (1,200)：" << (a == c) << "\n\n";
}

// ------------------------------------------------------------
// 示例四：vector<pair<...>> 可以直接排序。
//
// 下面用 pair 表示区间：
//   first  = 开始时间；
//   second = 结束时间。
//
// sort 会按照“先 first、后 second”的规则排列。
// ------------------------------------------------------------
void sortingExample() {
    cout << "========== 示例四：pair 的自动排序 ==========\n";

    vector<pair<int, int>> intervals = {
        {20, 80},
        {10, 130},
        {10, 100},
        {0, 50}
    };

    sort(intervals.begin(), intervals.end());

    for (const auto& interval : intervals) {
        cout << '[' << interval.first
             << ", " << interval.second << ")\n";
    }

    cout << '\n';
}

// ------------------------------------------------------------
// 示例五：map 的每个元素本身就是 pair。
//
// map<int, string> 中的一个元素近似于：
//   pair<const int, string>
//
// first  是 map 的 key；
// second 是 map 的 value。
// ------------------------------------------------------------
void pairInsideMapExample() {
    cout << "========== 示例五：map 中的 pair ==========\n";

    map<int, string> user_names;
    user_names[2] = "Li Si";
    user_names[1] = "Zhang San";

    // item 是 map 元素的引用，所以使用 .first 和 .second。
    for (const auto& item : user_names) {
        cout << "item.first=" << item.first
             << "，item.second=" << item.second << '\n';
    }

    // find 返回迭代器，所以使用 ->first 和 ->second。
    auto position = user_names.find(2);
    if (position != user_names.end()) {
        cout << "find找到：" << position->first
             << " -> " << position->second << '\n';
    }

    cout << '\n';
}

// ------------------------------------------------------------
// 示例六：用 pair 表示健康运动题目中的事件。
//
// pair<int, int> event：
//   first  = 事件类型，1表示开始，-1表示结束；
//   second = 速度。
// ------------------------------------------------------------
void exerciseEventExample() {
    cout << "========== 示例六：用 pair 表示运动事件 ==========\n";

    pair<int, int> start_event = {1, 8};
    pair<int, int> end_event = {-1, 8};

    cout << "开始事件：类型=" << start_event.first
         << "，速度=" << start_event.second << '\n';
    cout << "结束事件：类型=" << end_event.first
         << "，速度=" << end_event.second << '\n';

    // 实际题目中，同一时间可能有多个事件，所以使用 vector<pair<int,int>>。
    vector<pair<int, int>> events_at_time_100;
    events_at_time_100.emplace_back(-1, 5); // 速度5停止生效
    events_at_time_100.emplace_back(1, 8);  // 速度8开始生效

    cout << "时间100共有 " << events_at_time_100.size() << " 个事件：\n";
    for (const auto& event : events_at_time_100) {
        if (event.first == 1) {
            cout << "  速度 " << event.second << " 开始生效\n";
        } else {
            cout << "  速度 " << event.second << " 停止生效\n";
        }
    }
}

int main() {
    basicExample();
    returnTwoValuesExample();
    comparisonExample();
    sortingExample();
    pairInsideMapExample();
    exerciseEventExample();
    return 0;
}

