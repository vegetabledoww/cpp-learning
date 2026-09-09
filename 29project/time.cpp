#include "math.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <cstring>
#include <random>
#include <numeric>
#include <stdint.h>
#include <cmath>
using namespace std;

char ch[1000]; // 定义全局变量
char *itos(int m)
{
    int i = 0;
    int a = 0, len = 0;
    if (m < 0) // 判断正负情况
    {
        ch[i++] = '-';
        m = -m;
    }
    for (a = m; a >= 10; a = a / 10) // 计算除符号位之外的字符长度
        len++;
    ch[i + len + 1] = '\0';
    ch[i + len] = m % 10 + '0';
    while (m >= 10)
    {
        len--;
        m = m / 10;
        ch[i + len] = m % 10 + 48;
    }
    return ch;
}

int main(int argc, char const *argv[])
{
    long long now = time(0); // now为时间戳
    char c = ':';
    // char* dt=ctime(&now);
    tm *gmtm = gmtime(&now);
    int nian = gmtm->tm_year + 1900;    // 年
    int yue = gmtm->tm_mon + 1;         // 月
    int ri = gmtm->tm_mday;             // 日
    int shi = (gmtm->tm_hour + 8) % 24; // 时
    int fen = gmtm->tm_min;             // 分
    int miao = gmtm->tm_sec;            // 秒
    for (int i = 0; i < 10; i++)
    {
        miao++;
        if (miao >= 60)
        {
            miao -= 60;
            fen++;
        }
        if (fen >= 60)
        {
            fen -= 60;
            shi++;
        }
        cout << shi << c << fen << c << miao << endl;
    }
    return 0;
}

