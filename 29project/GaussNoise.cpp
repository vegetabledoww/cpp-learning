#include <iostream>
#include <fstream> // 包含fstream头文件
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
int main() {
    random_device rd;
    mt19937 gen(rd());
    vector<double>ans1;
    for (int i = 0; i < 100; i++)
    {
	    normal_distribution<double>distribution1(0, 1.0);
	    double rnd1 = distribution1(gen);//随机数生成种子
	    ans1.push_back(rnd1);
	//cout << ans[i] << endl;
	//system("pause");
    }
   ofstream file("D:\\VScode\\C++code\\example.txt"); // 打开或创建名为"example.txt"的文本文件    
    if (file) { // 确保文件已经被正常地打开
        string content = "这是要写入文件的内容";
        file << content; // 将字符串写入文件
        file.close(); // 关闭文件
        cout << "文件已成功生成！" << endl;
    } else {
        cerr << "无法打开文件！" << endl;
    }
    
    return 0;
}