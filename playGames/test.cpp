#include <iostream>
using namespace std;


class test
{
private:
    /* data */
public:
    test(/* args */);
    ~test();
};

test::test(/* args */)
{
}

test::~test()
{
}

struct student
{
    string name;
    int age;
    int score;
};

void printStdeunt(const student *s)
{
    cout << "name:" << s->name << " age: " << s->age << "score:" << s->score;
}
int main(int argc, char *argv[])

{

    struct student s = {"zhangsan", 12, 90};
    printStdeunt(&s);
    cout << "hello, world\n";
    return 0;
}