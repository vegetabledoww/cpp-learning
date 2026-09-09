// ============================================================
// 题目：ARP 表与报文缓存系统
// ============================================================
//
// 【题目背景】
//
// 某网络设备向目的 IP 发送报文时，需要在 ARP 表中查找该 IP 对应的
// MAC 地址，以补全报文的二层信息并进行转发。
//
// 如果 ARP 表中不存在对应关系，设备需要暂时缓存该报文。后续配置了
// 对应的 ARP 表项后，设备应立即补发该 IP 对应的缓存报文。
//
// 请实现 ArpSys 类，并完成下面三个接口。
//
// ------------------------------------------------------------
// 【接口一】初始化
// ------------------------------------------------------------
//
// ArpSys(int arpCap, int cachedPktCap, int perIpCap)
//
// 参数含义：
//   arpCap       ：ARP 表最多能够保存的表项数量；
//   cachedPktCap ：设备最多能够缓存的报文总数；
//   perIpCap     ：同一个 IP 最多能够缓存的报文数量。
//
// ------------------------------------------------------------
// 【接口二】配置 ARP 表项
// ------------------------------------------------------------
//
// vector<int> update(int ip, string macAddr)
//
// 配置一条 ip -> macAddr 的映射关系。
//
// 1. 如果 ARP 表中已经存在该 ip：
//    - 使用新的 macAddr 覆盖旧值；
//    - 更新该表项的最近使用状态；
//    - 返回空数组 {}。
//
// 2. 如果 ARP 表中不存在该 ip，并且 ARP 表尚未达到容量上限：
//    - 直接添加该表项。
//
// 3. 如果 ARP 表中不存在该 ip，但是 ARP 表已经达到容量上限：
//    - 淘汰最久未被命中的表项；
//    - 再添加新的表项。
//
// “命中”包括：
//   - 查询已有的 ARP 表项；
//   - 添加新的 ARP 表项；
//   - 覆盖已有的 ARP 表项。
//
// 添加新的表项后：
//   - 如果该 ip 存在缓存报文，将所有 pktId 按升序返回，表示补发；
//   - 随后清空该 ip 对应的缓存报文；
//   - 如果该 ip 没有缓存报文，返回空数组 {}。
//
// ------------------------------------------------------------
// 【接口三】转发报文
// ------------------------------------------------------------
//
// string forward(int ip, int pktId)
//
// 1. 如果 ARP 表中存在该 ip：
//    - 更新该表项的最近使用状态；
//    - 返回对应的 macAddr，表示能够成功转发。
//
// 2. 如果 ARP 表中不存在该 ip：
//    - 尝试缓存 pktId；
//    - 无论缓存成功还是失败，都返回空字符串 ""。
//
// 出现下面任意一种情况时，本次缓存失败，不能保存 pktId：
//   - 设备已缓存的报文总数达到 cachedPktCap；
//   - 当前 ip 已缓存的报文数达到 perIpCap。
//
// ------------------------------------------------------------
// 【示例一：缓存报文并在配置 ARP 后补发】
// ------------------------------------------------------------
//
// ArpSys system(3, 5, 3);
//
// system.forward(10, 30)
//   返回：""
//   说明：ARP 表中没有 ip=10，缓存 pktId=30。
//
// system.forward(10, 12)
//   返回：""
//   说明：继续缓存 pktId=12。
//
// system.update(10, "AA-AA-AA-AA-AA-AA")
//   返回：{12, 30}
//   说明：添加 ip=10 的 ARP 表项，并按照升序补发两个缓存报文。
//
// system.forward(10, 99)
//   返回："AA-AA-AA-AA-AA-AA"
//   说明：ARP 表中已经存在 ip=10，可以直接转发。
//
// ------------------------------------------------------------
// 【示例二：同一个 IP 的缓存容量限制】
// ------------------------------------------------------------
//
// ArpSys system(3, 5, 2);
//
// system.forward(1, 5)  -> 返回 ""，成功缓存 pktId=5
// system.forward(1, 7)  -> 返回 ""，成功缓存 pktId=7
// system.forward(1, 9)  -> 返回 ""，但缓存失败
//
// 第三次调用时，ip=1 已经缓存了两个报文，达到 perIpCap=2。
// forward 在缓存成功和失败时都返回空字符串，因此需要通过后续 update
// 的返回结果判断实际缓存了哪些报文。
//
// system.update(1, "11-11-11-11-11-11")
//   返回：{5, 7}
//   说明：pktId=9 没有被缓存。
//
// ------------------------------------------------------------
// 【示例三：设备的缓存总容量限制】
// ------------------------------------------------------------
//
// ArpSys system(3, 2, 2);
//
// system.forward(1, 11) -> 返回 ""，成功缓存 pktId=11
// system.forward(2, 22) -> 返回 ""，成功缓存 pktId=22
// system.forward(3, 33) -> 返回 ""，但缓存失败
//
// 此时设备已经缓存了两个报文，达到 cachedPktCap=2。
//
// system.update(3, "33-33-33-33-33-33") -> 返回 {}
// system.update(1, "11-11-11-11-11-11") -> 返回 {11}
// system.update(2, "22-22-22-22-22-22") -> 返回 {22}
//
// ------------------------------------------------------------
// 【示例四：ARP 表满时淘汰最久未命中的表项】
// ------------------------------------------------------------
//
// ArpSys system(2, 5, 3);
//
// system.update(1, "AA-AA-AA-AA-AA-01") -> 返回 {}
// system.update(2, "AA-AA-AA-AA-AA-02") -> 返回 {}
// system.forward(1, 100)                  -> 返回 "AA-AA-AA-AA-AA-01"
//
// 上面的 forward 再次命中了 ip=1，因此此时 ip=2 比 ip=1 更久未被命中。
//
// system.update(3, "AA-AA-AA-AA-AA-03") -> 返回 {}
//
// ARP 表容量为2，添加 ip=3 时应淘汰 ip=2。
//
// system.forward(2, 200)
//   返回：""
//   说明：ip=2 已被淘汰，因此 pktId=200 被缓存。
//
// system.update(2, "BB-BB-BB-BB-BB-02")
//   返回：{200}
//   说明：重新添加 ip=2，并补发其缓存报文。
//
// ------------------------------------------------------------
// 【补充说明】
// ------------------------------------------------------------
//
// 1. pktId 在所有报文中全局唯一。
// 2. 同一个 ip 可以缓存多个 pktId。
// 3. update 返回缓存报文时，必须按照 pktId 从小到大排列。
// 4. 请自行选择成员变量和数据结构。
// 5. 不需要修改下面给出的类名、函数名、参数和返回类型。
//
// ============================================================

