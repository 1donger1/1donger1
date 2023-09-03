/********************log_signup.c***************************/
#include "StdFile.h"
#include "DoubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static DLlist UserList;

struct User
{
    char UserName[20];
    char Passwd[20];
};

struct User *CreateUser(const char *name, const char *passwd)
{
    struct User *user = (struct User *)malloc(sizeof(struct User));
    if (user == NULL)
    {
        printf("malloc fail");
    }
    strcpy(user->UserName, name);
    strcpy(user->Passwd, passwd);
    return user;
}

void FreeUser(struct User *user)
{
    if (user != NULL)
    {
        free(user);
    }
}

void Strtok(ElementType element)
{
    char *str = (char *)element;
    char *userName = strtok(str, "=");
    char *passwd = strtok(NULL, "=");
    struct User *user = CreateUser(userName, passwd);
    InsertTail(&UserList, user);
}

int Login(const char *name, const char *passwd)
{
    LNode *TravelPoint = UserList.head;
    while (TravelPoint != NULL)
    {
        struct User *user = (struct User *)TravelPoint->data;
        if (strcmp(user->UserName, name) == 0 && strcmp(user->Passwd, passwd) == 0)
        {
            return 1;
        }
        TravelPoint = TravelPoint->next;
    }
    return 0;
}

int Signup(const char *name, const char *passwd)
{
    // 检查用户名是否已存在
    LNode *TravelPoint = UserList.head;
    while (TravelPoint != NULL)
    {
        struct User *user = (struct User *)TravelPoint->data;
        if (strcmp(user->UserName, name) == 0)
        {
            return 0; // 用户名已存在，注册失败
        }
        TravelPoint = TravelPoint->next;
    }

    // 创建用户结构体并插入到用户列表
    struct User *newUser = CreateUser(name, passwd);
    InsertTail(&UserList, newUser);

    // 将新用户信息写入文件
    FILE *file = fopen("test.txt", "a"); // 以追加模式打开文件
    if (file != NULL)
    {
        fprintf(file, "%s=%s\n", newUser->UserName, newUser->Passwd);
        fclose(file);
        return 1; // 注册成功
    }
    else
    {
        FreeUser(newUser); // 写入文件失败，释放内存
        return -1;         // 注册失败
    }
}

void Print(ElementType element)
{
    struct User *user = (struct User *)element;
    printf("user : %s passwd : %s\n", user->UserName, user->Passwd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("invaild numbers!\n");
        return 0;
    }
    InitDLlist(&UserList);

    DLlist *list = GetLineFromFile("test.txt");
    Travel(list, Strtok);


    if (Login(argv[1], argv[2]) == 1)
    {
        printf("login success\n");
    }
    else
    {
        printf("login fail\n");
    }

    return 0;
}