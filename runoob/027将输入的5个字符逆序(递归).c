#include <stdio.h>
#include <stdlib.h>

void fun()
{
    char ch;
    if((ch = getchar())!= '\n')
    {
        fun();
    }

    if(ch!='\n')
    {
        printf("%c", ch);
    }
}

int main(int argc, char *argv[])
{
    printf("请输入字符:\n");
    fun();

    return 0;
}
