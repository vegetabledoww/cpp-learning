/*
专题：list 双向链表
任务：练习两端操作、迭代器位置插入删除、排序去重和节点转移。
示例一：从 {2,3} 开始，头部加入 1，尾部加入 4，输出 {1,2,3,4}。
解释：list 可以高效操作两端，但不支持下标访问。
示例二：输入 {3,1,3,2}，调用成员 sort 再 unique，输出 {1,2,3}。
解释：list 的迭代器不支持随机访问，不能使用 std::sort。
*/
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
using namespace std;

int Check(const char *name, const list<int> &actual, const vector<int> &expected)
{
    cout << name << " expected=[";
    for (int x : expected) cout << x << ' ';
    cout << "] actual=[";
    for (int x : actual) cout << x << ' ';
    bool passed = vector<int>(actual.begin(), actual.end()) == expected;
    cout << ']' << (passed ? " PASS\n" : " FAIL\n");
    return passed ? 0 : 1;
}

int main()
{
    int failed = 0;
    list<int> a = {2,3};
    a.push_front(1);
    a.push_back(4);
    failed += Check("push both ends", a, {1,2,3,4});
    a.pop_front();
    a.pop_back();
    failed += Check("pop both ends", a, {2,3});
    auto position = next(a.begin()); // 走到元素 3；不是 begin()+1。
    a.insert(position, 9); // 插在 position 之前，不会让 position 失效。
    failed += Check("insert before", a, {2,9,3});
    a.erase(position);
    failed += Check("erase node", a, {2,9});
    list<int> sorted = {3,1,3,2};
    sorted.sort();
    sorted.unique(); // 成员 unique 会真正删除相邻重复节点。
    failed += Check("sort unique", sorted, {1,2,3});
    sorted.reverse();
    failed += Check("reverse", sorted, {3,2,1});
    sorted.remove(2); // 成员 remove 会直接删除所有等于 2 的节点。
    failed += Check("remove value", sorted, {3,1});

    list<int> target = {1,4};
    list<int> source = {2,3};
    auto saved = source.begin();
    target.splice(next(target.begin()), source);
    failed += Check("splice target", target, {1,2,3,4});
    failed += Check("splice source emptied", source, {});
    cout << "saved iterator expected=2 actual=" << *saved << '\n';
    if (*saved != 2) failed++;
    // splice 后 saved 仍指向原节点，但节点已属于 target。
    target.clear();
    failed += Check("clear", target, {});
    list<int> empty;
    empty.sort();
    empty.unique();
    failed += Check("empty operations", empty, {});
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：已持有位置迭代器时插入/删除单个节点 O(1)，找位置通常仍需 O(n)。
list 不连续存储，不支持 [] 和 it+n；插入不使现有迭代器失效，删除仅使被删节点失效。
成员 sort 为 O(n log n)，unique/remove/reverse 为 O(n)。
本例不同链表间整表 splice 为 O(1)，默认分配器相同；节点转移不会复制元素。
*/
