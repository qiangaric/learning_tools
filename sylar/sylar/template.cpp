#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-22 09:37:00
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-22 14:31:16
 */

/**
 * 泛型编程 主要利用的技术就是模板
 * c++ 提供两种模板机制 函数模板和类模板
 *
 * 函数模板作用：
 *      建立一个通用函数，其函数反馈值类型和形参类型可以不具体制定，用一个虚拟的类型来代表
 *
 * template<typename T>
 * 函数声明或定义
 * 解释：
 *    template --- 声明创建模板
 *    typename --- 表面其后面的符号是一种数据类型，可以用class代替
 *    T        ---  通用的数据类型，名称可以替换，通常为大写字母
 * 
 * 注意事项：
 *     1、自动类型推导，必须推导出一致的数据类型T才可以使用
 *     2、模板必须要确定出T的数据类型，才可以使用
 */

// 两个整型交换函数

template <typename T> // 声明一个模板，告诉编译器后面代码中紧跟着的T不要报错，T是一个通用数据类型
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

void test01()
{
    int a = 10;
    int b = 20;
    // 使用函数模板交换
    // 两种方式使用函数模板

    // 1、自动类型推到
    mySwap(a, b);

    // 2、显示指定类型
    // mySwap<int>(a, b);

    cout << "a = " << a << "  b=" << b << endl;
}
int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
