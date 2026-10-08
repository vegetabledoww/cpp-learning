/*
LeetCode 27：移除元素

原地移除 nums 中等于 val 的元素，返回剩余数量 k，前 k 项是保留元素，后面内容不作要求。要求 O(1) 额外空间。

样例一：[3,2,2,3],val=3 -> k=2，前两项 [2,2]。
样例二：[0,1,2,2,3,0,4,2],val=2 -> k=5，前五项 [0,1,3,0,4]。
来源：new_function/test_function.cpp:679-694（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    int removeElement(vector<int> &nums, int val)
    {
        int k = 0;
        for (int num : nums)
            if (num != val)
                nums[k++] = num;
        return k;
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
    Solution s;
    vector<int> a = {3, 2, 2, 3}, b = {0, 1, 2, 2, 3, 0, 4, 2}, c = {};
    int k = s.removeElement(a, 3);
    fail += check("sample1 count", k, 2);
    a.resize(k);
    fail += check("sample1 prefix", a, vector<int>{2, 2});
    k = s.removeElement(b, 2);
    fail += check("sample2 count", k, 5);
    b.resize(k);
    fail += check("sample2 prefix", b, vector<int>{0, 1, 3, 0, 4});
    fail += check("empty", s.removeElement(c, 1), 0);
    return fail ? 1 : 0;
}

/* 收获点：修正原稿辅助数组不符合原地空间要求；写指针不超过读指针。时间 O(n)，额外空间 O(1)。 */
