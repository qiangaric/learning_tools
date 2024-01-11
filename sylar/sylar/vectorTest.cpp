#include <vector>
#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-05 18:04:34
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-09 14:03:19
 */

class Person
{

public:
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};

void test01()
{

    // 创建一个vector容器，数组
    // vector<int> v;
    // v.push_back(10);
    // v.push_back(20);
    // v.push_back(30);
    // v.push_back(40);

    // 通过迭代器访问容器中的数据

    // vector<int>::iterator itBegin = v.begin(); // 起始迭代器 指向容器中第一个元素
    // vector<int>::iterator itEnd = v.end();     // 结束迭代器 指向容器中最后一个元素的下一个位置

    // while (itBegin != itEnd)
    // {
    //     cout << *itBegin << endl;
    //     itBegin++;
    // }

    // for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    // {
    //     cout << *itBegin << endl;
    // }
}

void test02()
{
    vector<Person> v;
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);
    Person p5("eee", 50);
    Person p6("fff", 60);
    // 向容器中添加数据
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    v.push_back(p5);
    v.push_back(p6);

    // 遍历容器中的数据
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "姓名： " << it->m_Name << " ,年龄: " << it->m_Age << endl;
    }
};

// 存放

void test03()
{

    vector<Person *> v;
    Person p1("aaa", 10);
    Person p2("bbb", 20);
    Person p3("ccc", 30);
    Person p4("ddd", 40);
    Person p5("eee", 50);
    Person p6("fff", 60);
    // 向容器中添加数据
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);
    v.push_back(&p6);

    // 遍历容器中的数据
    for (vector<Person *>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "姓名： " << (*it)->m_Name << " ,年龄: " << (*it)->m_Age << endl;
    }
}

void test04()
{
    vector<vector<int>> v;

    // 创建小容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;
    vector<int> v5;

    // 向容器中添加数据

    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i + 1);
        v2.push_back(i + 2);
        v3.push_back(i + 3);
        v4.push_back(i + 4);
        v5.push_back(i + 5);
    }
    // 将小容器插入到大容器中
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);

    // 通过大容器,把所有数据遍历一遍
    for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
    {
        for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
        {
            cout << *vit << " ";
        }
        cout << endl;
    }
}
int main(int argc, char const *argv[])
{
    test04();
    return 0;
}
