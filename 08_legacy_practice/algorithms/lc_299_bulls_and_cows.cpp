/*
LeetCode 299：猜数字游戏

secret 和 guess 是等长数字字符串。数字和位置都对计为 A；其余位置中数字能配对计为 B，每次出现只能用一次。返回 xAyB。

样例一：1807,7810 -> 1A3B，8 的位置正确，其余三位错位。
样例二：1123,0111 -> 1A1B，多余的 1 不能重复匹配。
来源：../originals/new_function/test_function.cpp:260-282（旧文件行号；完整映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    string getHint(string secret, string guess)
    {
        int bulls = 0, cows = 0;
        vector<int> secretCount(10), guessCount(10);
        for (size_t i = 0; i < secret.size(); ++i)
        {
            if (secret[i] == guess[i])
                ++bulls;
            else
            {
                ++secretCount[secret[i] - '0'];
                ++guessCount[guess[i] - '0'];
            }
        }
        // 修复：set 只记是否存在；错位匹配必须比较剩余出现次数。
        for (int i = 0; i < 10; ++i)
            cows += min(secretCount[i], guessCount[i]);
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};

// 以下仅为本地样例验证；提交平台时保留上面的题解即可。

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
    fail += check("sample1", s.getHint("1807", "7810"), string("1A3B"));
    fail += check("duplicate regression", s.getHint("1123", "0111"), string("1A1B"));
    fail += check("all exact", s.getHint("11", "11"), string("2A0B"));
    return fail ? 1 : 0;
}

/* 收获点：先排除公牛，再对剩余频数取最小值。时间 O(n)，空间 O(1)。 */
