/*
LeetCode 2129：将标题首字母大写

标题由 ASCII 英文字母单词组成，单词间一个空格。长度<=2 的单词全小写，其余仅首字母大写。

样例一：capiTalIze tHe titLe -> Capitalize The Title。
样例二：First leTTeR of EACH Word -> First Letter of Each Word，of 长度为 2。
来源：new_function/test_function.cpp:293-313（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

class Solution
{
  public:
    string capitalizeTitle(string title)
    {
        int n = title.size();
        int l = 0, r = 0; // 单词左右边界（左闭右开）
        while (r < n)
        {
            while (r < n && title[r] != ' ')
            {
                ++r;
            }
            // 对于每个单词按要求处理
            if (r - l > 2)
            { //对首字母单词大写
                title[l] = toupper(title[l]);
                l++;
            }
            while (l < r)
            { //对非首字母的单词小写
                title[l] = tolower(title[l]);
                l++;
            }
            l = ++r; //下一个单词操作
        }
        return title;
    }
};

// 本地验证

template <class T> void show(const T &value)
{
    cout << value;
}
template <class T> void show(const vector<T> &values)
{
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i)
            cout << ',';
        show(values[i]);
    }
    cout << ']';
}
template <class T> int check(const char *name, const T &actual, const T &expected)
{
    cout << name << " expected=";
    show(expected);
    cout << " actual=";
    show(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int fail = 0;
    Solution s;
    fail +=
        check("sample1", s.capitalizeTitle("capiTalIze tHe titLe"), string("Capitalize The Title"));
    fail += check("sample2", s.capitalizeTitle("First leTTeR of EACH Word"),
                  string("First Letter of Each Word"));
    fail += check("short words", s.capitalizeTitle("A AB ABC"), string("a ab Abc"));
    return fail ? 1 : 0;
}

/* 收获点：按左闭右开 [l,r) 扫描单词。时间 O(n)，额外空间 O(1)，传值输入占 O(n)。 */
