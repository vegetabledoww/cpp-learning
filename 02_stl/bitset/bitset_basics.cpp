/*
专题：bitset 固定长度位集合
任务：表示 8 个开关，练习设置、清除、翻转、查询、计数和位运算。
示例一：bitset<8>(5) 输出 00000101，count()=2，test(0)=true。
解释：整数 5 的二进制为 101，最右边是下标 0 的低位。
示例二：00000101 与 00000011 按位与，输出 00000001。
解释：只有两个操作数都为 1 的位才保留为 1。
*/
#include <bitset>
#include <iostream>
#include <string>
using namespace std;

int Check(const char *name, const string &actual, const string &expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    bitset<8> bits(5);
    failed += Check("integer construction", bits.to_string(), "00000101");
    failed += Check("count", to_string(bits.count()), "2");
    failed += Check("low bit", bits.test(0) ? "1" : "0", "1");
    bitset<8> other(string("00000011"));
    failed += Check("and", (bits & other).to_string(), "00000001");
    failed += Check("or", (bits | other).to_string(), "00000111");
    failed += Check("xor", (bits ^ other).to_string(), "00000110");
    failed += Check("not", (~bits).to_string(), "11111010");
    failed += Check("shift left", (bits << 1).to_string(), "00001010");
    failed += Check("shift right", (bits >> 1).to_string(), "00000010");
    failed += Check("shift all out", (bits << 8).to_string(), "00000000");
    bits.set(7); // 设置单个位为 1；省略参数的 set() 设置全部位。
    bits.reset(0);
    bits.flip(2);
    failed += Check("set reset flip", bits.to_string(), "10000000");
    bits[1] = true;
    failed += Check("subscript write", bits.to_string(), "10000010");
    failed += Check("to integer", to_string(bits.to_ulong()), "130");
    bits.reset();
    failed += Check("none", bits.none() ? "yes" : "no", "yes");
    failed += Check("any empty", bits.any() ? "yes" : "no", "no");
    bits.set();
    failed += Check("all", bits.all() ? "yes" : "no", "yes");
    failed += Check("size fixed", to_string(bits.size()), "8");
    bits.flip();
    failed += Check("flip all", bits.to_string(), "00000000");
    bitset<8> zero;
    failed += Check("default zero", zero.to_string(), "00000000");
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：N 是类型的一部分，bitset<N> 长度固定，只保存二进制位。
位下标从右向左数；打印的字符串从高位到低位。下标必须小于 N。
to_ulong/to_ullong 结果放不进目标整数类型时会抛 overflow_error。
位集合整体操作工作量随位数增加，常见实现按机器字批量处理，不能一概说 O(1)。
*/
