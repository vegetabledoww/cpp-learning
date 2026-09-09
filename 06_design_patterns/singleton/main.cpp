/*
题目：验证单例模式

类 A 和类 B 都只能通过静态函数 instance() 获取对象。请验证同一个类无论
调用多少次 instance()，返回的都是同一个对象；不同类拥有各自独立的实例。

示例一：
输入：连续两次调用 A::instance()
输出：两个指针相等，并且 show() 输出 A

示例二：
输入：连续两次调用 B::instance()
输出：两个指针相等，并且 show() 输出 B
*/

#include<iostream>
using namespace std;
#include "singleton_a.h"
#include "singleton_b.h"
int main()
{
    A *a1=A::instance();
    A *a2=A::instance();
    cout << boolalpha;
    cout << "示例一 expected=same instance: true，show: A\n";
    cout << "actual=same instance: " << (a1==a2) << "，show: ";
    a1->show();

    B *b1=B::instance();
    B *b2=B::instance();
    cout << "示例二 expected=same instance: true，show: B\n";
    cout << "actual=same instance: " << (b1==b2) << "，show: ";
    b1->show();
    return 0;
}
