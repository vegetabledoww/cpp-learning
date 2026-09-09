// ============================================================
// 题目：多关键字任务调度（自定义比较器优先队列）
// ============================================================
//
// 【背景】
//   有若干任务，每个任务包含 4 个属性：
//     [0] priority  : 优先级（越大越优先）
//     [1] arrive    : 到达时间（越早越优先）
//     [2] id        : 任务ID
//     [3] cost      : 执行耗时
//   要求按如下规则从优先队列中依次取出任务执行：
//     - 第一关键字 priority：从大到小
//     - 第二关键字 arrive  ：从小到大（优先级相同时，先到先做）
//
// 【样例】
//   输入任务（priority, arrive, id, cost）：
//     (5, 10, 1, 100)
//     (5,  3, 2,  50)   ← 与上面优先级相同，但到达更早
//     (8, 20, 3, 200)
//     (3,  1, 4,  10)
//   输出执行顺序：
//     3 → 2 → 1 → 4
//
// 【关键点：自定义比较器 Cmp】
//   priority_queue 的比较器返回 true 表示 a 的优先级"低于" b
//   （即 a 排在 b 后面，b 先出队）
//   注意这与 sort 的比较器语义相反！
// ============================================================
#include <iostream>
#include <queue>
#include <vector>
#include <array>
using namespace std;

// 元素类型：4 个 long long
using Arr = array<long long, 4>;

// 自定义比较器
struct Cmp {
    bool operator()(const Arr& a, const Arr& b) const {
        // 第一关键字 priority：从大到小（降序用小于）【跟sort的降序相反】
        // 注意：priority_queue 里返回 true 表示 a 优先级低于 b
        //       所以 "从大到小" 要写 a[0] < b[0]
        if (a[0] != b[0]) {
            return a[0] < b[0];   // a 的 priority 小 → a 排后面
        } else {
            // 第二关键字 arrive：从小到大(升序用大于)【跟sort的升序相反】
            // "从小到大" 即 a 大的排后面 → a[1] > b[1]
            return a[1] > b[1];
        }
    }
};

int main() {
    // 声明优先队列：元素类型 Arr，底层容器 vector<Arr>，比较器 Cmp
    priority_queue<Arr, vector<Arr>, Cmp> heap;

    // 插入测试任务：(priority, arrive, id, cost)
    vector<Arr> tasks = {
        {5, 10, 1, 100},
        {5,  3, 2,  50},
        {8, 20, 3, 200},
        {3,  1, 4,  10}
    };

    cout << "in queue order:" << endl;
    for (const auto& t : tasks) {
        cout << "  priority=" << t[0]
             << " arrive=" << t[1]
             << " id=" << t[2]
             << " cost=" << t[3] << endl;
        heap.push(t);
    }

    cout << "\nout queue order:" << endl;
    int order = 1;
    while (!heap.empty()) {
        Arr t = heap.top();
        heap.pop();
        cout << order++ << ". "
             << "priority=" << t[0]
             << " arrive=" << t[1]
             << " id=" << t[2]
             << " cost=" << t[3] << endl;
    }

    // 期望顺序：3(priority=8) → 2(priority=5,arrive=3) → 1(priority=5,arrive=10) → 4(priority=3)
    return 0;
}
