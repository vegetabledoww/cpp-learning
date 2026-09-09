/*
题目：社区配送任务分配

某配送中心需要向一条线路上的若干个社区配送物资。
communities[i] 表示第 i 个社区需要配送的物资数量，社区的先后顺序不能改变。

现有 num 名配送员，需要将所有社区划分成若干个连续区间，
每名配送员负责其中一个区间。每名配送员的工作量等于其负责区间内
所有社区的物资数量之和。

请合理划分配送区间，使所有配送员中“最大工作量”尽可能小，
并返回这个最小的最大工作量。

如果配送员数量不少于社区数量，则每个社区都可以由一名配送员单独负责，
此时答案为 communities 中的最大值。

示例：
输入：num = 2，communities = {1, 1, 6, 2}
输出：8
解释：可以划分为 {1, 1} 和 {6, 2}，两名配送员的工作量分别为 2 和 8，
      最大工作量为 8。不存在最大工作量小于 8 的划分方案。

说明：communities 非空，其中的物资数量均为正整数，num 为正整数。
*/

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution
{
public:
    // 判断在每名配送员的工作量不超过 maxSum 的情况下，num 名配送员是否够用（贪心）
    bool Check(int maxSum, int num, const vector<int> &communities)
    {
        int cnt = 1; // 当前需要的配送员数量，至少需要 1 名
        int sum = 0; // 当前配送员已经承担的工作量
        for (int v : communities)
        {
            if (sum + v > maxSum)
            {
                cnt++;  // 当前配送员装不下，新安排一名配送员
                sum = v; // 新配送员从当前社区开始配送
            }
            else
                sum += v; // 当前社区仍然交给当前配送员
        }
        return cnt <= num;
    }

    int Deliver(int num, const vector<int> &communities)
    {
        if (num >= communities.size())
            return *max_element(communities.begin(), communities.end());
        // 将数组communities分成num组，分组必须是下标连续的，使得每组之和的最大值最小，并返回该值
        int left = *max_element(communities.begin(), communities.end());
        int right = 0;
        for (int v : communities)
            right += v;
        while (left < right)//标准的二分算法的写法
        {
            int mid = left + (right - left) / 2;
            if (Check(mid, num, communities))//在mid的限制下可以分配成功，表明该限制可以进一步缩小
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left;
    }
};

int main(int argc, char const *argv[])
{
    Solution S;
    int num = 2;
    vector<int>test = {1,1,6,2};
    cout<<S.Deliver(num,test);
    return 0;
}
/*收获点：
1.贪心+二分经典用法，这个题目可以抽象为：
给定一个数组 communities 和一个整数 num，要求将数组分成 num 个连续子数组
（如果数组长度小于等于 num，则每个元素可以单独一组，此时返回数组中的最大值即可），
使得每个子数组的和的最大值最小，并返回这个最小的最大值。
2.Check 是普通成员函数，它通过参数接收 maxSum、num 和 communities，
  专门负责判断当前的最大工作量限制是否可行。
*/
