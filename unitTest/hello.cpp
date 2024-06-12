#include <iostream>
#include "swap.h"
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 10;
    int *p;
    p = &a;
    cout << "a的地址为: " << &a << endl;
    cout << "a的地址为: " << p << endl;

    // 解引用
    // 可以通过解引用的方式来找到指针指向的内存
    // 指针前加* 代表解引用，找到指针指向的内存中的数据

    *p = 100;
    cout << "a的地址为: " << &a << endl;
    cout << "a的地址为: " << a << endl;

    cout << "int占用的内存大小: " << sizeof(int *) << endl;
    cout << "double占用的内存大小: " << sizeof(double *) << endl;
    cout << "float占用的内存大小: " << sizeof(float *) << endl;

    return 0;
}
