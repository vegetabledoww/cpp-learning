#include <unordered_map>
#include <vector>
#include <cstring>
#include <random>
#include <numeric>
#include<algorithm>
#include<stdint.h>
#include <iostream>
using namespace std;
vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>>mp;
        for(string &str : strs)
        {
            string key=str;
            sort(key.begin(),key.end());
            mp[key].push_back(str);
        }
        vector<vector<string>>ans;
        for(auto it=mp.begin();it!=mp.end();it++)
        {
            ans.push_back(it->second);
        }
        return ans;
    }
int main(int argc, char const *argv[])
{
    vector<string>strs={"eat","tea","tan","ate","nat","bat"};
    vector<vector<string>>ans;
    ans=groupAnagrams(strs);
    //cout<<ans;
    return 0;
}
