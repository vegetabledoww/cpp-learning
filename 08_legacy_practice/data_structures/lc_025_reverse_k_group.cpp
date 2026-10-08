/*
LeetCode 25：K 个一组翻转链表

每 k 个节点一组反转，最后不足 k 个保持原顺序。k>=1，空链表返回空。只调整 next，不修改 val。

样例一：1->2->3->4->5,k=2 -> 2->1->4->3->5，最后一项不反转。
样例二：1->2->3->4->5,k=3 -> 3->2->1->4->5。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:389-418（原稿见 originals，映射见 SOURCES.md）。
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
    ListNode *reverse(ListNode *a, ListNode *b)
    {
        ListNode *pre, *cur, *nxt;
        pre = nullptr;
        cur = a;
        nxt = a;
        // while 终止的条件改一下就行了
        while (cur != b)
        {
            nxt = cur->next;
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return pre;
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (!head)
            return nullptr;
        //区间[a,b)包含k个待反转元素
        ListNode *a, *b;
        a = b = head;
        for (int i = 0; i < k; i++)
        {
            if (b == nullptr)
                return head;
            b = b->next;
        }
        //反转前K个元素
        ListNode *newHead = reverse(a, b);
        a->next = reverseKGroup(b, k);
        return newHead;
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
    auto a = makeNodes({1, 2, 3, 4, 5}), b = makeNodes({1, 2, 3, 4, 5}), c = makeNodes({7});
    fail += check("sample1", listValues(s.reverseKGroup(&a[0], 2), 5), vector<int>{2, 1, 4, 3, 5});
    fail += check("sample2", listValues(s.reverseKGroup(&b[0], 3), 5), vector<int>{3, 2, 1, 4, 5});
    fail += check("k one", listValues(s.reverseKGroup(&c[0], 1), 1), vector<int>{7});
    fail += check("empty", listValues(s.reverseKGroup(nullptr, 2), 0), vector<int>{});
    return fail ? 1 : 0;
}

/* 收获点：先确认 [a,b) 有 k 个节点再反转，避免误改短尾。时间 O(n)，递归空间 O(n/k)。 */
