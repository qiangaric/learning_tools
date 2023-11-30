#include <iostream>
using namespace std;

const double PI = 3.14;
class Circle
{
private:
    /* data */
    // 访问权限
    // 公共权限
public:
    // 属性
    // 半径

    int m_r;

    // 行为
    // 获取圆的周长
    double calculaZC()
    {
        return 2 * PI * m_r;
    }

    Circle(/* args */);
    ~Circle();
};

Circle::Circle(/* args */)
{
}

Circle::~Circle()
{
}

int main(int argc, char const *argv[])
{
    /* code */

    Circle c1;
    c1.m_r = 10;
    cout << "圆的周长: " << c1.calculaZC() << endl;
    return 0;
}
