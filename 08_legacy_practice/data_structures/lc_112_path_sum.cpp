/*
LeetCode 112：路径总和

判断二叉树是否存在从根到叶子的路径，节点值总和等于 targetSum；空树返回 false，叶子指没有左右孩子的节点。路径和在 int 范围。

样例一：树根1、左叶2、右叶3，target=3 -> true，路径 1->2。
样例二：同一棵树，target=1 -> false，不能在非叶子根节点结束。
来源：Top_K_C++/demo.cpp:343-372（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <queue>
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
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return 0;
        queue<TreeNode *> que;
        queue<int> que_val;
        que.push(root);
        que_val.push(root->val);
        while (!que.empty())
        {
            TreeNode *now = que.front();
            int temp = que_val.front();
            que.pop();
            que_val.pop();
            if (!now->left && !now->right)
            {
                if (temp == targetSum)
                    return true;
                else
                    continue;
            }
            if (now->left)
            {
                que.push(now->left);
                que_val.push(now->left->val + temp);
            }
            if (now->right)
            {
                que.push(now->right);
                que_val.push(now->right->val + temp);
            }
        }
        return false;
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
    TreeNode l(2), r(3), root(1, &l, &r);
    fail += check("sample1", s.hasPathSum(&root, 3), true);
    fail += check("sample2 nonleaf", s.hasPathSum(&root, 1), false);
    fail += check("empty", s.hasPathSum(nullptr, 0), false);
    TreeNode a(-2);
    fail += check("negative leaf", s.hasPathSum(&a, -2), true);
    return fail ? 1 : 0;
}

/* 收获点：保留节点队列与路径和队列同步推进。时间 O(n)，空间 O(n)。 */
