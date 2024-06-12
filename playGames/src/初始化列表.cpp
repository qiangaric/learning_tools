#include <iostream>
using namespace std;

class Person
{
private:
    /* data */
public:
    // 传统初始化方法
    // Person(int a, int b, int c)
    // {
    //     m_A = a;
    //     m_B = b;
    //     m_C = c;
    // };

    // 初始化列表
    Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c){

                                                  };
    int m_A;
    int m_B;
    int m_C;
};

void test01()
{
    Person p(10, 20, 30);
    cout << "A值: " << p.m_A << endl;
    cout << "B值: " << p.m_B << endl;
    cout << "C值: " << p.m_C << endl;
}
int main(int argc, char const *argv[])
{
    /* code */
    test01();

    return 0;
}
