#include <iostream>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{
    int i = 0;
    while (1)
    {
        printf("test gdb block run-time process %d\n", i++);
        sleep(1);
    }
    
    return 0;
}