#pragma once
#include<iostream>
using namespace std;
class A
{
    private:
        A():m_name("A"){}//默认构造函数（privite下）
        A(const A&)=delete;//拷贝构造函数
        ~A(){}
        A &operator=(const A&)=delete;//赋值构造函数
        static A* m_instance;
        string m_name;
    public:
        static A* instance()//公有静态函数
        {
            if(m_instance==nullptr)
            {
                m_instance=new A();//线程安全的饿汉模式
            }
            return m_instance;
        }
        void show()
        {
            cout<<m_name<<endl;
        }
};

A * A::m_instance=nullptr;//静态成员变量初始化必须在类外


