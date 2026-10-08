/*
LeetCode 11：盛最多水的容器

给出非负高度数组，两条竖线和横轴组成容器，返回最大面积。至少两条线，面积在 int 范围。

样例一：[1,8,6,2,5,4,8,3,7] -> 49，下标 1 和 8，宽 7、高 7。
样例二：[1,1] -> 1，宽 1、高 1。
来源：../originals/new_function/test_function.cpp:484-502（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int maxArea(vector<int> &ht)
    {
        int i = 0, j = ht.size() - 1, res = 0; //也可以为认定其为双指针法
        while (i < j)
        {
            //更新最大容量
            int cap = min(ht[i], ht[j]) * (j - i); // 宽度是两下标之差
            res = max(res, cap);
            if (ht[i] < ht[j]) //左侧板子较低
            {
                i++;
            }
            else
            {
                j--;
            }
        }
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
    vector<int> a = {1, 8, 6, 2, 5, 4, 8, 3, 7}, b = {1, 1}, c = {0, 0};
    fail += check("sample1", s.maxArea(a), 49);
    fail += check("width regression", s.maxArea(b), 1);
    fail += check("zero", s.maxArea(c), 0);
    return fail ? 1 : 0;
}

/* 收获点：较高边不动，移动较矮边才可能提高面积。修正 j-1 为 j-i。时间 O(n)，空间 O(1)。 */
