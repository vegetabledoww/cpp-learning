/*
题目：用并查集合并集合并判断连通（入门示例）

有 n 个节点，编号 0 到 n-1，最初每个节点各自属于一个集合。
Unite(a,b)：合并 a、b 所在集合；确实合并返回 true，原本同组返回 false。
Connected(a,b)：判断二者是否在同一个集合。
Count()：返回当前集合数量。输入保证 n >= 0，节点编号合法。
只能合并，不支持删除连接或拆分集合；n=0 时只查询 Count()。

示例一：n=5，合并 (0,1)、(1,2)
输出：Connected(0,2)=true，Connected(0,3)=false，Count()=3
解释：最终分组为 {0,1,2}、{3}、{4}。

示例二：n=3，合并 (0,1)、(1,0)
输出：两次合并依次返回 true、false，Count()=2
解释：重复合并不改变分组，不应再次减少集合数量。
*/
#include <iostream>
#include <vector>
using namespace std;

class UnionFind
{
private:
    vector<int> parent;
    vector<int> groupSize;
    int groupCount;

public:
    UnionFind(int n) : parent(n), groupSize(n, 1), groupCount(n)
    {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int Find(int x)
    {
        // 根节点的父亲是自己；查找时顺便把沿途节点直接连到根。
        if (parent[x] != x) parent[x] = Find(parent[x]);
        return parent[x];
    }

    bool Unite(int a, int b)
    {
        int rootA = Find(a);
        int rootB = Find(b);
        if (rootA == rootB) return false;
        // 小集合挂到大集合的根上，避免树轻易变成长链。
        if (groupSize[rootA] < groupSize[rootB])
        {
            int temp = rootA;
            rootA = rootB;
            rootB = temp;
        }
        parent[rootB] = rootA;
        groupSize[rootA] += groupSize[rootB];
        groupCount--;
        return true;
    }

    bool Connected(int a, int b) { return Find(a) == Find(b); }
    int Count() { return groupCount; }
};

int Check(const char *name, int actual, int expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    UnionFind uf(5);
    failed += Check("initial count", uf.Count(), 5);
    failed += Check("initial disconnected", uf.Connected(0,2), false);
    failed += Check("merge 0 1", uf.Unite(0,1), true);
    failed += Check("merge 1 2", uf.Unite(1,2), true);
    failed += Check("transitive connection", uf.Connected(0,2), true);
    failed += Check("disconnected", uf.Connected(0,3), false);
    failed += Check("three groups", uf.Count(), 3);
    failed += Check("self merge", uf.Unite(3,3), false);
    failed += Check("merge 3 4", uf.Unite(3,4), true);
    failed += Check("join smaller to larger", uf.Unite(4,2), true);
    failed += Check("one group", uf.Count(), 1);
    for (int i = 0; i < 5; i++)
        failed += Check("all connected", uf.Connected(0,i), true);

    UnionFind repeated(3);
    failed += Check("first merge", repeated.Unite(0,1), true);
    failed += Check("repeated merge", repeated.Unite(1,0), false);
    failed += Check("count unchanged", repeated.Count(), 2);
    UnionFind single(1);
    failed += Check("single self connection", single.Connected(0,0), true);
    failed += Check("single count", single.Count(), 1);
    UnionFind empty(0);
    failed += Check("empty count", empty.Count(), 0);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：判断同组要比较 Find 的根，不能直接比较 parent 的值。
合并连接两个根；只有合并成功才减少集合数量。groupSize 只在根节点上有效。
路径压缩 + 按大小合并后，每次操作均摊 O(alpha(n))，可以理解为几乎常数。
初始化时间和存储空间 O(n)；按大小合并保证单次递归深度至多 O(log n)。
*/
