#include"math.h"
#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include<ctime>
#include <cstring>
#include <random>
#include <numeric>
#include<stdint.h>
#include<cmath>
#include<random>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<int>ret(10,3200);//按照频率为3.2GHz来计算
    random_device rd;
	mt19937 gen(rd());
    normal_distribution<double> distribution(0,20);//均值为0，方差为20的高斯分布
    vector<float>ans;
    for(int i=0;i<10;i++)
    {
        ret[i]+=distribution(gen);
        ret[i]-=3200;
        ret[i]=abs(ret[i]);
        ans.push_back((3200-ret[i])/3200.0);
        cout<<ans[i]*100<<'%'<<endl;
    }
    return 0;
}
