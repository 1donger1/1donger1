#include <stdio.h>
#include <stdlib.h>

/*
请输入星期几的第一个字母来判断一下是星期几，
如果第一个字母一样，则继续判断第二个字母
*/

int main(int argc, char *argv[])
{
    char ch;
    printf("请输入第一个字符:\n");

    ch = getchar();
    getchar();

    switch (ch)
    {
    case 'm':
    case 'M':
        printf("monday\n");
        break;
    case 'w':
    case 'W':
        printf("wednesday\n");
        break;
    case 'f':
    case 'F':
        printf("Friday\n");
        break;
    case 't':
    case 'T':
    {
        printf("请输入下一个字母：\n");
        scanf(" %c", &ch);
        if (ch == 'h')
        {
            printf("thursday\n");
        }
        if (ch == 'u')
        {
            printf("tuesday\n");
        }
        break;
    }

    case 's':
    case 'S':
    {
        printf("请输入下一个字母：\n");
        scanf(" %c", &ch);
        if (ch == 'a')
        {
            printf("saturday\n");
        }
        if (ch == 'u')
        {
            printf("sunday\n");
        }
        break;
    }
    }

    return 0;
}
