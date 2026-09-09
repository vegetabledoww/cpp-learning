/*
题目：解析 IPv4 首部字段

给定一个由空格分隔的 IPv4 首部十六进制字符串。每两个十六进制字符
表示一个字节，取值范围为 00 到 ff，字节下标从 0 开始。

IPv4 基础首部的 20 个字节分布如下：

字节下标：  0    1    2-3    4-5      6-7       8    9    10-11    12-15    16-19
字段含义：版本  服务  总长度  标识符  Flags和偏移  TTL  协议  校验和    源IP     目的IP

请按照下面的规则计算三个结果：

1. 总长度 totalLength
   第 2 号字节是总长度的高 8 位，第 3 号字节是低 8 位。
   先把高位字节左移 8 位，再与低位字节拼接：

       totalLength = (bytes[2] << 8) | bytes[3]

2. Flags
   第 6、7 号字节共同保存“3 位 Flags + 13 位分片偏移”：

       bytes[6]                     bytes[7]
       F F F O O O O O              O O O O O O O O
       ----- -------------------------------
       Flags       13 位分片偏移

   因此 Flags 位于第 6 号字节的最高 3 位。右移 5 位，丢掉该字节
   低位的 5 个偏移位，即可得到 Flags：

       flags = bytes[6] >> 5

   三个 Flags 位从高到低分别是：保留位、DF（禁止分片）、MF（后续还有分片）。

3. 目的 IPv4 地址 destIP
   第 16、17、18、19 号字节分别对应目的 IP 的四段。
   把每个十六进制字节转换为十进制，再用小数点连接：

       bytes[16].bytes[17].bytes[18].bytes[19]

返回格式：总长度,Flags,目的IP

本题输入至少包含 IPv4 基础首部的 20 个字节。

示例 1：
输入：
45 00 10 3c 7c 48 20 03 80 06 00 00 c0 a8 01 02 c0 a8 14 b8
输出：
4156,1,192.168.20.184
解释：
- 总长度：第 2、3 号字节为 10、3c，
  0x10 * 256 + 0x3c = 16 * 256 + 60 = 4156。
- Flags：第 6 号字节为 20，二进制是 00100000，
  最高 3 位是 001，转换成十进制是 1。
- 目的 IP：第 16 到 19 号字节为 c0、a8、14、b8，
  分别转换成 192、168、20、184，结果为 192.168.20.184。

示例 2：
输入：
45 00 00 3c 12 34 40 00 40 11 00 00 0a 00 00 01 ac 10 00 05
输出：
60,2,172.16.0.5
解释：
- 总长度：第 2、3 号字节为 00、3c，
  0x00 * 256 + 0x3c = 0 + 60 = 60。
- Flags：第 6 号字节为 40，二进制是 01000000，
  最高 3 位是 010，转换成十进制是 2。
- 目的 IP：第 16 到 19 号字节为 ac、10、00、05，
  分别转换成 172、16、0、5，结果为 172.16.0.5。
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string parseIPHeader(const string &headerStr)
{
    vector<int>bytes;
    istringstream iss(headerStr);
    string byteStr;
    size_t pos;
    //按照空格分割，并把每个十六进制字节转换为十进制整数
    while (getline(iss,byteStr,' '))
    {
      bytes.push_back(stoi(byteStr, &pos, 16));
      //cout<<"pos is"<<" "<<pos<<endl;  //从字符串开头开始，成功参与数字转换的字符数量
    }

    //IPv4 的多字节字段按照网络字节序存放，高位字节在前
    int totalLength = (bytes[2] << 8) | bytes[3];
    int flags = bytes[6] >> 5;

    string destIP = to_string(bytes[16]) + "." +
                    to_string(bytes[17]) + "." +
                    to_string(bytes[18]) + "." +
                    to_string(bytes[19]);

    return to_string(totalLength) + "," +
           to_string(flags) + "," + destIP;
}

int main()
{
    string header1 = "45 00 10 3c 7c 48 20 03 80 06 00 00 c0 a8 01 02 c0 a8 14 b8";
    cout << "Example 1, expected=4156,1,192.168.20.184\n";
    cout << "actual=" << parseIPHeader(header1) << '\n';

    string header2 = "45 00 00 3c 12 34 40 00 40 11 00 00 0a 00 00 01 ac 10 00 05";
    cout << "Example 2, expected=60,2,172.16.0.5\n";
    cout << "actual=" << parseIPHeader(header2) << '\n';
    return 0;
}
