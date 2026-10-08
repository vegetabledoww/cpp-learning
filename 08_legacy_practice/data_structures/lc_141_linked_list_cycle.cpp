/*
LeetCode 141：环形链表

判断单链表沿 next 是否会重复到达同一节点。空链表无环。提供哈希表和快慢指针对照。

样例一：1->2->3->2... -> true，尾节点回到第二节点。
样例二：1->2->null -> false，可以走到末尾。
来源：Top_K_C++/demo.cpp:94-119（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <unordered_set>
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
    bool hasCycle(ListNode *head)
    {
        unordered_set<ListNode *> MP;
        while (head != nullptr)
        {
            if (MP.count(head)) //已经存在此结点
            {
                return true; //如果是1，是环
            }
            MP.insert(head);
            head = head->next;
        }
        return false; //遍历结束，返回false，不是环
    }

    //b.快慢指针
    bool hasCycle_fastslow(ListNode *head)
    {
        ListNode *fast = head, *slow = head; //初始化快慢指针
        while (fast != nullptr && fast->next != nullptr)
        {
            //快指针一次走两步，慢指针一次走一步
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast)
                return true;
        }
        return false;
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
    a[2].next = &a[1];
    fail += check("sample1 fast slow", s.hasCycle_fastslow(&a[0]), true);
    fail += check("sample1 hash", s.hasCycle(&a[0]), true);
    a[2].next = nullptr;
    fail += check("sample2", s.hasCycle_fastslow(&a[0]), false);
    fail += check("empty", s.hasCycle(nullptr), false);
    a[0].next = &a[0];
    fail += check("self loop", s.hasCycle_fastslow(&a[0]), true);
    return fail ? 1 : 0;
}

/* 收获点：比较节点地址，不是 val。两种方法时间 O(n)，哈希空间 O(n)，快慢指针 O(1)。原稿只有判环，没有实现 LC142 入口定位。 */
