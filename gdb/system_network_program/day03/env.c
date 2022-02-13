#include <stdio.h>
#include <stdlib.h>


int main(int argc,char **argv)
{
    
    printf("PATH:%s\n",getenv("PATH") );
    return 0;
}

// int main(int argc, char *argv[],char **env)
// {
//     while (*env++ != NULL)
//     {
//         printf("%s\n",*env);
//     }
//     int count = 0;
//     while (env[count] != NULL)
//     {
//         printf("%s\n",env[count]);
//         count++;
//     }
//     return 0;
// }