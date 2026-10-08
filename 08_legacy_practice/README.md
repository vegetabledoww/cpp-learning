# 去年手敲代码整理集

来源：`D:\Code\source\repos`。按你的要求单独收纳，不混入现有主分类；整理日期：2026-09-28。

这批旧目录共 24 个一级工程目录、44 份 C/C++ 源码或头文件（排除构建缓存）。其中 26 份练习源码已逐字节复制到 [originals](./originals)，另 18 份属于同一个 TinyWebServer 项目。WebServer 工程引用 TinyWebServer 的源码，不另算项目；Connect_sql_test 只是问候程序，不是已实现的数据库例子。

从练习原稿中拆出 **84 个可独立编译运行的学习文件**。这是本目录的文件数，不是“84 道全新原题”：部分文件合并几个相关知识点，部分题目与主仓已有基础主题重合。没有把每个重复版本、头文件或被注释的 main 都计为新题。

| 子目录 | 文件数 | 内容 |
| --- | ---: | --- |
| [basics](./basics) | 8 | 深拷贝、引用与转发、虚析构、内存、线程等 |
| [data_structures](./data_structures) | 14 | 链表、栈、队列、树、LFU、树状数组、ST 表 |
| [algorithms](./algorithms) | 59 | 二分、回溯、DP、滑窗、图、字符串及恢复规则的笔试练习 |
| [case_studies](./case_studies) | 3 | K-means、局部坐标转换、矩阵与协方差 |

## 先从哪里学

1. [内存与字符数组](./basics/memory_and_bit_fields.cpp) → [深拷贝](./basics/deep_copy.cpp) → [move 与 forward](./basics/move_and_forward.cpp)。先分清对象、指针、长度、所有权。
2. [反转链表](./data_structures/lc_206_reverse_list.cpp) → [环形链表](./data_structures/lc_141_linked_list_cycle.cpp) → [删除倒数节点](./data_structures/lc_019_remove_nth_from_end.cpp) → [区间反转](./data_structures/lc_092_reverse_between.cpp)。
3. [有效括号](./algorithms/lc_020_valid_parentheses.cpp) → [最小栈](./data_structures/lc_155_min_stack.cpp) → [双栈队列](./data_structures/lc_232_queue_using_stacks.cpp)。
4. [最大子数组和](./algorithms/lc_053_max_subarray.cpp) → [最长递增子序列](./algorithms/lc_300_longest_increasing_subsequence.cpp) → [0/1 背包](./algorithms/zero_one_knapsack.cpp) → [完全背包](./algorithms/unbounded_knapsack.cpp) → [零钱兑换 II](./algorithms/lc_518_coin_change_ii.cpp)。
5. [无重复最长子串](./algorithms/lc_003_longest_unique_substring.cpp) → [字母异位词](./algorithms/lc_438_find_anagrams.cpp) → [课程表 II](./algorithms/lc_210_course_schedule_ii.cpp) → [KMP](./algorithms/kmp_search.cpp)。
6. 树状数组、ST 表、LFU、数值计算案例放到后面；它们不适合拿来作为第一批手敲练习。

每份源码开头有题面和至少两个样例，末尾有收获点和复杂度，main 打印期望值、实际值和 PASS/FAIL。先自己实现核心函数，再运行本地测试。

## 如何验证

在仓库根目录运行：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\08_legacy_practice\verify.ps1
```

可用 `-Compiler C:\MinGW\mingw64\bin\g++.exe` 指定编译器，或用 `-Filter lc_092_reverse_between.cpp` 只跑一题。需要支持 C++17 和 std::thread 的编译器。脚本以 `-std=c++17 -Wall -Wextra -pedantic -Werror -pthread` 编译，检查进程退出码，并清理本次 GUID 临时目录。原稿的 .txt 不进入编译扫描。

也可以单独编译：

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic .\08_legacy_practice\data_structures\lc_206_reverse_list.cpp -o .\build\legacy_reverse_list.exe
.\build\legacy_reverse_list.exe
```

## 来源与完成范围

- [SOURCES.md](./SOURCES.md)：每份原稿与学习版的对应关系、已在主仓存在的重复主题。
- [manifest.json](./manifest.json)：26 份原始副本的相对路径、字节数和 SHA256；副本保留原始编码，以 .txt 后缀避免误编译。
- [FIXES.md](./FIXES.md)：修正了什么，为什么要改。
- [VERIFICATION.md](./VERIFICATION.md)：84/84通过的编译、样例和边界验证记录。
- [PENDING.md](./PENDING.md)：缺原题、规则矛盾的片段及需要补充的信息；这些只归档，不冒称已经修复或通过判题。
- [TinyWebServer 项目说明](./projects/TinyWebServer.md)：整项目入口和依赖，不计入这 84 个学习文件的验证结论。

