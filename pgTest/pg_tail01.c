#include <stdio.h>
#include <stdlib.h>

// �����������ֵĺ���
void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
}

// ��ת`buffer[i��j]`�ĺ���
char *reverse(char *buffer, int i, int j)
{
    while (i < j)
    {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

// �� C ��ʵ�� `itoa()` �����ĵ�������
char *itoa(int value, char *buffer, int base)
{
    // ������Ч
    if (base < 2 || base > 32)
    {
        return buffer;
    }

    // �������ֵľ���ֵ
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

    // �������Ϊ 0
    if (i == 0)
    {
        buffer[i++] = '0';
    }

    // �������Ϊ 10 ��ֵΪ�����������ַ���
    // ǰ����һ������ (-)
    // �����κ�����������ֵ���Ǳ���Ϊ���޷��ŵ�
    if (value < 0 && base == 10)
    {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null ��ֹ�ַ���

    // ��ת�ַ���������
    return reverse(buffer, 0, i - 1);
}

// �� C ��ʵ�� itoa ����
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
