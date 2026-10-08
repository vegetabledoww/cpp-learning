/*
LeetCode 232：用栈实现队列

实现 FIFO 队列 push/pop/peek/empty，仅使用栈。调用 pop、peek 时队列非空。

样例一：push(1),push(2),peek -> 1，pop -> 1。
样例二：push(1),push(2),pop,push(3),pop -> 2，不能让 3 插队。
来源：Top_K_C++/demo.cpp:272-311（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class MyQueue
{
  private:
    stack<int> s1, s2; //输入栈  输出栈
  public:
    MyQueue()
    {
    }

    void in2out() //输入栈-->输出栈
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
    }
    void push(int x)
    {
        s1.push(x);
    }

    int pop()
    {
        if (s2.empty()) //只有输出栈为空的时候才会考虑倒栈
            in2out();
        int x = s2.top();
        s2.pop();
        return x;
    }

    int peek() //返回最顶元素（类似s.top()）
    {
        if (s2.empty())
            in2out();
        return s2.top();
    }

    bool empty()
    {
        return s1.empty() && s2.empty();
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
    MyQueue q;
    q.push(1);
    q.push(2);
    fail += check("sample1 peek", q.peek(), 1);
    fail += check("sample1 pop", q.pop(), 1);
    q.push(3);
    fail += check("sample2 interleaved", q.pop(), 2);
    fail += check("last", q.pop(), 3);
    fail += check("empty", q.empty(), true);
    return fail ? 1 : 0;
}

/* 收获点：只有输出栈为空才倒栈。push O(1)，pop/peek 摊还 O(1)、单次最坏 O(n)，空间 O(n)。 */
