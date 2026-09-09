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
 * - selectedUsers：指定用户名列表
 *
 * 输出：
 * 按排序规则降序排列的应用名数组（最多3个）
 *
 * 示例1：单用户，按CPU排序
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
 * 示例2：单用户，按内存排序
 * 输入：
 * processes = [("IDE", "小王", 80, 100), ("浏览器", "小王", 20, 400),
 *              ("IDE", "小王", 10, 150), ("音乐", "小王", 30, 300)]
 * sortRules = ["memUsed"]
 * selectedUsers = ["小王"]
 *
 * 处理：
 * 1. 按应用合并 → IDE(90CPU, 250Mem), 浏览器(20CPU, 400Mem), 音乐(30CPU, 300Mem)
 * 2. 按内存降序 → 浏览器, 音乐, IDE
 * 输出：["浏览器", "音乐", "IDE"]
 *
 * 示例3：多用户，按CPU排序，CPU相同时再按内存排序
 * 输入：
 * processes = [("浏览器", "张三", 20, 60), ("浏览器", "李四", 30, 20),
 *              ("编译器", "张三", 50, 40), ("终端", "李四", 40, 30),
 *              ("音乐", "王五", 100, 100)]
 * sortRules = ["cpuUsed", "memUsed"]
 * selectedUsers = ["张三", "李四"]
 *
 * 处理：
 * 1. 筛选张三和李四，排除王五的音乐进程
 * 2. 按应用合并 → 浏览器(50CPU, 80Mem), 编译器(50CPU, 40Mem), 终端(40CPU, 30Mem)
 * 3. 浏览器和编译器的CPU相同，再比较内存 → 浏览器, 编译器, 终端
 * 输出：["浏览器", "编译器", "终端"]
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
        //step1. 先筛选出指定用户下的进程信息，并按应用名聚合CPU和内存使用量
        vector<tuple<string, int, int>> useVec; // appName, cpu,mem
        map<string, tuple<string, int, int>> maps; // appName -> appName, cpu,mem
        unordered_set<string> uset(selectedUsers.begin(), selectedUsers.end()); // 被选中的user names
        for (auto& process : processes) {
            if (uset.count(get<1>(process))) { // 找到userName分组了,只关心当前user下的东西
                    auto iter2 = maps.find(get<0>(process));//得到当前user的第一个app的名字
                    if (iter2 != maps.end()) { // 同一个userName 中appName 相同的情况，对其进行合并处理
                        tuple<string, int, int> tmps = iter2->second;//获取当前user下的appName对应的cpu和mem使用情况
                        get<1>(tmps) += get<2>(process);//cpuUsed累加
                        get<2>(tmps) += get<3>(process);//memUsed累加
                        maps[iter2->first] = tmps;//用累加后的值覆盖掉第一次出现时的值
                    } else {
                        maps[get<0>(process)] = {get<0>(process), get<2>(process), get<3>(process)};
                }
            }
        }
        //step2. 返回的值时user下的app列表
        for (auto& it : maps) {
            useVec.push_back(it.second);
        }
        return useVec;
    }
    
    vector<string> GetTop3App(const vector<tuple<string, string, int, int>>& processes, const vector<string>& sortRules, const vector<string>& selectedUsers) {
    auto useVec = GetUseVec(processes, selectedUsers);//得到的user下的app列表
    //step3. 按照sortRules进行排序
    sort(useVec.begin(), useVec.end(), [&](const tuple<string, int, int>& p1, const tuple<string, int, int>& p2) ->bool{
        //按照cpu、mem使用情况进行降序排列
        for (const string &rule : sortRules) {
            if (rule == "cpuUsed") {
                if (get<1>(p1) != get<1>(p2)) {
                    return get<1>(p1) > get<1>(p2);
                }
            } else if (rule == "memUsed") {
                if (get<2>(p1) != get<2>(p2)) {
                    return get<2>(p1) > get<2>(p2);
                }
            }
        }
        return get<0>(p1) < get<0>(p2); // 默认按 appName 升序排序
    });
        //step4. 构建答案，进行输出
        vector<string> res;
        for (auto& item : useVec) {
            res.push_back(get<0>(item));
        }
        if (res.size() > 3) {// 只取前3个应用名
            res.resize(3);
        }
        return res;
    }
};

/*收获点：
1. unordered_set<string> uset(selectedUsers.begin(), selectedUsers.end()); 
   将vector替换为unordered_map，利用其count函数，提高查找效率
2. 可以使用std::get访问tuple中的成员，比如std::get<0>(obj)可访问obj中第一个成员
3. lamda函数进行复杂数据结构的排序   大于-->降序排列，小于-->升序排列
*/
