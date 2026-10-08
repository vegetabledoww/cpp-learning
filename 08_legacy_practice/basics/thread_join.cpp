/*
线程入口与 join

演示普通函数和函数对象作为线程入口，将结果写入引用；主线程 join 后读取结果，避免数据竞争。不使用休眠来猜测线程是否完成。

样例一：子线程计算 2+4，join 后 result -> 6。
样例二：函数对象子线程计算 3+5，join 后 result -> 8。
来源：Project1/Project1/test1.cpp:108-169（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
using namespace std;

void sumTask(int x, int y, int &result)
{
    result = x + y;
}
class Task
{
  public:
    void operator()(int x, int y, int &result) const
    {
        result = x + y;
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
    int result = 0;
    thread t(sumTask, 2, 4, ref(result));
    t.join();
    fail += check("sample1", result, 6);
    fail += check("joined no longer joinable", t.joinable(), false);
    thread u(Task{}, 3, 5, ref(result));
    u.join();
    fail += check("sample2", result, 8);
    thread none;
    fail += check("default thread", none.joinable(), false);
    return fail ? 1 : 0;
}

/* 收获点：join 等待该子线程结束，不是把线程合并到主线程；不读写未同步的共享变量。需支持 std::thread 的工具链，MinGW 链接 -pthread。 */
