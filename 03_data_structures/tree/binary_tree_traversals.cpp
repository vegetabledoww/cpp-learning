/*
题目：二叉树的前序、中序、后序遍历（入门示例）

给定二叉树根节点 root，分别返回前序、中序、后序遍历的节点值。
前序：根、左、右；中序：左、根、右；后序：左、右、根。
空树返回空数组。这里使用递归，不要求二叉搜索树，也不要求节点值互不相同。

示例一：输入树形为
       1
      / \
     2   3
    / \
   4   5
输出：前序={1,2,4,5,3}，中序={4,2,5,1,3}，后序={4,5,2,3,1}
解释：三种遍历的区别是何时访问当前根节点，左右子树仍按同样规则递归。

示例二：输入只有根节点 7
输出：三种遍历均为 {7}，因为没有左右子树。
*/
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

void Preorder(TreeNode *root, vector<int> &result)
{
    if (root == nullptr) return;
    result.push_back(root->val); // 前序：先访问根。
    Preorder(root->left, result);
    Preorder(root->right, result);
}

void Inorder(TreeNode *root, vector<int> &result)
{
    if (root == nullptr) return;
    Inorder(root->left, result);
    result.push_back(root->val); // 中序：在左右子树之间访问根。
    Inorder(root->right, result);
}

void Postorder(TreeNode *root, vector<int> &result)
{
    if (root == nullptr) return;
    Postorder(root->left, result);
    Postorder(root->right, result);
    result.push_back(root->val); // 后序：最后访问根。
}

void Print(const vector<int> &values)
{
    cout << '[';
    for (int value : values) cout << value << ' ';
    cout << ']';
}

int Check(const char *name, const vector<int> &actual, const vector<int> &expected)
{
    cout << name << " expected=";
    Print(expected);
    cout << " actual=";
    Print(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int CheckTree(TreeNode *root, const vector<int> &pre,
              const vector<int> &in, const vector<int> &post)
{
    vector<int> a, b, c;
    Preorder(root, a);
    Inorder(root, b);
    Postorder(root, c);
    return Check("preorder", a, pre) + Check("inorder", b, in)
           + Check("postorder", c, post);
}

int main()
{
    TreeNode a(1), b(2), c(3), d(4), e(5);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    int failed = CheckTree(&a, {1,2,4,5,3}, {4,2,5,1,3}, {4,5,2,3,1});
    TreeNode single(7);
    failed += CheckTree(&single, {7}, {7}, {7});
    failed += CheckTree(nullptr, {}, {}, {});
    TreeNode x(1), y(2), z(3);
    x.right = &y;
    y.right = &z;
    failed += CheckTree(&x, {1,2,3}, {1,2,3}, {3,2,1});
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：先写空指针出口，再确定“访问根”放在两次递归之前、中间还是之后。
result 用引用传递，让所有递归层写入同一份结果。
时间 O(n)，递归栈空间 O(h)，结果空间 O(n)；h 是树高，最坏为 n。
普通二叉树的中序不一定有序，二叉搜索树的中序才有序。
*/
