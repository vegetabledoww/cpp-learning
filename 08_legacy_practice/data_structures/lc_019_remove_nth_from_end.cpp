/*
LeetCode 19：删除链表的倒数第 N 个结点

删除倒数第 n 个节点并返回头节点，保证链表非空且 n 合法。调用方负责节点内存，此函数只调整链接。

样例一：1->2->3->4->5,n=2 -> 1->2->3->5，删除 4。
样例二：1,n=1 -> 空链表，删除头节点。
来源：Top_K_C++/demo.cpp:242-269（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x = 0) : val(x), next(nullptr)
    {
    }
};
class Solution
{
  public:
    ListNode *findFromEnd(ListNode *head, int n)
    {
        ListNode *p1 = head;
        //p1先走k步
        for (int i = 0; i < n; i++)
        {
            p1 = p1->next;
        }
        ListNode *p2 = head;
        while (p1)
        {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p2;
    }
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *x = findFromEnd(&dummy, n + 1);
        x->next = x->next->next;
        return dummy.next;
    }
};
vector<ListNode> makeNodes(const vector<int> &values)
{
    vector<ListNode> nodes(values.size());
    for (size_t i = 0; i < values.size(); ++i)
    {
        nodes[i].val = values[i];
        if (i + 1 < values.size())
            nodes[i].next = &nodes[i + 1];
    }
    return nodes;
}
vector<int> listValues(ListNode *p, size_t limit)
{
    vector<int> values;
    // 有界读取：如果错误地形成环，结果长度会超出期望，测试失败而非卡死。
    while (p && values.size() <= limit)
    {
        values.push_back(p->val);
        p = p->next;
    }
    return values;
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
    Solution s;
    auto a = makeNodes({1, 2, 3, 4, 5}), b = makeNodes({1}), c = makeNodes({1, 2});
    fail += check("sample1", listValues(s.removeNthFromEnd(&a[0], 2), 5), vector<int>{1, 2, 3, 5});
    fail += check("sample2", listValues(s.removeNthFromEnd(&b[0], 1), 1), vector<int>{});
    fail += check("remove head", listValues(s.removeNthFromEnd(&c[0], 2), 2), vector<int>{2});
    return fail ? 1 : 0;
}

/* 收获点：虚拟头方便统一删除头节点；快指针先走 n+1 步找到前驱。时间 O(n)，额外空间 O(1)。 */
