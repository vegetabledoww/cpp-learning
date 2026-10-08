/*
LeetCode 1535：找出数组游戏的赢家

互不相同、至少两个整数组成队列。每轮比较头两个数，大者留队首、小者移到队尾；返回首个连胜 k 轮的数，k>=1。

样例一：[2,1,3,5,4,6,7], k=2 -> 5，依次击败 3 和 4。
样例二：[3,2,1], k=10 -> 3，最大值会一直获胜。
来源：../originals/new_function/test_function.cpp:699-723（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    int getWinner(vector<int> &arr, int k)
    {
        int prev = max(arr[0], arr[1]);
        if (k == 1)
            return prev;
        int consecutive = 1;
        int maxNum = prev;
        int length = arr.size();
        for (int i = 2; i < length; i++)
        {
            int curr = arr[i];
            if (prev > curr)
            {
                consecutive++;
                if (consecutive == k)
                    return prev;
            }
            else
            {
                prev = curr;
                consecutive = 1;
            }
            maxNum = max(maxNum, curr);
        }
        return maxNum;
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
    vector<int> a = {2, 1, 3, 5, 4, 6, 7}, b = {3, 2, 1}, c = {1, 9};
    fail += check("sample1", s.getWinner(a, 2), 5);
    fail += check("sample2", s.getWinner(b, 10), 3);
    fail += check("one win", s.getWinner(c, 1), 9);
    return fail ? 1 : 0;
}

/* 收获点：扫描维护当前擂主和连胜次数，扫完仍未达到 k 则最大值获胜。时间 O(n)，空间 O(1)。 */
