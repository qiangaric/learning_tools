#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-19 11:45:13
 * @LastEditors: sch
 * @LastEditTime: 2023-12-21 16:42:28
 */

class AbstrctCalculator
{
private:
    /* data */
public:
    virtual int getResult()
    {
        return 0;
    };
    int m_Num1;
    int m_Num2;
};
// �ӷ���������
class AddCalculator : public AbstrctCalculator
{
private:
    /* data */
public:
    int getResult()
    {
        return m_Num1 + m_Num2;
    }
};

// ������������
class SubstrctCalculator : public AbstrctCalculator
{
private:
    /* data */
public:
    int getResult()
    {
        return m_Num1 - m_Num2;
    }
};

void test02()
{
    // ��̬ʹ������
    // ����ָ���������ָ���������

    // �ӷ�����

    AbstrctCalculator *abc = new AddCalculator;
    abc->m_Num1 = 100;
    abc->m_Num2 = 200;
    cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;

    // �����Ժ�ǵ�����
    delete abc;

    abc = new SubstrctCalculator;
    abc->m_Num1 = 100;
    abc->m_Num2 = 200;
    cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;
}
int main(int argc, char const *argv[])
{
    test02();
    return 0;
}
