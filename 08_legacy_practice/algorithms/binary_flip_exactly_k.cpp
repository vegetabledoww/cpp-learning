/*
恰好翻转 K 次后的最小二进制字符串

由旧稿行为恢复的练习约定：每次选择任意一位0/1翻转，可重复选同一位，恰好操作 k 次，使字符串字典序最小。字符串非空，k>=0。原笔试是否同样允许重复翻转未核实。

样例一：s=110,k=1 -> 010，优先消除最高位的1。
样例二：s=11,k=3 -> 01，两次清零后还须翻一次最低位。
来源：byte_dancing/byte_dancing/byte_dancing.cpp:1-65（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string minimumAfterFlips(string s, long long k)
{
    for (char &c : s)
        if (c == '1' && k > 0)
        {
            c = '0';
            --k;
        }
    // 剩余偶数次可在同一位往返；奇数次必须留下一个1，应放最低位。
    if (k % 2 == 1)
        s.back() = '1';
    return s;
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
    fail += check("sample1", minimumAfterFlips("110", 1), string("010"));
    fail += check("sample2 all ones regression", minimumAfterFlips("11", 3), string("01"));
    fail += check("large k", minimumAfterFlips("000", 1000000000001LL), string("001"));
    fail += check("no operation", minimumAfterFlips("101", 0), string("101"));
    return fail ? 1 : 0;
}

/* 收获点：修复 bool 计数、剩余操作没有真正耗尽、全1且剩奇数次时漏翻转。时间 O(n)，输入副本空间 O(n)。仅验证这里声明的恢复规则。 */
