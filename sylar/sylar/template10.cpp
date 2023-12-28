
#include <iostream>
#include "person.hpp"
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-27 09:58:33
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-27 11:30:05
 */

/**
 * 类模板成员函数类外实现
 *
 */

void test01()
{
    Person<string, int> p("tom", 18);
    p.showPerson();
}

int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
