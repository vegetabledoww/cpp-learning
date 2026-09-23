/*
题目：设计循环队列（LeetCode 622）

实现容量固定为 k 的先进先出队列，k >= 1，存入的值为非负整数。
enQueue(value)：入队，成功返回 true，队满返回 false。
deQueue()：出队，成功返回 true，队空返回 false。
Front()/Rear()：查看队头/队尾，队空返回 -1。
isEmpty()/isFull()：判断队空/队满。
要求用数组实现，出队时不移动其他元素，也不使用 STL queue。

示例一：k=3，依次入队 1、2、3、4
输出：true、true、true、false；Front()=1，Rear()=3
解释：前三次入队后容量已满，第四次失败。

示例二：k=3，入队 1、2、3，出队一次，再入队 4
输出：出队和入队均为 true；Front()=2，Rear()=4
解释：4 放入数组开头腾出的槽位，逻辑顺序是 {2,3,4}。
*/
#include <iostream>
#include <vector>
using namespace std;

class MyCircularQueue
{
private:
    vector<int> data;
    int capacity;
    int head;
    int count;

public:
    MyCircularQueue(int k) : data(k), capacity(k), head(0), count(0) {}

    bool enQueue(int value)
    {
        if (isFull()) return false;
        // head 是队头；从队头向后走 count 步，就是下一个空位。
        int tail = (head + count) % capacity;
        data[tail] = value;
        count++;
        return true;
    }

    bool deQueue()
    {
        if (isEmpty()) return false;
        head = (head + 1) % capacity;
        count--;
        return true;
    }

    int Front() { return isEmpty() ? -1 : data[head]; }
    int Rear() { return isEmpty() ? -1 : data[(head + count - 1) % capacity]; }
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
};

int Check(const char *name, int actual, int expected)
{
    cout << name << " expected=" << expected << " actual=" << actual
         << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    MyCircularQueue q(3);
    failed += Check("initial empty", q.isEmpty(), true);
    failed += Check("empty front", q.Front(), -1);
    failed += Check("empty rear", q.Rear(), -1);
    failed += Check("empty pop", q.deQueue(), false);
    failed += Check("push 1", q.enQueue(1), true);
    failed += Check("push 2", q.enQueue(2), true);
    failed += Check("push 3", q.enQueue(3), true);
    failed += Check("full", q.isFull(), true);
    failed += Check("push when full", q.enQueue(4), false);
    failed += Check("front stays 1", q.Front(), 1);
    failed += Check("rear stays 3", q.Rear(), 3);
    failed += Check("pop 1", q.deQueue(), true);
    failed += Check("wrap push 4", q.enQueue(4), true);
    failed += Check("front is 2", q.Front(), 2);
    failed += Check("rear is 4", q.Rear(), 4);
    for (int expected : {2,3,4})
    {
        failed += Check("drain order", q.Front(), expected);
        failed += Check("drain pop", q.deQueue(), true);
    }
    failed += Check("empty again", q.isEmpty(), true);
    failed += Check("refill", q.enQueue(9), true);
    failed += Check("refill front", q.Front(), 9);
    failed += Check("refill rear", q.Rear(), 9);

    MyCircularQueue single(1);
    for (int value : {0,5,8})
    {
        failed += Check("capacity 1 push", single.enQueue(value), true);
        failed += Check("capacity 1 full", single.isFull(), true);
        failed += Check("capacity 1 overflow", single.enQueue(99), false);
        failed += Check("capacity 1 front", single.Front(), value);
        failed += Check("capacity 1 rear", single.Rear(), value);
        failed += Check("capacity 1 pop", single.deQueue(), true);
    }
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：用 head 和 count 区分空与满，数组槽位通过取模循环利用。
出队只移动队头，不必清除旧值；count 决定哪些槽位有效。
每次操作 O(1)，初始化 O(k)，队列存储空间 O(k)。
*/
