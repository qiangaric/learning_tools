#include <stdio.h>
#include <stdlib.h>

/*Student 为类型别名*/
struct Student
{
    char *name;
    int age;
    char *address;
}
// student ={"gaogao",18,"tianjin"};
/* student 初始化结构体名称
类似： Student student = {"gaogao",18,"tianjin"}
*/
;

int main(int argc, char const *argv[])
{

    struct Student student = {"gaogao"};
    struct Student *stu1;
    struct Student *stu2 = (struct Student *)malloc(sizeof(struct Student));
    // Student* stu1 = (Student*)malloc(sizeof(struct Student)) ;
    if (stu1 == NULL)
    {
        printf("stu1 内容we空\n");
    }
    if (stu2 == NULL)
    {
        printf("stu2内存分配失败");
    }
    printf("stu1 = \n", stu1);
    printf("stu1 = \n", stu2);
    printf("hello,wolrd \n");
    printf("name : %s ,age : %d, address : %s \n", student.name, student.age, student.address);
    free(stu2);
    struct Product
    {
        char symbol[5];
        int quantity;
        double price;
    };
    struct Product *purchase;

    /* 在内存中创建结构体 */
    purchase = (struct Product *)malloc(sizeof(struct Product));
    if (purchase == NULL)
    {
        puts("申请内存出现错误！");
        exit(1);
    }

    /* 分配结构体数据 */
    strcpy(purchase->symbol, "ABCDEF");
    // purchase->symbol= "abc";
    purchase->quantity = 100;
    purchase->price = 801.19;

    /* 显示结构体数据 */
    puts("投资组合如下:");
    printf("符号\t数量\t价格\t值\n");
    printf("%-6s\t%5d\t%.2f\t%.2f\n",
           purchase->symbol,
           purchase->quantity,
           purchase->price,
           purchase->quantity * purchase->price);
    free(purchase);

    return 0;
}
