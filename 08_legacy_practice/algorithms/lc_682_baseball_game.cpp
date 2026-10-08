/*
LeetCode 682：棒球比赛

操作数字=记录分数；C=撤销上一项；D=记录上一项两倍；+=记录前两项之和。返回最终总分，保证操作合法、分数在 int 范围。

样例一：["5","2","C","D","+"] -> 30，记录最终为 [5,10,15]。
样例二：["1","C"] -> 0，记录全部撤销。
来源：Top_K_C++/demo.cpp:510-528（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

class Solution
{
  public:
    int calPoints(vector<string> &operations)
    {
        vector<int> stk;
        for (size_t i = 0; i < operations.size(); i++)
        {
            if (operations[i][0] == 'C')
                stk.pop_back();
            else if (operations[i][0] == 'D')
                stk.push_back(stk.back() * 2);
            else if (operations[i][0] == '+')
            {
                int first = stk.back();
                int second = stk[stk.size() - 2];
                stk.push_back(first + second);
            }
            else
                stk.push_back(stoi(operations[i]));
        }
        return accumulate(stk.begin(), stk.end(), 0);
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
    vector<string> a = {"5", "2", "C", "D", "+"}, b = {"1", "C"}, c = {};
    fail += check("sample1", s.calPoints(a), 30);
    fail += check("sample2", s.calPoints(b), 0);
    fail += check("empty extension", s.calPoints(c), 0);
    return fail ? 1 : 0;
}

/* 收获点：保留 vector 作栈，统一从第一项处理，支持空操作。时间 O(n)，空间 O(n)。 */
