/*
带收益的区间选择

按旧稿的严格端点规则恢复：任务有 start<=end、非负 profit；两个任务兼容需要前者 end < 后者 start（相等仍冲突）。求总收益最大值，可一个不选。

样例一：[(1,2,5),(3,4,6),(2,4,20)] -> 20，第三项比前两项合计11更好。
样例二：[(1,2,5),(2,3,100)] -> 100，端点相等不能同时选。
来源：9_pen_exam/huawei/huawei.cpp:58-115（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Business
{
    int start, end, profit;
};
bool compareBusiness(const Business &a, const Business &b)
{
    return a.end < b.end;
}
long long maxProfit(vector<Business> businesses)
{
    sort(businesses.begin(), businesses.end(), compareBusiness);
    int n = businesses.size();
    vector<long long> dp(n + 1);
    for (int i = 0; i < n; ++i)
    {
        int low = 0, high = i - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (businesses[mid].end < businesses[i].start)
                low = mid + 1;
            else
                high = mid - 1;
        }
        // high 是最后一个兼容任务；dp 下标表示考虑前多少项。
        dp[i + 1] = max(dp[i], dp[high + 1] + businesses[i].profit);
    }
    return dp[n];
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
    fail += check("sample1", maxProfit({{1, 2, 5}, {3, 4, 6}, {2, 4, 20}}), 20LL);
    fail += check("sample2 strict endpoint", maxProfit({{1, 2, 5}, {2, 3, 100}}), 100LL);
    fail += check("empty", maxProfit({}), 0LL);
    fail += check("all compatible", maxProfit({{5, 6, 9}, {1, 2, 3}, {3, 4, 7}}), 19LL);
    return fail ? 1 : 0;
}

/* 收获点：修复原二分声明语法错误与空输入 dp[0] 越界；收益累加用 long long。排序+二分 DP 时间 O(n log n)，空间 O(n)。 */
