/*
题目：十六进制分组异或校验和

给定一个只包含十六进制字符的字符串 inputStr，请按照以下规则计算校验和：

1. 如果字符串长度不是 8 的倍数，则在字符串末尾补字符 'F'，
   直到字符串长度成为 8 的倍数；如果已经是 8 的倍数，则不补字符。
2. 字符串中的小写字母 a~f 按照对应的大写字母 A~F 处理。
3. 从左到右每 8 个字符分为一组，将每组看作一个 32 位十六进制无符号整数。
4. 将所有分组进行按位异或，得到最终校验和。
5. 返回一个长度固定为 8 的大写十六进制字符串，不足 8 位时在前面补 '0'。

题目保证 inputStr 只包含字符 0~9、a~f 和 A~F。

示例一：
输入：inputStr = "687561776569"
补齐："687561776569FFFF"
分组："68756177"、"6569FFFF"
计算：0x68756177 XOR 0x6569FFFF = 0x0D1C9E88
输出："0D1C9E88"

示例二：
输入：inputStr = "ABCDEF01abcdef01"
统一大写后分组："ABCDEF01"、"ABCDEF01"
计算：0xABCDEF01 XOR 0xABCDEF01 = 0x00000000
输出："00000000"
*/

#include <cctype>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Solution
{
public:
    string SimpleCheckSum(const string &inputStr)
    {
        // 在末尾补 F，使总长度成为 8 的倍数。
        string s = inputStr;
        size_t pad = (8 - s.length() % 8) % 8;
        s.append(pad, 'F');

        // 统一转换成大写，后面只需处理 0~9 和 A~F。
        for (char &c : s)
        {
            c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
        }

        // 每 8 个字符转换成一个 32 位整数，再依次进行异或。
        uint32_t token = 0;
        for (size_t i = 0; i < s.length(); i += 8)
        {
            token ^= Hex8ToUint(s.c_str() + i);
        }

        // 使用输出流将整数格式化为 8 位大写十六进制字符串。
        ostringstream output;
        output << hex << token;
        return output.str();
    }

private:
    // 把连续 8 个大写十六进制字符转换成一个 32 位无符号整数。
    static uint32_t Hex8ToUint(const char *p)
    {
        uint32_t value = 0;
        for (int i = 0; i < 8; i++)
        {
            char c = p[i];
            uint32_t digit = (c <= '9') ? (c - '0') : (c - 'A' + 10);
            value = (value << 4) | digit;
        }
        return value;
    }
};

int main()
{
    Solution solution;

    string input1 = "687561776569";
    cout << "example 1\n";
    cout << "expected=0D1C9E88\n";
    cout << "actual=" << solution.SimpleCheckSum(input1) << "\n\n";

    string input2 = "ABCDEF01abcdef01";
    cout << "example 2\n";
    cout << "expected=00000000\n";
    cout << "actual=" << solution.SimpleCheckSum(input2) << '\n';

    return 0;
}

/*
收获点：
1. 使用 (8 - len % 8) % 8 计算需要补齐的字符数量。
2. 每个十六进制字符代表 4 个二进制位，可以通过左移 4 位完成拼接。
3. 异或满足交换律和结合律，因此可以从左到右直接累计，不需要使用栈。
4. 使用 hex、uppercase、setw 和 setfill 可以控制整数的十六进制输出格式。
*/
