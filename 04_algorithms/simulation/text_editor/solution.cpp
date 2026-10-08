/*
题目：文本编辑器模拟（字符串模拟，根据用户提供的代码整理）

未提供原题平台和完整题面，以下操作语义依据现有代码整理。
实现 vector<string> StrEdit(const string& inputStr)，从空文本开始依次执行操作，
返回编辑后的各行内容，不包含换行符。空文本返回 {""}，末尾空行必须保留。
每次调用独立开始：光标位于文本开头，默认输入小写。

输入仅包含小写英文字母和以下操作字符：
- a～z：在光标处插入字母，受大小写开关影响，随后光标向右移动一格。
- @：切换大小写模式，只影响后续输入，不修改已存在的字母。
- +：在光标处插入换行符，光标移到新行开头，原光标右侧内容移到新行。
- ~：删除光标左侧字符（Backspace），光标向左移动；文本开头无效。
- -：删除光标右侧字符（Delete），光标不动；文本末尾无效。
- < / >：光标左移/右移一个字符位置，可跨越换行符；不能越过文本两端。
- ^ / *：光标上移/下移一行，尽量保持当前列；目标行较短时停在目标行末尾。
  第一行上移、最后一行下移无效。每次依据当前列移动，不记忆先前较长行的列。
删除换行符会合并相邻两行。列从 0 开始，表示光标左侧本行字符的数量。
本练习约定操作数量小于 INT_MAX，以便保留 int 光标和 -1 边界标记。

示例一：
输入："aaaa+bbbb~@cc<<<^--d@d"
输出：{"aaDd", "bbbCC"}
解释：先得到 "aaaa\nbbbCC"；左移三次后处于第二行第 2 列，
上移到第一行第 2 列，删除右侧两个 a，再依次插入大写 D 和小写 d。

示例二：
输入："ab+cd<<~"
输出：{"abcd"}
解释：左移两次到第二行开头，退格删除左侧换行符，将两行合并。

示例三：输入 "+"，输出 {"", ""}。
解释：一次换行产生两个空行，最后一个空行不能丢失。
*/
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    string text;

    // 从 pos 向左找换行符，找不到返回 -1；调用处允许 pos 为 -1。
    int find_pre(int pos)
    {
        for (int i = pos; i >= 0; i--)
        {
            if (text[i] == '\n') return i;
        }
        return -1;
    }

    // 从 pos 向右找换行符，找不到返回文本长度，作为最后一行的右边界。
    int find_back(int pos)
    {
        for (int i = pos; i < static_cast<int>(text.size()); i++)
        {
            if (text[i] == '\n') return i;
        }
        return static_cast<int>(text.size());
    }

    vector<string> StrEdit(const string &inputStr)
    {
        text.clear(); // 修正：重复调用同一对象时，不保留上次的文本。
        int pos = 0; // 光标是插入位置，范围为 [0, text.size()]。
        bool open = false;//小写
        for (char op : inputStr)
        {
            if ('a' <= op && op <= 'z')
            {
                // 用标准转换函数表达转大写，避免记忆 ASCII 的差值 32。
                char letter = open ? static_cast<char>(toupper(op)) : op;
                text.insert(pos, 1, letter);
                pos++;
            }
            if (op == '@') open = !open;
            if (op == '+')
            {
                text.insert(pos, 1, '\n');
                pos++;
            }
            if (op == '~')//类似backspace
            {
                if (pos == 0) continue;
                pos--;
                text.erase(pos, 1);
            }
            if (op == '-')//类似delete
            {
                if (pos == static_cast<int>(text.size())) continue;//没删除的
                text.erase(pos, 1);
            }
            if (op == '^')
            {
                int previousEnd = find_pre(pos - 1); // 上一行末尾的换行位置。
                if (previousEnd == -1) continue;//没找到换行符，说明是第一行，无事发生
                int previousSeparator = find_pre(previousEnd - 1); // 上一行前面的换行位置。
                // 当前列 = pos-previousEnd-1，上一行长度 = previousEnd-previousSeparator-1。
                // 比较时两边的 -1 抵消，保留原代码的写法。
                if (pos - previousEnd <= previousEnd - previousSeparator)
                    pos = previousSeparator + pos - previousEnd;
                else
                    pos = previousEnd;
            }
            if (op == '*')
            {
                int previousEnd = find_pre(pos - 1); // 当前行前面的换行位置。
                int currentEnd = find_back(pos); // 当前行末尾。
                if (currentEnd == static_cast<int>(text.size())) continue;
                int nextEnd = find_back(currentEnd + 1); // 下一行末尾。
                // 当前列 = pos-previousEnd-1，下一行长度 = nextEnd-currentEnd-1。
                if (pos - previousEnd <= nextEnd - currentEnd)
                    pos = currentEnd + pos - previousEnd;
                else
                    pos = nextEnd;
            }
            if (op == '<' && pos > 0) pos--;
            if (op == '>' && pos < static_cast<int>(text.size())) pos++;
        }

        vector<string> result;
        string currentLine;
        for (char ch : text)
        {
            if (ch == '\n')
            {
                result.push_back(currentLine);
                currentLine.clear();
            }
            else currentLine += ch;
        }
        // 无条件保存最后一行，同时覆盖空文本和末尾换行的情况。
        result.push_back(currentLine);
        return result;
    }
};

