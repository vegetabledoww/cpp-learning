/*
题目：解数独（LeetCode 37）

给定一个 9x9 的数独棋盘，空白格用字符 '.' 表示。请在原棋盘上填入数字，
使每一行、每一列以及每个 3x3 宫内的数字 1~9 都恰好出现一次。
题目保证输入棋盘只有一个解。

示例一：
输入第一行："53..7...."
求解后第一行："534678912"

示例二：
输入为一个只缺少左上角数字的合法棋盘，第一行是 ".34678912"
求解后第一行："534678912"
*/

#include<cstring>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
bool line[9][9];
bool column[9][9];
bool block[3][3][9];
bool valid;
vector<pair<int,int>>spaces;//保存需要添加的空闲位置

void dfs(vector<vector<char>>&board,int pos)
{
    if(static_cast<int>(spaces.size())==pos)
    {
        valid=true;//递归终止条件
        return;
    }
    auto [i,j]=spaces[pos];
    for (int digit = 0; digit < 9&&!valid; digit++)
    {
        if(!line[i][digit]&&!column[j][digit]&&!block[i/3][j/3][digit])
        {
            line[i][digit]=column[j][digit]=block[i/3][j/3][digit]=true;
            board[i][j]=digit+'0'+1;//int->char 
            dfs(board,pos+1);
            line[i][digit]=column[j][digit]=block[i/3][j/3][digit]=false;           
        }
    }
}
    void solveSudoku(vector<vector<char>>&board)
    {
        // 每次求解前清空全局状态，保证可以连续处理多个棋盘。
        memset(line, false, sizeof(line));
        memset(column, false, sizeof(column));
        memset(block, false, sizeof(block));
        spaces.clear();
        valid=false;

        for(int i=0;i<9;i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if(board[i][j]=='.')
                {
                    spaces.emplace_back(i,j);//将待输入的位置记录到spaces中
                }
                else
                {
                    int digit=board[i][j]-'0'-1;//将残局已有数字记录下来
                    line[i][digit]=column[j][digit]=block[i/3][j/3][digit]=true;//标记这些数字
                }
            }
        }
        dfs(board,0);
    }

void PrintBoard(const vector<vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char c : row)
        {
            cout << c;
        }
        cout << '\n';
    }
}

int main()
{
    vector<vector<char>> board1 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    solveSudoku(board1);
    cout << "示例一 expected first row=534678912\nactual board:\n";
    PrintBoard(board1);

    vector<vector<char>> board2 = {
        {'.','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}
    };
    solveSudoku(board2);
    cout << "\n示例二 expected first row=534678912\nactual board:\n";
    PrintBoard(board2);
    return 0;
}
