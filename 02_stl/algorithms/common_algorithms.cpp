/*
专题：常用标准库算法
任务：练习排序、反转、查找、计数、最值、去重和条件删除。
示例一：输入 {3,1,3,2}，排序去重后输出 {1,2,3}。
解释：unique 只压缩相邻重复项，因此先排序；再用 erase 真正缩短容器。
示例二：输入 {1,2,4,5}，删除偶数后输出 {1,5}。
解释：remove_if 将保留元素移到前部，返回新的逻辑末尾，但不改变 size。
*/
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool Descending(int a, int b) { return a > b; }
bool IsEven(int value) { return value % 2 == 0; }

vector<int> SortedUnique(vector<int> values)
{
    sort(values.begin(), values.end());
    auto newEnd = unique(values.begin(), values.end());
    values.erase(newEnd, values.end());
    return values;
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
    vector<int> a = {3,1,3,2};
    failed += Check("count 3", count(a.begin(), a.end(), 3), 2);
    auto position = find(a.begin(), a.end(), 2);
    failed += Check("find index", position - a.begin(), 3);
    failed += Check("missing", find(a.begin(), a.end(), 9) == a.end(), true);
    failed += Check("min", *min_element(a.begin(), a.end()), 1);
    failed += Check("max", *max_element(a.begin(), a.end()), 3);
    sort(a.begin(), a.end());
    failed += CheckValues("ascending", a, {1,2,3,3});
    sort(a.begin(), a.end(), Descending);
    failed += CheckValues("descending", a, {3,3,2,1});
    reverse(a.begin(), a.end());
    failed += CheckValues("reverse", a, {1,2,3,3});
    failed += CheckValues("sorted unique", SortedUnique({3,1,3,2}), {1,2,3});
    failed += CheckValues("empty unique", SortedUnique({}), {});
    failed += CheckValues("all equal", SortedUnique({7,7,7}), {7});
    vector<int> adjacent = {1,1,2,1};
    adjacent.erase(unique(adjacent.begin(), adjacent.end()), adjacent.end());
    failed += CheckValues("unique only adjacent", adjacent, {1,2,1});

    vector<int> b = {1,2,4,5};
    auto newEnd = remove_if(b.begin(), b.end(), IsEven);
    failed += Check("remove keeps size", b.size(), 4);
    b.erase(newEnd, b.end());
    failed += CheckValues("erase evens", b, {1,5});
    b.erase(remove(b.begin(), b.end(), 1), b.end());
    failed += CheckValues("erase value", b, {5});
    fill(b.begin(), b.end(), 9);
    failed += CheckValues("fill", b, {9});
    vector<int> empty;
    failed += Check("empty min is end", min_element(empty.begin(), empty.end()) == empty.end(), true);
    // 空区间的最值迭代器不能解引用。
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：sort 要求随机访问迭代器，list 应调用自己的 sort 成员函数。
比较函数必须是严格比较，不能把 > 写成 >=；相等元素不能互相“排在前面”。
sort 为 O(n log n)；reverse/find/count/最值/unique/remove_if/fill 为 O(n)。
unique 和 remove 系列返回逻辑末尾，尾部残留值不应当作有效结果使用。
*/
