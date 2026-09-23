/*
专题：stack 栈的基本操作
任务：将整数依次压栈，再依次弹出，返回弹出顺序。
示例一：输入 {1,2,3}，输出 {3,2,1}，因为最后入栈的 3 最先出栈。
示例二：输入 {7}，输出 {7}，弹出后栈为空。
允许空输入；访问 top 和调用 pop 之前必须保证非空。
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> StackOrder(const vector<int> &input)
{
    stack<int> s;
    for (int value : input) s.push(value);
    vector<int> result;
    while (!s.empty())
    {
        result.push_back(s.top()); // top 读取，pop 删除；pop 不返回元素。
        s.pop();
    }
    return result;
}

int Check(const vector<int> &input, const vector<int> &expected)
{
    vector<int> actual = StackOrder(input);
    cout << "expected=[";
    for (int x : expected) cout << x << ' ';
    cout << "] actual=[";
    for (int x : actual) cout << x << ' ';
    cout << ']' << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int failed = 0;
    failed += Check({1,2,3}, {3,2,1});
    failed += Check({7}, {7});
    failed += Check({}, {});
    failed += Check({-1,2,-1}, {-1,2,-1});
    stack<int> s;
    s.push(10);
    s.emplace(20); // 对 int 效果与 push(20) 相同。
    cout << "size expected=2 actual=" << s.size() << '\n';
    if (s.size() != 2) failed++;
    s.top() = 30; // top 返回栈顶元素的引用，可修改栈顶。
    cout << "top expected=30 actual=" << s.top() << '\n';
    if (s.top() != 30) failed++;
    cout << "failed tests: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
/*
收获点：stack 后进先出，queue 先进先出，priority_queue 按优先级出队。
stack 没有 begin/end，也不能下标访问；想保留原栈，可先复制再弹出查看。
默认底层容器为 deque；本例单次压栈/弹栈 O(1)，整体 O(n) 时间与空间。
*/
