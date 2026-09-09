/*
题目：自定义结构体的小根堆

给定若干个坐标 Node{x, y}，请使用 priority_queue 按照 x 从小到大取出；
当 x 相同时，按照 y 从小到大取出。

示例一：
输入：{(2,3), (1,5), (1,2)}
输出：(1,2) (1,5) (2,3)

示例二：
输入：{(0,0), (-1,4), (0,-2)}
输出：(-1,4) (0,-2) (0,0)
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct Node
{
    int x, y;
    Node(int a = 0, int b = 0) : x(a), y(b) {}
};

struct cmp
{
    bool operator()(Node a, Node b)//升序排列
    {
        if (a.x == b.x)
            return a.y > b.y;
        return a.x > b.x;
    }
};

void PrintInOrder(const vector<Node> &nodes)
{
    priority_queue<Node, vector<Node>, cmp> queue;
    for (const Node &node : nodes)
    {
        queue.push(node);
    }

    while (!queue.empty())
    {
        cout << '(' << queue.top().x << ',' << queue.top().y << ") ";
        queue.pop();
    }
    cout << '\n';
}

int main()
{
    cout << "示例一 expected=(1,2) (1,5) (2,3)\n";
    cout << "actual=";
    PrintInOrder({Node(2,3), Node(1,5), Node(1,2)});

    cout << "示例二 expected=(-1,4) (0,-2) (0,0)\n";
    cout << "actual=";
    PrintInOrder({Node(0,0), Node(-1,4), Node(0,-2)});

    return 0;
}
