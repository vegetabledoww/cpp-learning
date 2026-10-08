/*
LeetCode 75：颜色分类

nums 只含 0、1、2，原地按升序排列，要求一次扫描和 O(1) 额外空间。

样例一：[2,0,2,1,1,0] -> [0,0,1,1,2,2]。
样例二：[1,0] -> [0,1]，最后一个待处理元素也要检查。
来源：huawei/huawei/huawei.cpp:8-29（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Solution
{
  public:
    void sortColors(vector<int> &nums)
    {
        int red = 0, white = 0, blue = int(nums.size()) - 1;
        while (white <= blue)
        { // 修复：相等时仍有一个未分类元素。
            if (nums[white] == 0)
            {
                swap(nums[red], nums[white]);
                ++red;
                ++white;
            }
            else if (nums[white] == 1)
                ++white;
            else
            {
                swap(nums[white], nums[blue]);
                --blue;
            } // 新换来的值尚未检查。
        }
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
    vector<int> a = {2, 0, 2, 1, 1, 0}, b = {1, 0}, c = {};
    s.sortColors(a);
    s.sortColors(b);
    s.sortColors(c);
    fail += check("sample1", a, vector<int>{0, 0, 1, 1, 2, 2});
    fail += check("last slot regression", b, vector<int>{0, 1});
    fail += check("empty", c, vector<int>{});
    return fail ? 1 : 0;
}

/* 收获点：维护红区、白区、未处理区、蓝区。修复 white<blue 漏掉末元素。时间 O(n)，空间 O(1)。 */
