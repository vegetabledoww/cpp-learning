/*
LeetCode 215：数组中的第 K 大元素

返回排序后第 k 大的元素，重复数分别计数。保证 1 <= k <= nums.size()。

样例一：[3,2,1,5,6,4], k=2 -> 5，6 后面是 5。
样例二：[3,2,3,1,2,4,5,5,6], k=4 -> 4，两个 5 分别计数。
来源：../originals/Top_K_C++/demo.cpp:480-492（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
  public:
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int> q_max; //优先队列  大根堆（大的元素在最上面）
        for (const int num : nums)
        {
            q_max.push(num);
        }
        for (int i = 0; i < k - 1; i++)
        {
            q_max.pop();
        }
        return q_max.top();
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
    vector<int> a = {3, 2, 1, 5, 6, 4}, b = {3, 2, 3, 1, 2, 4, 5, 5, 6}, c = {-8};
    fail += check("sample1", s.findKthLargest(a, 2), 5);
    fail += check("sample2", s.findKthLargest(b, 4), 4);
    fail += check("single", s.findKthLargest(c, 1), -8);
    return fail ? 1 : 0;
}

/* 收获点：保留逐个入大根堆。修正原 O(n) 注释：时间 O(n log n + k log n)，空间 O(n)。 */
