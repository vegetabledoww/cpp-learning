/*
专题：set 与 unordered_set
任务：对整数去重，练习插入、查找、删除以及有序集合的范围查找。
示例一：输入 {3,1,3,2}，set 遍历输出 {1,2,3}。
解释：set 自动去重并按值排序；unordered_set 同样去重，但不保证遍历顺序。
示例二：集合 {1,3,5}，lower_bound(3) 得到 3，upper_bound(3) 得到 5。
解释：前者找第一个 >=3 的元素，后者找第一个 >3 的元素。
*/
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

int Check(const char *name, long long actual, long long expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    set<int> ordered = {3,1,3,2};
    cout << "ordered expected=[1 2 3] actual=[";
    for (int x : ordered) cout << x << ' ';
    cout << "]\n";
    failed += Check("ordered values", vector<int>(ordered.begin(), ordered.end()) == vector<int>({1,2,3}), true);
    auto inserted = ordered.insert(4); // pair<迭代器, 是否新增>。
    failed += Check("new value", inserted.second, true);
    failed += Check("duplicate value", ordered.insert(4).second, false);
    failed += Check("contains 2", ordered.find(2) != ordered.end(), true);
    failed += Check("count absent", ordered.count(9), 0);
    failed += Check("erase existing", ordered.erase(2), 1);
    failed += Check("erase missing", ordered.erase(2), 0);
    failed += Check("size", ordered.size(), 3);

    set<int> bounds = {1,3,5};
    auto lower = bounds.lower_bound(3);
    auto upper = bounds.upper_bound(3);
    failed += Check("lower bound", lower == bounds.end() ? -1 : *lower, 3);
    failed += Check("upper bound", upper == bounds.end() ? -1 : *upper, 5);
    failed += Check("past maximum", bounds.lower_bound(6) == bounds.end(), true);

    unordered_set<int> hashed = {3,1,3,2};
    failed += Check("hash size", hashed.size(), 3);
    for (int x : {1,2,3}) failed += Check("hash membership", hashed.count(x), 1);
    failed += Check("hash duplicate", hashed.insert(2).second, false);
    failed += Check("hash erase", hashed.erase(2), 1);
    failed += Check("hash absent", hashed.find(2) == hashed.end(), true);
    // 不检查哈希表的遍历顺序；不同实现和扩容都可能改变顺序。
    ordered.clear();
    hashed.clear();
    failed += Check("ordered empty", ordered.empty(), true);
    failed += Check("hash empty", hashed.empty(), true);
    failed += Check("empty bound", ordered.lower_bound(0) == ordered.end(), true);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：只保存“值是否出现过”用 set/unordered_set，保存“键对应的值”用 map。
set 的值不能通过迭代器直接修改；修改需先删除再插入。
set 插入、查找、按键删除为 O(log n)；unordered_set 对应操作平均 O(1)、最坏 O(n)。
unordered_set 没有 lower_bound/upper_bound，也不能通过下标访问元素。
*/
