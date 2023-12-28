
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

// ��������ģ��
template <class T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// �����㷨
template <class T>
void mySort(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int max = i; // �϶����ֵ���±�
        for (int j = i + 1; j < len; j++)
        {
            // �϶������ֵ�ȱ�������ֵҪС��˵��J�±�������������ֵ
            if (arr[max] < arr[j])
            {
                max = j; // �������ֵС��
            }
        }
        if (max != i)
        {
            // ����max��i����
            mySwap(arr[max], arr[i]);
        }
    }
}

// �ṩ��ӡ����ģ��
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
