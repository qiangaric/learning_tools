

#### 结构体使用
```c
typedef struct Student
{
   int no;
   char name[12];
}Stu,student;
//于是在声明变量的时候就可：Stu stu1;或者：student stu2;(Stu 和student 同时为Student的别名) 


struct Student
{
   int no;
   char name[12];
}Stu;
// 就必须用struct Student stu1;或者struct Stu stu1;来声明 
```

```

```