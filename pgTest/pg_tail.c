// #include <libpq-fe.h>
// #include "postgresql/server/c.h"
#define abc(x,y) (x##y)
#define printDBL( exp,exp1 ) printf( #exp " = %s \n", exp##exp1 )
#define UINT64CONST(x) (x##UL)
int main(int argc, char const *argv[])
{

    unsigned int a = 0x12345678;
    // printf("a= %x \n", a);
    unsigned long b = (unsigned long)a << 32;

    // printf("b= %lu \n", b);

    // uint32_t bnb = 888;

    char xx = "sas";
    char yy = "asda";
    printDBL(3,4);
    // printf("asbc = %s",printDBL(xx));

    printf("a is %x\n", UINT64CONST(0x100000000));
    return 0;
}
