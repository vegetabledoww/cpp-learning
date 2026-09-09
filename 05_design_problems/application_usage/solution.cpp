/**
 * 题目：应用使用统计
 *
 * 问题描述：
 * 根据进程运行记录，统计指定用户下各应用的总CPU和内存使用量，
 * 并按规则排序返回Top3应用名。
 *
 * 输入：
 * - processes：进程信息 [appName, userName, cpuUsed, memUsed]
 * - sortRules：排序规则，如 ["cpuUsed"] 或 ["memUsed"]
 * - selectedUsers：指定用户名列表（选中的usid）
 *
 * 输出：
 * 按排序规则降序排列的应用名数组（最多3个）
 *
 * 示例：
 * 输入：
 * processes = [("微信", "张三", 30, 20), ("QQ", "张三", 20, 10), ("微信", "张三", 10, 30)]
 * sortRules = ["cpuUsed"]
 * selectedUsers = ["张三"]
 *
 * 处理：
 * 1. 按用户筛选 → 张三的进程
 * 2. 按应用合并 → 微信(40CPU, 50Mem), QQ(20CPU, 10Mem)
 * 3. 按CPU降序 → 微信, QQ
 * 输出：["微信", "QQ"]
 *
 * 核心算法：
 * 1. 用 unordered_set 快速筛选用户
 * 2. 用 map 按应用名聚合（同用户同应用累加CPU/内存）
 * 3. 用 sort + Lambda 按规则降序排序
 * 4. 取前3个应用名
 */
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <string>
using namespace std;
//[appName, userName, cpuUsed, memUsed]
class Solution {
public:
   // 可以使用std::get访问tuple中的成员，比如std::get<0>(obj)可访问obj中第一个成员
    vector<tuple<string, int, int>> GetUseVec(const vector<tuple<string, string, int, int>>& processes,  const vector<string>& selectedUsers)
    {
       vector<tuple<string,int ,int>> useVec; // appName, cpu,mem
       map<string,tuple<string,int,int>>maps; //appName-->appName,cpu,mem
       unordered_set<string>usid(selectedUsers.begin(),selectedUsers.end());
       for(const auto& process : processes)
       {
        if(usid.count(get<1>(process))!=0)//process中存在选中的用户
        {
            auto it = maps.find(get<0>(process));
            if(it!=maps.end())
            {
                tuple<string,int,int>tmp = it->second;
                get<1>(tmp) += get<2>(process);
                get<2>(tmp) += get<3>(process);
                maps[it->first] = tmp;
            }
            else//没有重复的
            {
                maps[get<0>(process)] = make_tuple(get<0>(process),get<2>(process),get<3>(process));
            }
        }
        }
        //step2. 返回指定用户下的app列表
        for(auto it : maps)
        {
            useVec.push_back(it.second);
        }
       
       return useVec;
    }
    
    vector<string> GetTop3App(const vector<tuple<string, string, int, int>>& processes, const vector<string>& sortRules, const vector<string>& selectedUsers) {
        vector<string>ans;
        vector<tuple<string,int ,int>>user_list = GetUseVec(processes,selectedUsers);
        //step3. 根据指定规则进行排序
        sort(user_list.begin(),user_list.end(),[&](const auto& a,const auto& b)->bool{  //使用lambda表达式自定义排序规则，[&]表示捕获外部变量sortRules
            for(const string& s : sortRules)
            {
                if(s == "cpuUsed")
                {
                    //按照第2元素优先进行排序
                    if(get<1>(a)!=get<1>(b))
                        return get<1>(a)>get<1>(b);
                }

                if(s == "memUsed")
                {
                    //按照第3元素进行排序
                    if(get<2>(a)!=get<2>(b))
                        return get<2>(a)>get<2>(b);
                }
            }
             return get<0>(a)<get<0>(b);//默认按照第1个元素升序排列(兜底排序放到外部)
        });
        //step4.输出前三个
        if(user_list.size() > 3)
            user_list.resize(3);
        for(const auto& iv : user_list)
        {
            ans.push_back(get<0>(iv));
        }
        return ans;
    }
};