/*
LeetCode 236：二叉树的最近公共祖先

给定二叉树及其中两个不同节点 p、q，返回其最近公共祖先的地址。节点可以是自己的祖先，保证两节点都在树中。

样例一：根3，左子5，右子1；p=5,q=1 -> 根3，两侧各命中。
样例二：根3的左子5包含子节点2；p=5,q=2 -> 5，祖先也是候选。
来源：_top_k_8/_top_k_8/_top_k_8.cpp:230-240（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
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
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        //空二叉树或者给定的p、q为二叉树的根节点，则直接返回根节点
        if (root == nullptr || root == p || root == q)
            return root;
        //左右分别递归
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left == nullptr && right == nullptr)
            return nullptr; //均为空说明无（此题不存在）
        if (left == nullptr)
            return right; //两个节点分布于根节点右侧
        if (right == nullptr)
            return left; //两个节点分布于根节点左侧
        return root;     //左右递归结果都不为空，说明两个节点分布于根节点异测
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
    TreeNode a(2), b(5, &a), c(1), root(3, &b, &c);
    fail += check("sample1 address", s.lowestCommonAncestor(&root, &b, &c) == &root, true);
    fail += check("sample2 ancestor", s.lowestCommonAncestor(&root, &b, &a) == &b, true);
    TreeNode repeated(5);
    b.right = &repeated;
    fail += check("same value different nodes", s.lowestCommonAncestor(&root, &a, &repeated) == &b,
                  true);
    return fail ? 1 : 0;
}

/* 收获点：递归返回命中节点，两侧非空时当前根即 LCA。比较地址而不是值。时间 O(n)，空间 O(树高)。 */
