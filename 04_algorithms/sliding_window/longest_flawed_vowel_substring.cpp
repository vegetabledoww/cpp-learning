/* 题目：最长元音子串

给定一个字符串 str 和一个非负整数 flaw。

如果一个子串的第一个字符和最后一个字符都是元音字母，
则称该子串为“元音子串”。元音字母包括：
A、E、I、O、U、a、e、i、o、u。

元音子串中非元音字母的数量称为该子串的“瑕疵度”。
请找出瑕疵度恰好等于 flaw 的最长元音子串，并返回它的长度；
如果不存在满足条件的子串，则返回 0。

示例：
输入：flaw = 0，str = "asdbuiodevauufgh"
输出：3
解释："uio" 和 "auu" 的首尾都是元音，且都不含非元音字母，
     因此瑕疵度为 0，最长长度为 3。
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    static bool isVowel(char c)
    {
        static const set<char> vowels = {
            'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'
        };
        return vowels.count(c) > 0;
    }

    int GetLongestFlawedVowelSubstrLen(int flaw, const string& str)
    {
        size_t left = 0;
        int nonVowelCount = 0;
        size_t longestLength = 0;

        for (size_t right = 0; right < str.size(); ++right) {
            // 右边界纳入当前字符，扩大窗口。
            if (!isVowel(str[right])) {
                ++nonVowelCount;//非元音字母数量
            }

            // 瑕疵度超过 flaw 时，从左侧缩小窗口。
            while (left <= right && nonVowelCount > flaw) {
                if (!isVowel(str[left])) {
                    --nonVowelCount;
                }
                ++left;
            }

            // 只有瑕疵度恰好相等，且窗口两端都是元音时，才更新答案。
            if (left <= right
                && nonVowelCount == flaw
                && isVowel(str[left])
                && isVowel(str[right])) {
                longestLength = max(longestLength, right - left + 1);
            }
        }

        return static_cast<int>(longestLength);
    }
};

struct TestCase
{
    int flaw;
    string str;
    int expected;
};

int main()
{
    Solution solution;
    vector<TestCase> testCases = {
        {0, "asdbuiodevauufgh", 3}, // 题目原始样例
        {0, "bbb", 0},              // 没有元音，原代码会越界
        {0, "", 0},                 // 空字符串
        {0, "a", 1},                // 单个元音
        {1, "aba", 3},              // 恰好一个非元音
        {2, "AxxE", 4},             // 大写元音
        {0, "bba", 1},              // 字符串以非元音开头
        {1, "aeiou", 0},            // 要求恰好等于 flaw，不是至多
        {1, "aBCeDa", 3}            // 窗口需要收缩，最长子串是 "eDa"
    };

    int failures = 0;
    for (size_t i = 0; i < testCases.size(); ++i) {
        const TestCase& test = testCases[i];
        int actual = solution.GetLongestFlawedVowelSubstrLen(test.flaw, test.str);
        bool passed = actual == test.expected;

        cout << "test " << i + 1 << ": " << (passed ? "PASS" : "FAIL")
             << ", flaw=" << test.flaw
             << ", str=\"" << test.str << "\""
             << ", expected=" << test.expected
             << ", actual=" << actual << '\n';

        if (!passed) {
            ++failures;
        }
    }

    cout << "failures=" << failures << '\n';
    return failures == 0 ? 0 : 1;
}

/*收获点：
1. right 向右扩大窗口；非元音数量超过 flaw 时，left 向右缩小窗口。
2. nonVowelCount 始终表示当前窗口 [left, right] 内的非元音数量。
3. set::count 和 set::find 的复杂度都是 O(log n)。这里集合固定只有 10 个字符，
   并使用 static const 保证它只初始化一次。
4. 每个字符最多被左右边界各访问一次，所以整体时间复杂度为 O(n)，空间复杂度为 O(1)。
*/