可恢复的笔试练习明确写出“恢复规则”和必要的学习规模。通过本地样例只证明这些已声明规则下的测试结果，不能证明找回了未知原题的全部要求。LFU 保留旧稿 set 思路，操作是 O(log capacity)，与原平台平均 O(1) 要求有区别。坐标转换仅适用小范围近似；K-means 不保证全局最优。

## 全部学习文件

### 语言基础

- [构造、运算符重载、枚举、静态局部变量与宏](./basics/date_enum_static_macro.cpp)
- [深拷贝：构造、拷贝构造与拷贝赋值](./basics/deep_copy.cpp)
- [异常处理与 weak_ptr 解除循环持有](./basics/exceptions_and_weak_ptr.cpp)
- [forward_list 与逗号整数解析](./basics/forward_list_and_csv.cpp)
- [sizeof、strlen、字节复制、布局与位域](./basics/memory_and_bit_fields.cpp)
- [左值、右值、move 与完美转发](./basics/move_and_forward.cpp)
- [线程入口与 join](./basics/thread_join.cpp)
- [虚析构与非虚成员函数](./basics/virtual_destructor.cpp)

### 数据结构

- [树状数组：严格递减子序列计数](./data_structures/fenwick_decreasing_subsequences.cpp)
- [链表中首个未出现在另一字符串的字符](./data_structures/first_missing_character.cpp)
- [LeetCode 19：删除链表的倒数第 N 个结点](./data_structures/lc_019_remove_nth_from_end.cpp)
- [LeetCode 25：K 个一组翻转链表](./data_structures/lc_025_reverse_k_group.cpp)
- [LeetCode 92：反转链表 II](./data_structures/lc_092_reverse_between.cpp)
- [LeetCode 103：二叉树的锯齿形层序遍历](./data_structures/lc_103_zigzag_level_order.cpp)
- [LeetCode 112：路径总和](./data_structures/lc_112_path_sum.cpp)
- [LeetCode 141：环形链表](./data_structures/lc_141_linked_list_cycle.cpp)
- [LeetCode 155：最小栈](./data_structures/lc_155_min_stack.cpp)
- [LeetCode 206：反转链表](./data_structures/lc_206_reverse_list.cpp)
- [LeetCode 232：用栈实现队列](./data_structures/lc_232_queue_using_stacks.cpp)
- [LeetCode 236：二叉树的最近公共祖先](./data_structures/lc_236_lowest_common_ancestor.cpp)
- [LeetCode 460：LFU 缓存（有序集合学习版）](./data_structures/lc_460_lfu_cache.cpp)
- [ST 表：按子数组长度区间查询最大和](./data_structures/length_range_sparse_table.cpp)

### 算法

