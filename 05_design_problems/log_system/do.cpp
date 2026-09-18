/*
题目：日志管理系统（手敲练习）

实现一个日志管理系统。每个模块只向自己的“当前日志文件”写入日志，系统同时受到
单个文件最大长度和全部日志最大总长度的限制。

需要实现以下三个接口：

1. LogSystem(int maxFileLength, int maxTotalLength)
   初始化系统：
   - maxFileLength 表示单个日志文件允许的最大长度；
   - maxTotalLength 表示系统内所有日志允许的最大总长度；
   - 初始时系统中没有任何日志文件和日志。

2. int WriteLog(int moduleId, int length)
   为 moduleId 模块写入一条长度为 length 的日志，并返回写入和淘汰完成后，
   本次写入所在文件的当前长度。

   写入规则如下：
   - 每个模块只向自己的当前日志文件写入；
   - 每个文件内的日志索引 index 从 1 开始，后续写入依次递增；
   - 如果本次写入会使当前文件长度超过 maxFileLength，则先为该模块创建
     一个新文件，再将本条日志写入新文件，新文件的 index 从 1 开始；
   - 如果写入后文件长度恰好等于 maxFileLength，仍然允许写入当前文件；
   - 先完成本次写入，再检查系统日志总长度；
   - 如果总长度超过 maxTotalLength，则按照全局写入顺序，逐条删除最早
     写入的日志，直到总长度不超过限制；
   - 删除旧日志时，只删除对应的一条日志，不直接删除整个日志文件；
   - 删除日志后，需要同步扣减系统总长度和该日志所属文件的长度；
   - 被保留下来的日志索引不重新编号；
   - 文件变空后将其删除，同一模块下次写入时会创建新文件，index 重新从 1 开始。

3. vector<tuple<int, int, int>> Query()
   按照全局写入顺序返回当前仍保留的全部日志。每一项表示为：

       {moduleId, index, fileLength}

   其中：
   - moduleId：日志所属的模块编号；
   - index：该日志在所属文件中的索引；
   - fileLength：在当前仍保留的日志中，该文件累计到本条日志时的长度。

题目保证：
- 0 < maxFileLength <= maxTotalLength；
- 0 < length <= maxFileLength。

示例一：文件达到上限后滚动

输入：
LogSystem logs(10, 100);
logs.WriteLog(101, 2);
logs.WriteLog(102, 5);
logs.WriteLog(101, 5);
logs.WriteLog(101, 5);
logs.WriteLog(103, 5);
logs.Query();

输出：
WriteLog 依次返回：2、5、7、5、5
Query 返回：
{{101, 1, 2}, {102, 1, 5}, {101, 2, 7},
 {101, 1, 5}, {103, 1, 5}}

解释：
模块 101 的前两条日志位于同一个文件中，文件长度从 2 增加到 7。
第三次向模块 101 写入长度 5 时，7 + 5 > 10，因此创建新文件，
该日志在新文件中的 index 为 1，新文件长度为 5。

示例二：按照全局写入顺序淘汰旧日志

输入：
LogSystem logs(10, 12);
logs.WriteLog(1, 4);
logs.WriteLog(2, 5);
logs.WriteLog(1, 3);
logs.WriteLog(2, 4);
logs.Query();

输出：
WriteLog 依次返回：4、5、7、9
Query 返回：
{{2, 1, 5}, {1, 2, 3}, {2, 2, 9}}

解释：
最后一次写入后，系统总长度为 4 + 5 + 3 + 4 = 16，超过上限 12。
因此删除全局最早写入的 {模块 1, index 1, 长度 4}。
模块 1 的第二条日志仍然保留，其 index 仍为 2；Query 中该文件当前累计长度为 3。
*/

#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <deque>
#include <unordered_map>
#include <vector>

using namespace std;

class LogSystem
{
private:
    struct loginfo
    {
        int fileId;
        int id;
        int index;
        int length;//只表示本条日志的长度
    };

    int maxfilelength = 0;//单个文件最大值
    long long maxtotallength = 0;//系统允许最大值
    long long total_length = 0;//当前系统的长度
    int next_file_id = 1;//下一个新文件的唯一编号

    // table 按照全局写入顺序保存当前仍未被淘汰的日志。
    deque<loginfo>table;

