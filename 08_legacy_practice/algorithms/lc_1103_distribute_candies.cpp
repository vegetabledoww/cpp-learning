/*
LeetCode 1103：分糖果 II

n 人排一圈，依次发 1,2,3,... 颗糖，轮流发放；剩余不足就全部发给当前人。返回每人总数。candies>=0，n>=1，candies<=10^9。

样例一：candies=7,n=4 -> [1,2,3,1]，最后只剩 1。
样例二：candies=10,n=3 -> [5,2,3]，第四次回到第一个人。
来源：../originals/new_function/test_function.cpp:810-829（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    vector<int> distributeCandies(int candies, int num_people)
    {
        vector<int> ans(num_people);
        int i = 0, num = 1;
        while (candies > 0)
        {
            int take = min(num, candies);
            ans[i] += take;
            candies -= take;
            ++num;
            i = (i + 1) % num_people; // 修复：真正更新下标，并只发剩余数量。
        }
        return ans;
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
    fail += check("sample1", s.distributeCandies(7, 4), vector<int>{1, 2, 3, 1});
    fail += check("sample2", s.distributeCandies(10, 3), vector<int>{5, 2, 3});
    fail += check("single", s.distributeCandies(10, 1), vector<int>{10});
    fail += check("zero", s.distributeCandies(0, 3), vector<int>{0, 0, 0});
    return fail ? 1 : 0;
}

/* 收获点：循环下标用取余，实际发放量不能超过剩余糖。时间 O(n+sqrt(candies))，空间 O(n)。 */