- [恰好翻转 K 次后的最小二进制字符串](./algorithms/binary_flip_exactly_k.cpp)
- [固定长度数据块去重与计数](./algorithms/block_counting.cpp)
- [共同元素的下标映射](./algorithms/common_element_indices.cpp)
- [互斥任务：数量优先、耗时次优](./algorithms/conflicting_jobs.cpp)
- [数字条重叠后的最短总长度](./algorithms/digit_string_overlap.cpp)
- [Fisher–Yates 洗牌](./algorithms/fisher_yates_shuffle.cpp)
- [分数背包](./algorithms/fractional_knapsack.cpp)
- [按出现次数过滤数组](./algorithms/frequency_filter.cpp)
- [十字翻转：把小网格变为全零](./algorithms/grid_lights_out.cpp)
- [修改至多一个数后的最长严格递增连续段](./algorithms/increasing_segment_one_change.cpp)
- [三数递增 K 次后的最大乘积](./algorithms/increment_three_max_product.cpp)
- [KMP：首次子串匹配](./algorithms/kmp_search.cpp)
- [LeetCode 3：无重复字符的最长子串](./algorithms/lc_003_longest_unique_substring.cpp)
- [LeetCode 5：最长回文子串](./algorithms/lc_005_longest_palindrome.cpp)
- [LeetCode 8：字符串转换整数 atoi](./algorithms/lc_008_string_to_integer.cpp)
- [LeetCode 11：盛最多水的容器](./algorithms/lc_011_container_with_most_water.cpp)
- [LeetCode 17：电话号码的字母组合](./algorithms/lc_017_phone_letters.cpp)
- [LeetCode 20：有效的括号](./algorithms/lc_020_valid_parentheses.cpp)
- [LeetCode 27：移除元素](./algorithms/lc_027_remove_element.cpp)
- [LeetCode 32：最长有效括号](./algorithms/lc_032_longest_valid_parentheses.cpp)
- [LeetCode 34：在排序数组中查找元素的第一个和最后一个位置](./algorithms/lc_034_search_range.cpp)
- [LeetCode 51：N 皇后](./algorithms/lc_051_n_queens.cpp)
- [LeetCode 53：最大子数组和](./algorithms/lc_053_max_subarray.cpp)
- [LeetCode 70：爬楼梯](./algorithms/lc_070_climbing_stairs.cpp)
- [LeetCode 75：颜色分类](./algorithms/lc_075_sort_colors.cpp)
- [LeetCode 88：合并两个有序数组](./algorithms/lc_088_merge_sorted_arrays.cpp)
- [LeetCode 1103：分糖果 II](./algorithms/lc_1103_distribute_candies.cpp)
- [LeetCode 125：验证回文串](./algorithms/lc_125_valid_palindrome.cpp)
- [LeetCode 153：寻找旋转排序数组中的最小值](./algorithms/lc_153_rotated_minimum.cpp)
- [LeetCode 1535：找出数组游戏的赢家](./algorithms/lc_1535_array_game.cpp)
- [LeetCode 1673：最具竞争力的子序列](./algorithms/lc_1673_most_competitive.cpp)
- [LeetCode 179：最大数](./algorithms/lc_179_largest_number.cpp)
- [LeetCode 210：课程表 II](./algorithms/lc_210_course_schedule_ii.cpp)
- [LeetCode 2101：引爆最多的炸弹](./algorithms/lc_2101_maximum_detonation.cpp)
- [LeetCode 2105：给植物浇水 II](./algorithms/lc_2105_watering_plants_ii.cpp)
- [LeetCode 2129：将标题首字母大写](./algorithms/lc_2129_capitalize_title.cpp)
- [LeetCode 2144：打折购买糖果的最小开销](./algorithms/lc_2144_candy_discount.cpp)
- [LeetCode 215：数组中的第 K 大元素](./algorithms/lc_215_kth_largest.cpp)
- [LeetCode 2380：二进制字符串重新安排顺序需要的时间](./algorithms/lc_2380_binary_rearrangement.cpp)
- [LeetCode 2844：生成特殊数字的最少操作](./algorithms/lc_2844_special_number.cpp)
- [LeetCode 2965：找出缺失和重复的数字](./algorithms/lc_2965_missing_repeated.cpp)
- [LeetCode 2981：找出出现至少三次的最长特殊子字符串 I](./algorithms/lc_2981_special_substring.cpp)
- [LeetCode 299：猜数字游戏](./algorithms/lc_299_bulls_and_cows.cpp)
- [LeetCode 300：最长递增子序列](./algorithms/lc_300_longest_increasing_subsequence.cpp)
- [LeetCode 394：字符串解码](./algorithms/lc_394_decode_string.cpp)
- [LeetCode 438：找到字符串中所有字母异位词](./algorithms/lc_438_find_anagrams.cpp)
- [LeetCode 518：零钱兑换 II](./algorithms/lc_518_coin_change_ii.cpp)
- [LeetCode 682：棒球比赛](./algorithms/lc_682_baseball_game.cpp)
- [曼哈顿距离内的最大邻域人数](./algorithms/manhattan_neighbors.cpp)
- [长度至少 K 的子数组最大 GCD](./algorithms/max_gcd_subarray.cpp)
- [排列后前缀极差之和最小](./algorithms/min_prefix_range_sum.cpp)
- [区间异或与有界整数异或最大值](./algorithms/range_xor_maximum.cpp)
- [剪绳子：答案二分](./algorithms/rope_cutting.cpp)
- [冒泡、插入、非递归快排与桶排序](./algorithms/sorting_variants.cpp)
- [缩短木棍得到最大三角形周长](./algorithms/triangle_shortening.cpp)
- [完全背包](./algorithms/unbounded_knapsack.cpp)
- [墙壁位掩码：统计房间面积](./algorithms/wall_rooms.cpp)
- [带收益的区间选择](./algorithms/weighted_intervals.cpp)
- [0/1 背包](./algorithms/zero_one_knapsack.cpp)

### 数值案例

- [三维 K-means 聚类（确定性学习版）](./case_studies/k_means.cpp)
- [局部经纬度与东北天坐标近似转换](./case_studies/local_coordinates.cpp)
- [矩阵转置、乘法与样本协方差](./case_studies/matrix_statistics.cpp)
