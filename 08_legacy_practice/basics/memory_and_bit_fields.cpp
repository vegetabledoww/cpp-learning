/*
sizeof、strlen、字节复制、布局与位域

区分字符长度和对象占用字节；复制带终止符的字符数组；观察结构体对齐和位域，不假定跨平台字节布局。这里不读取未初始化内存或非活动 union 成员。

样例一：char s[]="hello" -> strlen=5,sizeof=6，包含一个终止符。
样例二：字节 146（10010010）按低7位年龄、高1位性别解码 -> 年龄18、性别1。
来源：Char/main.cpp; pen_exam_8/pen_exam_8/_8_pen_exam.cpp:606-689; 9_test/9_test/9_test.cpp:183-204（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <string>
using namespace std;

struct Layout
{
    char a;
    double b;
    int c;
};
struct Flags
{
    unsigned int age : 7;
    unsigned int gender : 1;
};
uint32_t swap32(uint32_t x)
{
    return ((x & 0x000000ffu) << 24) | ((x & 0x0000ff00u) << 8) | ((x & 0x00ff0000u) >> 8) |
           ((x & 0xff000000u) >> 24);
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
    char src[] = "hello";
    char dst[sizeof(src)] = {};
    memcpy(dst, src, sizeof(src));
    fail += check("sample1 strlen", int(strlen(src)), 5);
    fail += check("sample1 sizeof", int(sizeof(src)), 6);
    fail += check("copy includes terminator", string(dst), string("hello"));
    unsigned int byte = 146;
    Flags f{};
    f.age = byte & 127u;
    f.gender = (byte >> 7) & 1u;
    fail += check("sample2 age", int(f.age), 18);
    fail += check("sample2 gender", int(f.gender), 1);
    fail += check("byte swap twice", swap32(swap32(0x12345678u)), uint32_t(0x12345678u));
    cout << "layout sizeof=" << sizeof(Layout) << " alignof=" << alignof(Layout)
         << " double offset=" << offsetof(Layout, b) << '\n';
    fail += check("size respects alignment", sizeof(Layout) % alignof(Layout) == 0, true);
    vector<int> a = {1, 2}, b = a;
    b[0] = 9;
    fail += check("vector copy independence", a[0], 1);
    return fail ? 1 : 0;
}

/* 收获点：纠正旧注释：memcpy 按指定字节数复制，不自动补零；memset 按字节填充而非按 int 赋值；C++ 支持位域，但布局由实现决定。vector 对象不能整体 memcpy，元素正规拷贝不共享地址。 */
