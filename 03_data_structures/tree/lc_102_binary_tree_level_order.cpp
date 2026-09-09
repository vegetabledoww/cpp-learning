/*
题目：二叉树的层序遍历（LeetCode 102）

给定二叉树的根节点 root，按照从上到下、从左到右的顺序逐层访问节点，
返回每一层节点值组成的二维数组。

示例一：
输入：root=[3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]

示例二：
输入：root=[]
输出：[]
*/

#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left,*right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int _val):val(_val),left(nullptr),right(nullptr){}
    TreeNode(int _val,TreeNode* _left,TreeNode* _right):val(_val),left(_left),right(_right){}
};

vector<vector<int>>levelorder(TreeNode* root)
{
    vector<vector<int>>res;
    if(!root)return res;
    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty())
    {
        int sz=q.size();
        vector<int>level;
        for (int i = 0; i < sz; i++)
        {
            TreeNode* cur=q.front();
            q.pop();
            level.push_back(cur->val);
            if(cur->left)q.push(cur->left);
            if(cur->right)q.push(cur->right);
        }
        res.push_back(level);
    }
    return res;
}

void PrintLevels(const vector<vector<int>> &levels)
{
    cout << '[';
    for (size_t i = 0; i < levels.size(); i++)
    {
        cout << '[';
        for (size_t j = 0; j < levels[i].size(); j++)
        {
            cout << levels[i][j];
            if (j + 1 < levels[i].size()) cout << ',';
        }
        cout << ']';
        if (i + 1 < levels.size()) cout << ',';
    }
    cout << "]\n";
}

int main()
{
    TreeNode node15(15), node7(7), node9(9);
    TreeNode node20(20, &node15, &node7);
    TreeNode root(3, &node9, &node20);

    cout << "示例一 expected=[[3],[9,20],[15,7]]\nactual=";
    PrintLevels(levelorder(&root));

    cout << "示例二 expected=[]\nactual=";
    PrintLevels(levelorder(nullptr));
    return 0;
}
