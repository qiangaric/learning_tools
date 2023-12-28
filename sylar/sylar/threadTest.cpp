#include <iostream>
#include <unistd.h>

using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-26 15:32:55
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-26 16:01:25
 */

int main(int argc, char const *argv[])
{
    int bh = 8;
    string message = "我是一只傻鸟。";
    pid_t pid = fork();
    // 父进程返回值则是新建子进程的进程ID
    // 子进程返回是0
    if (pid > 0)
    { // 父进程将执行这段代码
        cout << "父: pid = " << pid << endl;
        cout << "父: 亲爱的 " << bh << "号: " << message << endl;
    }
    else
    {// 子进程将执行这段代码
        cout << "子: pid = " << pid << endl;
        cout << "子: 亲爱的 " << bh << "号: " << message << endl;
    }

    return 0;
}
