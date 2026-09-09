#pragma once
#include<iostream>
using namespace std;
class B
{
    private:
        B():m_name("B"){}
        B(const B&){}//拷贝构造函数
        ~B(){}
        B&operator=(const B&);//赋值构造函数
        static B* m_instance;
        string m_name;
    public:
        static B* instance()//公有静态函数
        {
            if(m_instance==nullptr)
            {
                m_instance=new B();
            }
            return m_instance;
        }
        void show()
        {
            cout<<m_name<<endl;
        }
};

B * B::m_instance=nullptr;//静态成员变量初始化