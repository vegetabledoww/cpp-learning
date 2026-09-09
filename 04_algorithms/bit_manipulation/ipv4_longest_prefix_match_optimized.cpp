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
    // 将点分十进制 IPv4 地址转换为 32 位无符号整数
    uint32_t string2ip(const string &ip)
    {
        uint32_t result = 0;
        stringstream ss(ip);
        string segment;

        while (getline(ss, segment, '.'))
        {
            //先左移八位，再或上分段的ip地址，即得到32位无符号整数
            result = (result << 8) | static_cast<uint32_t>(stoi(segment));
        }

        return result;
    }

    string RouterSearch(const string &dstIp, const vector<string> &ipTable)
    {
        uint32_t dst = string2ip(dstIp);
        int bestPrefix = -1;
        string bestRoute;

        // 一次遍历所有路由，只记录当前最长的匹配项
        for (const string &element : ipTable)
        {
            size_t pos = element.find('/');
            if (pos == string::npos)//表示没找到，路由格式不正确
                continue;

            string ip = element.substr(0, pos);//字符串分割
            int prefix = stoi(element.substr(pos + 1));//这个就是后面的掩码数
            uint32_t entry = string2ip(ip);

            // /0 的掩码为 0，能够匹配任意目标 IP
            uint32_t mask = prefix == 0
                                ? 0
                                : UINT32_MAX << (32 - prefix);

            bool matched = (dst & mask) == (entry & mask);//表示掩码条件下是否相等
            if (matched && prefix > bestPrefix)
            {
                bestPrefix = prefix;
                bestRoute = element;
            }
        }

        return bestPrefix == -1 ? "empty" : bestRoute;
    }
};

void runExample(int number,
                const string &dstIp,
                const vector<string> &ipTable,
                const string &expected)
{
    Solution solution;
    string actual = solution.RouterSearch(dstIp, ipTable);

    cout << "example " << number << ": "
         << (actual == expected ? "PASS" : "FAIL")
         << ", expected=" << expected
         << ", actual=" << actual << '\n';
}

int main()
{
    runExample(1,
               "192.168.0.3",
               {"10.166.50.0/23",
                "192.0.0.0/8",
                "10.255.255.255/32",
                "192.168.0.1/24",
                "127.0.0.0/8",
                "192.168.0.0/24"},
               "192.168.0.1/24");

    runExample(2,
               "8.8.8.8",
               {"10.0.0.0/8", "172.16.0.0/12", "0.0.0.0/0"},
               "0.0.0.0/0");

    return 0;
}
