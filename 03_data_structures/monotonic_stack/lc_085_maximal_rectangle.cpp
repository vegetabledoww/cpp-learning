/*
题目：最大矩形（LeetCode 85）

给定一个只包含字符 '0' 和 '1' 的二维矩阵，找出只包含 '1' 的最大矩形，
并返回该矩形的面积。

示例一：
输入：{{'1','0','1','0','0'}, {'1','0','1','1','1'},
      {'1','1','1','1','1'}, {'1','0','0','1','0'}}
输出：6

示例二：
输入：{{'0'}}
输出：0
*/

#include <vector>
#include <iostream>
using namespace std;
int maximalRectangle(vector<vector<char>>& matrix) 
{
        int m=matrix.size(),n=matrix[0].size();
        if(m==0) return 0;
        vector<vector<int>>left(m,vector<int>(n,0));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(matrix[i][j]=='1')
                    left[i][j]=(j==0?0:left[i][j-1])+1;
            }
        }
    int ret=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(matrix[i][j]=='0')  
                continue;        
            int width=left[i][j];
            int area=width;
            for (int k = i - 1; k >= 0; k--) 
            {
                width = min(width, left[k][j]);
                area = max(area, (i - k + 1) * width);
            }
            ret=max(ret,area);
        }
    }
    return ret;
}

int main()
{
    vector<vector<char>>matrix1={{'1','0','1','0','0'},
                                {'1','0','1','1','1'},
                                {'1','1','1','1','1'},
                                {'1','0','0','1','0'}};
    cout << "示例一 expected=6\n";
    cout << "actual=" << maximalRectangle(matrix1) << '\n';

    vector<vector<char>>matrix2={{'0'}};
    cout << "示例二 expected=0\n";
    cout << "actual=" << maximalRectangle(matrix2) << '\n';
    return 0;
}
