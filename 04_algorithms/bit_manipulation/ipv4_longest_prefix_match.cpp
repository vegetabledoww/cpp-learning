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

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
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
            result = (result << 8) | static_cast<uint32_t>(stoi(segment));
        }

        return result;
    }

    // 普通比较函数：前缀越长，排序后越靠前
    static bool longerPrefixFirst(const pair<int, string> &a,
                                  const pair<int, string> &b)
    {
        return a.first > b.first;
    }

    string RouterSearch(const string &dstIp, const vector<string> &ipTable)
    {
        vector<pair<int, string>> routes;
        routes.reserve(ipTable.size());

        // 将每条路由拆分为前缀长度和 IP 地址
        for (const string &element : ipTable)
        {
            size_t pos = element.find('/');
            if (pos == string::npos)
                continue;

            string ip = element.substr(0, pos);
            int prefix = stoi(element.substr(pos + 1));
            routes.push_back({prefix, ip});
        }

        // stable_sort 保证相同前缀长度的路由仍保持原有顺序
        stable_sort(routes.begin(), routes.end(), longerPrefixFirst);

        uint32_t dst = string2ip(dstIp);
        string defaultRoute;

        // 从最长前缀开始检查，首个匹配项就是答案
        for (const pair<int, string> &route : routes)
        {
            int prefix = route.first;

            if (prefix == 0)
            {
                if (defaultRoute.empty())
                    defaultRoute = route.second + "/0";
                continue;
            }

            uint32_t entry = string2ip(route.second);
            uint32_t mask = UINT32_MAX << (32 - prefix);

            if ((dst & mask) == (entry & mask))
                return route.second + '/' + to_string(prefix);
        }

        return defaultRoute.empty() ? "empty" : defaultRoute;
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
