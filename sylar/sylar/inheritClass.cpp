/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-14 11:35:50
 * @LastEditors: sch
 * @LastEditTime: 2023-12-14 13:18:58
 */

// 继承方式

// 公共继承

class Base
{
private:
    /* data */
public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;
};
class Son1 : public Base
{
public:
    void func()
    {
        m_A = 10; // 父类中的公共权限成员 到子类中依然是公共权限
        m_B = 10; // 父类中的保护权限成员到子类中依然是保护权限
        // m_C = 10; // 父类中的私有权限成员 子类访问不到
    }
};



class Son2 : protected Base
{
public:
    void func()
    {
        m_A = 10; // 父类中的公共权限成员 到子类中依然是公共权限
        m_B = 10; // 父类中的保护权限成员到子类中依然是保护权限
        // m_C = 10; // 父类中的私有权限成员 子类访问不到
    }
};

class Son3 : private Base
{
public:
    void func()
    {
        m_A = 10; // 父类中的公共权限成员 到子类中 变成私有成员
        m_B = 10; // 父类中的保护权限成员到子类中依 变成私有成员
        // m_C = 10; // 父类中的私有权限成员 子类访问不到
    }
};

void test01()
{
    Son1 s1;
    s1.m_A = 100;
    // s1.m_B =10; // 到Son1中m_B是保护权限 类访问不到
}

void test02()
{
    Son2 s1;
    // s1.m_A = 100; // 在son2中 m_A 变为保护权限，因此类外访问不到
    // s1.m_B =10; // 在Son2中 m_B 保护权限 不可以访问
}

void test03()
{
    Son3 s1;
    // s1.m_A = 100; // 在son3中 m_A 变为私有成员，因此类外访问不到
    // s1.m_B =10; // 在son3中 m_B 变为私有成员，因此类外访问不到
}
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
