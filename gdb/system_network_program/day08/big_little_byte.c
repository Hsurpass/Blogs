#include <stdio.h>

typedef union big_little_byte
{
    int data;
    char ch;
}blb;


int main()
{
    blb tmp;
    tmp.data = 0x12345678;
    printf("ch = %x\n",tmp.ch);
    
    return 0;
}