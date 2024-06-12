#include <iostream>
#include <string>
#include <stdlib.h> // 随机数
#include <ctime>
using namespace std;

struct Student
{
    string sName;
    int score;
};

struct Teacher
{
    string tName;
    struct Student sAarry[5];
};

void allocateSpace(struct Teacher tArray[], int len)
{

    string nameSeed = "ABCDE";
    for (int i = 0; i < len; i++)
    {

        tArray[i].tName = "Teacher_";
        tArray[i].tName += nameSeed[i];
        for (int j = 0; j < 5; j++)
        {
            tArray[i].sAarry[j].sName = "Student_";
            tArray[i].sAarry[j].sName += nameSeed[j];
            int random = rand() % 61 + 40;
            tArray[i].sAarry[j].score = random;
        }
    }
}

void printInfo(struct Teacher tArray[], int len)
{

    for (int i = 0; i < len; i++)
    {
        cout << "老师姓名: " << tArray[i].tName << endl;
        for (int j = 0; j < len; j++)
        {
            cout << "\t学生姓名: " << tArray[i].sAarry[j].sName << " 学生分数: " << tArray[i].sAarry[j].score << endl;
        }
    }
}

int main(int argc, char const *argv[])

{

    srand((unsigned int)time(NULL));

    // 创建3名老师的数组
    struct Teacher tArray[3];
    // 通过函数给3名老师的信息赋值，并给老师的学生信息赋值

    int len = sizeof(tArray) / sizeof(tArray[0]);
    allocateSpace(tArray, len);

    // 打印所有老师及所带的学生信息
    printInfo(tArray, len);

    /* code */
    return 0;
}
