#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-25 11:27:39
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-25 11:32:34
 */
template <class T>
class Base
{
    T m;
};

// template <class T>
// class Son : public Base //����,����Ҫ֪�������е�T���ͣ����ܼ̳и�����
class Son : public Base<int>
{

};

void test01()
{
    Son s1;
    
}
int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
