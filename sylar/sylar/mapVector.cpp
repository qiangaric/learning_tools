#include <iostream>
#include <map>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-08 09:50:59
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-08 10:49:15
 */

void test01()
{
    map<int, int> m;
    m.insert(pair<int, int>(1, 10));
    m.insert(pair<int, int>(2, 20));
    m.insert(pair<int, int>(3, 30));
    m.insert(pair<int, int>(4, 40));
    if (m.empty())
    {
        cout << "m is empty" << endl;
    }
    else
    {
        cout << "m is not empty" << endl;
    }
}
void printMap(map<int, int> &m)
{
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "key = " << it->first << " vaLue = " << it->second << endl;
    }

    cout << endl;
}

void test02()
{
    map<int, int> m;
    m.insert(pair<int, int>(1, 10));
    m.insert(pair<int, int>(2, 20));
    m.insert(pair<int, int>(3, 30));
    m.insert(pair<int, int>(4, 40));

    map<int, int> m2;
    m2.insert(pair<int, int>(5, 50));
    m2.insert(pair<int, int>(6, 60));
    m2.insert(pair<int, int>(7, 70));
    m2.insert(pair<int, int>(8, 80));

    cout << "before swap" << endl;
    printMap(m);
    printMap(m2);

    m.swap(m2);
    cout << "after swap" << endl;
    printMap(m);
    printMap(m2);
}

int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