#include <string>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>
using namespace std;

class ArpSys {
private:
public:
//step1. 定义数据结构，复杂的一般用map（int->vector<int>）
    int time;    //时间，用来删除最久未使用的表单
    int arpcap;  //表单的最大数量
    int cachedpktcap; //缓存ip中最大的数量
    int peripcap;    //单个ip的缓存最大数量
    //这种问题一般是一个总表，后面跟着一两个辅表
    map<int,string>arpTable; //每个ip对应的mac表
    map<int,int>ipTime;   //每个ip出现时对应的时间表
    map<int,vector<int>>ipCache;//每个ip对应的pktId，可能不止一个，因此用vector来表示v

    //初始化整个函数
    ArpSys(int arpCap, int cachedPktCap, int perIpCap)
    {
       time = 0;
       arpcap = arpCap ;
       cachedpktcap = cachedPktCap;
       peripcap = perIpCap;
    }

    //更新ip table
    vector<int> update(int ip, string macAddr)
    {
        //step2. 给定的ip存在，更新此值
        time++;
        vector<int>res;
        if((arpTable.count(ip)))//给定的ip存在
        {
            arpTable[ip] = macAddr; //更新该ip的值
            ipTime[ip] = time;   //以备后面缓存删除
            return res;          //返回空数组
        }

        //step3. 表满了，要删除
        if(arpTable.size() >= arpcap)
        {
            int early_ip = 0;
            int min_time = INT_MAX;
            //开始寻找最小时间
            for(const auto& kv : ipTime)
            {
                if(kv.second < min_time)
                {
                    early_ip = kv.first;
                    min_time = kv.second;    
                }
            }
            //找到最小的之后删除之
            arpTable.erase(early_ip);
            ipTime.erase(early_ip);
            //如果有这个缓存也要清理掉
            if(ipCache.count(early_ip))
                ipCache.erase(early_ip);    
        }
        //step4. 表单未满，直接新增
        arpTable.insert({ip,macAddr});
        ipTime.insert({ip,time}); 
        //进行排序
        if(ipCache.count(ip))
        {
            res = ipCache[ip];
            sort(res.begin(),res.end());
            ipCache.erase(ip);//删除缓存
        }
        return res;
    }
    
    //转发报文
    string forward(int ip, int pktId)
    {
        time++;
        if((arpTable.count(ip)))//在缓存中
        {
            ipTime[ip] = time;
            return arpTable[ip];//直接返回此ip对应的mac地址
        }   
        //未返回证明不在arp表中，这时应该考虑是否超过总缓存限制
        int totalCached = 0;
        for (const auto& kv : ipCache)
        {
            totalCached += kv.second.size();//全部缓存的size()相加
        }

        if (ipCache[ip].size() >= peripcap)
        {
            return "";
        }
        //未返回证明缓存成功
        ipCache[ip].push_back(pktId);
        return "";
    }
};
