/*
构造、运算符重载、枚举、静态局部变量与宏

用小例子观察对象按字段相等、枚举递增值、static 局部变量跨调用保留，以及带括号宏的优先级。各测试独立说明输入输出。

样例一：Date(2024,2,2)==Date(2024,2,2) -> true；不同日期 -> false。
样例二：nextCount 连调三次 -> [1,2,3]，局部 static 只初始化一次。
来源：operation/main.cpp:4-35; new_function/test_function.cpp:35-58; Pureproject/test.c:5-15（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

class Date
{
    int year, month, day;

  public:
    Date(int y = 1900, int m = 1, int d = 1) : year(y), month(m), day(d)
    {
    }
    bool operator==(const Date &other) const
    {
        return year == other.year && month == other.month && day == other.day;
    }
};
enum Age
{
    a = 5,
    b = 10,
    c,
    d,
    e,
    f = 0
};
char getAgeString(Age value)
{
    switch (value)
    {
    case a:
        return 'a';
    case b:
        return 'b';
    case c:
        return 'c';
    case d:
        return 'd';
    case e:
        return 'e';
    case f:
        return 'f';
    }
    return '?';
}
int nextCount()
{
    static int count = 0;
    return ++count;
}
#define MAX_VALUE(x, y) ((x) > (y) ? (x) : (y))

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
    fail += check("sample1 equal", Date(2024, 2, 2) == Date(2024, 2, 2), true);
    fail += check("different", Date(2024, 2, 2) == Date(2024, 2, 3), false);
    vector<int> counts;
    for (int i = 0; i < 3; ++i)
        counts.push_back(nextCount());
    fail += check("sample2", counts, vector<int>{1, 2, 3});
    fail += check("enum auto increment", int(c), 11);
    fail += check("enum name", getAgeString(e), 'e');
    fail += check("macro precedence", 3 + MAX_VALUE(1, 2 != 3), 4);
    return fail ? 1 : 0;
}

/* 收获点：补枚举返回路径，比较运算符可作用于 const 对象。宏须给整个表达式加括号，但参数仍可能重复求值，不传 ++i 等副作用表达式。示例均 O(1)。 */
