
#include <iostream>
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-22 14:42:41
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-22 16:57:02
 */

// 交换函数模板
template <class T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// 排序算法
template <class T>
void mySort(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int max = i; // 认定最大值的下标
        for (int j = i + 1; j < len; j++)
        {
            // 认定的最大值比遍历的数值要小，说明J下标才是真正的最大值
            if (arr[max] < arr[j])
            {
                max = j; // 更新最大值小标
            }
        }
        if (max != i)
        {
            // 交换max和i函数
            mySwap(arr[max], arr[i]);
        }
    }
}

// 提供打印数组模板
template <class T>
void printArray(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void test01()
{
    char charArr[] = "sdfdasd";
    int num = sizeof(charArr) / sizeof(char);
    mySort(charArr, num);
    printArray(charArr, num);
}

int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
