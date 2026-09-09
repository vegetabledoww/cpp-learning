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
解释："uio" 和 "auu" 的首尾都是元音，并且都不含非元音字母，
     所以瑕疵度为 0，最长长度为 3。
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class Solution
{
public:
    bool isVower(char c)
    {
        set<char>v = {'a','e','i','o','u','A','E','I','O','U'};
        return v.count(c);
    }

    int GetLongestFlawedVowelSubstrLen(int flaw, const string& str)
    {
        size_t n = str.length();
        int tmp = 0;  //表示瑕疵度
        size_t left = 0;
        size_t maxlength = 0;
        //滑动窗口的套路【for循环来向右扩大窗口，while来控制左边界向右从而缩小窗口】
        for (size_t right = 0; right < n; right++)
        {
            if(!isVower(str[right]))
                tmp++;
            while (left <= right && tmp > flaw)//窗口内的非元音多了
            {
                if(!isVower(str[left]))
                    tmp--;
                left++;
            }
            if(left <= right && flaw == tmp
                &&isVower(str[left]) 
                &&isVower(str[right]))
                maxlength = max(maxlength, right-left+1);
        }
        return maxlength;
    }
};

struct TestCase
{
    string name;
    int flaw;
    string str;
    int expected;
};

int main()
{
    Solution solution;
    vector<TestCase> testCases = {
        {"original example", 0, "asdbuiodevauufgh", 3},
        {"no vowel", 0, "bbb", 0},
        {"empty string", 0, "", 0},
        {"single vowel", 0, "a", 1},
        {"one flaw", 1, "aba", 3},
        {"uppercase vowels", 2, "AxxE", 4},
        {"leading consonants", 0, "bba", 1},
        {"exact flaw required", 1, "aeiou", 0},
        {"window needs shrinking", 1, "aBCeDa", 3}
    };

    int failures = 0;
    for (size_t i = 0; i < testCases.size(); ++i) {
        const TestCase& test = testCases[i];
        int actual = solution.GetLongestFlawedVowelSubstrLen(test.flaw, test.str);
        bool passed = actual == test.expected;

        cout << "test " << i + 1 << " (" << test.name << "): "
             << (passed ? "PASS" : "FAIL")
             << ", expected=" << test.expected
             << ", actual=" << actual << '\n';

        if (!passed) {
            ++failures;
        }
    }

    cout << "failures=" << failures << '\n';
    return failures == 0 ? 0 : 1;
}
