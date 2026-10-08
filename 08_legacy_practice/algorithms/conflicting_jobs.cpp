/*
互斥任务：数量优先、耗时次优

恢复练习：n<=20 个任务，times 为各任务非负耗时，冲突对下标从 0 开始。选择两两不冲突的任务，使数量最多；数量并列时总耗时最少。返回 [数量,总耗时]。

样例一：times=[5,2,4],conflicts=[[0,1]] -> [2,6]，选任务1和2。
样例二：times=[5,2],conflicts=[[0,1]] -> [1,2]，数量相同选耗时2。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:418-479（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class JobSelector
{
    vector<int> times;
    vector<vector<bool>> conflict;
    vector<int> chosen;
    int ans = 0;
    long long cost = 0;
    void dfs(int i, long long time)
    {
        int n = times.size();
        if (int(chosen.size()) + n - i < ans)
            return;
        if (i == n)
        {
            int count = chosen.size();
            if (count > ans || (count == ans && time < cost))
            {
                ans = count;
                cost = time;
            }
            return;
        }
        dfs(i + 1, time);
        for (int u : chosen)
            if (conflict[u][i])
                return;
        chosen.push_back(i);
        dfs(i + 1, time + times[i]);
        chosen.pop_back();
    }

  public:
    vector<long long> solve(const vector<int> &values, const vector<vector<int>> &pairs)
    {
        times = values;
        int n = times.size();
        conflict.assign(n, vector<bool>(n));
        for (const auto &p : pairs)
            conflict[p[0]][p[1]] = conflict[p[1]][p[0]] = true;
        ans = 0;
        cost = 0;
        chosen.clear();
        dfs(0, 0);
        return {ans, cost};
    }
};

// 本地验证

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
    JobSelector s;
    fail += check("sample1", s.solve({5, 2, 4}, {{0, 1}}), vector<long long>{2, 6});
    fail += check("sample2 tie", s.solve({5, 2}, {{0, 1}}), vector<long long>{1, 2});
    fail += check("empty repeated call", s.solve({}, {}), vector<long long>{0, 0});
    fail += check("count before cost", s.solve({100, 100, 1}, {{0, 2}, {1, 2}}),
                  vector<long long>{2, 200});
    return fail ? 1 : 0;
}

/* 收获点：保留选/不选 DFS，清空跨调用状态、处理空任务并扩宽耗时。时间 O(n*2^n)，空间 O(n²) 冲突表及 O(n) 递归。 */
