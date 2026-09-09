/*
题目：IPv4 路由最长前缀匹配

给定一个目标 IPv4 地址 dstIp 和一张路由表 ipTable。
路由表中的每个元素格式为 "a.b.c.d/m"，其中 m 表示网络前缀长度。

如果目标 IP 和某条路由的前 m 个二进制位相同，则称该路由匹配目标 IP。
请返回所有匹配路由中前缀长度最大的那一条。

如果有多条相同长度的路由同时匹配，返回它们在 ipTable 中最先出现的一条；
如果没有任何路由匹配，返回字符串 "empty"。前缀长度为 0 的路由可以匹配任意 IP。

题目保证：
1. dstIp 和路由中的 IP 都是合法的 IPv4 地址；
2. 每条路由都包含合法的前缀长度，范围为 [0, 32]。

示例 1：
输入：
dstIp = "192.168.0.3"
ipTable = {"10.166.50.0/23", "192.0.0.0/8", "10.255.255.255/32",
           "192.168.0.1/24", "127.0.0.0/8", "192.168.0.0/24"}
输出："192.168.0.1/24"
解释：两条 /24 路由都能匹配，返回路由表中先出现的 "192.168.0.1/24"。

示例 2：
输入：
dstIp = "8.8.8.8"
ipTable = {"10.0.0.0/8", "172.16.0.0/12", "0.0.0.0/0"}
输出："0.0.0.0/0"
解释：前两条路由都不匹配，因此返回能够匹配任意 IP 的默认路由。
*/

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    uint32_t string2ip(const string &ip)
    {
        // TODO：将点分十进制 IPv4 地址转换为 32 位无符号整数
        uint32_t nums = 0;
        stringstream ss(ip);
        string segment;
        while (getline(ss,segment,'.'))
        {
            nums = nums << 8 | (uint32_t)stoi(segment);  
        }   
        return nums;
    }

    string RouterSearch(const string &dstIp, const vector<string> &ipTable)
    {
        // TODO：查找与 dstIp 匹配并且前缀最长的路由
        uint32_t dst = string2ip(dstIp);
        int pre_length = -1;
        int prefix = -1;
        string answer;
        for (auto const ele : ipTable)
        {
            size_t pos = ele.find('/');
            if(pos == string::npos)
                continue;
            string stringip = ele.substr(0,pos);
            prefix = stoi(ele.substr(pos+1));
            uint32_t ip = string2ip(stringip);
            uint32_t mask = prefix == 0
                                ? 0
                                : UINT32_MAX << (32 - prefix);
            bool matched = (ip & mask)== (dst & mask);//判断在掩码的范围内是否相同
            if(matched && (prefix > pre_length))
            {
                pre_length = prefix;//更新最大前缀长度
                answer = stringip + '/'+ to_string(pre_length);
            }
        }
        
        return pre_length == -1 ? "empty" : answer;
    }
};

int main()
{
    Solution solution;

    string dstIp1 = "192.168.0.3";
    vector<string> ipTable1 = {
        "10.166.50.0/23",
        "192.0.0.0/8",
        "10.255.255.255/32",
        "192.168.0.1/24",
        "127.0.0.0/8",
        "192.168.0.0/24"
    };
    cout << "example 1: expected=192.168.0.1/24, actual="
         << solution.RouterSearch(dstIp1, ipTable1) << '\n';

    string dstIp2 = "8.8.8.8";
    vector<string> ipTable2 = {
        "10.0.0.0/8",
        "172.16.0.0/12",
        "0.0.0.0/0"
    };
    cout << "example 2: expected=0.0.0.0/0, actual="
         << solution.RouterSearch(dstIp2, ipTable2) << '\n';

    return 0;
}
