#include <stdio.h>
#include <stdlib.h>

// 交换两个数字的函数
void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
}

// 反转`buffer[i…j]`的函数
char *reverse(char *buffer, int i, int j)
{
    while (i < j)
    {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

// 在 C 中实现 `itoa()` 函数的迭代函数
char *itoa(int value, char *buffer, int base)
{
    // 输入无效
    if (base < 2 || base > 32)
    {
        return buffer;
    }

    // 考虑数字的绝对值
    int n = abs(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
        {
            buffer[i++] = 65 + (r - 10);
        }
        else
        {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    // 如果数字为 0
    if (i == 0)
    {
        buffer[i++] = '0';
    }

    // 如果基数为 10 且值为负数，则结果字符串
    // 前面有一个减号 (-)
    // 对于任何其他基数，值总是被认为是无符号的
    if (value < 0 && base == 10)
    {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null 终止字符串

    // 反转字符串并返回
    return reverse(buffer, 0, i - 1);
}

// 在 C 中实现 itoa 函数
int main(void)
{
    // __uint32_t aa = log2(16777216);
    // char ss[10];
    // itoa(aa, ss, 2);
    // printf("integer = %d  string = %s\n", aa, ss);

    __uint32_t a = ((__uint32_t)log2(16777216));
    char s[10];
    itoa(a, s, 2);
    __uint32_t off_upper, xrecoff;
    off_upper = 101;
    xrecoff = 40;
    // xrecoff += off_upper << ((__uint32_t)log2(16777216));

    char soff_upper[32];
    itoa(off_upper, soff_upper, 2);
    // xrecoff += off_upper
    char sxrecoff[32];
    itoa(xrecoff, sxrecoff, 2);

    printf("off_upper--integer = %-20d  off_upper--string = %-40s\n", off_upper, soff_upper);
    printf("xrecoff--integer   = %-20d    xrecoff--string = %-40s\n", xrecoff, sxrecoff);
    xrecoff += off_upper << 24;
    char sxxrecoff[32];
    itoa(xrecoff, sxxrecoff, 2);
    printf("LSN--integer       = %-20d     xrecoff--string = %-40s\n", xrecoff, sxxrecoff);

    return 0;
}
