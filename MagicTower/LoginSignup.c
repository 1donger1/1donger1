#include "LoginSignup.h"
#include "StdFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0

struct User
{
    char *name;
    char *password;
};

struct User *CreaterUser(char *name, char *pwd)
{
    struct User *user = (struct User *)malloc(sizeof(struct User));
    if (user == NULL)
    {
        printf("CreateUser malloc error!\n");
        return NULL;
    }
    user->name = name;
    user->password = pwd;
    return user;
}

int IsEqualID(const char *FilePath, char *userName)
{
    FILE *file = fopen(FilePath, "r+");
    if (file == NULL)
    {
        printf("fopen error!\n");
        return false;
    }
    char line[15];
    while (fgets(line, sizeof(line), file))
    {
        char *name = strtok(line, "=");
        if (name != NULL && strcmp(name, userName) == 0)
        {
            fclose(file);
            return true;
        }
        memset(line, 0, 15);
    }
    fclose(file);
    return false;
}

int SignUp(char *name, char *pwd)
{
    if (IsEqualID("UserInfo.txt", name))
    {
        printf("名字已被占用,请输入1(注册)重试！\n");
        return 0;
    }
    int len = strlen(name) + strlen(pwd) + 1 + 1;
    char *userdata = NULL;
    userdata = (char *)malloc(sizeof(char) * len);
    if (userdata == NULL)
    {
        printf("userdata malloc error!\n");
        return false;
    }
    strcpy(userdata, name);
    strcat(userdata, "=");
    strcat(userdata, pwd);
    printf("%s\n", userdata);
    AppendToFile("UserInfo.txt", userdata, len - 1); // StdFile.c文件
    printf("注册成功,请前往登录!\n");
    free(userdata);
    return true;
}

void StrTok(ElementType element, DLlist *list)
{
    char *str = (char *)element;
    char *UserName = strtok(str, "=");
    char *pwd = strtok(NULL, "=");
    struct User *user = CreaterUser(UserName, pwd);
    DBInsertTail(list, user);
}

int Login(char *name, char *pwd, DLlist *list)
{
    struct Node *TravelPoint = list->head;
    while (TravelPoint != NULL)
    {
        struct User *user = (struct User *)TravelPoint->data;
        if (strcmp(user->name, name) == 0 && strcmp(user->password, pwd) == 0)
        {
            printf("欢迎用户%s进入魔塔!\n", name);
            return true;
        }
        TravelPoint = TravelPoint->next;
    }
    // printf("用户或密码错误!\n");
    return false;
}
