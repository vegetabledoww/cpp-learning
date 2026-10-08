/*
虚析构与非虚成员函数

通过 Base* 指向派生对象，观察非虚 print 的静态绑定，以及 delete 时虚析构的调用顺序。析构记录写入调用方保存的数组。

样例一：Base* p=new Derived; p->print() -> Base，print 非虚。
样例二：delete p -> 记录 [Derived,Base]，先析构派生部分再析构基类部分。
来源：pen_exam_8/pen_exam_8/_8_pen_exam.cpp:568-604（原稿见 originals，映射见 SOURCES.md）。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Base
{
  protected:
    vector<string> &events;

  public:
    explicit Base(vector<string> &e) : events(e)
    {
    }
    virtual ~Base()
    {
        events.push_back("Base");
    }
    string print() const
    {
        return "Base";
    }
};
class Derived : public Base
{
  public:
    explicit Derived(vector<string> &e) : Base(e)
    {
    }
    ~Derived() override
    {
        events.push_back("Derived");
    }
    string print() const
    {
        return "Derived";
    }
};

// 本地验证

template <class T> void show(const T &value)
{
    cout << value;
}
template <class T> void show(const vector<T> &values)
{
    cout << '[';
    for (size_t i = 0; i < values.size(); ++i)
    {
        if (i)
            cout << ',';
        show(values[i]);
    }
    cout << ']';
}
template <class T> int check(const char *name, const T &actual, const T &expected)
{
    cout << name << " expected=";
    show(expected);
    cout << " actual=";
    show(actual);
    cout << (actual == expected ? " PASS\n" : " FAIL\n");
    return actual == expected ? 0 : 1;
}

int main()
{
    int fail = 0;
    vector<string> events;
    Base *p = new Derived(events);
    fail += check("sample1 nonvirtual", p->print(), string("Base"));
    delete p;
    fail += check("sample2 destructor order", events, vector<string>{"Derived", "Base"});
    events.clear();
    {
        Derived d(events);
        fail += check("direct derived", d.print(), string("Derived"));
    }
    fail += check("automatic object", events, vector<string>{"Derived", "Base"});
    return fail ? 1 : 0;
}

/* 收获点：虚析构保证通过基类指针删除时完整析构，不能把所有同名函数都误认为虚调用。示例操作 O(1)。 */