struct TestCase
{
    string name;
    string input;
    vector<string> expected;
};

void PrintLines(const vector<string> &lines)
{
    cout << '[';
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (i != 0) cout << ", ";
        cout << '"' << lines[i] << '"'; // 引号让空行可见。
    }
    cout << ']';
}

int main()
{
    vector<TestCase> tests = {
        {"original example", "aaaa+bbbb~@cc<<<^--d@d", {"aaDd", "bbbCC"}},
        {"backspace joins lines", "ab+cd<<~", {"abcd"}},
        {"trailing newline", "+", {"", ""}},
        {"empty input", "", {""}},
        {"empty boundary operations", "~-><^*", {""}},
        {"uppercase toggle", "ab@cd@e", {"abCDe"}},
        {"double toggle", "@@a", {"a"}},
        {"insert in middle", "ac<b", {"abc"}},
        {"delete joins lines", "ab+cd<<<-", {"abcd"}},
        {"all deleted", "abc~~~", {""}},
        {"multiple empty lines", "++", {"", "", ""}},
        {"split in middle", "abcd<<+", {"ab", "cd"}},
        {"up to same column", "abcd+xy^z", {"abzcd", "xy"}},
        {"up clamps to shorter line", "a+bcde^z", {"az", "bcde"}},
        {"down clamps to shorter line", "abcd+x^^^^>>>*z", {"abcd", "xz"}},
        {"down to longer line", "ab+cdef^*z", {"ab", "cdzef"}},
        {"up into empty line", "+abc^x", {"x", "abc"}},
        {"down into empty line", "abc+^*x", {"abc", "x"}},
        {"first and last row boundaries", "ab^*c", {"abc"}},
        {"left crosses newline", "a+b<<x", {"ax", "b"}},
        {"right crosses newline", "a+b<<>x", {"a", "xb"}},
        {"text end boundaries", "a>>-", {"a"}},
        {"text start boundaries", "a<<<~x", {"xa"}},
        {"no remembered column", "abcd+x+pqrs^^*z", {"abcd", "xz", "pqrs"}},
        {"case mode only", "@", {""}},
        {"new call resets mode and text", "a", {"a"}}};

    // 刻意复用同一个对象，验证每次调用独立开始。
    Solution solution;
    int failed = 0;
    for (const TestCase &test : tests)
    {
        vector<string> actual = solution.StrEdit(test.input);
        bool passed = actual == test.expected;
        cout << test.name << " expected=";
        PrintLines(test.expected);
        cout << " actual=";
        PrintLines(actual);
        cout << (passed ? " PASS\n" : " FAIL\n");
        if (!passed) failed++;
    }
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

/*
收获点：
1. '\n' 是一个字符，可被插入、删除，删除它就相当于合并两行。
2. 光标位于字符之间，pos 是右侧字符下标，pos==size 表示全文末尾。
3. 上下移动先求当前列和目标行长度，再选择同列或目标行行尾。
4. find_pre 返回 -1，find_back 返回 size，让首尾行也能使用统一的长度公式。
5. n 次操作中，字符串插入删除和逐行边界扫描最坏 O(n)，总时间最坏 O(n^2)，
   文本与结果占用 O(n) 空间。当前版本优先保留原实现，便于理解和手敲。
*/
