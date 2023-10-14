// #include "postgres.h"
int main(int argc, char const *argv[])
{

    unsigned int a = 0x12345678;
    printf("a= %x \n", a);
    unsigned long b = (unsigned long)a << 32;

    printf("b= %lu \n", b);

    // uint32_t a = 888;

    printf("a is %ld", a);
    return 0;
}
