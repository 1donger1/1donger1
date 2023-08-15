#include <stdio.h>
#include <stdlib.h>
#include "SystemHead.h"

int main(int argc, char *argv[])
{
    // execl("/bin/ls", "ls", "-l", NULL);
    // execlp("ls", "ls", "-ah", NULL);

    // static char *env[] = {"USER=Donger", "PASSWD=190621"};
    // 允许用户自定义环境变量
    // execle("./test", "test", NULL, env);

    //相当于对execl的封装
    char *value[] = {"ls", "-l", NULL};
    // execv("/bin/ls", value);

    // execvp("ls", value);
    char *enve[] = {"USER=Donger", "PASSWD=190621"};
    execve("./test", value,enve);
    return 0;
}