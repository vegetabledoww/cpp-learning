#include <iostream>
#include <ctime>
#include<fstream>
#include <random>
#define random(a, b) (rand() % (b - a) + a) //使随机数函数更加便于使用
using namespace std;
int main()
{
    ofstream out;
    out.open("D:\\VScode\\C++code\\data.txt");//,ios::app);
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double>distribution1(0, 1.0);
    //srand((int)time(0)); // 产生随机种子  把0换成NULL也行
    for (int i = 0; i < 1000; i++)
    {
        out << distribution1(gen) << " ";
    }
    out<<"\n";
    out.close();
    return 0;
}
