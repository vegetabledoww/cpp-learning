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

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool check(int maxsum,int num,const vector<int> &communities)
    {
        int cnt = 1;//至少需要一个快递员
        int sum = 0;//快递员当前所承担的工作量
        for(int v : communities)
        {
            if(sum+v <= maxsum)//当前快递员还可以承担
                //当前快递员来做
                sum += v; 
            else
            {
                sum = v;//重启一个快递员
                cnt++;
            }
        }
        return cnt <= num;
        //在最大为num下，当前cnt个快递员在maxsum工作量的情况下，是否能够完成任务
    }
    
    //找最小可行的上界
    int Deliver(int num, const vector<int> &communities)
    {
        int left = *max_element(communities.begin(),communities.end());
        int right = 0;
        for(int num : communities)
            right += num;
        int answer = right;//先让其等于最大的，然后一步步缩小范围
        while (left <= right)
        {
            int mid = left + (right - left)/2;
            if(check(mid, num, communities))
            //如果满足条件，找较小值
            {
                right = mid -1;
                answer = mid;
            }
            else
                left = mid + 1;
        }
        return answer;
    }
};

int main()
{
    Solution solution;
    int num = 2;
    vector<int> communities = {1, 1, 6, 2};

    cout << "expected = 8, actual = "
         << solution.Deliver(num, communities) << '\n';

    return 0;
}
