/*
题目大意：
给定一组进程信息 processes，每条进程为 (appName, userName, cpuUsed, memUsed)，
表示某用户运行的某应用占用的 CPU 与内存。再给定：
  - sortRules：排序规则列表，元素为 "cpuUsed" 或 "memUsed"，
    按列表顺序依次作为排序关键字（靠前的优先级高），均为降序；
  - selectedUsers：被选中的用户集合，只统计这些用户的进程。

要求：
  1. 只考虑 selectedUsers 中用户的进程；
  2. 对同一 appName 的所有进程，将其 cpuUsed 与 memUsed 分别累加；
  3. 按 sortRules 中的顺序依次比较 (cpuUsed / memUsed) 进行降序排序；
     若所有指定规则都相等，则按应用名升序作为 tie-breaker；
  4. 返回排序后的前 3 个应用名（不足 3 个则全部返回）。

示例：
  processes = {("appA","u1",100,10), ("appA","u2",200,20),
               ("appB","u1",200,5), ("appC","u2",100,100),
               ("appD","u1",50,50)}
  sortRules  = {"cpuUsed"}
  selectedUsers = {"u1","u2"}
  -> appA(cpu=300) > appB(cpu=200) > appC(cpu=100) > appD(cpu=50)
  -> 返回 ["appA","appB","appC"]

实现思路：
  - 用 unordered_set 存放选中用户，O(1) 判断是否计入；
  - 用 unordered_map<app, pair<cpu,mem>> 做累加聚合；
  - 将聚合结果拷贝到 vector 后调用 sort，comparator 内按 sortRules
    顺序逐项比较，全部相等再按应用名升序；
  - 取前 3 个应用名返回。

复杂度：
  - 时间：O(n + m log m)，n 为进程数（聚合），m 为不同应用数（排序）；
  - 空间：O(m)，存放聚合结果与输出。
*/

#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<string> GetTop3App(const vector<tuple<string, string, int, int>>& processes,
                              const vector<string>& sortRules,
                              const vector<string>& selectedUsers) {
        unordered_set<string> userSet(selectedUsers.begin(), selectedUsers.end());// 用集合去重，存放选中的用户
        unordered_map<string, pair<int, int>> agg; // app -> {cpu, mem}
        for (const auto& p : processes) {
            if (!userSet.count(get<1>(p))) continue;// 仅统计选中用户的进程
            agg[get<0>(p)].first  += get<2>(p);// 累加 CPU 占用
            agg[get<0>(p)].second += get<3>(p);// 累加内存占用
        }
        vector<pair<string, pair<int, int>>> apps(agg.begin(), agg.end());//用加和之后的结果进行后续的操作
        sort(apps.begin(), apps.end(), [&](const auto& a, const auto& b) {// 排序规则：先按 sortRules 中的顺序，再按应用名升序
            for (const auto& rule : sortRules) {//这里妙用，其实是双重排序，sortRules 中的顺序，即先按 cpuUsed 排序，再按 memUsed 排序
                if (rule == "cpuUsed" && a.second.first != b.second.first)
                    return a.second.first > b.second.first;
                if (rule == "memUsed" && a.second.second != b.second.second)
                    return a.second.second > b.second.second;
            }
            return a.first < b.first; // tie-breaker: 应用名升序
        });

        vector<string> res;
        for (int i = 0, n = min(int(apps.size()), 3); i < n; ++i)
            res.push_back(apps[i].first);
        return res;
    }
};

// 辅助：打印 vector<string>
ostream& operator<<(ostream& os, const vector<string>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) os << ", ";
        os << v[i];
    }
    return os << "]";
}

int main()
{
    Solution sol;

    // 测试 1：按 cpuUsed 排序，选中所有用户
    // appA cpu=300, appB cpu=200, appC cpu=100, appD cpu=50
    {
        vector<tuple<string, string, int, int>> procs = {
            {"appA", "u1", 100, 10},
            {"appA", "u2", 200, 20},
            {"appB", "u1", 200, 5},
            {"appC", "u2", 100, 100},
            {"appD", "u1", 50, 50},
        };
        vector<string> rules = {"cpuUsed"};
        vector<string> users = {"u1", "u2"};
        auto r = sol.GetTop3App(procs, rules, users);
        cout << "test1: " << r << endl;
        assert((r == vector<string>{"appA", "appB", "appC"}));
    }

    // 测试 2：按 memUsed 排序
    // appC mem=100, appA mem=30, appD mem=50 -> 顺序 appC > appD > appA
    {
        vector<tuple<string, string, int, int>> procs = {
            {"appA", "u1", 100, 10},
            {"appA", "u2", 200, 20},
            {"appB", "u1", 200, 5},
            {"appC", "u2", 100, 100},
            {"appD", "u1", 50, 50},
        };
        vector<string> rules = {"memUsed"};
        vector<string> users = {"u1", "u2"};
        auto r = sol.GetTop3App(procs, rules, users);
        cout << "test2: " << r << endl;
        assert((r == vector<string>{"appC", "appD", "appA"}));
    }

    // 测试 3：用户过滤——只选 u1，未选中用户的进程不计入
    // appA(u1)=100, appB(u1)=200, appD(u1)=50, appC 只有 u2 被过滤掉
    {
        vector<tuple<string, string, int, int>> procs = {
            {"appA", "u1", 100, 10},
            {"appA", "u2", 200, 20},
            {"appB", "u1", 200, 5},
            {"appC", "u2", 100, 100},
            {"appD", "u1", 50, 50},
        };
        vector<string> rules = {"cpuUsed"};
        vector<string> users = {"u1"};
        auto r = sol.GetTop3App(procs, rules, users);
        cout << "test3: " << r << endl;
        assert((r == vector<string>{"appB", "appA", "appD"}));
    }

    // 测试 4：tie-breaker——CPU 相同则按应用名升序
    // appB/appC/appD 的 cpu 都是 100，应用名升序 -> appB, appC, appD
    {
        vector<tuple<string, string, int, int>> procs = {
            {"appD", "u1", 100, 1},
            {"appC", "u1", 100, 2},
            {"appB", "u1", 100, 3},
            {"appA", "u1", 50, 999},
        };
        vector<string> rules = {"cpuUsed"};
        vector<string> users = {"u1"};
        auto r = sol.GetTop3App(procs, rules, users);
        cout << "test4: " << r << endl;
        assert((r == vector<string>{"appB", "appC", "appD"}));
    }

    // 测试 5：应用数少于 3，返回全部
    {
        vector<tuple<string, string, int, int>> procs = {
            {"onlyApp", "u1", 10, 10},
        };
        vector<string> rules = {"cpuUsed", "memUsed"};
        vector<string> users = {"u1"};
        auto r = sol.GetTop3App(procs, rules, users);
        cout << "test5: " << r << endl;
        assert((r == vector<string>{"onlyApp"}));
    }

    cout << "All tests passed." << endl;
    return 0;
}