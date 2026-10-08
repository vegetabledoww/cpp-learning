/*
LeetCode 1673：最具竞争力的子序列

从 nums 按原顺序选 k 个数，使结果字典序最小；保证 0 <= k <= n。

样例一：[3,5,2,6], k=2 -> [2,6]，首位最小且可补足。
样例二：[2,4,3,3,5,4,9,6], k=4 -> [2,3,3,4]。
来源：../originals/new_function/test_function.cpp:725-738（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    vector<int> mostCompetitive(vector<int> &nums, int k)
    {
        vector<int> res;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            while (!res.empty() && n - i + int(res.size()) > k && res.back() > nums[i])
            {
                res.pop_back();
            }
            res.push_back(nums[i]);
        }
        res.resize(k);
        return res;
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
    vector<int> a = {3, 5, 2, 6}, b = {2, 4, 3, 3, 5, 4, 9, 6};
    fail += check("sample1", s.mostCompetitive(a, 2), vector<int>{2, 6});
    fail += check("sample2", s.mostCompetitive(b, 4), vector<int>{2, 3, 3, 4});
    fail += check("zero", s.mostCompetitive(a, 0), vector<int>{});
    fail += check("all", s.mostCompetitive(a, 4), a);
    return fail ? 1 : 0;
}

/* 收获点：仅在剩余元素足够补齐时弹出更大的尾元素。时间 O(n)，空间 O(n)。 */