    // 直接遍历 table，计算指定文件中当前仍保留的日志总长度。
    int get_file_length(int fileId) const
    {
        int fileLength = 0;
        for(const loginfo &log : table)
        {
            if(log.fileId == fileId)
                fileLength += log.length;
        }
        return fileLength;
    }

public:
    // 保存单文件上限和系统总长度上限，并初始化为空日志系统。
    LogSystem(int maxFileLength, int maxTotalLength)
    {
        maxfilelength = maxFileLength;
        maxtotallength = maxTotalLength;
    }

    // 写入一条日志，必要时创建新文件并淘汰全局最早的日志。
    int WriteLog(int moduleId, int length)
    {
        int fileId = -1;
        int nextIndex = 1;

        // 从后向前找到该模块最后写入的日志，它所属的就是当前文件。
        for(auto it = table.rbegin(); it != table.rend(); it++)
        {
            if(it->id == moduleId)
            {
                fileId = it->fileId;
                nextIndex = it->index + 1;
                break;
            }
        }

        int currentFileLength = 0;
        if(fileId != -1)
            currentFileLength = get_file_length(fileId);

        // 没有当前文件，或者当前文件放不下时，为该模块分配新 fileId。
        if(fileId == -1 ||
           static_cast<long long>(currentFileLength) + length > maxfilelength)//超限
        {
            fileId = next_file_id++;//新开一个file
            nextIndex = 1;//此新flie的第一个index为1
        }

        loginfo log = {fileId, moduleId, nextIndex, length};
        total_length += length;
        table.push_back(log);

        // 写入后总长度超限时，从队首逐条淘汰最早写入的日志。
        while (total_length > maxtotallength && !table.empty())
        {
            total_length -= table.front().length;
            table.pop_front();
        }

        return get_file_length(fileId);
    }

    // 按照全局写入顺序返回当前仍然保留的日志。
    vector<tuple<int, int, int>> Query() const
    {
        vector<tuple<int, int, int>>answer;
        unordered_map<int, int>length_by_file;//fileid-->总的length
        for(const loginfo &log : table)
        {
            length_by_file[log.fileId] += log.length;
            answer.push_back({log.id, log.index, length_by_file[log.fileId]});
        }
        return answer;
    }
};

// 将日志列表打印为 {{moduleId, index, fileLength}, ...}，方便观察错误结果。
static void PrintLogs(const vector<tuple<int, int, int>> &logs)
{
    cout << '{';
    for (size_t i = 0; i < logs.size(); i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << '{' << get<0>(logs[i]) << ", "
             << get<1>(logs[i]) << ", "
             << get<2>(logs[i]) << '}';
    }
    cout << '}';
}

// 将 WriteLog 的返回值列表打印出来，方便观察错误结果。
static void PrintValues(const vector<int> &values)
{
    cout << '{';
    for (size_t i = 0; i < values.size(); i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << values[i];
    }
    cout << '}';
}

static int CheckValues(const string &name,
                       const vector<int> &actual,
                       const vector<int> &expected)
{
    bool passed = actual == expected;
    cout << name << ": " << (passed ? "PASS" : "FAIL") << '\n';
    if (!passed)
    {
        cout << "  expected = ";
        PrintValues(expected);
        cout << "\n  actual   = ";
        PrintValues(actual);
        cout << '\n';
    }
    return passed ? 0 : 1;
}

static int CheckLogs(const string &name,
                     const vector<tuple<int, int, int>> &actual,
                     const vector<tuple<int, int, int>> &expected)
{
    bool passed = actual == expected;
    cout << name << ": " << (passed ? "PASS" : "FAIL") << '\n';
    if (!passed)
    {
        cout << "  expected = ";
        PrintLogs(expected);
        cout << "\n  actual   = ";
        PrintLogs(actual);
        cout << '\n';
    }
    return passed ? 0 : 1;
}

