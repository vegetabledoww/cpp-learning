/*
专题：multiset 与 multimap
任务：保存允许重复的有序值或键，查询同键范围，并区分删除一个和删除全部。
示例一：multiset 输入 {2,1,2,3}，count(2)=2。
删除 find(2) 返回的一个位置后 count(2)=1；再 erase(2) 后 count(2)=0。
示例二：multimap 插入 (1,"Alice")、(1,"Bob")、(2,"Carol")。
输出：键 1 对应 {"Alice","Bob"}。解释：同一个键可以对应多条记录。
*/
#include <iostream>
#include <map>
#include <set>
#include <string>
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
    multiset<int> values = {2,1,2,3};
    cout << "ordered expected=[1 2 2 3] actual=[";
    for (int x : values) cout << x << ' ';
    cout << "]\n";
    failed += Check("ordered values", vector<int>(values.begin(), values.end()) == vector<int>({1,2,2,3}), true);
    failed += Check("duplicate count", values.count(2), 2);
    auto position = values.find(2);
    if (position != values.end()) values.erase(position); // 只删这一项。
    failed += Check("erase one", values.count(2), 1);
    failed += Check("erase key return count", values.erase(2), 1);
    failed += Check("erase all", values.count(2), 0);
    values.insert(5);
    values.insert(5);
    failed += Check("erase two matches", values.erase(5), 2);
    failed += Check("erase missing", values.erase(9), 0);

    multimap<int,string> records;
    records.insert({1,"Alice"});
    records.insert({1,"Bob"});
    records.emplace(2,"Carol");
    // multimap 没有 operator[]，因为一个键可能有多个值。
    auto range = records.equal_range(1);
    vector<string> names;
    for (auto it = range.first; it != range.second; ++it) names.push_back(it->second);
    cout << "names expected=[Alice Bob] actual=[";
    for (const string &name : names) cout << name << ' ';
    cout << "]\n";
    failed += Check("same key values", names == vector<string>({"Alice","Bob"}), true);
    auto missing = records.equal_range(99);
    failed += Check("empty range", missing.first == missing.second, true);
    failed += Check("remove all key 1", records.erase(1), 2);
    failed += Check("remaining size", records.size(), 1);
    failed += Check("key 2 intact", records.count(2), 1);
    records.clear();
    failed += Check("empty", records.empty(), true);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：普通 set/map 的键唯一，multi 版本允许重复；默认按值/键排序。
equal_range 返回 [first,second)，不要以为 find 会给出所有同键元素。
查找边界和插入 O(log n)，count/按键删除为 O(log n + 匹配数量)。
同键记录保持插入的相对顺序（C++11 起）；测试不应把它误当成按 value 排序。
*/
