#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // for (int i = 0; i < 252;i++)
    //     printf("abcd");
    // fflush(stdout);
    // while (1)
    //     ;

    char c = 0;
    while (1)
    {
        scanf("%c", &c); // 输入要以\n结尾，但是\n也会进入输入缓冲区，影响下一次读取
        // scanf(" %c", &c);//加空格
        // getchar();
        printf("char : %c\n", c);
      
        while (getchar() != '\n')
            ;
    }

    return 0;
}