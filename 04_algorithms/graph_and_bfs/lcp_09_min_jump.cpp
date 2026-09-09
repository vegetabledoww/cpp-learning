// 为了给刷题的同学一些奖励，力扣团队引入了一个弹簧游戏机。游戏机由 N 个特殊
//弹簧排成一排，编号为 0 到 N-1。初始有一个小球在编号 0 的弹簧处。若小球在编
//号为 i 的弹簧处，通过按动弹簧，可以选择把小球向右弹射 jump[i] 的距离，或者
//向左弹射到任意左侧弹簧的位置。也就是说，在编号为 i 弹簧处按动弹簧，小球可以
//弹向 0 到 i-1 中任意弹簧或者 i+jump[i] 的弹簧（若 i+jump[i]>=N ，则表示
//小球弹出了机器）。小球位于编号 0 处的弹簧时不能再向左弹。

// 为了获得奖励，你需要将小球弹出机器。请求出最少需要按动多少次弹簧，可以将小
//球从编号 0 弹簧弹出整个机器，即: 向右越过编号 N-1 的弹簧。
#include<vector>
#include<queue>
#include<iostream>
using namespace std;
class Solution {
public:
    int minJump(vector<int>& jump) {
        int n = jump.size();
        vector<int> dist(n, -1);   // dist[i]：到达弹簧 i 的最少按动次数，-1 表示未访问
        queue<int> q;
        dist[0] = 0;
        q.push(0);
        int leftmost = 0;          // [0, leftmost] 内的弹簧都已访问过

        while (!q.empty()) {
            int i = q.front(); q.pop();//表示开始执行，这时把队列中的此项值弹出
            int d = dist[i];           //将此时的步骤拿出来

            // 操作一：向右弹射到 i + jump[i]
            int r = i + jump[i];               //在当前i下标下，弹出的距离
            if (r >= n) return d + 1;          // 弹出机器
            if (dist[r] == -1)                 //如果这个地方还没访问
            {
                dist[r] = d + 1;                //标记为最少第d+1步可以访问
                q.push(r);                      //更新距离，从这个距离出发🚀
            }

            // 操作二：向左可弹到 0..i-1 任意位置
            // 其中 [0, leftmost] 已访问过，只需处理 (leftmost, i) 中的未访问位置
            for (int k = leftmost + 1; k < i; ++k) {
                if (dist[k] == -1) //确认尚未访问过
                {
                    dist[k] = d + 1;  // 到达 k 的最少按动次数 = 到达 i 的最少按动次数 + 1
                    q.push(k);
                }
            }
            if (i - 1 > leftmost) leftmost = i - 1;   // 此时 [0, i-1] 已全部访问
        }
        return -1;   // 题目保证有解，不会执行到这里
    }
};

int main()
{
    Solution solution;

    vector<int> jump1 = {2, 5, 1, 1, 1, 1};
    cout << "示例一：期望结果 = 3，实际结果 = "
         << solution.minJump(jump1) << '\n';

    vector<int> jump2 = {3, 7, 6, 1, 4, 3, 7, 8, 1, 2,
                         8, 5, 9, 8, 3, 2, 7, 5, 1, 1};
    cout << "示例二：期望结果 = 6，实际结果 = "
         << solution.minJump(jump2) << '\n';

    return 0;
}
