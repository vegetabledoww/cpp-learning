/*
ST 表：按子数组长度区间查询最大和

恢复练习：给数组 a，查询 [l,r] 表示允许的连续子数组长度区间（不是下标区间），返回其中最大子数组和。1<=l<=r<=n<=2000，元素绝对值<=10^9。

样例一：a=[1,-2,3],query[1,2] -> 3，取长度1的 [3]。
样例二：a=[-5,-2],query[2,2] -> -7，只能取整个数组。
来源：byte_dancing/byte_dancing/byte_dancing.cpp:95-193（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class LengthQueries
{
    vector<vector<long long>> st;
    vector<int> lg;

  public:
    explicit LengthQueries(const vector<int> &a)
    {
        int n = a.size();
        vector<long long> best(n + 1, LLONG_MIN);
        for (int i = 0; i < n; ++i)
        {
            long long sum = 0;
            for (int j = i; j < n; ++j)
            {
                sum += a[j];
                best[j - i + 1] = max(best[j - i + 1], sum);
            }
        }
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i)
            lg[i] = lg[i / 2] + 1;
        st.assign(lg[n] + 1, vector<long long>(n + 1, LLONG_MIN));
        st[0] = best;
        for (int k = 1; k <= lg[n]; ++k)
            for (int i = 1; i + (1 << k) - 1 <= n; ++i)
                st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }
    long long query(int l, int r) const
    {
        int k = lg[r - l + 1];
        return max(st[k][l], st[k][r - (1 << k) + 1]);
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
    LengthQueries a({1, -2, 3}), b({-5, -2}), c({-8});
    fail += check("sample1", a.query(1, 2), 3LL);
    fail += check("sample2 negative regression", b.query(2, 2), -7LL);
    fail += check("full length", a.query(3, 3), 2LL);
    fail += check("single", c.query(1, 1), -8LL);
    LengthQueries d({1000000000, 1000000000, 1000000000});
    fail += check("wide sum", d.query(3, 3), 3000000000LL);
    return fail ? 1 : 0;
}

/* 收获点：修复原长度 n 未初始化为负无穷导致全负数组错误。ST 两块允许重叠，因为 max 幂等。预处理 O(n²+n log n)，查询 O(1)，空间 O(n log n)。 */
