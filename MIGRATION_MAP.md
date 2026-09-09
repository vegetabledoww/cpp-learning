# 旧路径与新路径对照表

本表只记录本次整理涉及的源码和头文件。`29project` 整体保持原样，没有迁移记录。

## 根目录与基础示例

| 旧路径 | 新路径 |
| --- | --- |
| `binary_search.cpp` | `04_algorithms/binary_search/binary_search_demo.cpp` |
| `lru.cpp` | `03_data_structures/cache/lru_cache_demo.cpp` |
| `quicksort.cpp` | `04_algorithms/sorting/quicksort_optimized.cpp` |
| `data_strcture/map_example.cpp` | `02_stl/associative_containers/map_unordered_map_example.cpp` |
| `data_strcture/pair_example.cpp` | `02_stl/utility/pair_example.cpp` |
| `C++/1.cpp` | `04_algorithms/string_parsing/mac_address_counter.cpp` |
| `C++/2.cpp` | `05_design_problems/application_usage/solution_verified.cpp` |

## 后续算法归类

| 旧路径 | 新路径 |
| --- | --- |
| `04_algorithms/yuanyin.cpp` | `04_algorithms/sliding_window/longest_flawed_vowel_substring.cpp` |

## 原 design 目录

| 旧路径 | 新路径 |
| --- | --- |
| `design/app_pro_status.cpp` | `05_design_problems/application_usage/problem_and_examples.cpp` |
| `design/do.cpp` | `05_design_problems/application_usage/solution.cpp` |
| `design/arp_missing.cpp` | `05_design_problems/arp_system/solution.cpp` |

## 原 build 目录中的源码

| 旧路径 | 新路径 |
| --- | --- |
| `build/huawei.cpp` | `04_algorithms/graph_and_bfs/huawei_maze_bfs.cpp` |
| `build/min_heap.cpp` | `02_stl/container_adapters/min_heap_custom_comparator.cpp` |
| `build/single_figure.cpp` | `04_algorithms/backtracking/lc_037_sudoku_solver.cpp` |
| `build/smart_ptr.cpp` | `01_cpp_basics/memory_management/smart_pointer_demo.cpp` |
| `build/singlemode.cpp` | `06_design_patterns/singleton/main.cpp` |
| `build/singlemode.h` | `06_design_patterns/singleton/singleton_a.h` |
| `build/B.h` | `06_design_patterns/singleton/singleton_b.h` |
| `build/8.23kuaishou.cpp` | `90_scratch_and_incomplete/mixed_topics/kuaishou_2023_08_23.cpp` |
| `build/head.h` | `90_scratch_and_incomplete/mixed_topics/common_headers.h` |
| `build/redo/test.cpp` | `90_scratch_and_incomplete/mixed_topics/algorithm_practice.cpp` |
| `build/redo/test.h` | `90_scratch_and_incomplete/mixed_topics/tree_node.h` |
| `build/redo/compare1.cpp` | `90_scratch_and_incomplete/incomplete/empty_compare1.cpp` |

## 原 LeetCode 目录

| 旧路径 | 新路径 |
| --- | --- |
| `leetcode/BFS/LC102.cpp` | `03_data_structures/tree/lc_102_binary_tree_level_order.cpp` |
| `leetcode/BFS/LCP09.cpp` | `04_algorithms/graph_and_bfs/lcp_09_min_jump.cpp` |
| `leetcode/DP/LC10.cpp` | `04_algorithms/dynamic_programming/lc_010_regex_match.cpp` |
| `leetcode/DP/LC72.cpp` | `04_algorithms/dynamic_programming/lc_072_edit_distance.cpp` |
| `leetcode/DP/LC121.cpp` | `04_algorithms/dynamic_programming/lc_121_stock_profit.cpp` |
| `leetcode/DP/LC198.cpp` | `04_algorithms/dynamic_programming/lc_198_house_robber.cpp` |
| `leetcode/DP/LC213.cpp` | `04_algorithms/dynamic_programming/lc_213_house_robber_ii.cpp` |
| `leetcode/DP/LC2560.cpp` | `04_algorithms/binary_search/lc_2560_house_robber_iv.cpp` |
| `leetcode/DP/LC332.cpp` | `04_algorithms/dynamic_programming/lc_322_coin_change.cpp` |
| `leetcode/DP/LC337.cpp` | `04_algorithms/dynamic_programming/lc_337_house_robber_iii.cpp` |
| `leetcode/LC146.cpp` | `03_data_structures/cache/lc_146_lru_cache.cpp` |
| `leetcode/ListNode/LC21.cpp` | `03_data_structures/linked_list/lc_021_merge_two_sorted_lists.cpp` |
| `leetcode/ListNode/LRC136.cpp` | `03_data_structures/linked_list/lcr_136_delete_list_node.cpp` |
| `leetcode/order/leetcode347.cpp` | `02_stl/priority_queue/lc_347_top_k_frequent.cpp` |
| `leetcode/priority_queue.cpp` | `02_stl/container_adapters/priority_queue_custom_comparator.cpp` |
| `leetcode/stack_like/LC735.cpp` | `03_data_structures/stack/lc_735_asteroid_collision.cpp` |
| `leetcode/stack_like/LC85.cpp` | `03_data_structures/monotonic_stack/lc_085_maximal_rectangle.cpp` |
| `leetcode/stack_like/quick_sort.cpp` | `04_algorithms/sorting/quicksort_lomuto.cpp` |

`LC332.cpp` 中实现的是 LeetCode 322“零钱兑换”，因此整理时更正为 `lc_322_coin_change.cpp`。

## 健康运动案例

| 旧路径 | 新路径 |
| --- | --- |
| `sim_test/do.cpp` | `07_case_studies/health_exercise/src/solution_readable.cpp` |
| `sim_test/do_better.cpp` | `07_case_studies/health_exercise/src/solution_optimized.cpp` |
| `sim_test/健康运动步数统计.cpp` | `07_case_studies/health_exercise/src/solution_reference.cpp` |
| `sim_test/健康运动步数统计_思路说明.md` | `07_case_studies/health_exercise/docs/approach.md` |
| `sim_test/健康运动步数统计_计算流程草图.png` | `07_case_studies/health_exercise/assets/calculation_flow.png` |
| `sim_test/健康运动步数统计_计算流程草图.svg` | `07_case_studies/health_exercise/assets/calculation_flow.svg` |

## 服务器空闲案例

| 旧路径 | 新路径 |
| --- | --- |
| `07_case_studies/server_busy.cpp` | `07_case_studies/server_busy/server_busy.cpp` |
| `07_case_studies/server_busy_optimized.cpp` | `07_case_studies/server_busy/server_busy_optimized.cpp` |

旧 `.exe` 曾按原相对路径归档，现已在用户确认后统一删除；源码均保留。
