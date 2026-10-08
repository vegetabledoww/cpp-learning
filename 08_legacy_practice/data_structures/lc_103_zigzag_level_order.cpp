/*
LeetCode 103：二叉树的锯齿形层序遍历

按层返回二叉树节点值，第一层从左到右，第二层从右到左，此后交替。

样例一：树 [3,9,20,null,null,15,7] -> [[3],[20,9],[15,7]]。
样例二：只有根节点 1 -> [[1]]，没有下一层。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:280-303（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v, TreeNode *l = nullptr, TreeNode *r = nullptr) : val(v), left(l), right(r)
    {
    }
};
class Solution
{
  public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> res;
        queue<TreeNode *> q;
        bool flag = 1;
        q.push(root);
        if (!root)
            return res;
        while (!q.empty())
        {
            int sz = q.size();
            list<int> l; //双向链表，可以头部插入和尾部插入
            for (int i = 0; i < sz; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                if (flag)
                    l.push_back(cur->val);
                else
                    l.push_front(cur->val);
                if (cur->left)
                    q.push(cur->left);
                if (cur->right)
                    q.push(cur->right);
            }
            flag = !flag;
            res.emplace_back(
                l.begin(),
                l.end()); // 用迭代器范围直接构造 vector；也可 push_back(vector<int>(...))
        }
        return res;
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
    Solution s;
    TreeNode a(15), b(7), c(9), d(20, &a, &b), root(3, &c, &d), single(1);
    fail += check("sample1", s.zigzagLevelOrder(&root), vector<vector<int>>{{3}, {20, 9}, {15, 7}});
    fail += check("sample2", s.zigzagLevelOrder(&single), vector<vector<int>>{{1}});
    fail += check("empty", s.zigzagLevelOrder(nullptr), vector<vector<int>>{});
    return fail ? 1 : 0;
}

/* 收获点：保留 list 交替头尾插入，队列始终从左到右入队。时间 O(n)，空间 O(n)。 */
