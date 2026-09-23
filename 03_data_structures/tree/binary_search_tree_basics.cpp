/*
题目：二叉搜索树的插入与查找（入门示例）

将一组整数依次插入最初为空的二叉搜索树，再查询某个值是否存在。
对于任意节点，左子树所有值小于它，右子树所有值大于它；重复值忽略。
插入函数返回更新后的根指针，查找函数返回 bool，中序遍历用于查看有序结果。

示例一：插入 {5,3,7,2,4,6,8}，查询 4 和 9
输出：true、false；中序={2,3,4,5,6,7,8}
解释：4 位于根 5 的左子树、节点 3 的右侧，树中没有 9。

示例二：插入 {2,2,1}，查询 2
输出：true；中序={1,2}
解释：重复的 2 不新增节点。
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

TreeNode *Insert(TreeNode *root, int value)
{
    if (root == nullptr) return new TreeNode(value);
    // 接住递归返回的根指针，才能把新建节点连回父节点。
    if (value < root->val) root->left = Insert(root->left, value);
    else if (value > root->val) root->right = Insert(root->right, value);
    return root;
}

bool Contains(TreeNode *root, int value)
{
    while (root != nullptr)
    {
        if (value == root->val) return true;
        if (value < root->val) root = root->left;
        else root = root->right;
    }
    return false;
}

void Inorder(TreeNode *root, vector<int> &result)
{
    if (root == nullptr) return;
    Inorder(root->left, result);
    result.push_back(root->val);
    Inorder(root->right, result);
}

void Destroy(TreeNode *root)
{
    if (root == nullptr) return;
    // 先释放子节点，再释放父节点，避免提前丢失子树指针。
    Destroy(root->left);
    Destroy(root->right);
    delete root;
}

void Print(const vector<int> &values)
{
    cout << '[';
    for (int value : values) cout << value << ' ';
    cout << ']';
}

int CheckTree(const vector<int> &values, const vector<int> &expected,
              int query, bool expectedFound)
{
    TreeNode *root = nullptr;
    for (int value : values) root = Insert(root, value);
    vector<int> actual;
    Inorder(root, actual);
    bool found = Contains(root, query);
    cout << "inorder expected=";
    Print(expected);
    cout << " actual=";
    Print(actual);
    cout << "; query=" << query << " expected=" << expectedFound << " actual=" << found;
    bool passed = actual == expected && found == expectedFound;
    cout << (passed ? " PASS\n" : " FAIL\n");
    Destroy(root);
    return passed ? 0 : 1;
}

int main()
{
    int failed = 0;
    failed += CheckTree({5,3,7,2,4,6,8}, {2,3,4,5,6,7,8}, 4, true);
    failed += CheckTree({5,3,7,2,4,6,8}, {2,3,4,5,6,7,8}, 9, false);
    failed += CheckTree({2,2,1}, {1,2}, 2, true);
    failed += CheckTree({}, {}, 1, false);
    failed += CheckTree({7}, {7}, 7, true);
    failed += CheckTree({1,2,3,4}, {1,2,3,4}, 4, true);
    failed += CheckTree({4,3,2,1}, {1,2,3,4}, 0, false);
    failed += CheckTree({0,-2,3,-1}, {-2,-1,0,3}, -1, true);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：二叉搜索树利用大小关系，每次只走一边；普通二叉树没有这个保证。
查找/插入时间 O(h)，插入递归栈 O(h)，迭代查找额外空间 O(1)。
这不是平衡树：有序插入会退化成链，h 最坏为 n；不能总说操作是 O(log n)。
中序和释放均为 O(n) 时间、O(h) 栈空间；new 创建的节点最终用 delete 释放。
*/
