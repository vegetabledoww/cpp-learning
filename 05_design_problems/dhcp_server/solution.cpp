/*
题目：DHCP 地址分配系统（根据用户草稿补齐的学习题）

原题来源、地址范围与完整规则尚未提供。下面的地址池、分配优先级和失败返回值
是本练习明确采用的约定，不代表已核实的原题规则；本程序只模拟状态，不操作网络。

实现类 DHCPServerSys，提供默认构造函数和两个接口：
1. string Request(const string& mac)：为设备申请地址。
   a. 设备正在使用地址：返回原地址，不重复分配。
   b. 设备曾释放的地址仍在回收表：优先取回这个地址，恢复占用状态。
   c. 否则，分配从未使用过的最小地址。
   d. 若没有未使用地址，分配回收表中最小的地址，并移除旧设备的回收记录。
   e. 所有地址都被占用时，返回空字符串 ""，状态不变。
2. bool Release(const string& mac)：若设备正在使用地址，将其移入回收表，
   返回 true；设备不存在或已释放则返回 false。

本练习地址池固定为 192.168.0.1～192.168.0.4，方便手工验证地址耗尽与复用。
地址大小按最后一段数字比较；地址池已按这个顺序保存，不对 IP 字符串排序。
MAC 作为非空、大小写敏感的唯一标识，示例简写为 A、B 等，不校验真实 MAC 格式。
不模拟租期、超时、网络报文或并发操作；不同系统对象状态相互独立。

示例一（一个新系统）：
Request("A") -> "192.168.0.1"
Request("A") -> "192.168.0.1"
Release("A") -> true
Release("A") -> false
Request("A") -> "192.168.0.1"
解释：重复请求返回原地址；回收地址没有被别人复用时，原设备可以优先取回。

示例二（另一个新系统）：
Request("A") -> "192.168.0.1"
Release("A") -> true
Request("B") -> "192.168.0.2"
Request("C") -> "192.168.0.3"
Request("D") -> "192.168.0.4"
Request("E") -> "192.168.0.1"
Request("A") -> ""
解释：新设备优先使用未分配过的地址，耗尽未使用地址后才复用回收地址。
E 复用了 A 的旧地址后，A 不能再直接返回该地址，否则会与 E 冲突。
*/
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class DHCPServerSys
{
private:
    vector<pair<string, string>> mp; // 正在使用的表：{MAC, IP}。
    vector<pair<string, string>> jc; // 已释放且尚未被复用的表：{原 MAC, IP}。
    vector<string> addressPool;

    bool HasAddress(const vector<pair<string, string>> &table, const string &ip) const
    {
        for (const auto &record : table)
        {
            if (record.second == ip) return true;
        }
        return false;
    }

public:
    DHCPServerSys()
    {
        for (int last = 1; last <= 4; last++)
            addressPool.push_back("192.168.0." + to_string(last));
    }

    string Request(const string &mac)
    {
        for (const auto &record : mp)
        {
            if (record.first == mac) return record.second;
        }
        // 必须遍历完使用表，才能确定不存在；不能放在首个不匹配元素的 else 中。

        for (auto it = jc.begin(); it != jc.end(); ++it)
        {
            if (it->first == mac)
            {
                string ip = it->second;
                mp.push_back(*it); // 取回地址，同时恢复占用状态。
                jc.erase(it);
                return ip;
            }
        }

        for (const string &ip : addressPool)
        {
            // 既不在使用表也不在回收表，说明该地址从未分配过。
            if (!HasAddress(mp, ip) && !HasAddress(jc, ip))
            {
                mp.push_back({mac, ip});
                return ip;
            }
        }

        // 按地址池顺序挑选，不能依赖回收时间顺序。
        for (const string &ip : addressPool)
        {
            for (auto it = jc.begin(); it != jc.end(); ++it)
            {
                if (it->second == ip)
                {
                    jc.erase(it); // 撤销原设备的回收记录，防止原设备以后抢回地址。
                    mp.push_back({mac, ip});
                    return ip;
                }
            }
        }
        return "";
    }

    bool Release(const string &mac)
    {
        for (auto it = mp.begin(); it != mp.end(); ++it)
        {
            if (it->first == mac)
            {
                jc.push_back(*it); // 先保存，erase 之后 it 就不能再使用。
                mp.erase(it);
                return true;
            }
        }
        return false;
    }
};

