#include <iostream>
using namespace std;

class Person
{
private:
    /* data */
public:
    // ��ͳ��ʼ������
    // Person(int a, int b, int c)
    // {
    //     m_A = a;
    //     m_B = b;
    //     m_C = c;
    // };

    // ��ʼ���б�
    Person(int a, int b, int c) : m_A(a), m_B(b), m_C(c){

                                                  };
    int m_A;
    int m_B;
    int m_C;
};

void test01()
{
    Person p(10, 20, 30);
    cout << "Aֵ: " << p.m_A << endl;
    cout << "Bֵ: " << p.m_B << endl;
    cout << "Cֵ: " << p.m_C << endl;
}
int main(int argc, char const *argv[])
{
    /* code */
    test01();

    return 0;
}
