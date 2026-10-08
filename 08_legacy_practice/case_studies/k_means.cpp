/*
三维 K-means 聚类（确定性学习版）

有限三维点集合，1<=k<=点数，以前 k 个点作为初始中心，重复最近中心分配和均值更新。距离并列选下标小的簇；空簇保留旧中心。最多迭代 maxIterations>=1 次，返回中心是否达到 tolerance>=0 的收敛阈值。它是局部聚类算法，不保证全局最优。

样例一：点 [(0,0,0),(10,0,0),(2,0,0),(12,0,0)],k=2 -> 中心 x=[1,11]，每簇两个点。
样例二：点 [(0,0,0),(0,0,0)],k=2 -> 中心仍为0，第二簇可为空，不做除零。
来源：K_means/main.cpp; 10.22/10.22/10.22.cpp:460-586（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
using namespace std;

struct Point
{
    double x, y, z;
};
struct Cluster
{
    Point center;
    vector<Point> points;
};
double Distance(const Point &a, const Point &b)
{
    return hypot(hypot(a.x - b.x, a.y - b.y), a.z - b.z);
}
void UpdateClusterCenter(Cluster &cluster)
{
    if (cluster.points.empty())
        return;
    Point sum = {0, 0, 0};
    for (const auto &p : cluster.points)
    {
        sum.x += p.x;
        sum.y += p.y;
        sum.z += p.z;
    }
    double count = cluster.points.size();
    cluster.center = {sum.x / count, sum.y / count, sum.z / count};
}
bool KMeans(const vector<Point> &data, int k, vector<Cluster> &clusters, int maxIterations = 100,
            double tolerance = 1e-9)
{
    if (k <= 0 || k > int(data.size()) || maxIterations <= 0 || tolerance < 0)
        throw invalid_argument("invalid KMeans parameters");
    clusters.clear();
    for (int i = 0; i < k; ++i)
        clusters.push_back({data[i], {}});
    for (int step = 0; step < maxIterations; ++step)
    {
        for (auto &c : clusters)
            c.points.clear();
        for (const auto &p : data)
        {
            int best = 0;
            for (int i = 1; i < k; ++i)
                if (Distance(p, clusters[i].center) < Distance(p, clusters[best].center))
                    best = i;
            clusters[best].points.push_back(p);
        }
        double shift = 0;
        for (auto &c : clusters)
        {
            Point old = c.center;
            UpdateClusterCenter(c);
            shift = max(shift, Distance(old, c.center));
        }
        if (shift <= tolerance)
            return true;
    }
    return false; // 保留最后一轮结果，但不能声称已收敛。
}

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
    vector<Cluster> c;
    bool ok = KMeans({{0, 0, 0}, {10, 0, 0}, {2, 0, 0}, {12, 0, 0}}, 2, c);
    fail += check("sample1 converged", ok, true);
    fail += check("sample1 centers", vector<double>{c[0].center.x, c[1].center.x},
                  vector<double>{1, 11});
    fail += check("sample1 sizes", vector<int>{int(c[0].points.size()), int(c[1].points.size())},
                  vector<int>{2, 2});
    ok = KMeans({{0, 0, 0}, {0, 0, 0}}, 2, c);
    fail +=
        check("sample2 empty cluster", ok && c[1].points.empty() && isfinite(c[1].center.x), true);
    bool rejected = false;
    try
    {
        KMeans({{0, 0, 0}}, 2, c);
    }
    catch (const invalid_argument &)
    {
        rejected = true;
    }
    fail += check("k larger than n", rejected, true);
    fail += check("iteration limit",
                  KMeans({{0, 0, 0}, {10, 0, 0}, {2, 0, 0}, {12, 0, 0}}, 2, c, 1), false);
    fail += check("all three coordinates converge", KMeans({{1, 2, 3}, {3, 4, 5}}, 1, c), true);
    fail +=
        check("three dimensional mean", vector<double>{c[0].center.x, c[0].center.y, c[0].center.z},
              vector<double>{2, 3, 4});
    fail += check("distance remains above 20 but converges", KMeans({{0, 0, 0}, {100, 0, 0}}, 1, c),
                  true);
    fail += check("large spread mean", c[0].center.x, 50.0);
    return fail ? 1 : 0;
}

/* 收获点：合并重复 K-means 原稿；修复 k 越界、空簇除零、重复调用累加簇，以及用总距离>20导致不终止。每轮 O(nk)，最多 I 轮 O(Ink)，空间 O(n+k)。在上限处返回 false，结果是最后分组及其均值。 */
