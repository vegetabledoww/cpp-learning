/*
题目：简易文件系统

实现一个简易文件系统。系统中只管理目录之间的继承关系，并维护一个“当前目录”。
系统初始位于空的虚拟根目录，根目录本身没有目录编号。

目录路径使用连字符 '-' 连接。例如，目录 6 是目录 5 的子目录，目录 7 又是
目录 6 的子目录，那么目录 7 的完整路径表示为 "5-6-7"。

需要实现以下四个接口：

1. SimpleFileSystem()
   初始化文件系统。此时系统中没有任何目录，当前目录为虚拟根目录。

2. string Enter(int dirId, bool inherit)
   创建编号为 dirId 的新目录，并进入该目录。

   - inherit 为 true：在当前目录下创建新目录，新目录继承当前目录的完整路径；
   - inherit 为 false：在虚拟根目录下创建一条新的独立目录分支；
   - 当当前目录为虚拟根目录时，inherit 为 true 和 false 的效果相同；
   - 创建新的根级分支时，系统中原有的其他目录和分支仍然保留；
   - 返回进入新目录后的完整路径。

3. string show(const string &content)
   返回“当前目录完整路径 + \": \" + content”，中间使用英文冒号和一个空格。
   例如当前路径为 "5-6-7" 时，show("jzq") 返回 "5-6-7: jzq"。
   如果当前目录为虚拟根目录，则直接返回 content。

4. string leave(int dirId)
   删除编号为 dirId 的目录以及它的所有后代，并返回删除后的当前目录路径。

   - 如果当前目录位于被删除的子树中，当前目录退回到 dirId 的父目录；
   - 如果删除的是另一条非当前分支，当前目录保持不变；
   - 如果 dirId 不存在，不执行删除，直接返回当前目录路径；
   - 如果删除后当前目录回到虚拟根目录，返回空字符串 ""。

题目保证所有传给 Enter 的 dirId 都是正整数，并且在所有 Enter 调用中均不重复。

示例一：
输入：
SimpleFileSystem fileSystem;
fileSystem.Enter(5, true);
fileSystem.Enter(6, true);
fileSystem.Enter(7, true);
fileSystem.show("jzq");
fileSystem.leave(6);
fileSystem.show("zm");

输出：
"5"
"5-6"
"5-6-7"
"5-6-7: jzq"
"5"
"5: zm"

解释：目录 5、6、7 依次形成继承链。删除目录 6 时，它的后代目录 7 也被删除，
当前目录退回到目录 5。

示例二：
输入：
SimpleFileSystem fileSystem;
fileSystem.Enter(5, true);
fileSystem.Enter(6, true);
fileSystem.Enter(8, false);
fileSystem.Enter(9, true);
fileSystem.leave(5);
fileSystem.show("abc");

输出：
"5"
"5-6"
"8"
"8-9"
"8-9"
"8-9: abc"

解释：Enter(8, false) 在根目录下创建了独立分支 8-9，但原来的 5-6 分支仍被保存。
leave(5) 会删除整个 5-6 分支，因为当前目录位于 8-9，所以当前目录不受影响。
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class SimpleFileSystem
{
private:
    struct DirectoryNode
    {
        int parentId;
        vector<int> children;
    };

    // -1 表示没有编号的虚拟根目录。
    int currentDirId;
    unordered_map<int, DirectoryNode> directories;

    // 根据当前目录不断寻找父目录，并拼接出从根到当前目录的完整路径。
    string GetCurrentPath() const
    {
        vector<int> path;
        int dirId = currentDirId;

        while (dirId != -1)
        {
            path.push_back(dirId);
            dirId = directories.at(dirId).parentId;
        }

        reverse(path.begin(), path.end());

        string result;
        for (size_t i = 0; i < path.size(); i++)
        {
            if (i != 0)
            {
                result += '-';
            }
            result += to_string(path[i]);
        }
        return result;
    }

    // 判断当前目录是否等于 dirId，或者是否位于 dirId 的后代中。
    bool CurrentDirectoryWillBeDeleted(int dirId) const
    {
        int current = currentDirId;
        while (current != -1)
        {
            if (current == dirId)
            {
                return true;
            }
            current = directories.at(current).parentId;
        }
        return false;
    }

    // 递归删除指定目录及其所有后代。
    void DeleteSubtree(int dirId)
    {
        vector<int> children = directories.at(dirId).children;
        for (int childId : children)
        {
            DeleteSubtree(childId);
        }
        directories.erase(dirId);
    }

public:
    // 初始化为空文件系统，当前目录指向虚拟根目录。
    SimpleFileSystem() : currentDirId(-1)
    {
    }

    // 创建并进入新目录。inherit 决定新目录继承当前目录，还是另起根级分支。
    string Enter(int dirId, bool inherit)
    {
        int parentId = inherit ? currentDirId : -1;
        directories[dirId] = {parentId, {}};

        if (parentId != -1)
        {
            directories.at(parentId).children.push_back(dirId);
        }

        currentDirId = dirId;
        return GetCurrentPath();
    }

    // 在当前完整路径后显示给定内容；位于虚拟根目录时只返回内容。
    string show(const string &content) const
    {
        string currentPath = GetCurrentPath();
        if (currentPath.empty())
        {
            return content;
        }
        return currentPath + ": " + content;
    }

    // 删除指定目录及其所有后代，并返回操作完成后的当前目录路径。
    string leave(int dirId)
    {
        auto targetIt = directories.find(dirId);
        if (targetIt == directories.end())
        {
            return GetCurrentPath();
        }

        int parentId = targetIt->second.parentId;
        bool currentWillBeDeleted = CurrentDirectoryWillBeDeleted(dirId);

        // 从父目录的孩子列表中断开 dirId；根级目录没有真实父节点，无需处理。
        if (parentId != -1)
        {
            vector<int> &siblings = directories.at(parentId).children;
            auto position = find(siblings.begin(), siblings.end(), dirId);
            if (position != siblings.end())
            {
                siblings.erase(position);
            }
        }

        DeleteSubtree(dirId);
        if (currentWillBeDeleted)
        {
            currentDirId = parentId;
        }

        return GetCurrentPath();
    }
};

// 比较一次接口调用的实际返回值和期望值，并返回失败数量。
static int CheckResult(const string &name,
                       const string &actual,
                       const string &expected)
{
    bool passed = actual == expected;
    cout << name << ": " << (passed ? "PASS" : "FAIL")
         << ", expected=\"" << expected
         << "\", actual=\"" << actual << "\"\n";
    return passed ? 0 : 1;
}

// 运行题面中的两个样例和删除边界测试。
int main()
{
    int failed = 0;

    SimpleFileSystem example1;
    failed += CheckResult("example 1 - Enter 5", example1.Enter(5, true), "5");
    failed += CheckResult("example 1 - Enter 6", example1.Enter(6, true), "5-6");
    failed += CheckResult("example 1 - Enter 7", example1.Enter(7, true), "5-6-7");
    failed += CheckResult("example 1 - show", example1.show("jzq"),
                          "5-6-7: jzq");
    failed += CheckResult("example 1 - leave 6", example1.leave(6), "5");
    failed += CheckResult("example 1 - show again", example1.show("zm"), "5: zm");

    SimpleFileSystem example2;
    failed += CheckResult("example 2 - Enter 5", example2.Enter(5, true), "5");
    failed += CheckResult("example 2 - Enter 6", example2.Enter(6, true), "5-6");
    failed += CheckResult("example 2 - new branch", example2.Enter(8, false), "8");
    failed += CheckResult("example 2 - Enter 9", example2.Enter(9, true), "8-9");
    failed += CheckResult("example 2 - delete old branch", example2.leave(5), "8-9");
    failed += CheckResult("example 2 - show", example2.show("abc"), "8-9: abc");

    // 删除当前目录的祖先后退回其父目录；删除不存在的目录不改变当前路径。
    SimpleFileSystem boundaryCase;
    boundaryCase.Enter(10, false);
    boundaryCase.Enter(11, true);
    boundaryCase.Enter(12, true);
    failed += CheckResult("delete current ancestor", boundaryCase.leave(11), "10");
    failed += CheckResult("delete missing directory", boundaryCase.leave(99), "10");
    failed += CheckResult("delete root-level directory", boundaryCase.leave(10), "");
    failed += CheckResult("show at virtual root", boundaryCase.show("root"), "root");

    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. 多个根级目录组成“森林”；每个目录保存父目录和直接子目录。
2. currentDirId 记录当前目录，沿 parentId 向上可以恢复完整路径。
3. 删除目录时需要递归删除整棵子树，并判断当前目录是否也会被删除。
4. 设目录总数为 n、当前路径高度为 h、被删子树大小为 k、目标目录的兄弟数为 d：
   Enter 和 show 的时间复杂度为 O(h)，leave 的时间复杂度为 O(h + k + d)，
   整个系统的空间复杂度为 O(n)。
*/
