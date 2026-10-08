/*
LeetCode 92：反转链表 II

原地反转链表从 left 到 right 的节点（位置从 1 开始，区间合法），其余节点顺序保持。返回新头节点。

样例一：1->2->3->4->5,left=2,right=4 -> 1->4->3->2->5。
样例二：1->2->3,left=1,right=2 -> 2->1->3，尾节点不能丢失。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:364-385（原稿见 originals，映射见 SOURCES.md）。
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
    ListNode *succ = nullptr; // 跨递归层保留第 n+1 个节点，不能作为每层的局部变量。
    ListNode *reverseN(ListNode *head, int n)
    {
        if (n == 1)
        {
            succ = head->next;
            return head;
        }
        ListNode *last = reverseN(head->next, n - 1);
        head->next->next = head;
        head->next = succ;
        return last;
    }

  public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        if (left == 1)
            return reverseN(head, right); // 从 head 开始，不能跳过 head。
        head->next = reverseBetween(head->next, left - 1, right - 1);
        return head;
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
    auto a = makeNodes({1, 2, 3, 4, 5}), b = makeNodes({1, 2, 3}), c = makeNodes({8});
    fail += check("sample1 tail regression", listValues(s.reverseBetween(&a[0], 2, 4), 5),
                  vector<int>{1, 4, 3, 2, 5});
    fail += check("sample2 head regression", listValues(s.reverseBetween(&b[0], 1, 2), 3),
                  vector<int>{2, 1, 3});
    fail += check("single reuse", listValues(s.reverseBetween(&c[0], 1, 1), 1), vector<int>{8});
    return fail ? 1 : 0;
}

/* 收获点：保留递归反转前 n 个的思路，修复后继丢失和跳过头节点。时间 O(right)，递归空间 O(right)。 */
