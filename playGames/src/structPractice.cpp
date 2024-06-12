#include <iostream>
using namespace std;

struct Hero
{
    string name;
    int age;
    string sex;
};

void bubbleSort(struct Hero herroArray[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (herroArray[j].age > herroArray[j+1].age)
            {
                struct Hero temp = herroArray[j];
                herroArray[j] = herroArray[j + 1];
                herroArray[j + 1] = temp;
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    // 创建英雄结构体

    // 创建数组存放5名英雄
    struct Hero heroArray[5] = {
        {"刘备", 23, "男"},
        {"关羽", 22, "男"},
        {"张飞", 20, "男"},
        {"赵云", 21, "男"},
        {"貂蝉", 19, "女"},
    };

    

    // 对数组进行排序，按照年龄进行升序排序

    bubbleSort(heroArray, 5);

    // 将排序后结果打印输出

    int len = sizeof(heroArray) / sizeof(heroArray[0]);
    for (int i = 0; i < len; i++)
    {
        cout << " 姓名: " << heroArray[i].name << " 年龄: " << heroArray[i].age
             << " 性别: " << heroArray[i].sex << endl;
    }
    return 0;
}