int Check(const char *name, const string &actual, const string &expected)
{
    cout << name << " expected=\"" << expected << "\" actual=\"" << actual << '"'
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int Check(const char *name, bool actual, bool expected)
{
    cout << boolalpha << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    DHCPServerSys first;
    failed += Check("release on empty table", first.Release("A"), false);
    failed += Check("example 1 first request", first.Request("A"), "192.168.0.1");
    failed += Check("example 1 repeated request", first.Request("A"), "192.168.0.1");
    failed += Check("example 1 release", first.Release("A"), true);
    failed += Check("example 1 repeated release", first.Release("A"), false);
    failed += Check("example 1 reclaim", first.Request("A"), "192.168.0.1");
    failed += Check("reclaim restores active state", first.Release("A"), true);
    failed += Check("second reclaim", first.Request("A"), "192.168.0.1");

    DHCPServerSys second;
    failed += Check("example 2 independent system", second.Request("A"), "192.168.0.1");
    failed += Check("example 2 release", second.Release("A"), true);
    failed += Check("example 2 unused before recycled", second.Request("B"), "192.168.0.2");
    failed += Check("example 2 next unused", second.Request("C"), "192.168.0.3");
    failed += Check("find MAC beyond first record", second.Request("C"), "192.168.0.3");
    failed += Check("example 2 last unused", second.Request("D"), "192.168.0.4");
    failed += Check("example 2 reuse old address", second.Request("E"), "192.168.0.1");
    failed += Check("example 2 old owner cannot reclaim", second.Request("A"), "");
    failed += Check("exhausted pool", second.Request("F"), "");
    failed += Check("failed request creates no lease", second.Release("F"), false);
    failed += Check("old owner cannot release new lease", second.Release("A"), false);
    failed += Check("current owner unchanged", second.Request("E"), "192.168.0.1");

    // 先回收较大地址 4，再回收较小地址 2，验证不是按回收顺序分配。
    failed += Check("release larger first", second.Release("D"), true);
    failed += Check("release smaller second", second.Release("B"), true);
    failed += Check("smallest recycled first", second.Request("F"), "192.168.0.2");
    failed += Check("old owner gets different free address", second.Request("B"), "192.168.0.4");
    failed += Check("displaced owner blocked", second.Request("D"), "");
    failed += Check("reused lease can release", second.Release("F"), true);
    failed += Check("reused lease can reclaim", second.Request("F"), "192.168.0.2");

    // 自己的旧地址优先级高于“回收表中的最小地址”。
    failed += Check("free smallest", second.Release("E"), true);
    failed += Check("free personal address", second.Release("C"), true);
    failed += Check("own address has priority", second.Request("C"), "192.168.0.3");
    failed += Check("other device reuses smallest", second.Request("G"), "192.168.0.1");
    failed += Check("first instance unaffected", first.Request("A"), "192.168.0.1");
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. 查表的“不存在”结论必须在完整查找后得出，不能根据第一个元素判断。
2. Request/Release 都在改变状态：返回地址的同时，要更新它属于哪个表。
3. 同一个 IP 不能同时出现在使用表和回收表，也不能同时分配给两个 MAC。
4. vector.erase 会使被删位置及之后的迭代器失效；删除前保存所需数据。
5. 地址池 N 个地址时，本扫描版本 Request 最坏 O(N^2)，Release O(N)，
   总存储 O(N)（按固定长度地址与 MAC 计）。练习采用小池，优先保证清晰易懂。
*/
