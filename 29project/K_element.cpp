#include <unordered_map>
#include <vector>
#include <cstring>
#include <random>
#include <numeric>
#include <queue>
#include <iostream>
#include<algorithm>
#include<stdint.h>
using namespace std;
static bool cmp(pair<int, int>& m, pair<int, int>& n) {
        return m.second > n.second;
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occ;
        for (auto& v : nums)//for循环作用是构建哈希键值对
            occ[v]++;
        // pair的第一个元素代表数组的值，第二个代表该值出现的次数,使用function函数
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)>q(cmp);
        for (auto& [num, count] : occ) {
            if (q.size() == k) {
                if (q.top().second < count) {
                    q.pop();
                    q.emplace(num, count);
                }
            } else {
                q.emplace(num, count);
            }
        }
        vector<int> ret;
        while (!q.empty()) {
            ret.emplace_back(q.top().first);
            q.pop();
        }
        return ret;
    }
    int main(int argc, char const *argv[])
    {
        vector<int>nums={1,1,1,2,2,3};
        int K=2;
        vector<int>ans;
        ans=topKFrequent(nums,K);
        for(auto a:ans)
        {
            cout<<a<<endl;
        }
        return 0;
    }
    