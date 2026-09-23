/*
专题：vector 动态数组基础
任务：练习初始化、追加、插入删除、容量、二维数组以及拷贝与引用。
示例一：{1,2,3} 中在下标 1 插入 9，再删除下标 2，输出 {1,9,3}。
解释：插入后为 {1,9,2,3}，随后删除的是 2。
示例二：{1,2} 扩大到长度 4，新位置填 7，输出 {1,2,7,7}。
解释：resize 改变实际元素数，reserve 只预留存储空间。
*/
#include <iostream>
#include <vector>
using namespace std;

int Check(const char *name, long long actual, long long expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int CheckValues(const char *name, const vector<int> &actual, const vector<int> &expected)
{
    cout << name << " expected=[";
    for (int x : expected) cout << x << ' ';
    cout << "] actual=[";
    for (int x : actual) cout << x << ' ';
    cout << ']' << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    vector<int> empty;
    failed += Check("empty", empty.empty(), true);
    vector<int> repeated(3, 5);
    failed += CheckValues("three copies", repeated, {5,5,5});
    vector<int> a = {1,2,3};
    a.insert(a.begin() + 1, 9);
    a.erase(a.begin() + 2);
    failed += CheckValues("insert and erase", a, {1,9,3});
    a.push_back(4);
    failed += Check("back", a.back(), 4);
    a.pop_back(); // 只删除，不返回元素；调用前必须非空。
    failed += Check("front", a.front(), 1);
    failed += Check("at", a.at(1), 9); // at 越界抛异常，[] 不做边界检查。

    vector<int> b = {1,2};
    b.reserve(10);
    failed += Check("reserve keeps size", b.size(), 2);
    failed += Check("capacity at least 10", b.capacity() >= 10, true);
    // reserve 后仍不能访问 b[2]，只有 resize 才会创建这些元素。
    b.resize(4, 7);
    failed += CheckValues("resize grow", b, {1,2,7,7});
    b.resize(1);
    failed += CheckValues("resize shrink", b, {1});

    vector<int> copy = a;
    copy[0] = 100;
    failed += Check("copy is independent", a[0], 1);
    vector<int> &alias = a;
    alias[0] = 8;
    failed += Check("reference changes original", a[0], 8);
    for (int &value : a) value *= 2; // 没有 & 时，修改的是循环变量的副本。
    failed += CheckValues("reference traversal", a, {16,18,6});

    vector<vector<int>> grid(2, vector<int>(3, 0));
    grid[0][1] = 9;
    failed += CheckValues("grid row 0", grid[0], {0,9,0});
    failed += CheckValues("rows independent", grid[1], {0,0,0});
    a.clear();
    failed += Check("clear size", a.size(), 0);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：size 是元素数，capacity 是可容纳的元素数，二者不是同一回事。
下标访问 O(1)，尾部追加均摊 O(1)，中间插入删除 O(n)，拷贝 O(n)。
扩容会使原迭代器、指针、元素引用失效；容量的具体增长倍数不由标准保证。
*/
