
#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-21 18:24:03
 * @LastEditors: sch
 * @LastEditTime: 2023-12-21 19:12:43
 */

class Anminal
{

public:
    Anminal(/* args */)
    {
        cout << "Animal 构造函数调用 " << endl;
    };
    virtual void Speak() = 0;
    // 利用虚析构可以解决 父类指针释放子类对象时不干净的问题
    // virtual ~Anminal(/* args */)
    // {
    //     cout << "Animal 析构函数调用 " << endl;
    // };
    // 纯虚析构函数
    virtual ~Anminal() = 0;
};
Anminal ::~Anminal(/* args */)
{
    cout << "Animal 纯虚函数调用" << endl;
};

class Cat : public Anminal
{

public:
    Cat(string name)
    {
        cout << "Cat 构造函数调用 " << endl;
        m_Name = new string(name);
    };
    virtual void Speak()
    {
        cout << *m_Name << "小猫在说话" << endl;
    }
    ~Cat()
    {
        if (m_Name != NULL)
        {
            cout << "Cat 析构函数调用" << endl;
            delete m_Name;
            m_Name = NULL;
        }
    }
    string *m_Name;
};

void test01()
{
    Anminal *animal = new Cat("Tom");
    animal->Speak();
    delete animal;
}

int main(int argc, char const *argv[])
{
    test01();

    return 0;
}
