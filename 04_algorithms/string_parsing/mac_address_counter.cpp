/*
题目大意：
给定一个字符串 s，统计其中出现的不同 MAC 地址的数量。
MAC 地址由 6 组字节组成，每组用 2 位十六进制数表示，组与组之间以 '-' 或 ':' 分隔，
形如 XX-XX-XX-XX-XX-XX 或 XX:XX:XX:XX:XX:XX。
其中字母大小写不敏感；分隔符不同的等价 MAC 视为同一个地址
（解析时统一转为大写并以 '-' 连接后去重）。

示例一：
输入：s = "AA-BB-CC-DD-EE-FF"
输出：1
解释：字符串中包含一个使用 '-' 分隔的合法 MAC 地址。

示例二：
输入：s = "AA:BB:CC:DD:EE:FF aa-bb-cc-dd-ee-ff 01-23-45-67-89-AB"
输出：2
解释：前两个 MAC 只在大小写和分隔符上不同，规范化后都是
     "AA-BB-CC-DD-EE-FF"，因此只计算一次；第三个 MAC 与它不同。

实现思路：
在原串上以长度 17 为窗口枚举起点，分别尝试用 '-' 与 ':' 作为分隔符解析；
逐字节校验两位十六进制字符，合法则拼成规范形式插入 unordered_set 去重，
最后返回集合大小即为不同 MAC 的数量。
*/

#include <string>
#include <unordered_set>
#include <cctype>
#include <iostream>
#include <cassert>
using namespace std;

class Solution {
    public:
        // 统计字符串 s 中出现的不同 MAC 地址的数量
        int ParseMacNum(const string& s)
        {
            unordered_set<string>macs;                  // 用集合去重，存放规范化后的 MAC
            // 滑动窗口枚举每个起点 i，标准MAC地址的长度为 17（5 个分隔符 + 12 个十六进制字符）
            for(size_t i=0;i+17<=s.size();i++)
            {
                trySep(s,i,'-',macs);                    // 尝试用 '-' 作为分隔符解析
                trySep(s,i,':',macs);                    // 尝试用 ':' 作为分隔符解析
            }
            return macs.size();                          // 返回不同 MAC 的数量
        }
    private:
        // 从位置 i 开始，尝试按分隔符 sep 解析出一个 MAC；成功则加入 macs
        void trySep(const string& s,size_t i,char sep,unordered_set<string>& macs)
        {
            string mac;
            mac.reserve(17);                             // 预分配 17 字节，避免反复扩容
            for(int g=0;g<6;g++)                         // MAC 共 6 个字节
            {
                char a = s[i+g*3];                       // 每个字节占 2 个字符，字节间由 sep 隔开（步长 3）
                char b = s[i+g*3+1];
                if(!isxdigit(a)||!isxdigit(b))           // 两位必须都是十六进制字符
                {
                    return;                              // 不是合法十六进制，放弃本次解析
                }
                mac+=toupper(a);                         // 统一转大写，便于去重
                mac+=toupper(b);
                if(g<5)                                  // 前 5 个字节后需要跟分隔符
                {
                    if(s[i+g*3+2]!=sep)                  // 分隔符必须保持一致，不能混用，否则放弃
                        return;
                    mac+='-';                             // 规范化时统一用 '-' 连接
                }
            }
            macs.insert(mac);                            // 解析成功，插入集合（自动去重）
        }
};

int main()
{
    Solution sol;

    string input1 = "AA-BB-CC-DD-EE-FF";
    int actual1 = sol.ParseMacNum(input1);
    cout << "示例一：期望结果 = 1，实际结果 = " << actual1 << '\n';
    assert(actual1 == 1);

    string input2 = "AA:BB:CC:DD:EE:FF aa-bb-cc-dd-ee-ff 01-23-45-67-89-AB";
    int actual2 = sol.ParseMacNum(input2);
    cout << "示例二：期望结果 = 2，实际结果 = " << actual2 << '\n';
    assert(actual2 == 2);

    string input3 = "01-23-45-67-89-AA 01:23:45:67:89:AA invalid-MAC";
    int actual3 = sol.ParseMacNum(input3);
    cout << "补充测试：期望结果 = 1，实际结果 = " << actual3 << '\n';
    assert(actual3 == 1);

    cout << "All tests passed." << endl;
    return 0;
}
