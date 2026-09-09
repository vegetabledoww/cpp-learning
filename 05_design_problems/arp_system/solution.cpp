/*
某网络设备向目的IP发送报文时，需要在ARP表中根据已配置的表项（表项即为IP 和 MAC地址的映射关系），找到对应的MAC地址，补全报文的二层信息后进行转发；如果找不到，则需要将报文缓存起来，
等到后续配置了对应的表项后，再立即进行补发。

请实现如下接口：

ArpSys(int arpCap, int cachedPktCap, int perIpCap) - 初始化

ARP表中表项的最大数量为 arpCap；
缓存能力：设备最多可缓存 cachedPktCap 个报文，且同一个IP最多缓存perIpCap 个报文。
update(int ip, string macAddr) - 配置一条ARP表的表项：

如果已存在该 ip 的映射关系，则覆盖该 ip 对应的 macAddr；返回空列表 []。

如果不存在，

当表项未满时，直接添加一条表项；
当表项已满时，将最久未被命中（包括查询、添加和覆盖配置）的表项替换。
添加或替换表项后，将该 ip 缓存的报文升序返回（模拟补发），然后清空对应 ip 的缓存报文。

forward(int ip, int pktId) - 在ARP表中查询此 ip 对应的 macAddr，进行模拟转发：

若找到对应的 macAddr，则返回该 macAddr 表示能成功转发；
否则，尝试将报文 pktId 进行缓存，返回空字符串 "" ：
若超出 cachedPktCap 或 perIpCap 中的任一个，则缓存失败；
否则，缓存成功。
注：报文 pktId 全局唯一。
*/
#include <bits/stdc++.h>
#include <string>
using namespace std;
class ArpSys {
public:
    int time;          // 新加的时间，用来删除最久未使用的那个表单
    int arpcap;        // 表单中的最大数量
    int cachedpktcap;  // 缓存ip中缓存最大数量
    int peripcap;      // 单个ip的缓存最大数量

    map<int, string> arpTable;      // 每个ip对应的mac表
    map<int, int> ipTime;           // 每个ip出现时对应的时间表
    map<int, vector<int>> ipCache;  // 每个ip对应的pktId，可能不止一个，因此用vector
    // 初始化函数
    ArpSys(int arpCap, int cachedPktCap, int perIpCap)
        : time(0),
          arpcap(arpCap),
          cachedpktcap(cachedPktCap),
          peripcap(perIpCap)
    {
        // 表项最大数量
        // 设备最多缓存报文数
        // 每个ip最多缓存的报文数
        // cout<<"null";
    }
    // 更新arp表内容
    vector<int> Update(int ip, const string &macAddr)
    {
        ++time;
        vector<int> res;
        if ((arpTable.count(ip)) != 0) {  // 这个ip值存在
            arpTable[ip] = macAddr;       // 更新该ip值
            ipTime[ip] = time;            // 更新时间
            return res;                   // 返回空数组
        }
        // 表项满了
        if (arpTable.size() >= arpcap) {
            int early_ip = 0;
            int min_time = INT_MAX;
            // 寻找最小时间项
            for (auto &kv : ipTime) {
                if (kv.second < min_time) {
                    early_ip = kv.first;
                    min_time = kv.second;
                }
            }
            // 三个map都要删除
            // 然后删除这个ip表单
            arpTable.erase(early_ip);
            // 删除其对应的时间
            ipTime.erase(early_ip);
            // 可能需要清理对应的缓存
            if ((ipCache.count(early_ip)) != 0) {
                ipCache.erase(early_ip);
            }
        }
        // 表单未满，则直接新增
        arpTable[ip] = macAddr;
        ipTime[ip] = time;
        return reIpcache(ip);
    }
    // 返回选项
    vector<int> reIpcache(int ip)
    {
        vector<int> res;
        // ipCache中配置了此ip的表项，则按照升序返回该值，并在缓存中删除该表项
        if ((ipCache.count(ip)) != 0) {
            res = ipCache[ip];
            sort(res.begin(), res.end());
            ipCache.erase(ip);
        }
        return res;
    }

    string Forward(int ip, int pktId)
    {
        ++time;
        // 通过ip值判断是否在缓存之中
        if ((arpTable.count(ip)) != 0) {
            ipTime[ip] = time;    // 更新时间戳
            return arpTable[ip];  // 直接返回此ip对应的mac地址
        }
        // 未返回证明当前ip并不在arp表中
        // 检查是否超过总缓存限制
        int totalCached = 0;
        for (const auto &kv : ipCache) {
            totalCached += kv.second.size();
        }

        if (totalCached >= cachedpktcap) {
            return "";
        }

        // 检查单IP缓存限制
        if (ipCache[ip].size() >= peripcap) {
            return "";
        }
        // 未返回说明未超过总缓存限制，也未超过单ip缓存限制,则缓存成功
        // 此时，向ip缓存中添加pktId,以备arp表中有了此ip缓存之后可以直接输出pktId序列
        ipCache[ip].push_back(pktId);
        return "";
    }
};

void print_ele(vector<int> v)
{
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(int /* argc */, char const *argv[] /* argv */)
{
    ArpSys S(3, 3, 2);
    print_ele(S.Update(123, "AB-AB-AB-AB-AB-AB"));
    cout << S.Forward(456, 23) << endl;
    cout << S.Forward(456, 0) << endl;
    cout << S.Forward(456, 8) << endl;
    print_ele(S.Update(456, "BA-BA-BA-BA-BA-BA"));
    print_ele(S.Update(456, "CD-EF-AB-AA-AB-AB"));
    cout << S.Forward(123, 5) << endl;
    return 0;
}

/* 收获点：
1. 设计题写法：先定义好数据结构，一般套路是在全局定义数据结构，初始化时将初始化函数中的变量赋值给全局变量，便于后面函数的调用；
2. time变量的引入：因为有最久未使用的限制，所以引入iptime（map）数据结构,实时更新ip调用时间；
3. 根据题目描述，一条一条的写逻辑，建议先把思路（骨架）写出，然后再丰富细节
*/