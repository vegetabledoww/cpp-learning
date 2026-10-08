/*
深拷贝：构造、拷贝构造与拷贝赋值

实现拥有独立字符缓冲区的 Mystring。拷贝后修改一份不影响另一份；支持空字符串和自赋值。此例专门练习手动资源管理，日常代码优先 std::string。

样例一：a=hello，b 拷贝 a，再把 b 首字母改 H -> a=hello,b=Hello。
样例二：已有 c=old，再 c=a -> c=hello，旧缓冲区正确释放。
来源：9_test/9_test/9_test.cpp:119-167（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

class Mystring
{
    char *data;

  public:
    Mystring(const char *str = "")
    {
        if (!str)
            str = "";
        data = new char[strlen(str) + 1];
        strcpy(data, str); // 已按长度+终止符分配，不能用 sizeof(data) 当缓冲区长度。
    }
    Mystring(const Mystring &other) : Mystring(other.data)
    {
    }
    Mystring &operator=(const Mystring &other)
    {
        if (this == &other)
            return *this;
        char *next = new char[strlen(other.data) + 1];
        strcpy(next, other.data);
        delete[] data; // 与 new[] 配对；先分配成功再释放旧数据。
        data = next;
        return *this;
    }
    ~Mystring()
    {
        delete[] data;
    }
    const char *c_str() const
    {
        return data;
    }
    void setFirst(char c)
    {
        if (data[0] != '\0')
            data[0] = c;
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
    Mystring a("hello"), b(a);
    b.setFirst('H');
    fail += check("sample1 original", string(a.c_str()), string("hello"));
    fail += check("sample1 copy", string(b.c_str()), string("Hello"));
    Mystring c("old");
    c = a;
    fail += check("sample2 assignment", string(c.c_str()), string("hello"));
    c = c;
    fail += check("self assignment", string(c.c_str()), string("hello"));
    Mystring empty(nullptr);
    fail += check("empty", string(empty.c_str()), string(""));
    return fail ? 1 : 0;
}

/* 收获点：修复旧稿 delete/delete[] 不匹配、空析构泄漏、把指针大小误当容量。拷贝 O(n)，空间 O(n)。三法则：析构、拷贝构造、拷贝赋值协同。 */
