/*
forward_list 与逗号整数解析

演示单链表在指定位置之后插入、反转；解析逗号分隔的合法整数列表。练习约定：token 不含空格、空 token 和非数字后缀，空输入返回空数组。

样例一：forward_list [1,2,3]，头插4，再 before_begin 后插5，反转 -> [3,2,1,4,5]。
样例二：CSV 1,-2,30 -> [1,-2,30]，逐段读取再转换。
来源：Project1/Project1/test1.cpp:72-87; 9_test/9_test/9_test.cpp:11-33（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <forward_list>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

vector<int> parseCsv(const string &input)
{
    if (input.empty())
        return {};
    if (input.back() == ',')
        throw invalid_argument("empty field");
    stringstream ss(input);
    string item;
    vector<int> result;
    while (getline(ss, item, ','))
    {
        if (item.empty())
            throw invalid_argument("empty field");
        size_t used = 0;
        int value = stoi(item, &used);
        if (used != item.size())
            throw invalid_argument("trailing characters");
        result.push_back(value);
    }
    return result;
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
    forward_list<int> values = {1, 2, 3};
    values.emplace_front(4);
    values.emplace_after(values.before_begin(), 5);
    values.reverse();
    fail += check("sample1", vector<int>(values.begin(), values.end()), vector<int>{3, 2, 1, 4, 5});
    fail += check("sample2", parseCsv("1,-2,30"), vector<int>{1, -2, 30});
    fail += check("empty", parseCsv(""), vector<int>{});
    bool rejected = false;
    try
    {
        parseCsv("12x,3");
    }
    catch (const invalid_argument &)
    {
        rejected = true;
    }
    fail += check("reject numeric prefix only", rejected, true);
    return fail ? 1 : 0;
}

/* 收获点：before_begin 指向首元素之前，insert_after 操作其后位置。stoi 默认允许数字前缀，检查 used 可拒绝尾部杂字符。链表反转/CSV 解析均线性。 */
