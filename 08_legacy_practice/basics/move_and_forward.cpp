/*
左值、右值、move 与完美转发

通过重载观察表达式类别。func(int&) 返回 lvalue，func(int&&) 返回 rvalue；wrapper 使用 forward 保留调用方传来的类别。

样例一：int x=42; wrapper(x) -> lvalue，因为 x 是有名字的对象。
样例二：wrapper(42) -> rvalue，因为字面量为右值。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:516-565（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

string func(int &)
{
    return "lvalue";
}
string func(int &&)
{
    return "rvalue";
}
template <class T> string wrapper(T &&arg)
{
    return func(forward<T>(arg));
}

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
    int x = 42;
    int &&y = 2;
    fail += check("sample1", wrapper(x), string("lvalue"));
    fail += check("sample2", wrapper(42), string("rvalue"));
    fail += check("named rvalue-reference regression", wrapper(y), string("lvalue"));
    fail += check("explicit move", wrapper(move(y)), string("rvalue"));
    fail += check("move alone does not alter int", y, 2);
    return fail ? 1 : 0;
}

/* 收获点：纠正旧稿 wrapper(y) 的注释：y 的声明类型是右值引用，但表达式 y 是左值。move 只是转换，是否搬运资源取决于后续构造/赋值。操作 O(1)。 */
