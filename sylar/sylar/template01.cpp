#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-25 09:49:09
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-25 09:55:46
 */

template <class NameType, class AgeType>
class Person
{
private:
    /* data */
public:
    Person(NameType name, AgeType age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    void showPerson()
    {
        cout << "name: " << this->m_Name << " age: " << this->m_Age << endl;
    }
    NameType m_Name;
    AgeType m_Age;
};

void test01()
{
    Person<string, int>p1("aric",18);
    p1.showPerson();
}
int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
