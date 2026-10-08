/*
LeetCode 460：LFU 缓存（有序集合学习版）

get 命中返回值并增加频次，未命中返回 -1；put 更新也增加频次，新项频次为 1。满时先淘汰最低频，平频淘汰最久未使用项。容量>=0。本版保留原稿 set 实现，操作 O(log capacity)，不满足原平台要求的平均 O(1)。

样例一：容量2，put(1,1),put(2,2),get(1),put(3,3)：get(2) -> -1，2 频次更低。
样例二：容量2，put(1,10),put(2,20),put(3,30)：get(1) -> -1，平频时 1 更旧。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:120-191（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <utility>
using namespace std;

struct Node
{
    int cnt;
    long long time;
    int key, value;
    Node(int _cnt, long long _time, int _key, int _value)
        : cnt(_cnt), time(_time), key(_key), value(_value)
    {
    }
    bool operator<(const Node &rhs) const //运算符重载
    {
        return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};

class LFUCache
{
  public:
    //缓存容量、时间戳
    int capacity;
    long long time;
    unordered_map<int, Node> key_table;
    set<Node> S; //set天然有序，只不过这个顺序是我们自己定义的（优先使用类内重载运算符）
    LFUCache(int capacity) : capacity(capacity), time(0)
    {
        key_table.clear();
        S.clear();
    }

    int get(int key)
    {
        if (capacity == 0)
            return -1;
        auto it = key_table.find(key);
        //如果哈希表中没有键，返回-1
        if (it == key_table.end())
            return -1;
        //从哈希表中得到旧的缓存
        Node cache = it->second;
        //从平衡二叉树中删除旧的缓存
        S.erase(cache);
        //将旧的缓存更新
        cache.cnt += 1;
        cache.time = ++time;
        //将新的缓存重新放入平衡二叉树和哈希表之中
        S.insert(cache);
        it->second = cache;
        return cache.value;
    }

    void put(int key, int value)
    {
        if (!capacity)
            return;
        auto it = key_table.find(key);
        if (it == key_table.end())
        {
            if (int(key_table.size()) == capacity)
            {
                key_table.erase(S.begin()->key);
                S.erase(S.begin());
            }
            //创建新的缓存结点
            Node cache = Node(1, ++time, key, value);
            //将新的缓存放入哈希表与平衡二叉树之中
            key_table.insert(make_pair(key, cache));
            S.insert(cache);
        }
        //这里与get函数相似
        else
        {
            Node cache = it->second;
            S.erase(cache);
            cache.cnt += 1;
            cache.time = ++time;
            cache.value = value;
            S.insert(cache);
            it->second = cache;
        }
    }
};

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
    LFUCache s(2);
    s.put(1, 1);
    s.put(2, 2);
    fail += check("hit", s.get(1), 1);
    s.put(3, 3);
    fail += check("sample1 LFU", s.get(2), -1);
    fail += check("keep frequent", s.get(1), 1);
    LFUCache t(2);
    t.put(1, 10);
    t.put(2, 20);
    t.put(3, 30);
    fail += check("sample2 LRU tie", t.get(1), -1);
    t.put(2, 25);
    t.put(4, 40);
    fail += check("update raises frequency", t.get(2), 25);
    fail += check("updated eviction", t.get(3), -1);
    LFUCache z(0);
    z.put(1, 1);
    fail += check("zero capacity", z.get(1), -1);
    return fail ? 1 : 0;
}

/* 收获点：保留 hash 定位、set 按频次和时间排序。改用 long long 时间戳。操作 O(log capacity)，空间 O(capacity)；不是 O(1) LFU。 */
