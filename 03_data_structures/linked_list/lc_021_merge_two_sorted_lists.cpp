/*
题目：合并两个有序链表（LeetCode 21）

给定两个按非递减顺序排列的单链表，将它们合并成一个新的非递减链表。
新链表由原来两个链表中的节点组成，并返回合并后链表的头节点。

示例一：
输入：list1=[1,2,4]，list2=[1,3,4]
输出：[1,1,2,3,4,4]

示例二：
输入：list1=[]，list2=[0]
输出：[0]
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
//保留的第一次尝试，仅用于和下面的正确版本对照
ListNode *mergeTwoListsFirstAttempt(ListNode *List1, ListNode *List2)
{
    ListNode *dummy = new ListNode(-1), *p = dummy;
    ListNode *p1 = List1, *p2 = List2;
    while (p1 && p2)
    {
        if (List1->val > List2->val)
        {
            p->next = p2;
            p2 = p2->next;
        }
        else
        {
            p->next = p1;
            p1 = p1->next;
        }
    }
    p=p->next;
    if (p1)
        p->next = p1;
    if (p2)
        p->next = p2;
    return dummy->next;
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    ListNode *dummy = new ListNode(-1), *p = dummy;
    ListNode *p1 = list1, *p2 = list2;
    while (p1 && p2)
    {
        if (p1->val > p2->val)
        {
            p->next = p2;
            p2 = p2->next;
        }
        else
        {
            p->next = p1;
            p1 = p1->next;
        }
        p = p->next;
    }
    if (p1)
        p->next = p1;
    if (p2)
        p->next = p2;
    return dummy->next;
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
    cout << "示例一 expected=[1,1,2,3,4,4]\nactual=";
    PrintAndDeleteList(mergeTwoLists(BuildList({1,2,4}), BuildList({1,3,4})));

    cout << "示例二 expected=[0]\nactual=";
    PrintAndDeleteList(mergeTwoLists(BuildList({}), BuildList({0})));
    return 0;
}
