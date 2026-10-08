/*
链表中首个未出现在另一字符串的字符

沿第一个字符串构建的字符链表，从头找首个未出现在第二字符串中的字符；若没有，返回 '\0'。字符串不含内嵌零字符。本题比较字符集合，不是寻找两条链表的公共节点。

样例一：s1=abc,s2=ac -> b，a存在但b不存在。
样例二：s1=abc,s2=cba -> 空字符，三个字符都存在。
来源：9_pen_exam/huawei/huawei.cpp:261-304（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

struct LinkNode
{
    char value;
    LinkNode *next;
    explicit LinkNode(char c) : value(c), next(nullptr)
    {
    }
};
LinkNode *creatlinknode(const string &str)
{
    if (str.empty())
        return nullptr;
    LinkNode *head = new LinkNode(str[0]);
    LinkNode *cur = head;
    for (size_t i = 1; i < str.size(); ++i)
    { // 修复：首字符已建节点，从1继续。
        cur->next = new LinkNode(str[i]);
        cur = cur->next;
    }
    return head;
}
char findfirstnode(LinkNode *head, const string &str2)
{
    unordered_set<char> charSet(str2.begin(), str2.end());
    for (LinkNode *cur = head; cur; cur = cur->next)
        if (!charSet.count(cur->value))
            return cur->value;
    return '\0';
}
void destroy(LinkNode *head)
{
    while (head)
    {
        LinkNode *next = head->next;
        delete head;
        head = next;
    }
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
    LinkNode *head = creatlinknode("abc");
    fail += check("sample1", findfirstnode(head, "ac"), 'b');
    fail += check("sample2 no missing", findfirstnode(head, "cba") == '\0', true);
    int count = 0;
    for (auto p = head; p; p = p->next)
        ++count;
    fail += check("duplicate first node regression", count, 3);
    destroy(head);
    head = creatlinknode("");
    fail += check("empty", head == nullptr, true);
    destroy(head);
    return fail ? 1 : 0;
}

/* 收获点：修复首节点重复和示例内存未释放，保留集合查找与链表遍历。期望时间 O(n+m)，空间 O(n+字符集大小)，包含链表节点。 */
