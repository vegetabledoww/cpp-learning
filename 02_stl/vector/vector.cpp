#include<iostream>
#include<vector>
using namespace std;
int main(int argc, char const *argv[])
{
    vector<int>v;
    int m;
    for (size_t i = 0; i < 3; i++)
    {
        v.push_back(i);
        m = v.size();
        cout<<v[i]<<endl;
    }
    
    return 0;
}
