/*
题目：删除链表中的指定节点（LCR 136）

给定一个单链表的头节点 head 和整数 val，删除链表中值等于 val 的节点，
并返回删除后的头节点。题目保证链表中节点值互不相同，且 val 一定存在。

示例一：
输入：head=[4,5,1,9]，val=5
输出：[4,1,9]

示例二：
输入：head=[4,5,1,9]，val=4
输出：[5,1,9]
*/

#include <iostream>
#include <vector>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int _val) : val(_val), next(nullptr) {}
};
ListNode *deleteNode(ListNode *head, int val)
{
    if (head->val == val)
        return head->next;
    ListNode *prev = head, *cur = prev->next;
    while (cur != nullptr && cur->val != val)
    {
        prev = cur;
        cur = cur->next;
    }
    if (cur != nullptr)
    {
        prev->next = cur->next;
    }
    return head;
}

ListNode *BuildList(const vector<int> &values)
{
    ListNode dummy(0);
    ListNode *tail = &dummy;
    for (int value : values)
    {
        tail->next = new ListNode(value);
        tail = tail->next;
    }
    return dummy.next;
}

void PrintAndDeleteList(ListNode *head)
{
    cout << '[';
    while (head != nullptr)
    {
        cout << head->val;
        if (head->next != nullptr)
        {
            cout << ',';
        }
        ListNode *next = head->next;
        delete head;
        head = next;
    }
    cout << "]\n";
}

int main()
{
    cout << "示例一 expected=[4,1,9]\nactual=";
    PrintAndDeleteList(deleteNode(BuildList({4,5,1,9}), 5));

    cout << "示例二 expected=[5,1,9]\nactual=";
    PrintAndDeleteList(deleteNode(BuildList({4,5,1,9}), 4));
    return 0;
}
