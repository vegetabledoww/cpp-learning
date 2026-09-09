# 健康运动步数统计：每分钟速度数组与滑动窗口

对应源代码：[solution_reference.cpp](../src/solution_reference.cpp)

## 一、题目目标

每条运动记录包含：

```text
(userid, start_time, end_time, avg_speed)
```

需要找出连续 120 分钟内累计里程最大的窗口，返回：

```text
(总里程, userid, 窗口开始时间)
```

同一个用户的记录可能重叠。同一分钟被多条记录覆盖时，该分钟的真实速度取最大值。

如果总里程相同，则依次选择：

1. `userid` 更小的结果；
2. `userid` 也相同时，开始时间更早的结果。

## 二、采用的核心思路

当前实现使用：

```text
按用户分组
    ↓
收集时间端点并拆成小段
    ↓
计算每个小段的最大速度
    ↓
构造每分钟真实速度数组 speed
    ↓
使用长度为 120 的普通滑动窗口
    ↓
比较所有用户的最优结果
```

这种写法建立在题目时间范围不会太大的前提下，时间、速度和里程都使用 `int`。

## 三、按照用户分组

程序先使用下面的数据结构保存每个用户的记录：

```cpp
map<int, vector<tuple<int, int, int>>> user_raw;
```

其中：

```text
key   = userid
value = 该用户的所有 (start, end, speed) 记录
```

每个用户单独拆分区间、构造速度数组并计算最佳窗口，最后再进行全局比较。

## 四、保留原来的端点分段处理

对于一个用户，先把所有开始时间和结束时间放进 `set`：

```cpp
set<int> time_points;
for (const auto& iv : intervals) {
    time_points.insert(get<0>(iv));
    time_points.insert(get<1>(iv));
}
```

排序后的相邻端点组成互不重叠的小段。对于每个小段，遍历原始记录并取覆盖它的最大速度：

```cpp
vector<int> times(time_points.begin(), time_points.end());
vector<tuple<int, int, int>> segments;

for (int i = 0; i + 1 < (int)times.size(); ++i) {
    int start = times[i];
    int end = times[i + 1];
    int best_speed = 0;

    for (const auto& iv : intervals) {
        if (get<0>(iv) <= start && get<1>(iv) >= end) {
            best_speed = max(best_speed, get<2>(iv));
        }
    }
    segments.emplace_back(start, end, best_speed);
}
```

这部分沿用了原来的处理结构，负责正确解决区间重叠问题。

## 五、在分段结果上构造每分钟速度数组

最早时间、最晚时间和总分钟数可以直接从已排序的端点得到：

```cpp
int min_time = times.front();
int max_time = times.back();
int total_minutes = max_time - min_time;
```

创建长度为 `total_minutes` 的数组：

```cpp
vector<int> speed(total_minutes, 0);
```

`speed[i]` 表示的不是绝对时间 `i`，而是：

```text
实际时间区间 [min_time + i, min_time + i + 1)
```

所以实际时间和数组下标之间的关系为：

```text
index = time - min_time
time  = min_time + index
```

数组初始值为 0，表示该分钟没有运动记录。

这里不再直接展开原始区间，而是展开已经计算好真实速度的 `segments`：

```cpp
for (const auto& segment : segments) {
    int start = get<0>(segment);
    int end = get<1>(segment);
    int segment_speed = get<2>(segment);

    for (int time = start; time < end; ++time) {
        speed[time - min_time] = segment_speed;
    }
}
```

这里把运动区间理解为左闭右开区间：

```text
[start, end)
```

例如 `[0, 100)` 包含第 0 分钟到第 99 分钟，一共 100 分钟。

重叠记录的 `max` 已经在生成 `segments` 时处理完毕，所以这里直接赋值即可。

## 六、重叠记录示例

假设用户 1 有两条记录：

```text
[0, 100)   速度 5
[50, 150)  速度 8
```

先按照端点拆成三个小段：

```text
[0, 50)    速度 5
[50, 100)  速度 8
[100, 150) 速度 8
```

再把这些小段按分钟展开，得到：

```text
speed[0..49]   = 5
speed[50..149] = 8
```

这样只提高真正重叠部分的速度，不会把速度 8 错误扩展到 `[0, 50)`。

## 七、计算第一个 120 分钟窗口

先直接累加数组中的前 120 个速度：

```cpp
int window_distance = 0;
for (int i = 0; i < 120; ++i) {
    window_distance += speed[i];
}
```

因为数组的每个元素代表一分钟，所以一分钟的里程就是：

```text
1 分钟 × 该分钟速度
```

120 个元素之和就是连续 120 分钟的总里程。

## 八、滑动窗口如何右移

窗口起点从 `start - 1` 移到 `start` 时：

```text
旧窗口：[start - 1, start + 119)
新窗口：[start,     start + 120)
```

只发生两个变化：

1. `speed[start - 1]` 离开窗口；
2. `speed[start + 119]` 进入窗口。

所以新的窗口里程为：

```text
新窗口里程 = 旧窗口里程
             - 离开窗口的一分钟速度
             + 新进入窗口的一分钟速度
```

对应代码：

```cpp
if (start > 0) {
    window_distance -= speed[start - 1];
    window_distance += speed[start + 119];
}
```

这种写法每次移动只需要一次减法和一次加法，不需要重新累加 120 个元素。

## 九、数组下标转换为实际开始时间

滑动窗口中的 `start` 是数组下标，返回值需要的是实际时间：

```cpp
int actual_start_time = min_time + start;
```

例如：

```text
min_time = 20
start = 30
```

那么窗口的实际开始时间是：

```text
20 + 30 = 50
```

## 十、样例一计算过程

用户 1 的真实速度数组为：

```text
speed[0..49]   = 5
speed[50..149] = 8
```

最佳窗口从实际时间 30 开始，对应 `[30, 150)`：

```text
30 到 50：20 分钟 × 5 = 100
50 到 150：100 分钟 × 8 = 800
总里程：100 + 800 = 900
```

因此该用户的结果为：

```text
(900, 1, 30)
```

## 十一、答案比较规则

每计算出一个窗口，就按照下面的优先级更新答案：

```text
1. 窗口里程更大；
2. 里程相同，userid 更小；
3. 里程和 userid 都相同，实际开始时间更早。
```

对应代码为：

```cpp
if (window_distance > max_distance ||
    (window_distance == max_distance && uid < best_uid) ||
    (window_distance == max_distance && uid == best_uid &&
     actual_start_time < best_start_time)) {
    max_distance = window_distance;
    best_uid = uid;
    best_start_time = actual_start_time;
}
```

## 十二、复杂度

设一个用户有 `R` 条记录、`B` 个不同的时间端点，从最早记录到最晚记录共有 `T` 分钟。

端点分段并计算每段最大速度需要：

```text
O(B * R)
```

从分段结果构造速度数组并完成滑动窗口需要：

```text
O(T)
```

主要额外空间为端点、分段和速度数组：

```text
O(B + T)
```

因为题目中的时间范围不会太大，所以这种实现更直观，也足够使用。

## 十三、当前测试结果

程序中的三组测试输出为：

```text
(900, 1, 30)
(600, 3, 100)
(480, 1, 20)
```
