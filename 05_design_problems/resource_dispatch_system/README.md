# 资源请求分发系统

[problem_template.cpp](./problem_template.cpp) 保留题面、函数签名和样例，适合自己手敲；[solution.cpp](./solution.cpp) 是使用 `set<pair<int, int>>` 的完整题解和可运行测试。

原题平台和完整约束没有提供，下面的规则根据现有代码还原：

1. 每个请求只能分配给一台剩余容量不小于请求量的机器。
2. 优先选择“剩余容量最小但足够”的机器，避免浪费更大的机器。
3. 剩余容量相同时，选择下标更小的机器。
4. 分配成功后扣除请求量；失败时返回 `-1`，所有机器状态不变。

## 为什么使用 set<pair<int, int>>

集合中保存 `(剩余容量, 机器下标)`。`pair` 默认先比较 `first`，相同时再比较 `second`，所以 `set` 会自动按“容量优先、下标次之”排序。

```cpp
auto position = machines.lower_bound({request, -1});
```

`lower_bound` 找到第一个不小于 `(request, -1)` 的元素。因为机器下标都不小于 0，这正好就是容量至少为 `request` 的第一台机器，也就是满足题目两级优先规则的答案。

机器的剩余容量发生变化时，要先从 `set` 删除旧记录，再插入新记录。`set` 中元素同时也是排序键，不能直接修改。

## 相比原来的 33 个优先队列

原代码先把容量除以 32，再放进固定的 33 个桶。只有“所有容量和请求都是 32 的倍数，并且容量不超过 1024”时，这种分桶才准确且不会越界。它还在每个队列中重复保存了桶编号，并需要自定义比较器。

当前实现直接保存真实容量：

- 不要求数值是 32 的倍数；
- 没有固定的最大容量下标；
- 不需要仿函数或 lambda；
- 两台机器容量相同也不会冲突，因为它们的下标不同，整个 `pair` 仍然不同。

设机器数为 `N`，请求数为 `M`，建表时间为 `O(N log N)`，每个请求的查找、删除和重新插入都是 `O(log N)`，总时间复杂度为 `O((N + M) log N)`，额外空间复杂度为 `O(N)`。

## 编译运行

从仓库根目录执行：

```powershell
New-Item -ItemType Directory -Force .\build | Out-Null
g++ -std=c++17 -Wall -Wextra -pedantic -Werror .\05_design_problems\resource_dispatch_system\solution.cpp -o .\build\resource_dispatch_system.exe
.\build\resource_dispatch_system.exe
```
