/*
专题：numeric 数值工具（C++17）
任务：练习 accumulate 求和、iota 连续赋值、partial_sum 前缀和及 gcd/lcm。
示例一：输入 {1,2,3}，输出总和 6，前缀和 {1,3,6}。
解释：每个前缀和是从第一个元素到当前位置的累加结果。
示例二：输入 {1000000000,1000000000,1000000000}，输出总和 3000000000。
解释：求和超过 int，需要从 long long 初值开始计算。
*/
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

vector<long long> PrefixSums(const vector<int> &values)
{
    // partial_sum 的累加类型取决于输入元素类型，只把输出改为 long long 不够。
    vector<long long> wide(values.begin(), values.end());
    vector<long long> result(wide.size());
    partial_sum(wide.begin(), wide.end(), result.begin());
    return result;
}

int Check(const char *name, long long actual, long long expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int CheckPrefix(const vector<int> &input, const vector<long long> &expected)
{
    vector<long long> actual = PrefixSums(input);
    cout << "prefix expected=[";
    for (long long x : expected) cout << x << ' ';
    cout << "] actual=[";
    for (long long x : actual) cout << x << ' ';
    cout << ']' << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    vector<int> a = {1,2,3};
    failed += Check("sum", accumulate(a.begin(), a.end(), 0LL), 6);
    failed += CheckPrefix(a, {1,3,6});
    vector<int> big = {1000000000,1000000000,1000000000};
    failed += Check("wide sum", accumulate(big.begin(), big.end(), 0LL), 3000000000LL);
    failed += CheckPrefix(big, {1000000000LL,2000000000LL,3000000000LL});
    failed += CheckPrefix({-2,5,-1}, {-2,3,2});
    failed += CheckPrefix({}, {});
    vector<int> empty;
    failed += Check("empty sum", accumulate(empty.begin(), empty.end(), 0LL), 0);
    vector<int> sequence(4);
    iota(sequence.begin(), sequence.end(), 5);
    cout << "iota expected=[5 6 7 8] actual=[";
    for (int x : sequence) cout << x << ' ';
    cout << "]\n";
    failed += Check("iota values", sequence == vector<int>({5,6,7,8}), true);
    failed += Check("gcd", gcd(12,18), 6);
    failed += Check("lcm", lcm(12,18), 36);
    failed += Check("gcd negative", gcd(-12,18), 6);
    failed += Check("gcd zero", gcd(0,18), 18);
    failed += Check("gcd both zero", gcd(0,0), 0);
    failed += Check("lcm zero", lcm(0,18), 0);
    failed += Check("wide lcm", lcm(1000000000LL,3LL), 3000000000LL);
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：accumulate(..., 0LL) 从 long long 开始累加，写成 0 会按 int 累加。
iota/partial_sum 的目标位置必须已经存在，reserve 不能代替 resize。
前三种算法 O(n)；gcd 用欧几里得算法可在 O(log M) 内计算。
gcd/lcm 不是任意精度：输入绝对值和 lcm 结果必须能由参与计算的公共类型表示。
*/
