/*
LeetCode 206：反转链表

将单链表所有节点原地反转，返回新头节点。分别练习迭代和递归实现。节点由调用方管理。

样例一：1->2->3 -> 3->2->1，所有 next 反向。
样例二：空链表 -> 空链表。
来源：Top_K_C++/demo.cpp:211-237（原稿见 originals，映射见 SOURCES.md）。
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
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr; //前指针结点
        ListNode *curr = head;    //当前指针结点
        //每次循环，都将当前节点指向它前面的节点，然后当前节点和前节点后移
        while (curr)
        {
            ListNode *next = curr->next; //临时节点，暂存当前节点的下一节点，用于后移
            curr->next = prev;           //将当前节点指向它前面的节点
            prev = curr;                 //前指针后移
            curr = next;                 //当前指针后移
        }
        return prev;
    }

    //递归实现链表反转
    // 递归一遍的状态
    //1-->2-->3-->4
    //1<--2-->3-->4
    ListNode *reverseList_rec(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }
        ListNode *last = reverseList_rec(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
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
    auto a = makeNodes({1, 2, 3});
    auto head = s.reverseList(&a[0]);
    fail += check("sample1 iterative", listValues(head, a.size()), vector<int>{3, 2, 1});
    head = s.reverseList_rec(head);
    fail += check("recursive restores", listValues(head, a.size()), vector<int>{1, 2, 3});
    fail += check("sample2", listValues(s.reverseList(nullptr), 0), vector<int>{});
    auto b = makeNodes({9});
    fail += check("single", listValues(s.reverseList_rec(&b[0]), 1), vector<int>{9});
    return fail ? 1 : 0;
}

/* 收获点：迭代先存 next 再改指向；递归先反转后缀再接回。时间 O(n)，迭代额外空间 O(1)，递归 O(n)。 */