int main()
{
    int failed = 0;

    // 示例一：同一文件累加，超过单文件上限后创建新文件。
    LogSystem example1(10, 100);
    vector<int> writeResults1 = {
        example1.WriteLog(101, 2),
        example1.WriteLog(102, 5),
        example1.WriteLog(101, 5),
        example1.WriteLog(101, 5),
        example1.WriteLog(103, 5)};
    vector<tuple<int, int, int>> expectedLogs1 = {
        {101, 1, 2}, {102, 1, 5}, {101, 2, 7},
        {101, 1, 5}, {103, 1, 5}};
    failed += CheckValues("example 1 WriteLog", writeResults1,
                          {2, 5, 7, 5, 5});
    failed += CheckLogs("example 1 Query", example1.Query(), expectedLogs1);

    // 示例二：超过系统总长度后，逐条淘汰全局最早的日志。
    LogSystem example2(10, 12);
    vector<int> writeResults2 = {
        example2.WriteLog(1, 4),
        example2.WriteLog(2, 5),
        example2.WriteLog(1, 3),
        example2.WriteLog(2, 4)};
    vector<tuple<int, int, int>> expectedLogs2 = {
        {2, 1, 5}, {1, 2, 3}, {2, 2, 9}};
    failed += CheckValues("example 2 WriteLog", writeResults2,
                          {4, 5, 7, 9});
    failed += CheckLogs("example 2 Query", example2.Query(), expectedLogs2);

    // 边界一：文件长度恰好达到上限时不滚动，再写一条才创建新文件。
    LogSystem exactLimitCase(5, 20);
    vector<int> exactResults = {
        exactLimitCase.WriteLog(7, 2),
        exactLimitCase.WriteLog(7, 3),
        exactLimitCase.WriteLog(7, 1)};
    vector<tuple<int, int, int>> expectedExactLogs = {
        {7, 1, 2}, {7, 2, 5}, {7, 1, 1}};
    failed += CheckValues("exact file limit WriteLog", exactResults,
                          {2, 5, 1});
    failed += CheckLogs("exact file limit Query", exactLimitCase.Query(),
                        expectedExactLogs);

    // 边界二：文件被淘汰至空后，同一模块的新文件从 index 1 开始。
    LogSystem emptyFileCase(6, 6);
    emptyFileCase.WriteLog(1, 4);
    emptyFileCase.WriteLog(2, 3);
    emptyFileCase.WriteLog(1, 2);
    vector<tuple<int, int, int>> expectedAfterEmpty = {
        {2, 1, 3}, {1, 1, 2}};
    failed += CheckLogs("empty file creates a new index",
                        emptyFileCase.Query(), expectedAfterEmpty);

    // 边界三：当前文件只淘汰部分旧日志时，文件继续使用且 index 不重置。
    LogSystem sameFileEvictionCase(10, 10);
    vector<int> sameFileResults = {
        sameFileEvictionCase.WriteLog(1, 4),
        sameFileEvictionCase.WriteLog(2, 3),
        sameFileEvictionCase.WriteLog(1, 4),
        sameFileEvictionCase.WriteLog(1, 6)};
    vector<tuple<int, int, int>> expectedSameFileLogs = {
        {1, 2, 4}, {1, 3, 10}};
    failed += CheckValues("same file eviction WriteLog", sameFileResults,
                          {4, 3, 4, 10});
    failed += CheckLogs("same file eviction Query",
                        sameFileEvictionCase.Query(), expectedSameFileLogs);

    // 边界四：长度接近 int 上限时，加法比较不能溢出。
    int intMax = numeric_limits<int>::max();
    LogSystem largeLengthCase(intMax, intMax);
    vector<int> largeLengthResults = {
        largeLengthCase.WriteLog(3, intMax),
        largeLengthCase.WriteLog(3, 1)};
    vector<tuple<int, int, int>> expectedLargeLengthLogs = {
        {3, 1, 1}};
    failed += CheckValues("large length WriteLog", largeLengthResults,
                          {intMax, 1});
    failed += CheckLogs("large length Query",
                        largeLengthCase.Query(), expectedLargeLengthLogs);

    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
完成这道题后应掌握：
1. 如何把 deque 中的日志记录作为系统唯一的数据来源。
2. 如何按照全局写入顺序逐条淘汰最早日志。
3. 如何通过 fileId 区分同一模块先后创建的多个日志文件。
4. 如何通过扫描现有日志，得到当前文件及其剩余长度。
5. WriteLog 的时间复杂度为 O(n)，Query 的平均时间复杂度为 O(n)，
   保存日志所需的空间复杂度为 O(n)。
6. 多个 int 做加法可能在比较前溢出，需要先提升为 long long。
*/
