#pragma once
struct TreeNode
{
    int val;
    TreeNode* left, *right;
    TreeNode():val(0),left(nullptr),right(nullptr){}
    TreeNode(int val):val(val),left(nullptr),right(nullptr){}
    TreeNode(int val,TreeNode* _left,TreeNode* _right):val(val),left(_left),right(_right){}
};
