/*
题目：日志管理系统

实现一个日志管理系统。每个模块只向自己的“当前日志文件”写入日志，系统同时受到
单个文件最大长度和全部日志最大总长度的限制。

需要实现以下接口：

1. LogSystem(maxFileLength, maxTotalLength)
   初始化系统。maxFileLength 表示单个日志文件允许的最大长度，maxTotalLength
   表示系统内所有日志允许的最大总长度。

2. WriteLog(moduleId, length)
   为 moduleId 模块写入一条长度为 length 的日志，并返回写入完成、淘汰旧日志后，
   本次写入所在文件的当前长度。写入规则如下：
   - 每个文件内的日志索引 index 从 1 开始，后续写入依次递增；
   - 如果写入后会超过单个文件最大长度，则为该模块新建文件，index 重新从 1 开始；
   - 先完成本次写入，再检查总长度；
   - 如果总长度超过限制，则按照全局写入顺序逐条删除最早的日志，直到总长度合法；
   - 删除日志后，要同时扣减系统总长度和该日志所属文件的长度；
   - 被保留下来的日志索引不重新编号；文件变空后删除，下次写入会创建新文件。

3. Query()
   按照全局写入顺序返回当前仍保留的日志。每一项为
   {moduleId, index, fileLength}：
   - moduleId：模块编号；
   - index：该日志在所属文件中的索引；
   - fileLength：在当前仍保留的日志中，该文件累计到本条日志时的长度。

题目保证：
- 0 < maxFileLength <= maxTotalLength；
- 0 < length <= maxFileLength。

示例一：
输入：
LogSystem logs(10, 100);
logs.WriteLog(101, 2);
logs.WriteLog(102, 5);
logs.WriteLog(101, 5);
logs.WriteLog(101, 5);
logs.WriteLog(103, 5);
logs.Query();

输出：
WriteLog 依次返回 2、5、7、5、5
Query 返回 {{101, 1, 2}, {102, 1, 5}, {101, 2, 7},
            {101, 1, 5}, {103, 1, 5}}

解释：101 模块的前两条日志位于同一文件，文件长度由 2 增加到 7。
第三次向 101 模块写入长度 5 时，7 + 5 > 10，因此新建文件，index 从 1 开始。

示例二：
输入：
LogSystem logs(10, 12);
logs.WriteLog(1, 4);
logs.WriteLog(2, 5);
logs.WriteLog(1, 3);
logs.WriteLog(2, 4);
logs.Query();

输出：
WriteLog 依次返回 4、5、7、9
Query 返回 {{2, 1, 5}, {1, 2, 3}, {2, 2, 9}}

解释：最后一次写入后总长度为 16，超过 12，因此删除全局最早写入的
{模块 1, index 1, 长度 4}。模块 1 的 index 2 不重新编号，其文件当前只剩
长度为 3 的一条日志。
*/

#include <deque>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

class LogSystem
{
private:
    struct LogRecord
    {
        int fileId;
        int moduleId;
        int index;
        int length;
    };

    struct FileState
    {
        int moduleId;
        int length;
        int nextIndex;
    };

    int maxFileLength;
    long long maxTotalLength;
    long long totalLength;
    int nextFileId;

    // 模块编号 -> 该模块当前写入的文件编号。
    unordered_map<int, int> currentFileByModule;
    // 文件编号 -> 文件当前长度以及下一个日志索引。
    unordered_map<int, FileState> files;
    // 队首始终是系统中最早写入且尚未删除的日志。
    deque<LogRecord> logQueue;

    // 为指定模块创建一个空日志文件，并把它设置为该模块的当前文件。
    // 返回系统内部唯一的 fileId，用于区分同一模块先后创建的多个文件。
    int CreateFile(int moduleId)
    {
        int fileId = nextFileId++;
        files[fileId] = {moduleId, 0, 1};
        currentFileByModule[moduleId] = fileId;
        return fileId;
    }

    // 当日志总长度超过上限时，按照全局写入顺序逐条淘汰最早的日志。
    // 淘汰时同步扣减总长度和所属文件长度；文件变空后还要删除文件状态。
    void RemoveOldestLogs()
    {
        while (totalLength > maxTotalLength && !logQueue.empty())
        {
            LogRecord oldest = logQueue.front();
            logQueue.pop_front();
            totalLength -= oldest.length;

            auto fileIt = files.find(oldest.fileId);
            if (fileIt == files.end())
            {
                continue;
            }

            fileIt->second.length -= oldest.length;
            if (fileIt->second.length != 0)
            {
                continue;
            }

            // 只有被删空的是该模块当前文件时，才清除当前文件记录。
            auto moduleIt = currentFileByModule.find(oldest.moduleId);
            if (moduleIt != currentFileByModule.end() &&
                moduleIt->second == oldest.fileId)
            {
                currentFileByModule.erase(moduleIt);
            }
            files.erase(fileIt);
        }
    }

public:
    // 构造日志系统：保存单文件上限和总长度上限，并初始化为空系统。
    LogSystem(int maxFileLength, int maxTotalLength)
        : maxFileLength(maxFileLength),
          maxTotalLength(maxTotalLength),
          totalLength(0),
          nextFileId(1)
    {
    }

