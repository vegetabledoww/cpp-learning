# C++ 代码知识点索引

本目录按照“语言基础 -> STL -> 数据结构 -> 算法 -> 设计题 -> 设计模式 -> 完整案例”组织。

旧文件名与新路径的完整对应关系见 [MIGRATION_MAP.md](./MIGRATION_MAP.md)。

## 目录说明

| 目录 | 内容 |
| --- | --- |
| `01_cpp_basics` | C++ 语言基础、内存管理等示例 |
| `02_stl` | STL 工具类、关联容器和容器适配器 |
| `03_data_structures` | 链表、树、栈、单调栈和缓存结构 |
| `04_algorithms` | 排序、二分、动态规划、BFS、回溯、哈希等算法 |
| `05_design_problems` | 给定类或函数接口，需要补写业务逻辑的设计题 |
| `06_design_patterns` | 单例等经典设计模式 |
| `07_case_studies` | 包含多个实现版本、文档和图片的完整案例 |
| `29project` | 独立且有机的项目，内部结构和文件保持原样 |
| `90_scratch_and_incomplete` | 多知识点混合练习、空文件或待修复代码 |
| `artifacts` | 尚需归位的少量数据文件和非 C++ 配置；已批准的旧产物已清理 |
| `build` | 新的编译产物目录，不存放源码 |

## 分类索引

### STL

- `02_stl/utility/pair_example.cpp`：`pair` 的创建、比较、排序和返回多个结果。
- `02_stl/associative_containers/map_unordered_map_example.cpp`：`map` 与 `unordered_map`。
- `02_stl/priority_queue`：`priority_queue`、小根堆、自定义比较和 Top-K 问题。

### 数据结构

- `03_data_structures/linked_list`：链表合并与节点删除。
- `03_data_structures/tree`：二叉树层序遍历。
- `03_data_structures/stack`：栈模拟题。
- `03_data_structures/monotonic_stack`：单调栈问题。
- `03_data_structures/cache`：LRU 缓存实现。

### 算法

- `04_algorithms/sorting`：快速排序，以及最小价格差的统计问题。
- `04_algorithms/binary_search`：普通二分和答案二分。
- `04_algorithms/bit_manipulation`：IPv4 地址转换、首部解析、CIDR 掩码、最长前缀匹配和十六进制异或校验和。
- `04_algorithms/dynamic_programming`：编辑距离、打家劫舍、股票、零钱兑换等。
- `04_algorithms/graph_and_bfs`：图搜索与迷宫搜索。
- `04_algorithms/graph_and_dfs`：二维网格 DFS 与连通区域问题。
- `04_algorithms/backtracking`：数独回溯。
- `04_algorithms/sliding_window`：可变长度滑动窗口、前缀和与连续子串问题。
- `04_algorithms/string_parsing`：MAC 地址识别与规范化。

### 设计题与案例

- `05_design_problems/application_usage`：应用资源聚合、多规则排序和 Top-3。
- `05_design_problems/arp_system`：ARP 表、报文缓存和淘汰规则。
- `05_design_problems/video_service`：视频频道分配、计费和释放后的资源迁移。
- `05_design_problems/timer_system`：周期定时器的启动、停止和超时事件模拟。
- `06_design_patterns/singleton`：单例模式示例。
- `07_case_studies/health_exercise`：健康运动步数统计的多个实现及说明资料。
- `07_case_studies/server_busy`：服务器空闲时段统计的分步实现与事件扫描优化版。

## Codex 题目整理 Skill

- 仓库级 Skill 位于 `.agents/skills/cpp-exercise-curator`。
- 新增、整理或补全 C++ 题目时会自动应用，也可以明确使用 `$cpp-exercise-curator` 调用。
- Skill 统一约束题目归类、中文题面、样例、`main()`、边界测试、编译验证和仓库索引更新。

## 文件命名约定

- 普通示例使用描述性 `snake_case.cpp` 名称。
- LeetCode 题解使用 `lc_题号_题目.cpp`。
- 同一设计题的不同文件使用 `problem_and_examples.cpp`、`solution.cpp` 等职责名称。
- 不再使用 `1.cpp`、`2.cpp`、`do.cpp` 这类无法表达用途的名称。

## 编译约定

建议从仓库根目录编译，并把输出统一放进 `build`：

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic .\02_stl\utility\pair_example.cpp -o .\build\pair_example.exe
```

`90_scratch_and_incomplete` 中的文件可能包含多个题目、残缺实现或历史问题，不作为全量编译通过的基线。

## 当前已知编译问题

- `03_data_structures/linked_list/lc_021_merge_two_sorted_lists.cpp` 中存在两个同签名的 `mergeTwoLists`，属于迁移前已有的重复定义。
- `04_algorithms/binary_search/lc_2560_house_robber_iv.cpp` 使用了 `max_element`，但迁移前的源码没有包含 `<algorithm>`。
- `05_design_problems/arp_system/solution.cpp` 在当前 MinGW GCC 8.1 下可用 C++14 通过语法检查；用 C++17 包含 `bits/stdc++.h` 时会触发该工具链的 `filesystem` 头文件兼容问题。

## 受保护目录

`29project` 是一个完整项目。整理其他学习代码时，不移动、不改名、不拆分、不清理该目录中的任何文件。
