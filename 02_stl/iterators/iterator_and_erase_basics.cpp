/*
专题：迭代器、左闭右开区间与安全删除
任务：用迭代器访问、修改容器，删除所有偶数，并理解 end() 的含义。
示例一：输入 {1,2,4,5}，删除偶数后输出 {1,5}。
解释：删除后接住 erase 返回的下一个迭代器，连续的偶数也不会漏掉。
示例二：输入 {2,4}，删除偶数后输出空数组。
解释：最后一次删除返回 end()，循环自然结束，不能继续解引用。
*/
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>
using namespace std;

void RemoveEven(vector<int> &values)
{
    for (auto it = values.begin(); it != values.end(); )
    {
        if (*it % 2 == 0) it = values.erase(it);
        else ++it; // 删除分支不能再 ++，否则会跳过紧接着的元素。
    }
}

int Check(const char *name, long long actual, long long expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int CheckRemoval(vector<int> input, const vector<int> &expected)
{
    RemoveEven(input);
    cout << "remove even expected=[";
    for (int x : expected) cout << x << ' ';
    cout << "] actual=[";
    for (int x : input) cout << x << ' ';
    cout << ']' << (input == expected ? " PASS\n" : " FAIL\n");
    return input == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    vector<int> a = {10,20,30};
    auto it = a.begin();
    failed += Check("dereference", *it, 10);
    ++it;
    *it = 25;
    failed += Check("modify through iterator", a[1], 25);
    // [begin,end) 包含 begin、不包含 end；end 是尾后位置，不是最后一个元素。
    failed += Check("distance", distance(a.begin(), a.end()), 3);
    failed += Check("next", *next(a.begin(), 2), 30);
    failed += Check("last", *prev(a.end()), 30); // 必须非空。
    failed += Check("reverse begin", *a.rbegin(), 30);
    const vector<int> &readOnly = a;
    failed += Check("const iterator", *readOnly.cbegin(), 10);
    // cbegin() 得到只读迭代器，不能通过它修改元素。
    failed += CheckRemoval({1,2,4,5}, {1,5});
    failed += CheckRemoval({2,4}, {});
    failed += CheckRemoval({}, {});
    failed += CheckRemoval({1,3}, {1,3});

    set<int> s = {1,2,4,5};
    for (auto p = s.begin(); p != s.end(); )
    {
        if (*p % 2 == 0) p = s.erase(p);
        else ++p;
    }
    failed += Check("set remaining", s == set<int>({1,5}), true);
    map<int,int> scores = {{1,10}, {2,20}, {3,30}};
    for (auto p = scores.begin(); p != scores.end(); )
    {
        // map 迭代器的 ->first 是 key，->second 是 value。
        if (p->second < 25) p = scores.erase(p);
        else ++p;
    }
    failed += Check("map remaining", scores == map<int,int>({{3,30}}), true);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：vector 迭代器支持 +n 和相减；list/set/map 迭代器不支持这些运算。
next/prev 可移动相应类别的迭代器，但不能跨出有效范围。
vector erase 使删除位置及之后的迭代器失效；扩容使全部迭代器失效。
set/map/list 删除只使被删除元素的迭代器失效；哈希表 rehash 会使迭代器失效。
本例逐个 vector.erase 最坏 O(n^2)，大量筛除可改用 remove_if + erase。
*/
