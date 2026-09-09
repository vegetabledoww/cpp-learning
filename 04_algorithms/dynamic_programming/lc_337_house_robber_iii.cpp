/*
题目：打家劫舍 III（LeetCode 337）

房屋组成一棵二叉树。直接相连的父子节点不能在同一晚被偷，返回能够偷到的
最大金额。

示例一：
输入：root=[3,2,3,null,3,null,1]
输出：7

示例二：
输入：root=[3,4,5,1,3,null,1]
输出：9
*/

#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int _val):val(_val),left(nullptr),right(nullptr){}
    TreeNode(int _val,TreeNode*left,TreeNode* right):val(_val),left(left),right(right){}
};
unordered_map<TreeNode*,int>f,g;//f表示被选中当前层，g表示未被选中当前层
void dfs(TreeNode* node)
{
    if(!node)return;    //后序遍历
    dfs(node->left);
    dfs(node->right);
    f[node]=node->val+g[node->left]+g[node->right];//选中当前层
    g[node]=max(f[node->left],g[node->left])+max(f[node->right],g[node->right]);//未选中当前层
}
int rob3(TreeNode* root)
{
    f.clear();
    g.clear();
    dfs(root);
    return max(f[root],g[root]);
}

int main()
{
    TreeNode a3(3), a1(1);
    TreeNode a2(2,nullptr,&a3), aRight(3,nullptr,&a1);
    TreeNode root1(3,&a2,&aRight);
    cout << "示例一 expected=7\n";
    cout << "actual=" << rob3(&root1) << '\n';

    TreeNode b1(1), b3(3), bRight1(1);
    TreeNode b4(4,&b1,&b3), b5(5,nullptr,&bRight1);
    TreeNode root2(3,&b4,&b5);
    cout << "示例二 expected=9\n";
    cout << "actual=" << rob3(&root2) << '\n';
    return 0;
}
