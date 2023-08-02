#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
题目：字符串反转，
如将字符串 "www.runoob.com" 反转为 "moc.boonur.www"。
*/

void reverse(char *str)
{
    int len;
    char temp;
    char *begin, *end;
    len = strlen(str);
    begin = str;
    end = str + len - 1;
    while (begin < end)
    {
        temp = *begin;
        *begin = *end;
        *end = temp;
        begin++;
        end--;
    }
}

int main(int argc, char *argv[])
{
    char *str = (char *)malloc(sizeof(char) * 100);
    fgets(str, sizeof(char) * 100, stdin);

    reverse(str);

    puts(str);

    return 0;
}