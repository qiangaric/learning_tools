#include <stdio.h>
#include <stdint.h>
#include <bits/stdc++.h>

using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-12 15:15:47
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-17 13:34:09
 */

long getFileSize(FILE *file)
{
    long fileSize;

    // 将文件指针移到文件末尾
    fseek(file, 0, SEEK_END);

    // 获取文件指针的当前位置，即文件大小
    fileSize = ftell(file);

    // 将文件指针复位到文件开头
    fseek(file, 0, SEEK_SET);

    return fileSize;
}

struct Node
{
    int data;
    Node *next;
};
Node *head, *p, *r;
int x;

void insert(Node *head, int i, int x)
{
    Node *p, *s;
    int j;
    p = head;
    j = 0;
    while ((p->next != NULL) && (j < i - 1))
    {
        p = p->next;
        j++;
    }
    if (p->next == NULL)
    {
        cout << "没有这个位置" << endl;
    }
    else
    {
        s = new Node;
        s->data = x;
        s->next = p->next;
        p->next = s;
    }
};

void del(Node *head, int i)
{
    Node *p, *s;
    int j;
    p = head;
    j = 0;
    while ((p->next != NULL) && (j < i - 1))
    {
        p = p->next;
        j++;
    }
    if (p->next == NULL)
    {
        cout << "没有这个位置" << endl;
    }
    else
    {

        s = p->next;
        p->next = p->next->next;
        free(s);
    }
};

int test01()
{
    cin >> x;
    // 申请头节点
    head = new Node;
    r = head;
    while (x != -1)
    {
        // 申请下一个节点，数据赋值，next置NULL
        p = new Node;
        p->data = x;
        p->next = NULL;

        // 将新节点指向前一个节点
        r->next = p;
        // 指针想后移
        r = p;

        cin >> x;
    }

    // 读链表数据
    // 重新指定头指针
    printf("开始读取数据\n");
    p = head->next;
    while (p->next != NULL)
    {
        cout << p->data << " ";
        // 指针向后移动
        p = p->next;
    }
    cout << p->data << " " << endl;
    printf("读取结束 \n");

    // 查找数据

    p = head->next;
    int i = 0;
    while (p->next != NULL)
    {
        if (p->data == 3)
        {
            i++;
        }
        p = p->next;
    }
    if (p->data == 3)
    {
        i++;
    }
    printf("data == 3的 有 %d 个\n", i);

    insert(head, 5, 99);

    // 读链表数据
    // 重新指定头指针
    printf("开始读取数据\n");
    p = head->next;
    while (p->next != NULL)
    {
        cout << p->data << " ";
        // 指针向后移动
        p = p->next;
    }
    cout << p->data << " " << endl;
    printf("读取结束 \n");

    del(head, 2);
    // 读链表数据
    // 重新指定头指针
    printf("开始读取数据\n");
    p = head->next;
    while (p->next != NULL)
    {
        cout << p->data << " ";
        // 指针向后移动
        p = p->next;
    }
    cout << p->data << " " << endl;
    printf("读取结束 \n");
    return 0;
}

#include <stdio.h>

// 定义 Log_event_type 枚举类型
enum Log_event_type
{
    UNKNOWN_EVENT = 0,
    // 添加其他枚举值
    EVENT_ONE,
    EVENT_TWO,
    EVENT_THREE,
    // ... 添加其他枚举值
    EVENT_COUNT // 用于获取枚举值的数量
};

// 获取 Log_event_type 的名字
const char *getEventName(int eventTypeValue)
{
    switch (eventTypeValue)
    {
    case UNKNOWN_EVENT:
        return "Unknown Event";
    case EVENT_ONE:
        return "Event One";
    case EVENT_TWO:
        return "Event Two";
    case EVENT_THREE:
        return "Event Three";
    // ... 添加其他名字
    default:
        return "Invalid Event";
    }
}

int main()
{
    // 使用 Log_event_type 枚举类型的数值
    int eventTypeValue = 1; // 例如，0 表示 UNKNOWN_EVENT

    // 获取对应的名字
    const char *eventName = getEventName(eventTypeValue);

    // 输出名字
    printf("Event Type: %s\n", eventName);

    return 0;
}
