# STL 与刷题常用标准库

本目录把容器、迭代器和算法放在一起学习，也包括 `string`、数值工具和 `bitset` 等常用标准库内容。新增的每份示例都能独立编译运行，包含中文任务说明、至少两个样例和实际结果校验。

## 学习顺序与文件入口

| 顺序 | 专题 | 文件与要点 |
| --- | --- | --- |
| 1 | vector | [完整基础](vector/vector_basics.cpp)：初始化、二维数组、容量、增删、拷贝与引用；原始简短练习 `vector/vector.cpp` 仍保留 |
| 2 | array | [使用与 vector 对照](array/array_vector_comparison.cpp)、[详细说明](array/README.md)：固定长度、类型、初始化、传参、存储与迭代器 |
| 3 | string | [字符串操作](string/string_basics.cpp)：拼接、截取、查找、替换、转换和转换异常 |
| 4 | 迭代器 | [访问与安全删除](iterators/iterator_and_erase_basics.cpp)：左闭右开区间、const 迭代器、失效问题 |
| 5 | 常用算法 | [算法示例](algorithms/common_algorithms.cpp)：sort/reverse/find/count/最值、去重和条件删除 |
| 6 | 二分查找 | [上下边界](algorithms/binary_search_bounds.cpp)：lower_bound/upper_bound/equal_range/binary_search |
| 7 | 数值工具 | [numeric 示例](algorithms/numeric_basics.cpp)：求和、连续赋值、前缀和、gcd/lcm |
| 8 | 集合 | [set 与 unordered_set](associative_containers/set_unordered_set_basics.cpp)：去重、查找与有序范围 |
| 9 | 键值表 | [已有 map/unordered_map 示例](associative_containers/map_unordered_map_example.cpp)：增删改查、分组 |
| 10 | 重复键容器 | [multiset/multimap](associative_containers/multiset_multimap_basics.cpp)：同键范围、删一个与删全部 |
| 11 | pair | [已有 pair 示例](utility/pair_example.cpp)：两个相关值、比较与返回结果 |
| 12 | 栈和队列 | [stack](container_adapters/stack_basics.cpp)、[queue/deque](../03_data_structures/queue/queue_deque_basics.cpp)：读取与弹出、访问顺序 |
| 13 | 优先队列 | [已有大小根堆对照](priority_queue/heap.cpp)、[Top-K](priority_queue/lc_347_top_k_frequent.cpp)：动态维护最值 |
| 14 | 双向链表 | [list](list/list_basics.cpp)：节点插入删除、成员排序、splice 转移节点 |
| 15 | 位集合 | [bitset](bitset/bitset_basics.cpp)：位编号、设置、查询、计数和位运算 |

## 常见选择

| 需求 | 先考虑 |
| --- | --- |
| 数量动态变化、频繁下标访问 | vector |
| 编译期确定固定数量，如三维坐标 | array |
| 两端追加和删除，还想按下标访问 | deque |
| 判断某个值是否出现过 | unordered_set；需要有序时用 set |
| 从键查到对应的值或统计次数 | unordered_map；需要按键有序时用 map |
| 允许重复并需要有序 | multiset/multimap |
| 后进先出、先进先出、最高优先级先出 | stack、queue、priority_queue |
| 已有节点位置，需要插入删除或转移节点 | list；如果还要线性查找位置，应算上查找成本 |
| 固定数量的二进制开关 | bitset |

## 几条容易混淆的规则

1. `begin()` 指向首元素，`end()` 指向尾后位置。空容器中二者相等，不能解引用。`front/back/top/pop` 也要满足非空前提。
2. `size` 是实际元素数，`reserve` 只预留容量。`array` 不支持变长，`vector` 支持；详细对照见 [array 指南](array/README.md)。
3. `unique` 只处理相邻重复值；全局去重通常先排序，再 `erase(unique(...), end())`。它和 `remove_if` 都不直接缩短 vector。
4. 本目录的二分示例要求升序。找不到时迭代器可能等于 `end()`，先检查再读取。set/map 优先使用成员边界查找。
5. 哈希容器没有可依赖的遍历顺序；集合不支持通过下标读取第几个元素。
6. `multiset.erase(value)` 删除所有同值元素；只删一个应查找后 `erase(iterator)`。multimap 没有 `operator[]`。
7. 求和写 `accumulate(..., 0LL)`。`partial_sum` 的输入元素类型也要足够宽，只把输出设为 long long 不够。
8. 大小根堆比较规则与最终出队顺序要结合理解；普通 `sort` 比较函数要求严格比较，不能写 `>=` 或 `<=`。

例子尽量使用普通函数和直接循环；复杂度和边界说明写在各文件末尾。测试中为了打印 PASS/FAIL 使用的辅助函数不是需要背诵的算法。

## 编译运行

从仓库根目录运行，以下以 array 对照为例：

```powershell
New-Item -ItemType Directory -Force .\build | Out-Null
g++ -std=c++17 -Wall -Wextra -pedantic .\02_stl\array\array_vector_comparison.cpp -o .\build\array_vector_comparison.exe
.\build\array_vector_comparison.exe
```

新示例最后应输出 `failed tests: 0`，失败时进程返回非零。替换源码和输出文件名即可运行其他专题。
