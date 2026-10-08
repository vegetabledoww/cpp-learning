/*
题目：代码量统计系统（根据用户代码整理的学习题）

未提供原题来源和完整约束，以下为本练习的明确约定，不代表原题原文。

一个产品包含若干代码仓，每个仓库可以使用多种语言。实现三个接口：
1. CodeStatsSystem(products)：初始化系统，清空旧数据，所有代码量从 0 开始。
   products 的每项为 {产品编号, 仓库编号列表}。
2. ChangeCodelines(repoId, languageId, codeline)：将指定仓库、指定语言的
   代码量加上 codeline，返回修改后的代码量。codeline 可以为正、负或 0。
3. StatLanguage(productId)：汇总该产品所有仓库中各语言的代码量，
   只返回总量大于 0 的语言编号，按总量降序、总量相同时按语言编号升序排列。
   productId=0 表示统计全部产品的全部仓库。

本练习约束：
- 产品编号为正且不重复，0 保留给全局查询；仓库编号为正且全局不重复，
  一个仓库只属于一个产品。允许产品列表为空，也允许产品没有仓库。
- 语言编号为 1～6；更新只针对初始化时登记的仓库。
- 每次更新后，该仓库该语言的代码量在 [0, INT_MAX] 内，不需要处理非法更新。
- 跨仓库总量可能超过 int，汇总使用 long long，并约定总量在其范围内。
- 不存在的产品查询返回空数组；本例采用用户原来的单系统、普通函数接口。

示例一：
CodeStatsSystem({{10,{102,101}}})
StatLanguage(0)                 -> {}
ChangeCodelines(102,2,100)       -> 100
StatLanguage(0)                 -> {2}
ChangeCodelines(102,2,-100)      -> 0
StatLanguage(0)                 -> {}
解释：增加代码后语言 2 出现，减少到 0 后不再出现在统计结果中。

示例二：
CodeStatsSystem({{10,{101,102}},{20,{201}}})
ChangeCodelines(101,2,100)       -> 100
ChangeCodelines(102,2,50)        -> 50
ChangeCodelines(101,1,150)       -> 150
ChangeCodelines(201,3,200)       -> 200
StatLanguage(10)                -> {1,2}
StatLanguage(20)                -> {3}
StatLanguage(0)                 -> {3,1,2}
解释：全局语言 3 为 200 行，语言 1 和 2 都为 150 行，同量时编号 1 排在 2 前。
*/
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

vector<int> repo;
vector<vector<int>> repo_code_lines; // 每行：{仓库编号, 语言编号, 代码量}。
unordered_map<int, vector<int>> mp;  // 产品编号 -> 仓库列表；0 对应全部仓库。

void CodeStatsSystem(const vector<pair<int, vector<int>>> &products)
{
    // 本例使用全局变量，重新初始化时必须清空上一轮数据。
    repo.clear();
    repo_code_lines.clear();
    mp.clear();
    for (const auto &product : products)
    {
        for (int repoId : product.second) repo.push_back(repoId);
        mp[product.first] = product.second;
    }
    mp[0] = repo;
}

int exist(const vector<vector<int>> &v, int a, int b)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i][0] == a && v[i][1] == b)
            return static_cast<int>(i) + 1;
    }
    return 0; // 保留原约定：0 表示没找到，找到则返回下标加 1。
}

int ChangeCodelines(int repoId, int languageId, int codeline)
{
    int flag = exist(repo_code_lines, repoId, languageId);
    if (flag != 0)
    {
        repo_code_lines[flag - 1][2] += codeline;
        return repo_code_lines[flag - 1][2];
    }
    // 空表也会走到这里，不需要再单独写 empty 分支。
    repo_code_lines.push_back({repoId, languageId, codeline});
    return codeline;
}

bool CompareLanguage(const pair<long long, int> &a, const pair<long long, int> &b)
{
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}

vector<int> StatLanguage(int productId)
{
    auto position = mp.find(productId);
    if (position == mp.end()) return {};
    const vector<int> &repo_id = position->second;

    vector<long long> language_id_lines(7, 0); // 0 号位置不使用；汇总可能超过 int。
    for (int ele : repo_id)
    {
        for (size_t i = 0; i < repo_code_lines.size(); i++)
        {
            if (repo_code_lines[i][0] == ele)
                language_id_lines[repo_code_lines[i][1]] += repo_code_lines[i][2];
        }
    }

    vector<pair<long long, int>> no_zero; // first：总行数，second：语言编号。
    for (int languageId = 1; languageId <= 6; languageId++)
    {
        if (language_id_lines[languageId] > 0)
            no_zero.push_back({language_id_lines[languageId], languageId});
    }
    sort(no_zero.begin(), no_zero.end(), CompareLanguage);

    vector<int> res;
    for (const auto &value : no_zero) res.push_back(value.second);
    return res;
}

