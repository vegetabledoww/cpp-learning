/*
树状数组：严格递减子序列计数

按旧代码的查询方向恢复：统计所有非空、严格递减子序列，按下标选择不同即为不同子序列，结果模 1000000007。空输入为0。

样例一：[3,2,1] -> 7，所有非空子序列都严格递减。
样例二：[2,2] -> 2，相等不能连接，只能选两个单元素之一。
来源：byte_dancing/byte_dancing/byte_dancing.cpp:196-273（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int mod = 1000000007;
class BIT
{
    vector<int> tree;

  public:
    explicit BIT(int n) : tree(n + 1)
    {
    }
    void update(int idx, int val)
    {
        for (; idx < int(tree.size()); idx += idx & -idx)
            tree[idx] = (tree[idx] + val) % mod;
    }
    int query(int idx) const
    {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res = (res + tree[idx]) % mod;
        return res;
    }
};
int countDecreasing(const vector<int> &a)
{
    vector<int> values = a;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    int m = values.size();
    BIT bit(m);
    for (int x : a)
    {
        int idx = lower_bound(values.begin(), values.end(), x) - values.begin() + 1;
        // 严格更大的旧值才能接上 x；减去 <=x 的前缀。
        int sum = (bit.query(m) - bit.query(idx) + mod) % mod;
        bit.update(idx, (sum + 1) % mod);
    }
    return bit.query(m);
}
int bruteDecreasing(const vector<int> &a)
{
    int answer = 0, n = a.size();
    for (int mask = 1; mask < (1 << n); ++mask)
    {
        bool ok = true, first = true;
        int prev = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i))
            {
                if (!first && prev <= a[i])
                    ok = false;
                first = false;
                prev = a[i];
            }
        if (ok)
            ++answer;
    }
    return answer;
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
    fail += check("sample1", countDecreasing({3, 2, 1}), 7);
    fail += check("sample2", countDecreasing({2, 2}), 2);
    fail += check("empty", countDecreasing({}), 0);
    bool same = true;
    for (int code = 0; code < 729; ++code)
    {
        int x = code;
        vector<int> a(6);
        for (int &v : a)
        {
            v = x % 3;
            x /= 3;
        }
        if (countDecreasing(a) != bruteDecreasing(a))
            same = false;
    }
    fail += check("729 small arrays vs enumeration", same, true);
    return fail ? 1 : 0;
}

/* 收获点：离散化保证下标从1开始，BIT 的0下标不能 update，否则死循环。保留原递减方向，不能把此实现误称递增计数。时间 O(n log n)，空间 O(n)。 */
