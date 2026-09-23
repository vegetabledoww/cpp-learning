/*
题目：队列与双端队列的基本操作（入门示例）

给定整数数组 values：
1. 依次放入 queue，再依次取出，返回出队顺序。
2. 依次放入 deque 的尾部，再交替从头部、尾部取出（先头部），返回取出顺序。
数组可以为空；元素可以重复，也可以为负数。

示例一：输入 values={1,2,3,4}
输出：queue={1,2,3,4}，deque={1,4,2,3}
解释：队列先进先出；双端队列可以从两端取出。

示例二：输入 values={5,6,7}
输出：queue={5,6,7}，deque={5,7,6}
解释：交替取头尾时，最后剩下的 6 只取一次。
*/
#include <deque>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> QueueOrder(const vector<int> &values)
{
    queue<int> q;
    for (int value : values) q.push(value);
    vector<int> result;
    while (!q.empty())
    {
        // front 读取队头，pop 删除队头；pop 本身不返回元素。
        result.push_back(q.front());
        q.pop();
    }
    return result;
}

vector<int> DequeOrder(const vector<int> &values)
{
    deque<int> q;
    for (int value : values) q.push_back(value);
    vector<int> result;
    bool takeFront = true;
    while (!q.empty())
    {
        if (takeFront)
        {
            result.push_back(q.front());
            q.pop_front();
        }
        else
        {
            result.push_back(q.back());
            q.pop_back();
        }
        takeFront = !takeFront;
    }
    return result;
}

void Print(const vector<int> &values)
{
    cout << '[';
    for (int value : values) cout << value << ' ';
    cout << ']';
}

int Check(const char *name, const vector<int> &actual, const vector<int> &expected)
{
    cout << name << " expected=";
    Print(expected);
    cout << " actual=";
    Print(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    failed += Check("queue even", QueueOrder({1,2,3,4}), {1,2,3,4});
    failed += Check("deque even", DequeOrder({1,2,3,4}), {1,4,2,3});
    failed += Check("queue odd", QueueOrder({5,6,7}), {5,6,7});
    failed += Check("deque odd", DequeOrder({5,6,7}), {5,7,6});
    failed += Check("queue empty", QueueOrder({}), {});
    failed += Check("deque empty", DequeOrder({}), {});
    failed += Check("deque single", DequeOrder({-1}), {-1});
    failed += Check("deque duplicates", DequeOrder({2,2,3}), {2,3,2});

    // push_front 也是双端队列的基本操作：这里得到 {1,2,3}。
    deque<int> q;
    q.push_back(2);
    q.push_front(1);
    q.push_back(3);
    failed += Check("push both ends", vector<int>(q.begin(), q.end()), {1,2,3});
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：
1. queue：push 入队，front/back 读两端，pop 只能删除队头。
2. deque：push_front/push_back 和 pop_front/pop_back 分别操作两端。
3. 读取或删除前先保证非空；以上单次队列操作为 O(1)。
4. 两个示例算法均为 O(n) 时间、O(n) 额外空间（包括结果）。
*/
