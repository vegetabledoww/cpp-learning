#include <unordered_map>
#include <vector>
#include <cstring>
#include<iostream>
#include <random>
#include <numeric>
#include<algorithm>
using namespace std;
// enum Freq : int32_t
// {
//     频率不变,
//     参差重频,
//     线性调频,
//     捷变频
// };
vector<int>decline(vector<int>&source)//输入参数为数组，输出为数组的差（比原数组size少1）
{
    vector<int>ans;
    for(int i=1;i<source.size();i++)
    {
        ans.push_back(source[i]-source[i-1]);
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    vector<int>source_FM(10);
    vector<int>source_constance(10);
    vector<int>standard;
    vector<int>ret_first;
    vector<int>ret_second;
    vector<int>source_agile;
    source_FM={1000,1100,1200,1300,1400,1500,1600,1700,1800,1900};//线性调频信号
    source_constance={1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};//恒定频率信号 
    source_agile={1000,5000,4000,4100,3200,2222,1234,587,0,123};//频率捷变信号
    for(int i=1;i<source_FM.size();i++)
    {
        standard.push_back(0);
        ret_first=decline(source_agile);//第一次做差
        ret_second=decline(ret_first);  //第二次做差
        if(ret_first[i]==0)  
        {
            cout<<"频率不变信号"<<endl;
        }
        else if (ret_second[i]==0)
        {
            cout<<"线性调频信号"<<endl;
        }
        else
        {
            cout<<"频率捷变信号"<<endl;
        }
        
        //system("pause");
    }
    return 0;
}
