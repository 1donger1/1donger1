#include <stdio.h>
#include <string.h>

// fegts()会把\n读入，故要消除垃圾字符
// 则buf[strlen(buf) - 1] = '\0';
int main()
{
    char buf[32] = "";
    fgets(buf, 32, stdin);//chen
    int len = strlen(buf);
    printf("%d\n", len);//5

    return 0;
}