/*
题目：使用 priority_queue 排序任务

每个任务由 {优先级, 名称} 表示。请使用 priority_queue 按优先级从小到大
取出任务；优先级相同时，按照名称的字典序从小到大取出。

示例一：
输入：{{1,"jinzongquan"}, {1,"aaa"}, {2,"bbb"}}
输出：(1,aaa) (1,jinzongquan) (2,bbb)

示例二：
输入：{{3,"z"}, {2,"b"}, {2,"a"}}
输出：(2,a) (2,b) (3,z)
*/

#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
struct cmp
{
    bool operator()(const pair<int,string>& a, const pair<int,string>& b){
        if(a.first==b.first)
            return a.second>b.second;
        return a.first>b.first;//pop的时候是升序
    }
};

void PrintInPriorityOrder(const vector<pair<int,string>>& tasks)
{
    priority_queue<pair<int,string>,vector<pair<int,string>>,cmp> queue;
    for (const auto &task : tasks)
    {
        queue.push(task);
    }

    while(!queue.empty())
    {
        cout << '(' << queue.top().first << ',' << queue.top().second << ") ";
        queue.pop();
    }
    cout << '\n';
}

int main()
{
    cout << "示例一 expected=(1,aaa) (1,jinzongquan) (2,bbb)\n";
    cout << "actual=";
    PrintInPriorityOrder({{1,"jinzongquan"}, {1,"aaa"}, {2,"bbb"}});

    cout << "示例二 expected=(2,a) (2,b) (3,z)\n";
    cout << "actual=";
    PrintInPriorityOrder({{3,"z"}, {2,"b"}, {2,"a"}});

    return 0;
}
