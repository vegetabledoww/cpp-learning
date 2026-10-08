/*
LeetCode 88：合并两个有序数组

nums1 长度 m+n，前 m 项有效且非递减，nums2 有 n 个非递减元素。将二者合并写入 nums1。本版保留原稿辅助数组思路。

样例一：nums1=[1,2,3,0,0,0],m=3,nums2=[2,5,6],n=3 -> [1,2,2,3,5,6]。
样例二：nums1=[0],m=0,nums2=[1],n=1 -> [1]，有效区为空。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:251-273（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int p1 = 0, p2 = 0;
        vector<int> sorted(m + n); // 变长栈数组 int sorted[m+n] 不是标准 C++。
        while (p1 < m || p2 < n)
        {
            int cur;
            if (p1 == m)
                cur = nums2[p2++];
            else if (p2 == n)
                cur = nums1[p1++];
            else if (nums1[p1] < nums2[p2])
                cur = nums1[p1++];
            else
                cur = nums2[p2++];
            sorted[p1 + p2 - 1] = cur;
        }
        nums1 = sorted;
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
    vector<int> a = {1, 2, 3, 0, 0, 0}, b = {2, 5, 6};
    s.merge(a, 3, b, 3);
    fail += check("sample1", a, vector<int>{1, 2, 2, 3, 5, 6});
    vector<int> c = {0}, d = {1};
    s.merge(c, 0, d, 1);
    fail += check("sample2", c, vector<int>{1});
    vector<int> e = {};
    s.merge(c, 1, e, 0);
    fail += check("empty second", c, vector<int>{1});
    return fail ? 1 : 0;
}

/* 收获点：双指针总共各走一次。用 vector 替换非标准变长数组。时间 O(m+n)，空间 O(m+n)；后续可练习从后往前合并以省空间。 */
