#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <random>
#include <numeric>
#include<stdint.h>
#include<cmath>
using namespace std;
#define PI 3.14159265358
#define R 6373.393
//计算经纬度,参数为：基点经度，基点纬度，方位角，距离单位KM
vector<double>calcLatAndlon(double basePointLongitude, double basePointLatitude, double azimuth, double distance)
{
    //转换单位
    vector<double>ans;
    double arc = R* 1000;//地球半径，单位米
    azimuth=azimuth*PI/180;//角度变为弧度
    distance*=1000;
    double longlitude=basePointLongitude+distance*sin(azimuth)/(arc*cos(basePointLongitude)*4*PI/360);   
   // cout<<distance*sin(azimuth)/(arc*cos(basePointLongitude)*2*PI/360);
    double latitude = basePointLatitude+distance*cos(azimuth)/(arc*2*PI/360);
    ans.push_back(longlitude);
    ans.push_back(latitude);
    return ans;
}

//计算高度(相对高度)，参数为距离，俯仰角
double clacHeight(double distance,double E1)
{
    E1=E1*PI/180;//角度变为弧度
    distance*=1000;//转换单位
    double Height=distance*sin(E1);
    Height=abs(Height);//角度为负数时，将高度变为正数
    return Height;
}

int main(int argc, char const *argv[])
{
    vector<double>ret;
    ret=calcLatAndlon(111.88,32.97,96.812l,3000.2);//以正北方向为0，东向为正
    cout<<ret[0]<<'\t'<<ret[1]<<'\t'<<clacHeight(162.848,-3.52058)<<endl; 
    return 0;
}
