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
    int main()
    {
        vector<int>nums={0,1,2,3,4,6};
        cout<<*find(nums.begin(),nums.end(),6);   
        getchar();
        getchar();
        system("pause"); 
        return 0;        
    }