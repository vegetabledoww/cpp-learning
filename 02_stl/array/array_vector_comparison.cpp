/*
专题：array 的使用，以及它与 vector 的异同

任务：对固定三维坐标 array<int,3> 和动态整数列表 vector<int>，
练习初始化、访问、遍历、排序、拷贝、传参和互相转换。
示例一：array 输入 {3,1,2}，排序输出 {1,2,3}，长度一直为 3。
解释：长度 3 是 array 类型的一部分，没有 push_back/resize。
示例二：vector 输入 {3,1,2}，追加 4 后输出 {3,1,2,4}，长度变为 4。
解释：vector 的长度在运行时变化，vector<int> 的类型不随长度变化。

相同点：普通元素连续存储，支持 []、at、front/back、迭代器、排序和按值拷贝。
不同点：array 把固定数量的元素放在对象内部；vector 管理另外分配的动态存储。
注意：vector<bool> 是特殊版本，不适用这里关于普通 vector 连续 T 元素的结论。
*/
#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

// 3 是类型的一部分，此函数不能直接接收 array<int,4>。
int SumCoordinate(const array<int,3> &point)
{
    int sum = 0;
    for (int value : point) sum += value;
    return sum;
}

// 同一个 vector<int> 参数可以接收任意长度的 int 动态数组。
int SumList(const vector<int> &values)
{
    int sum = 0;
    for (int value : values) sum += value;
    return sum;
}

void SetFirst(array<int,3> &point, int value)
{
    point[0] = value; // 非 const 引用用于修改原对象。
}

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
    array<int,3> a = {3,1,2};
    sort(a.begin(), a.end());
    failed += CheckValues("array sorted", vector<int>(a.begin(), a.end()), {1,2,3});
    failed += Check("array fixed size", a.size(), 3);
    failed += Check("array front", a.front(), 1);
    failed += Check("array back", a.back(), 3);
    failed += Check("array at", a.at(1), 2);
    failed += Check("array data", a.data()[2], 3);

    array<int,3> zero{}; // {} 使 int 元素全部初始化为 0。
    array<int,3> partial = {7}; // 未列出的元素补 0，不是填充为 7。
    failed += CheckValues("array zero initialization", vector<int>(zero.begin(), zero.end()), {0,0,0});
    failed += CheckValues("array partial initialization", vector<int>(partial.begin(), partial.end()), {7,0,0});
    zero.fill(5);
    failed += CheckValues("array fill", vector<int>(zero.begin(), zero.end()), {5,5,5});
    // 局部 array<int,3> uninitialized; 的 int 元素没有初始化，不能直接读取。

    array<int,3> copy = a; // 与原生 C 数组不同，array 支持整体拷贝、赋值和比较。
    copy[0] = 99;
    failed += Check("array copy independent", a[0], 1);
    SetFirst(a, 8);
    failed += Check("array reference parameter", a[0], 8);
    failed += Check("array const reference sum", SumCoordinate(a), 13);
    copy = a;
    failed += Check("array equality", copy == a, true);
    a.swap(zero); // 逐元素交换，长度 N 的 array 交换为 O(N)。
    failed += CheckValues("array swap", vector<int>(a.begin(), a.end()), {5,5,5});

    vector<int> v = {3,1,2};
    v.push_back(4);
    failed += CheckValues("vector grows", v, {3,1,2,4});
    failed += Check("vector parameter sum", SumList(v), 10);
    vector<int> defaultVector; // 默认构造的 vector 为空，不会产生 3 个元素。
    vector<int> vectorZeros(3); // 三个 0。
    vector<int> vectorOne{3}; // 一个值为 3 的元素，与 (3) 完全不同。
    failed += Check("default vector empty", defaultVector.empty(), true);
    failed += CheckValues("vector parentheses", vectorZeros, {0,0,0});
    failed += CheckValues("vector braces", vectorOne, {3});
    v.reserve(20);
    failed += Check("reserve preserves size", v.size(), 4);
    failed += Check("reserve capacity", v.capacity() >= 20, true);
    v.resize(6, 9);
    failed += CheckValues("resize creates elements", v, {3,1,2,4,9,9});

    vector<int> fromArray(copy.begin(), copy.end()); // 转换需要显式复制元素。
    failed += CheckValues("array to vector", fromArray, {8,2,3});
    array<int,3> fromVector{};
    if (fromArray.size() == fromVector.size())
        std::copy(fromArray.begin(), fromArray.end(), fromVector.begin());
    failed += Check("vector to array", fromVector == copy, true);
    // 目标长度不够时不能 std::copy 全部元素；不能直接写 fromVector = fromArray。

    array<int,0> emptyArray{}; // 零长度合法，但没有 front/back 或可访问的元素。
    failed += Check("zero length array", emptyArray.empty(), true);
    failed += Check("empty range", emptyArray.begin() == emptyArray.end(), true);
    bool arrayCaught = false;
    bool vectorCaught = false;
    try { a.at(a.size()); }
    catch (const out_of_range &) { arrayCaught = true; }
    try { v.at(v.size()); }
    catch (const out_of_range &) { vectorCaught = true; }
    failed += Check("array at checks bounds", arrayCaught, true);
    failed += Check("vector at checks bounds", vectorCaught, true);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：
1. 已知固定维度，如坐标、RGB、固定字段记录，用 array；数量随输入变化，用 vector。
2. 两者都提供 O(1) 下标访问、O(n) 遍历和拷贝；排序都是 O(n log n)。
3. array 不会扩容，元素地址不因扩容改变；vector 扩容会使旧元素指针/引用/迭代器失效。
4. array 不会自动退化成指针；需要元素指针时显式调用 data()。
5. array 自身不为元素另外动态分配，但对象可以是局部、静态、动态分配的对象或成员。
   所以“array 在栈上、vector 在堆上”不是准确的区别。
*/
