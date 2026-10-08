/*
LeetCode 210：课程表 II

课程编号 0..numCourses-1，先修关系 [a,b] 表示先学 b 才能学 a。返回任一完整合法顺序，存在有向环返回空数组。

样例一：numCourses=2, prerequisites=[[1,0]] -> [0,1]。
样例二：numCourses=2, prerequisites=[[1,0],[0,1]] -> []，形成环。
来源：../originals/pen_exam_8/pen_exam_8/_8_pen_exam.cpp:111-168（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  private:
    // 存储有向图
    vector<vector<int>> edges;
    // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
    vector<int> visited;
    // 用数组来模拟栈，下标 0 为栈底，n-1 为栈顶
    vector<int> result;
    // 判断有向图中是否有环
    bool valid = true;

  public:
    void dfs(int u)
    {
        // 将节点标记为「搜索中」
        visited[u] = 1;
        // 搜索其相邻节点
        // 只要发现有环，立刻停止搜索
        for (int v : edges[u])
        {
            // 如果「未搜索」那么搜索相邻节点
            if (visited[v] == 0)
            {
                dfs(v);
                if (!valid)
                {
                    return;
                }
            }
            // 如果「搜索中」说明找到了环
            else if (visited[v] == 1)
            {
                valid = false;
                return;
            }
        }
        // 将节点标记为「已完成」
        visited[u] = 2;
        // 将节点入栈
        result.push_back(u);
    }

    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        edges.assign(numCourses, {});
        result.clear();
        valid = true; // 修复：重复调用时所有状态都要复位
        visited.assign(numCourses, 0);
        for (const auto &info : prerequisites)
        {
            edges[info[1]].push_back(info[0]);
        }
        // 每次挑选一个「未搜索」的节点，开始进行深度优先搜索
        for (int i = 0; i < numCourses && valid; ++i)
        {
            if (!visited[i])
            {
                dfs(i);
            }
        }
        if (!valid)
        {
            return {};
        }
        // 如果没有环，那么就有拓扑排序
        // 注意下标 0 为栈底，因此需要将数组反序输出
        reverse(result.begin(), result.end());
        return result;
    }
};

// 以下仅为本地样例验证；提交平台时保留上面的题解即可。

template <class T> void show(const T &value)
{
    cout << value;
}
template <class T> void show(const vector<T> &values)
{
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i)
            cout << ',';
        show(values[i]);
    }
    cout << ']';
}
template <class T> int check(const char *name, const T &actual, const T &expected)
{
    cout << name << " expected=";
    show(expected);
    cout << " actual=";
    show(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int fail = 0;
    Solution s;
    vector<vector<int>> a = {{1, 0}}, b = {{1, 0}, {0, 1}}, c = {};
    fail += check("sample1", s.findOrder(2, a), vector<int>{0, 1});
    fail += check("cycle", s.findOrder(2, b), vector<int>{});
    fail += check("reuse after cycle", s.findOrder(1, c), vector<int>{0});
    vector<vector<int>> d = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    auto order = s.findOrder(4, d);
    vector<int> pos(4, -1);
    bool ok = order.size() == 4;
    for (size_t i = 0; i < order.size(); ++i)
    {
        if (order[i] < 0 || order[i] >= 4 || pos[order[i]] != -1)
            ok = false;
        else
            pos[order[i]] = i;
    }
    for (const auto &e : d)
        if (pos[e[1]] >= pos[e[0]])
            ok = false;
    fail += check("diamond ordering", ok, true);
    return fail ? 1 : 0;
}

/* 收获点：0 未访问、1 递归中、2 完成；遇到 1 说明环，后序逆序即拓扑序。更正原 207 标注。时间 O(V+E)，空间 O(V+E)。 */
