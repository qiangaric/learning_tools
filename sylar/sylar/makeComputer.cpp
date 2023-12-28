#include <iostream>
using namespace std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-21 19:10:32
 * @LastEditors: sch
 * @LastEditTime: 2023-12-21 19:38:58
 */

// 抽象不同得到零件类
// 抽象CPU类
class CPU
{
private:
    /* data */
public:
    // 抽象的计算函数
    virtual void calculate() = 0;
};

// 抽象显卡类

class VideoCard
{
private:
    /* data */
public:
    // 抽象的显示函数
    virtual void diskPaly() = 0;
};

// 抽象内存条类
class Memory
{
private:
    /* data */
public:
    // 抽象的存储函数
    virtual void storage() = 0;
};

// 电脑类

class Compulter
{
private:
    CPU *m_cpu;      // CPU的零件指针
    VideoCard *m_vc; // 显卡零件指针
    Memory *m_mem;   // 内存条指针
public:
    Compulter(CPU *cpu, VideoCard *vc, Memory *mem)
    {
        m_cpu = cpu;
        m_vc = vc;
        m_mem = mem;
    }

    // 提供工作函数
    void work()
    {
        // 让零件工作起来，调用接口
        m_cpu->calculate();
        m_vc->diskPaly();
        m_mem->storage();
    }
    ~Compulter()
    {
        if (m_cpu !=NULL)
        {
            delete m_cpu;
            m_cpu = NULL;
        }
         if (m_vc !=NULL)
        {
            delete m_vc;
            m_vc = NULL;
        }
         if (m_mem !=NULL)
        {
            delete m_mem;
            m_mem = NULL;
        }
        
    }
};

// 具体厂商
// Intel厂商

class IntelCPU : public CPU
{
    virtual void calculate()
    {
        cout << "Inter CPU 开始计算" << endl;
    }
};

class IntelVideoCard : public VideoCard
{
    virtual void diskPaly()
    {
        cout << "Inter 显卡开始显示了" << endl;
    }
};

class IntelMemory : public Memory
{
    virtual void storage()
    {
        cout << "Inter 内存开始存储了" << endl;
    }
};

// Lenovo 厂商

class LenovoCPU : public CPU
{
    virtual void calculate()
    {
        cout << "Lenovo CPU 开始计算" << endl;
    }
};

class LenovoVideoCard : public VideoCard
{
    virtual void diskPaly()
    {
        cout << "Lenovo 显卡开始显示了" << endl;
    }
};

class LenovoMemory : public Memory
{
    virtual void storage()
    {
        cout << "Lenovo 内存开始存储了" << endl;
    }
};
void test01()
{
    // 第一台电脑零件
    CPU *interlCpu = new IntelCPU;
    VideoCard *intelCard = new IntelVideoCard;
    Memory *intelMem = new IntelMemory;

    // 创建第一台电脑
    Compulter *c1 = new Compulter(interlCpu, intelCard, intelMem);
    c1->work();
    delete c1;
}
int main(int argc, char const *argv[])
{
    test01();
    return 0;
}
