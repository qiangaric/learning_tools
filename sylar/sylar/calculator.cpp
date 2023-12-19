#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-19 11:45:13
 * @LastEditors: sch
 * @LastEditTime: 2023-12-19 16:31:12
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
// 加法计算器类
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

//减法计算器类
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

// 乘法计算器类
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

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
