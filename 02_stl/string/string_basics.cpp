/*
专题：string 常用操作
任务：练习拼接、截取、查找、插入、删除、替换和整数转换。
示例一：s="hello world"，截取下标 6 开始的 5 个字符，输出 "world"。
解释：substr 的第二个参数是长度，不是结束下标。
示例二：s="a,b,c"，查找逗号得到 1，查找 "xyz" 得到 string::npos。
解释：找不到时不能把结果直接当作下标使用。
字符串示例使用 ASCII；std::string 的下标按字节计数，不能直接视为中文字符下标。
*/
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

int Check(const char *name, const string &actual, const string &expected)
{
    cout << name << " expected=\"" << expected << "\" actual=\"" << actual
         << '"' << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    string s = "hello";
    s += " world";
    failed += Check("append", s, "hello world");
    failed += Check("substring", s.substr(6, 5), "world");
    failed += Check("suffix", s.substr(6), "world");
    failed += Check("empty suffix", s.substr(s.size()), "");
    failed += Check("length", to_string(s.size()), "11");
    s[0] = 'H';
    s.push_back('!');
    failed += Check("modify", s, "Hello world!");
    s.pop_back(); // 必须非空；front/back 同样要求非空。
    s.replace(6, 5, "C++");
    failed += Check("replace", s, "Hello C++");
    s.insert(5, ",");
    failed += Check("insert", s, "Hello, C++");
    s.erase(5, 1);
    failed += Check("erase", s, "Hello C++");

    string csv = "a,b,c";
    size_t position = csv.find(',');
    failed += Check("find first", to_string(position), "1");
    position = csv.find(',', position + 1);
    failed += Check("find next", to_string(position), "3");
    failed += Check("not found", csv.find("xyz") == string::npos ? "yes" : "no", "yes");

    // stoi/stoll 允许只转换开头的数字，pos 告诉我们读到了哪里。
    size_t used = 0;
    int value = stoi("123abc", &used);
    failed += Check("stoi prefix", to_string(value), "123");
    failed += Check("characters consumed", to_string(used), "3");
    long long large = stoll("3000000000");
    failed += Check("stoll", to_string(large), "3000000000");
    failed += Check("negative", to_string(stoi("-42")), "-42");
    bool invalid = false;
    try { stoi("abc"); }
    catch (const invalid_argument &) { invalid = true; }
    failed += Check("invalid text", invalid ? "caught" : "missed", "caught");
    bool overflow = false;
    try { stoll("999999999999999999999999999999"); }
    catch (const out_of_range &) { overflow = true; }
    failed += Check("overflow", overflow ? "caught" : "missed", "caught");
    string empty;
    failed += Check("empty substring", empty.substr(0), "");
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：find 的返回值用 size_t 保存，并与 string::npos 比较。
substr 复制字符；erase/replace 的第二个参数也是长度。substr 起点大于 size 会抛异常。
下标访问 O(1)，substr O(截取长度)，中间插入删除通常需要 O(n) 移动。
整数转字符串用 to_string；转换输入不可信时要检查异常和是否消费了整个字符串。
*/