    // 向 moduleId 模块写入一条长度为 length 的日志。
    // 当前文件放不下时会创建新文件；写入后还会触发全局旧日志淘汰。
    // 返回本次写入所在文件淘汰后的实际长度；length 非法时返回 -1。
    int WriteLog(int moduleId, int length)
    {
        if (length <= 0 || length > maxFileLength)
        {
            return -1;
        }

        int fileId;
        auto moduleIt = currentFileByModule.find(moduleId);
        if (moduleIt == currentFileByModule.end())
        {
            fileId = CreateFile(moduleId);
        }
        else
        {
            fileId = moduleIt->second;
            FileState &currentFile = files.at(fileId);
            if (static_cast<long long>(currentFile.length) + length > maxFileLength)
            {
                fileId = CreateFile(moduleId);
            }
        }

        FileState &file = files.at(fileId);
        int index = file.nextIndex++;
        file.length += length;
        totalLength += length;
        logQueue.push_back({fileId, moduleId, index, length});

        RemoveOldestLogs();
        return files.at(fileId).length;
    }

    // 按全局写入顺序查询所有尚未被淘汰的日志。
    // 每个 tuple 依次保存：模块编号、文件内日志索引、累计到本条时的文件长度。
    vector<tuple<int, int, int>> Query() const
    {
        vector<tuple<int, int, int>> result;
        unordered_map<int, int> lengthByFile;

        for (const LogRecord &log : logQueue)
        {
            lengthByFile[log.fileId] += log.length;
            result.push_back({log.moduleId, log.index, lengthByFile[log.fileId]});
        }
        return result;
    }
};

// 将 Query 返回的日志列表打印成 {{moduleId, index, fileLength}, ...} 格式，
// 方便在测试失败时直观看到完整结果。
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

// 比较一组 WriteLog 返回值与期望值，并打印 PASS 或 FAIL。
// 返回 0 表示通过，返回 1 表示失败，便于 main 累加失败数量。
static int CheckValues(const string &name,
                       const vector<int> &actual,
                       const vector<int> &expected)
{
    bool passed = actual == expected;
    cout << name << ": " << (passed ? "PASS" : "FAIL") << '\n';
    return passed ? 0 : 1;
}

// 比较 Query 返回的日志列表与期望列表。
// 如果不一致，会同时打印期望结果和实际结果，便于定位问题。
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

// 运行题面样例和边界测试，并汇总失败数量。
// 全部通过时返回 0，存在失败用例时返回 1。
int main()
{
    int failed = 0;

    // 题面示例一：测试同文件累加和超过单文件上限后新建文件。
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
    failed += CheckValues("example 1 WriteLog", writeResults1, {2, 5, 7, 5, 5});
    failed += CheckLogs("example 1 Query", example1.Query(), expectedLogs1);

    // 题面示例二：淘汰的是最早的一条日志，不是整个文件。
    LogSystem example2(10, 12);
    vector<int> writeResults2 = {
        example2.WriteLog(1, 4),
        example2.WriteLog(2, 5),
        example2.WriteLog(1, 3),
        example2.WriteLog(2, 4)};
    vector<tuple<int, int, int>> expectedLogs2 = {
        {2, 1, 5}, {1, 2, 3}, {2, 2, 9}};
    failed += CheckValues("example 2 WriteLog", writeResults2, {4, 5, 7, 9});
    failed += CheckLogs("example 2 Query", example2.Query(), expectedLogs2);

    // 边界：文件被删空后，同一模块再次写入时 index 从 1 重新开始。
    LogSystem emptyFileCase(6, 6);
    emptyFileCase.WriteLog(1, 4);
    emptyFileCase.WriteLog(2, 3);
    emptyFileCase.WriteLog(1, 2);
    vector<tuple<int, int, int>> expectedAfterEmpty = {
        {2, 1, 3}, {1, 1, 2}};
    failed += CheckLogs("empty file creates a new index", emptyFileCase.Query(),
                        expectedAfterEmpty);

    // 边界：恰好达到上限仍使用原文件，再多写一条才创建新文件。
    LogSystem exactLimitCase(5, 20);
    vector<int> exactResults = {
        exactLimitCase.WriteLog(7, 2),
        exactLimitCase.WriteLog(7, 3),
        exactLimitCase.WriteLog(7, 1)};
    vector<tuple<int, int, int>> expectedExactLogs = {
        {7, 1, 2}, {7, 2, 5}, {7, 1, 1}};
    failed += CheckValues("exact file limit WriteLog", exactResults, {2, 5, 1});
    failed += CheckLogs("exact file limit Query", exactLimitCase.Query(),
                        expectedExactLogs);

    // 边界：淘汰同一当前文件中的旧日志后，文件继续使用且 index 不重置。
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
    failed += CheckLogs("same file eviction Query", sameFileEvictionCase.Query(),
                        expectedSameFileLogs);

    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. 用 deque 保存全局写入顺序，超过总容量时从队首逐条淘汰最早日志。
2. moduleId 只能找到模块，额外的 fileId 才能区分同一模块先后创建的多个文件。
3. 删除日志时必须同步维护总长度、文件长度和模块当前文件三个状态。
4. 单次 WriteLog 的均摊时间复杂度为 O(1)，因为每条日志最多入队、出队各一次；
   Query 的时间复杂度和返回结果数量均为 O(n)，系统额外空间复杂度为 O(n)。
*/
