#include <iostream>
#include <map>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-08 10:52:02
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-08 13:39:41
 */

void printMap(map<int, int> &m)
{
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "key = " << it->first << " vaLue = " << it->second << endl;
    }

    cout << endl;
}

void test01()
{
    map<int, int> m;
    // ����
    // ��һ��
    m.insert(pair<int, int>(1, 10));

    // �ڶ���
    m.insert(make_pair(2, 20));

    // ������
    m.insert(map<int, int>::value_type(3, 30));

    // ������ ��; ��������key���ʵ�value
    m[4] = 40;

    // ɾ����ʼ����
    // m.erase(m.begin());
    // m.erase(5);

    // ���
    //
    //  m.erase(m.begin(),m.end());
    // m.clear();

    // ���Һ�ͳ��

    map<int, int>::iterator pos = m.find(5);
    if (pos != m.end())
    {
        cout << "find the element key = " << (*pos).first << " value = " << pos->second << endl;
    }
    else
    {
        cout << "nono" << endl;
    }

    // ͳ��
    // map ����������ظ�keyԪ��
    int num = m.count(3);
    cout << "num = " << num << endl;

    printMap(m);
}
class MyCompare
{

public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};

void printMap01(map<int, int> m)
{
    for (map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "key = " << it->first << " vaLue = " << it->second << endl;
    }

    cout << endl;
}

void test02()
{

    map<int, int, MyCompare> m;
    m.insert(pair<int, int>(1, 10));
    m.insert(pair<int, int>(2, 20));
    m.insert(pair<int, int>(3, 30));
    m.insert(pair<int, int>(4, 40));
    // m.insert(make_pair(2, 20));

    for (map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "key = " << it->first << " vaLue = " << it->second << endl;
    }
    // printMapLess(m);
    // printMap01(m);
}

int main(int argc, char const *argv[])
{

    test02();
    return 0;
}
