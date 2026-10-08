/*
LeetCode 155：最小栈

实现 push、pop、top、getMin，均 O(1)。调用 pop/top/getMin 前保证非空，重复最小值需正确处理。

样例一：push(-2),push(0),push(-3),getMin -> -3；pop 后 getMin -> -2。
样例二：push(2),push(2),pop,getMin -> 2，相同最小值仍存在。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:334-359（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
using namespace std;

class MinStack
{
    stack<int> x_stack;   //主栈
    stack<int> min_stack; //辅助栈
  public:
    MinStack()
    {
        min_stack.push(INT_MAX);
    }

    void push(int val)
    {
        x_stack.push(val);
        min_stack.push(min(val, min_stack.top()));
    }

    void pop()
    {
        x_stack.pop();
        min_stack.pop();
    }

    int top()
    {
        return x_stack.top();
    }

    int getMin()
    {
        return min_stack.top();
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
    MinStack s;
    s.push(-2);
    s.push(0);
    s.push(-3);
    fail += check("sample1 minimum", s.getMin(), -3);
    s.pop();
    fail += check("sample1 after pop", s.getMin(), -2);
    fail += check("top", s.top(), 0);
    MinStack t;
    t.push(2);
    t.push(2);
    t.pop();
    fail += check("sample2 duplicates", t.getMin(), 2);
    MinStack u;
    u.push(INT_MAX);
    fail += check("sentinel equality", u.getMin(), INT_MAX);
    return fail ? 1 : 0;
}

/* 收获点：辅助栈每一层记录当时最小值，两个栈同步弹出。各操作 O(1)，总空间 O(n)。 */