int CheckValue(const char *name, int actual, int expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int CheckLanguages(const char *name, const vector<int> &actual, const vector<int> &expected)
{
    cout << name << " expected=[";
    for (int value : expected) cout << value << ' ';
    cout << "] actual=[";
    for (int value : actual) cout << value << ' ';
    cout << ']' << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    CodeStatsSystem({{10,{102,101}}});
    failed += CheckLanguages("example 1 initially empty", StatLanguage(0), {});
    failed += CheckValue("example 1 add", ChangeCodelines(102,2,100), 100);
    failed += CheckLanguages("example 1 language appears", StatLanguage(0), {2});
    failed += CheckValue("example 1 subtract", ChangeCodelines(102,2,-100), 0);
    failed += CheckLanguages("example 1 zero excluded", StatLanguage(0), {});

    CodeStatsSystem({{10,{101,102}},{20,{201}},{30,{}}});
    failed += CheckValue("example 2 first repo", ChangeCodelines(101,2,100), 100);
    failed += CheckValue("example 2 second repo", ChangeCodelines(102,2,50), 50);
    failed += CheckValue("example 2 another language", ChangeCodelines(101,1,150), 150);
    failed += CheckValue("example 2 another product", ChangeCodelines(201,3,200), 200);
    failed += CheckLanguages("example 2 product tie", StatLanguage(10), {1,2});
    failed += CheckLanguages("example 2 isolated product", StatLanguage(20), {3});
    failed += CheckLanguages("example 2 global ranking", StatLanguage(0), {3,1,2});
    failed += CheckLanguages("empty product", StatLanguage(30), {});
    failed += CheckLanguages("unknown product", StatLanguage(99), {});
    failed += CheckLanguages("query preserves data", StatLanguage(0), {3,1,2});
    failed += CheckValue("same record grows", ChangeCodelines(102,2,200), 250);
    failed += CheckLanguages("rank changes after add", StatLanguage(0), {2,3,1});
    failed += CheckValue("subtract to zero", ChangeCodelines(101,1,-150), 0);
    failed += CheckLanguages("zero disappears", StatLanguage(10), {2});
    failed += CheckValue("zero delta new record", ChangeCodelines(201,6,0), 0);
    failed += CheckLanguages("zero record excluded", StatLanguage(20), {3});
    failed += CheckValue("language 6 enabled", ChangeCodelines(201,6,200), 200);
    failed += CheckLanguages("language boundary tie", StatLanguage(20), {3,6});

    CodeStatsSystem({{10,{101,102}},{20,{201}}});
    failed += CheckLanguages("reset all old amounts", StatLanguage(0), {});
    failed += CheckValue("large repo 1", ChangeCodelines(101,1,2000000000), 2000000000);
    failed += CheckValue("large repo 2", ChangeCodelines(102,1,2000000000), 2000000000);
    failed += CheckValue("competing language", ChangeCodelines(201,2,2100000000), 2100000000);
    // 语言 1 合计 40 亿，必须排在 21 亿的语言 2 之前。
    failed += CheckLanguages("sum exceeds int", StatLanguage(0), {1,2});

    CodeStatsSystem({{40,{401}}});
    failed += CheckLanguages("reset removes old product", StatLanguage(10), {});
    failed += CheckLanguages("new system empty", StatLanguage(0), {});
    failed += CheckValue("new repo update", ChangeCodelines(401,4,10), 10);
    failed += CheckLanguages("only new repo counted", StatLanguage(0), {4});
    CodeStatsSystem({});
    failed += CheckLanguages("no products", StatLanguage(0), {});
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. 先维护每个“仓库+语言”的当前行数，再按产品查询、汇总、筛零、排序。
2. 产品已存入 unordered_map，用 find 直接查，不必再遍历整个 map。
3. 保留原来的二维记录表和 exist；普通比较函数表达两级排序，无需 lambda。
4. 单仓库数值合法，不代表跨仓库汇总仍能放进 int；排序键也要使用 long long。
5. 设已有记录 M 条，查询产品含 R 个仓库，语言数 L=6：
   修改 O(M)，查询平均 O(R*M + L*log L)，查询额外空间 O(L)。
   总存储为 O(P+R_all+M)，P 为产品数、R_all 为全部仓库数。
   没有给出大规模性能约束，主版本采用易读的扫描方式。
*/
