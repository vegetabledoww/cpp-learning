/*
题目：行星碰撞（LeetCode 735）

给定整数数组 asteroids，绝对值表示行星大小，正数向右移动，负数向左移动。
相向移动的行星会碰撞：较小者消失；大小相同则同时消失。返回最终剩余行星。

示例一：
输入：[5,10,-5]
输出：[5,10]

示例二：
输入：[8,-8]
输出：[]
*/

#include <vector>
#include <iostream>
using namespace std;
vector<int> asteroidCollision(vector<int> &asteroids)
{
    vector<int> st;
    for (const auto &num : asteroids)
    {
        bool flag = true; // 朝右的速度为真
        while (flag && !st.empty() && num < 0 && st.back() > 0)
        {
            flag = -num > st.back();
            if (st.back() <= -num)
            {
                st.pop_back();
            }
        }
        if (flag)
        {
            st.push_back(num);
        }
    }
    return st;
}

void PrintVector(const vector<int> &values)
{
    cout << '[';
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << values[i];
        if (i + 1 < values.size())
        {
            cout << ',';
        }
    }
    cout << "]\n";
}

int main()
{
    vector<int> test1 = {5, 10, -5};
    cout << "示例一 expected=[5,10]\nactual=";
    PrintVector(asteroidCollision(test1));

    vector<int> test2 = {8, -8};
    cout << "示例二 expected=[]\nactual=";
    PrintVector(asteroidCollision(test2));
    return 0;
}
