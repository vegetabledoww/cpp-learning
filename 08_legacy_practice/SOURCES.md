# 原稿与学习版对应关系

原路径基准：`D:\Code\source\repos`。本次复制而非移动；外部原文件与原工程保持原样，因此不改主仓 MIGRATION_MAP.md 的迁移记录。来源行号是归档时旧文件的行号，学习版不继承硬编码的绝对 include。

## 26 份源码副本

### [Char/main.cpp](./originals/Char/main.cpp.txt)

- [sizeof、strlen、字节复制、布局与位域](./basics/memory_and_bit_fields.cpp)（来源 Char/main.cpp; pen_exam_8/pen_exam_8/_8_pen_exam.cpp:606-689; 9_test/9_test/9_test.cpp:183-204）
- [Fisher–Yates 洗牌](./algorithms/fisher_yates_shuffle.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:420-446; Char/main.cpp:66-95）
- [矩阵转置、乘法与样本协方差](./case_studies/matrix_statistics.cpp)（来源 Char/main.cpp:173-222; cov_Matrix/main.cpp:4-30）

### [cov_Matrix/main.cpp](./originals/cov_Matrix/main.cpp.txt)

- [矩阵转置、乘法与样本协方差](./case_studies/matrix_statistics.cpp)（来源 Char/main.cpp:173-222; cov_Matrix/main.cpp:4-30）

### [K_means/main.cpp](./originals/K_means/main.cpp.txt)

- [三维 K-means 聚类（确定性学习版）](./case_studies/k_means.cpp)（来源 K_means/main.cpp; 10.22/10.22/10.22.cpp:460-586）

### [lonANDlat/son.cpp](./originals/lonANDlat/son.cpp.txt)

- [局部经纬度与东北天坐标近似转换](./case_studies/local_coordinates.cpp)（来源 lonANDlat/son.cpp:12-41）

### [new_function/test_function.cpp](./originals/new_function/test_function.cpp.txt)

- [LeetCode 32：最长有效括号](./algorithms/lc_032_longest_valid_parentheses.cpp)（来源 new_function/test_function.cpp:784-808）
- [LeetCode 1673：最具竞争力的子序列](./algorithms/lc_1673_most_competitive.cpp)（来源 new_function/test_function.cpp:725-738）
- [LeetCode 2981：找出出现至少三次的最长特殊子字符串 I](./algorithms/lc_2981_special_substring.cpp)（来源 new_function/test_function.cpp:740-763）
- [LeetCode 2965：找出缺失和重复的数字](./algorithms/lc_2965_missing_repeated.cpp)（来源 new_function/test_function.cpp:765-782）
- [LeetCode 1535：找出数组游戏的赢家](./algorithms/lc_1535_array_game.cpp)（来源 new_function/test_function.cpp:699-723）
- [KMP：首次子串匹配](./algorithms/kmp_search.cpp)（来源 new_function/test_function.cpp:847-883）
- [完全背包](./algorithms/unbounded_knapsack.cpp)（来源 new_function/test_function.cpp:363-381）
- [LeetCode 299：猜数字游戏](./algorithms/lc_299_bulls_and_cows.cpp)（来源 new_function/test_function.cpp:260-282）
- [LeetCode 11：盛最多水的容器](./algorithms/lc_011_container_with_most_water.cpp)（来源 new_function/test_function.cpp:484-502）
- [LeetCode 2105：给植物浇水 II](./algorithms/lc_2105_watering_plants_ii.cpp)（来源 new_function/test_function.cpp:590-634）
- [LeetCode 1103：分糖果 II](./algorithms/lc_1103_distribute_candies.cpp)（来源 new_function/test_function.cpp:810-829）
- [LeetCode 438：找到字符串中所有字母异位词](./algorithms/lc_438_find_anagrams.cpp)（来源 new_function/test_function.cpp:121-156）
- [LeetCode 17：电话号码的字母组合](./algorithms/lc_017_phone_letters.cpp)（来源 new_function/test_function.cpp:222-257）
- [LeetCode 51：N 皇后](./algorithms/lc_051_n_queens.cpp)（来源 new_function/test_function.cpp:325-360）
- [LeetCode 20：有效的括号](./algorithms/lc_020_valid_parentheses.cpp)（来源 new_function/test_function.cpp:553-580）
- [LeetCode 179：最大数](./algorithms/lc_179_largest_number.cpp)（来源 new_function/test_function.cpp:510-524）
- [LeetCode 2129：将标题首字母大写](./algorithms/lc_2129_capitalize_title.cpp)（来源 new_function/test_function.cpp:293-313）
- [LeetCode 27：移除元素](./algorithms/lc_027_remove_element.cpp)（来源 new_function/test_function.cpp:679-694）
- [LeetCode 518：零钱兑换 II](./algorithms/lc_518_coin_change_ii.cpp)（来源 new_function/test_function.cpp:831-843）
- [构造、运算符重载、枚举、静态局部变量与宏](./basics/date_enum_static_macro.cpp)（来源 operation/main.cpp:4-35; new_function/test_function.cpp:35-58; Pureproject/test.c:5-15）
- [分数背包](./algorithms/fractional_knapsack.cpp)（来源 new_function/test_function.cpp:434-472）
- [共同元素的下标映射](./algorithms/common_element_indices.cpp)（来源 new_function/test_function.cpp:393-410）

### [operation/main.cpp](./originals/operation/main.cpp.txt)

- [构造、运算符重载、枚举、静态局部变量与宏](./basics/date_enum_static_macro.cpp)（来源 operation/main.cpp:4-35; new_function/test_function.cpp:35-58; Pureproject/test.c:5-15）

### [order_methods/order.cpp](./originals/order_methods/order.cpp.txt)

- [冒泡、插入、非递归快排与桶排序](./algorithms/sorting_variants.cpp)（来源 order_methods/order.cpp:14-134; Top_K_C++/demo.cpp:11-90）

### [Pureproject/helloC.c](./originals/Pureproject/helloC.c.txt)

C 工程入口/头文件；静态局部变量学习版见 basics/date_enum_static_macro.cpp，原工程不作为 C++17 单文件编译对象。

### [Pureproject/test.c](./originals/Pureproject/test.c.txt)

- [构造、运算符重载、枚举、静态局部变量与宏](./basics/date_enum_static_macro.cpp)（来源 operation/main.cpp:4-35; new_function/test_function.cpp:35-58; Pureproject/test.c:5-15）

### [Pureproject/test.h](./originals/Pureproject/test.h.txt)

C 工程入口/头文件；静态局部变量学习版见 basics/date_enum_static_macro.cpp，原工程不作为 C++17 单文件编译对象。

### [Top_K_C++/assist.h](./originals/Top_K_C++/assist.h.txt)

链表、树、缓存节点的公共声明；学习版按题放入必要的局部结构，不单独计题。

### [Top_K_C++/demo.cpp](./originals/Top_K_C++/demo.cpp.txt)

- [LeetCode 53：最大子数组和](./algorithms/lc_053_max_subarray.cpp)（来源 Top_K_C++/demo.cpp:495-508）
- [LeetCode 300：最长递增子序列](./algorithms/lc_300_longest_increasing_subsequence.cpp)（来源 Top_K_C++/demo.cpp:531-544）
- [LeetCode 215：数组中的第 K 大元素](./algorithms/lc_215_kth_largest.cpp)（来源 Top_K_C++/demo.cpp:480-492）
- [LeetCode 2844：生成特殊数字的最少操作](./algorithms/lc_2844_special_number.cpp)（来源 Top_K_C++/demo.cpp:446-477）
- [LeetCode 206：反转链表](./data_structures/lc_206_reverse_list.cpp)（来源 Top_K_C++/demo.cpp:211-237）
- [LeetCode 141：环形链表](./data_structures/lc_141_linked_list_cycle.cpp)（来源 Top_K_C++/demo.cpp:94-119）
- [LeetCode 19：删除链表的倒数第 N 个结点](./data_structures/lc_019_remove_nth_from_end.cpp)（来源 Top_K_C++/demo.cpp:242-269）
- [LeetCode 232：用栈实现队列](./data_structures/lc_232_queue_using_stacks.cpp)（来源 Top_K_C++/demo.cpp:272-311）
- [LeetCode 112：路径总和](./data_structures/lc_112_path_sum.cpp)（来源 Top_K_C++/demo.cpp:343-372）
- [LeetCode 682：棒球比赛](./algorithms/lc_682_baseball_game.cpp)（来源 Top_K_C++/demo.cpp:510-528）
- [LeetCode 2101：引爆最多的炸弹](./algorithms/lc_2101_maximum_detonation.cpp)（来源 Top_K_C++/demo.cpp:374-419）
- [冒泡、插入、非递归快排与桶排序](./algorithms/sorting_variants.cpp)（来源 order_methods/order.cpp:14-134; Top_K_C++/demo.cpp:11-90）

### [Top_K_C++/main.cpp](./originals/Top_K_C++/main.cpp.txt)

重复调用示例或草稿，相关链表、LRU、层序和排序见下方重复主题索引；原稿保留。

### [Top_K_C++/practice.cpp](./originals/Top_K_C++/practice.cpp.txt)

重复调用示例或草稿，相关链表、LRU、层序和排序见下方重复主题索引；原稿保留。

### [10.22/10.22/10.22.cpp](./originals/10.22/10.22/10.22.cpp.txt)

- [墙壁位掩码：统计房间面积](./algorithms/wall_rooms.cpp)（来源 10.22/10.22/10.22.cpp:1-71; huawei/huawei/huawei.cpp:180-235）
- [按出现次数过滤数组](./algorithms/frequency_filter.cpp)（来源 10.22/10.22/10.22.cpp:154-194）
- [三维 K-means 聚类（确定性学习版）](./case_studies/k_means.cpp)（来源 K_means/main.cpp; 10.22/10.22/10.22.cpp:460-586）
- [排列后前缀极差之和最小](./algorithms/min_prefix_range_sum.cpp)（来源 10.22/10.22/10.22.cpp:199-222）
- [缩短木棍得到最大三角形周长](./algorithms/triangle_shortening.cpp)（来源 10.22/10.22/10.22.cpp:107-127）
- [十字翻转：把小网格变为全零](./algorithms/grid_lights_out.cpp)（来源 10.22/10.22/10.22.cpp:234-288）

### [9_pen_exam/huawei/huawei.cpp](./originals/9_pen_exam/huawei/huawei.cpp.txt)

- [带收益的区间选择](./algorithms/weighted_intervals.cpp)（来源 9_pen_exam/huawei/huawei.cpp:58-115）
- [链表中首个未出现在另一字符串的字符](./data_structures/first_missing_character.cpp)（来源 9_pen_exam/huawei/huawei.cpp:261-304）

### [9_test/9_test/9_test.cpp](./originals/9_test/9_test/9_test.cpp.txt)

- [0/1 背包](./algorithms/zero_one_knapsack.cpp)（来源 9_test/9_test/9_test.cpp:378-393）
- [深拷贝：构造、拷贝构造与拷贝赋值](./basics/deep_copy.cpp)（来源 9_test/9_test/9_test.cpp:119-167）
- [sizeof、strlen、字节复制、布局与位域](./basics/memory_and_bit_fields.cpp)（来源 Char/main.cpp; pen_exam_8/pen_exam_8/_8_pen_exam.cpp:606-689; 9_test/9_test/9_test.cpp:183-204）
- [forward_list 与逗号整数解析](./basics/forward_list_and_csv.cpp)（来源 Project1/Project1/test1.cpp:72-87; 9_test/9_test/9_test.cpp:11-33）
- [长度至少 K 的子数组最大 GCD](./algorithms/max_gcd_subarray.cpp)（来源 9_test/9_test/9_test.cpp:298-325）
- [LeetCode 8：字符串转换整数 atoi](./algorithms/lc_008_string_to_integer.cpp)（来源 9_test/9_test/9_test.cpp:77-105）

### [byte_dancing/byte_dancing/byte_dancing.cpp](./originals/byte_dancing/byte_dancing/byte_dancing.cpp.txt)

- [树状数组：严格递减子序列计数](./data_structures/fenwick_decreasing_subsequences.cpp)（来源 byte_dancing/byte_dancing/byte_dancing.cpp:196-273）
- [ST 表：按子数组长度区间查询最大和](./data_structures/length_range_sparse_table.cpp)（来源 byte_dancing/byte_dancing/byte_dancing.cpp:95-193）
- [恰好翻转 K 次后的最小二进制字符串](./algorithms/binary_flip_exactly_k.cpp)（来源 byte_dancing/byte_dancing/byte_dancing.cpp:1-65）

### [Connect_sql_test/Connect_sql_test/main.cpp](./originals/Connect_sql_test/Connect_sql_test/main.cpp.txt)

仅问候程序，无数据库连接实现。保留原稿，不虚构数据库题目。

### [huawei/huawei/huawei.cpp](./originals/huawei/huawei/huawei.cpp.txt)

- [剪绳子：答案二分](./algorithms/rope_cutting.cpp)（来源 huawei/huawei/huawei.cpp:48-87）
- [墙壁位掩码：统计房间面积](./algorithms/wall_rooms.cpp)（来源 10.22/10.22/10.22.cpp:1-71; huawei/huawei/huawei.cpp:180-235）
- [LeetCode 75：颜色分类](./algorithms/lc_075_sort_colors.cpp)（来源 huawei/huawei/huawei.cpp:8-29）
- [LeetCode 2144：打折购买糖果的最小开销](./algorithms/lc_2144_candy_discount.cpp)（来源 huawei/huawei/huawei.cpp:98-123）
- [曼哈顿距离内的最大邻域人数](./algorithms/manhattan_neighbors.cpp)（来源 huawei/huawei/huawei.cpp:499-536）
- [修改至多一个数后的最长严格递增连续段](./algorithms/increasing_segment_one_change.cpp)（来源 huawei/huawei/huawei.cpp:319-425）

### [jingdong/jingdong/3.cpp](./originals/jingdong/jingdong/3.cpp.txt)

树颜色、频次与异或片段缺少输入和规则，见 PENDING.md。

### [mi/mi/mi.cpp](./originals/mi/mi/mi.cpp.txt)

- [区间异或与有界整数异或最大值](./algorithms/range_xor_maximum.cpp)（来源 mi/mi/mi.cpp:8-44）

### [pen_exam_8/pen_exam_8/_8_pen_exam.cpp](./originals/pen_exam_8/pen_exam_8/_8_pen_exam.cpp.txt)

- [LeetCode 210：课程表 II](./algorithms/lc_210_course_schedule_ii.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:111-168）
- [LeetCode 394：字符串解码](./algorithms/lc_394_decode_string.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:171-238）
- [左值、右值、move 与完美转发](./basics/move_and_forward.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:516-565）
- [虚析构与非虚成员函数](./basics/virtual_destructor.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:568-604）
- [sizeof、strlen、字节复制、布局与位域](./basics/memory_and_bit_fields.cpp)（来源 Char/main.cpp; pen_exam_8/pen_exam_8/_8_pen_exam.cpp:606-689; 9_test/9_test/9_test.cpp:183-204）
- [LeetCode 2380：二进制字符串重新安排顺序需要的时间](./algorithms/lc_2380_binary_rearrangement.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:79-108）
- [固定长度数据块去重与计数](./algorithms/block_counting.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:317-358）
- [互斥任务：数量优先、耗时次优](./algorithms/conflicting_jobs.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:418-479）
- [LeetCode 88：合并两个有序数组](./algorithms/lc_088_merge_sorted_arrays.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:251-273）
- [数字条重叠后的最短总长度](./algorithms/digit_string_overlap.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:14-45）
- [三数递增 K 次后的最大乘积](./algorithms/increment_three_max_product.cpp)（来源 pen_exam_8/pen_exam_8/_8_pen_exam.cpp:494-513）

### [Project1/Project1/test1.cpp](./originals/Project1/Project1/test1.cpp.txt)

- [异常处理与 weak_ptr 解除循环持有](./basics/exceptions_and_weak_ptr.cpp)（来源 Project1/Project1/test1.cpp:9-68）
- [线程入口与 join](./basics/thread_join.cpp)（来源 Project1/Project1/test1.cpp:108-169）
- [forward_list 与逗号整数解析](./basics/forward_list_and_csv.cpp)（来源 Project1/Project1/test1.cpp:72-87; 9_test/9_test/9_test.cpp:11-33）

### [_10_exam/_10_exam/_10_exam.cpp](./originals/_10_exam/_10_exam/_10_exam.cpp.txt)

行编辑命令 a/r 尚无实现，语义不明，见 PENDING.md。

### [_top_k_8/_top_k_8/_top_k_8.cpp](./originals/_top_k_8/_top_k_8/_top_k_8.cpp.txt)

- [LeetCode 3：无重复字符的最长子串](./algorithms/lc_003_longest_unique_substring.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:450-471）
- [LeetCode 70：爬楼梯](./algorithms/lc_070_climbing_stairs.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:214-227）
- [LeetCode 153：寻找旋转排序数组中的最小值](./algorithms/lc_153_rotated_minimum.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:264-275）
- [LeetCode 92：反转链表 II](./data_structures/lc_092_reverse_between.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:364-385）
- [LeetCode 25：K 个一组翻转链表](./data_structures/lc_025_reverse_k_group.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:389-418）
- [LeetCode 155：最小栈](./data_structures/lc_155_min_stack.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:334-359）
- [LeetCode 460：LFU 缓存（有序集合学习版）](./data_structures/lc_460_lfu_cache.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:120-191）
- [LeetCode 103：二叉树的锯齿形层序遍历](./data_structures/lc_103_zigzag_level_order.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:280-303）
- [LeetCode 236：二叉树的最近公共祖先](./data_structures/lc_236_lowest_common_ancestor.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:230-240）
- [LeetCode 34：在排序数组中查找元素的第一个和最后一个位置](./algorithms/lc_034_search_range.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:57-83）
- [LeetCode 5：最长回文子串](./algorithms/lc_005_longest_palindrome.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:545-570）
- [LeetCode 125：验证回文串](./algorithms/lc_125_valid_palindrome.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:306-331）
- [Fisher–Yates 洗牌](./algorithms/fisher_yates_shuffle.cpp)（来源 _top_k_8/_top_k_8/_top_k_8.cpp:420-446; Char/main.cpp:66-95）

## 不重复搬入的已有主题

| 旧稿中的主题 | 本仓学习入口 |
| --- | --- |
| 旋转数组查找、最长公共子序列 | [原有综合练习](../90_scratch_and_incomplete/mixed_topics/algorithm_practice.cpp) |
| LRU 缓存 | [缓存分类](../03_data_structures/cache) |
| 合并链表、删除指定值节点 | [链表分类](../03_data_structures/linked_list) |
| 二叉树普通层序遍历 | [树分类](../03_data_structures/tree) |
| 滑动窗口最大值：旧稿用堆，现有版用单调队列 | [单调队列分类](../03_data_structures/monotonic_queue) |
| 柱状图最大矩形 | [单调栈分类](../03_data_structures/monotonic_stack) |
| 打家劫舍 I/II | [动态规划分类](../04_algorithms/dynamic_programming) |
| 数独 | [数独回溯](../04_algorithms/backtracking/lc_037_shudoku_solver.cpp) |
| 普通二分、递归快排 | [二分](../04_algorithms/binary_search)、[排序](../04_algorithms/sorting) |
| 数组去重、频数统计、字符串大小写、容器基本用法 | [STL 学习指南](../02_stl/README.md) |

这里只建立重复主题入口，不表示本轮重新验证了这些旧目录；主 README 中原有的已知编译问题仍保持原记录。新目录里的非递归快排和其它排序对照是独立可运行版本。
