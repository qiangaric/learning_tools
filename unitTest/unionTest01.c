
int main(int argc, char const *argv[])
{
    
    unsigned int a = 0x12345678;
    printf("a= %x \n",a);
    unsigned long  b = (unsigned long )a << 32;
    
    printf("b= %lu \n",b);
    return 0;
}
