/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-14 11:35:50
 * @LastEditors: sch
 * @LastEditTime: 2023-12-14 13:18:58
 */

// �̳з�ʽ

// �����̳�

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
        m_A = 10; // �����еĹ���Ȩ�޳�Ա ����������Ȼ�ǹ���Ȩ��
        m_B = 10; // �����еı���Ȩ�޳�Ա����������Ȼ�Ǳ���Ȩ��
        // m_C = 10; // �����е�˽��Ȩ�޳�Ա ������ʲ���
    }
};



class Son2 : protected Base
{
public:
    void func()
    {
        m_A = 10; // �����еĹ���Ȩ�޳�Ա ����������Ȼ�ǹ���Ȩ��
        m_B = 10; // �����еı���Ȩ�޳�Ա����������Ȼ�Ǳ���Ȩ��
        // m_C = 10; // �����е�˽��Ȩ�޳�Ա ������ʲ���
    }
};

class Son3 : private Base
{
public:
    void func()
    {
        m_A = 10; // �����еĹ���Ȩ�޳�Ա �������� ���˽�г�Ա
        m_B = 10; // �����еı���Ȩ�޳�Ա���������� ���˽�г�Ա
        // m_C = 10; // �����е�˽��Ȩ�޳�Ա ������ʲ���
    }
};

void test01()
{
    Son1 s1;
    s1.m_A = 100;
    // s1.m_B =10; // ��Son1��m_B�Ǳ���Ȩ�� ����ʲ���
}

void test02()
{
    Son2 s1;
    // s1.m_A = 100; // ��son2�� m_A ��Ϊ����Ȩ�ޣ����������ʲ���
    // s1.m_B =10; // ��Son2�� m_B ����Ȩ�� �����Է���
}

void test03()
{
    Son3 s1;
    // s1.m_A = 100; // ��son3�� m_A ��Ϊ˽�г�Ա�����������ʲ���
    // s1.m_B =10; // ��son3�� m_B ��Ϊ˽�г�Ա�����������ʲ���
}
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
