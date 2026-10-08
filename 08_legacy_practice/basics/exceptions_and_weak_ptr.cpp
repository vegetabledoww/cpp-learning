/*
异常处理与 weak_ptr 解除循环持有

练习安全整数除法和弱引用。除数为零或 INT_MIN/-1 抛出异常；两个对象通过 weak_ptr 互相观察，外部 shared_ptr 离开后对象应释放。

样例一：divide(8,2) -> 4；divide(8,0) -> 捕获 invalid_argument。
样例二：两个对象各仅有一个 shared_ptr 拥有者 -> use_count=1；离开作用域后弱引用 expired=true。
来源：Project1/Project1/test1.cpp:9-68（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <climits>
using namespace std;

int divide(int a, int b)
{
    if (b == 0)
        throw invalid_argument("division by zero");
    if (a == INT_MIN && b == -1)
        throw overflow_error("division overflow");
    return a / b;
}
class B;
class A
{
  public:
    weak_ptr<B> spb;
};
class B
{
  public:
    weak_ptr<A> spa;
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
    fail += check("sample1", divide(8, 2), 4);
    bool caught = false;
    try
    {
        divide(8, 0);
    }
    catch (const invalid_argument &)
    {
        caught = true;
    }
    fail += check("zero divisor", caught, true);
    caught = false;
    try
    {
        divide(INT_MIN, -1);
    }
    catch (const overflow_error &)
    {
        caught = true;
    }
    fail += check("overflow boundary", caught, true);
    weak_ptr<A> observer;
    {
        auto a = make_shared<A>();
        auto b = make_shared<B>();
        a->spb = b;
        b->spa = a;
        observer = a;
        fail += check("sample2 owners", int(a.use_count()), 1);
        fail += check("lock alive", bool(observer.lock()), true);
    }
    fail += check("sample2 released", observer.expired(), true);
    return fail ? 1 : 0;
}

/* 收获点：weak_ptr 不增加强引用计数，使用前 lock；析构不靠手动 delete。补全 <memory>/<stdexcept> 等头文件。示例时间、空间 O(1)。 */
