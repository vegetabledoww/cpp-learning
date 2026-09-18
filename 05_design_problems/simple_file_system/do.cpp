/*
题目：简易文件系统（手敲练习）

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
   返回“当前目录完整路径 + ": " + content”，中间使用英文冒号和一个空格。
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

解释：Enter(8, false) 创建独立分支 8-9，但原来的 5-6 分支仍然保留。
leave(5) 删除 5-6 分支时，当前目录 8-9 不受影响。
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class SimpleFileSystem
{
private:
    // TODO：设计需要维护的成员变量和必要的辅助函数。
    vector<string>table;//维护目录表

public:
    // TODO：初始化为空文件系统，当前目录位于虚拟根目录。
    SimpleFileSystem()
    {
        table.push_back("");
    }

    // TODO：创建并进入新目录，返回新目录的完整路径。
    string Enter(int dirId, bool inherit)
    {
        if(table.empty() || table.back().empty() || !inherit)//根目录，此时里面啥也没有或者不选择继承
            table.push_back(to_string(dirId));
        else
        {
            int n = table.size();
            table[n - 1] += '-' + to_string(dirId);//开始拼接
        }
        return table.back();
    }

    // TODO：返回当前路径和 content 组合后的字符串。
    string show(const string &content) const
    {
        if(table.back() == "")
            return content;
        return table.back() + ":" +" " + content;;
    }

    // TODO：删除指定目录及其所有后代，返回删除后的当前路径。
    int string_int(const string & str)
    {
        int sum = 0;
        for (size_t i = 0; i < str.length(); i++)
        {
            sum = sum * 10 + (str[i] - '0');
        }
        return sum;
    }

    string leave(int dirId)
    {
        string str = table.back();  
        vector<int>nums;
        stringstream ss(str);
        string token;
        string answer;
        while (getline(ss,token,'-'))
        {
            nums.push_back(string_int(token));
        }
        bool check = false;
        int index = 0;
        for(size_t i = 0;i < nums.size(); i++)
        {
            if(nums[i] == dirId)
            {
                check = true;//最后有，则重新编排
                index = i;
                break;
            }
            if(i == nums.size()-1)
                return table.back();//临终最后一项没找到返回之前的内容
        }
        if(check)
        {
            for(int i = 0;i < index; i++)
            {
                if(i != 0)
                {
                    answer += '-';
                }
                answer += to_string(nums[i]);
            }
            table.back() = answer;
        }
        return table.back();
    }
};

// 测试辅助函数不属于题目接口，无需修改。
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

int main()
{
    int failed = 0;

    //题面示例一：建立继承链，并从中间目录开始级联删除。
    SimpleFileSystem example1;
    failed += CheckResult("example 1 - Enter 5", example1.Enter(5, true), "5");
    failed += CheckResult("example 1 - Enter 6", example1.Enter(6, true), "5-6");
    failed += CheckResult("example 1 - Enter 7", example1.Enter(7, true), "5-6-7");
    failed += CheckResult("example 1 - show", example1.show("jzq"),
                          "5-6-7: jzq");
    failed += CheckResult("example 1 - leave 6", example1.leave(6), "5");
    failed += CheckResult("example 1 - show again", example1.show("zm"), "5: zm");

    //题面示例二：另起根级分支，并删除已经保存的旧分支。
    SimpleFileSystem example2;
    failed += CheckResult("example 2 - Enter 5", example2.Enter(5, true), "5");
    failed += CheckResult("example 2 - Enter 6", example2.Enter(6, true), "5-6");
    failed += CheckResult("example 2 - new branch", example2.Enter(8, false), "8");
    failed += CheckResult("example 2 - Enter 9", example2.Enter(9, true), "8-9");
    failed += CheckResult("example 2 - delete old branch", example2.leave(5), "8-9");
    failed += CheckResult("example 2 - show", example2.show("abc"), "8-9: abc");

    // 边界：删除当前目录的祖先、删除不存在的目录以及退回虚拟根目录。
    SimpleFileSystem boundaryCase;
    boundaryCase.Enter(1, false);
    boundaryCase.Enter(11, true);
    boundaryCase.Enter(12, true);
    failed += CheckResult("delete current ancestor", boundaryCase.leave(11), "1");
    failed += CheckResult("delete missing directory", boundaryCase.leave(99), "1");
    failed += CheckResult("delete root-level directory", boundaryCase.leave(1), "");
    failed += CheckResult("show at virtual root", boundaryCase.show("root"), "root");

    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
