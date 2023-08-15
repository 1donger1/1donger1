#include "StdFile.h"
#include "DoubleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void Print(ElementType value)
// {
//     char *content = (char *)value;
//     printf("%s\n", content);
// }
// void freeStr(ElementType value)
// {
//     free(value);
// }

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

void Print(ElementType element)
{
    struct User *user = (struct User *)element;
    printf("user : %s passwd : %s\n", user->UserName, user->Passwd);
}

int main(int argc, char *argv[])
{
#if 0
    // char *content = LoardFromFile("file.txt");
    // if (content != NULL)
    // {
    //     printf("%s\n", content);
    //     free(content);
    // }

    // DLlist *list = GetLineFromFile("file.txt");
    // Trave(list, Print);

    // FreeDLlist(list, freeStr);
    // free(list);

    // char *str = "hello world";
    // WriteToFile("test.txt", str, strlen(str));

    // DLlist *list = GetLineFromFile("test.txt");
    // WriteLineToFile("test2.txt", list);

    // char temp[100] = "user=test";
    // char *user = strtok(temp, "=");
    // char *name = strtok(NULL, "=");

    // printf("%s %s\n", user, name);

    // CopyFile("test.txt", "test2.txt");

#endif

    if (argc != 3)
    {
        printf("invaild numbers!\n");
        return 0;
    }
    InitDLlist(&UserList);

    DLlist *list = GetLineFromFile("test.txt");
    Trave(list, Strtok);

    // LNode *TravelPoint = UserList.head;
    // while (TravelPoint != NULL)
    // {
    //     struct User *user = (struct User *)TravelPoint->data;
    //     if (user->UserName== argv[1] && user->Passwd == argv[2])
    //     {
    //         return 1;
    //     }
    // }
    Trave(&UserList, Print);

    if (Login(argv[1], argv[2]) == 1)
    {
        printf("login success\n");
    }
    else
    {
        printf("login fail\n");
    }

    struct User *newUser = CreateUser("chuang", "619");
    InsertTail(&UserList, newUser);

    WriteLineToFile("test.txt", &UserList);

    return 0;
}