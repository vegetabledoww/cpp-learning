/*
题目：前 K 个高频元素（LeetCode 347）

给定整数数组 nums 和整数 k，返回出现频率最高的 k 个元素。
题目保证答案唯一，返回结果的顺序不限。

示例一：
输入：nums=[1,1,1,2,2,3]，k=2
输出：[1,2]

示例二：
输入：nums=[4,4,4,5,5,6,7]，k=1
输出：[4]
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
struct cmp
{
    bool operator()(const pair<int,int>&m, const pair<int,int>&n)
    {
        return m.second > n.second;//降序
    }
};

vector<int> topKFrequent(vector<int> &nums, int k)
{
    unordered_map<int, int> occ;
    for (auto &v : nums) // for循环作用是构建哈希键值对
        occ[v]++;
    // pair的第一个元素代表数组的值，第二个代表该值出现的次数，小根堆
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q; 
    for (const auto &[num, count] : occ)
    {
        if (q.size() == static_cast<size_t>(k))
        {
            //当频率大的时候才会先出队，再将更大频率的元素入队，否则啥都不做
            if (q.top().second < count)
            {
                q.pop();
                q.emplace(num, count);
            }
        }
        else
        {
            q.emplace(num, count);
        }
    }
    vector<int> ret;
    while (!q.empty())
    {
        ret.emplace_back(q.top().first);
        q.pop();
    }
    return ret;
}
void PrintVector(vector<int> values)
{
    // 题目允许任意顺序，这里排序只是为了方便和 expected 对照。
    sort(values.begin(),values.end());
    cout << '[';
    for (size_t i=0;i<values.size();i++)
    {
        cout << values[i];
        if (i+1<values.size()) cout << ',';
    }
    cout << "]\n";
}

int main()
{
    vector<int> nums1={1,1,1,2,2,3};
    cout << "示例一 expected=[1,2]\nactual=";
    PrintVector(topKFrequent(nums1,2));

    vector<int> nums2={4,4,4,5,5,6,7};
    cout << "示例二 expected=[4]\nactual=";
    PrintVector(topKFrequent(nums2,1));
    return 0;
}
