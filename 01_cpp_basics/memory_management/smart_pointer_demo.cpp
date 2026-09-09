/*
题目：观察 shared_ptr 与 weak_ptr 的对象生命周期

编写示例观察智能指针管理的对象何时析构，并验证 weak_ptr 不会增加
shared_ptr 的引用计数，因此可以用来打破对象之间的循环引用。

示例一：
创建一个 shared_ptr<Myclass>，离开作用域后释放最后一个强引用。
输出：先调用构造函数，再调用析构函数。

示例二：
创建两个 shared_ptr<Myclass>，让它们通过 weak_ptr 相互引用。
输出：离开作用域后，两个对象都能正常调用析构函数。
*/

#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;
// 析构函数和虚析构函数
// class Base
// {
// public:
//     Base()
//     {
//         cout << "父类构造函数" << endl;
//     };
//     ~Base()
//     {
//         cout << "父类析构函数" << endl;
//     }
//     void print()
//     {
//         cout<<"弗雷打印"<<endl;
//     }
// };

// class Deriver:public Base
// {
// public:
//     Deriver(){};
//     ~Deriver()
//     {
//         cout<<"子类析构函数执行"<<endl;
//     };
//     void print()
//     {
//         cout<<"子类打印"<<endl;
//     }
// };

// int main()
// {
//     Base *p=new Deriver;
//    // p->print();
//     delete p;
//     return 0;
// }

class Myclass
{
public:
    shared_ptr<Myclass> other;
    weak_ptr<Myclass>w_other;
    Myclass()
    {
        cout << "构造函数" << endl;
    }
    ~Myclass()
    {
        cout << "析构函数" << endl;
    }
};

// int main(int argc, char const *argv[])
// {
//     shared_ptr<Myclass> ptr1(new Myclass());
//     shared_ptr<Myclass> ptr2(new Myclass());
//     //循环引用问题，一次析构函数也没调用(两个对象相互引用)
//     // ptr1->other=ptr2;
//     // ptr2->other=ptr1;
//     //弱引用可以很好的解决这个问题
//     ptr1->w_other=ptr2;
//     ptr2->w_other=ptr1;
//     return 0;
// }

int main()
{
    cout << "示例一：单个 shared_ptr\n";
    {
        shared_ptr<Myclass> ptr = make_shared<Myclass>();
    }

    cout << "\n示例二：使用 weak_ptr 相互引用\n";
    {
        shared_ptr<Myclass> ptr1 = make_shared<Myclass>();
        shared_ptr<Myclass> ptr2 = make_shared<Myclass>();
        ptr1->w_other = ptr2;
        ptr2->w_other = ptr1;
    }

    return 0;
}
