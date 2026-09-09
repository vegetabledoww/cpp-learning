#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <random>
#include <numeric>
#include<stdint.h>
using namespace std;
//字符数组整体赋��1�7
//const int SIZE = 5;  // 数组的大射1�7
//
//int main() {
//    int arr1[SIZE] = { 1, 2, 3, 4, 5 };  // 原始数组
//    int arr2[SIZE];  // 目标数组
//     //使用 std::copy 进行整体赋��1�7
//    std::copy(arr1, arr1 + SIZE, arr2);
//     //打印arr2的��1�7
//    for (int i = 0; i < SIZE; ++i) {
//        std::cout << arr2[i] << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}
// 
// 烫烫烫烫
// int main()
//{
//		char test[10];
//		char tran[10];
//		test[0] = 'a';
//		tran = test;
//		for (int i = 0; i < 10; i++)
//		{
//			std::cout << test[i];
//		}
//}
// 
// 
////分批函数
//int nums(vector<int>&data)
//{
//    int num = 1;
//    //data = { 1,1,2,6,3,100 };//4
//    sort(data.begin(), data.end());
//    for (int i = 0; i < data.size()-1; i++)
//    {
//        if (data[i] == data[i + 1])
//        {
//            continue;
//        }
//        else
//        {
//            num++;
//        }
//    }
//    return num;
//}


//高斯分布
//int main()
//{
//	random_device rd;
//	mt19937 gen(rd());
//	for (int i = 0; i < 3; i++)
//	{
//		normal_distribution<double> distribution(0, 1.0);
//		double rnd = distribution(gen);//随机数生成种孄1�7
//		cout << rnd << endl;
//		system("pause");
//	}
//}

// 字符串拷�敄1�7  strcpy_s
// int main()
// {
// 	char a[10] = {'0','0'};
// 	char b[10];
// 	strcpy_s(b,a);
// 	/*for (int i = 0; i < 10; i++)
// 		cout << b[i];*/
// 	cout << a<<endl;
// 	cout << b;
// }

//memcpy函数
// int main()
// {
//    char str1[3];
//    char str2[3];
//    cout << "Please enter str2: ";
//    cin.get(str2, 3);
//    memcpy(str1,str2,3);//复制str2的前两个字符给str1，因为字符类型最后一个都昄1�7/0，占丢�个字芄1�7
//    cout << "str1 is " << "\" " << str1 << "\".\n";
//    system("pause");
//    return 0;
// }
//朢�大最小��函敄1�7
// int main()
// {
// 	vector<float>sum = {0,6,5,7,9,10};
// 	float total = accumulate(sum.begin()+1, sum.end(), 0.0);
// 	int max = *max_element(sum.begin(), sum.end());
// 	int min = *min_element(sum.begin()+1, sum.end());
// 	cout << total / (sum.size()-1) << endl;
// 	cout << max << endl;
// 	cout << min << endl;
// 	//system("pause");
// }

//memcpy以及memset函数
// int main()
// {
// 	int arr1[] = {5,6,7,8,2};
// 	int arr2[] = { 1 ,100,12,45};
// 	memcpy(arr1, arr2, sizeof(arr2));
// 	//memset(arr1, 0, sizeof(arr1));//此函数第二个参数只能昄1�70或��1�7-1，一般用于初始化操作
// 	int mm = sizeof(arr1);
// 	int nn = sizeof(arr2);
// 	for(auto &num:arr1)
// 	cout << num;
// 	return 0;
// }

//枚举类型
// enum week   //字符类型
// {
// 	周一,
// 	周二,
// 	周三,
// 	周四,
// 	周五,
// 	周六,
// 	周天,
// };
// int main()
// {
// 	week today = 周天;
// 	cout << today;
// 	return 0;
// }

//棢�测输入输凄1�7
// int main(int argc, char const *argv[])
// {
// 	vector<int>ans={1,2,45};
// 	vector<int>ret(ans);
// 	for(auto &num : ans)
// 	{
// 		cout<<num<<" ";
// 	}
// 	return 0;
// }

//hello world!
// int main()
// {
// 	cout<<"你好 world!"<<endl;
// 	return 0;
// }
  
      string capitalizeTitle(string title) {
        int n = title.size();
        int l = 0, r = 0;   // 单词左右边界（左闭右开）
        while (r < n) {
            while (r < n && title[r] != ' ') {
                ++r;
            }
            // 对于每个单词按要求处理
            if (r - l > 2) {
                title[l++] = toupper(title[l]);
            }
            while (l < r) {
                title[l++] = tolower(title[l]);
            }
            l = ++r;
        }
        return title;
    }


// int main() {
//     string str1 = "capiTalIze tHe titLe";
//     string str2;
//     str2=capitalizeTitle(str1);
//     for (auto c : str2)  cout << c;
//     return 0;
// }
int main() {

    std::string str = "Hello World!";

    std::cout << "Original string: " << str << std::endl;

    str.lower();

    std::cout << "Lowercase string: " << str << std::endl;

    return 0;

}