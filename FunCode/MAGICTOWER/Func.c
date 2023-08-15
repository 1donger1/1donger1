#include <stdlib.h>
#include "time.h"
#include "Func.h"
#include "DoubleLinkList.h"
#include <string.h>


int GetRandNumber(int max)
{
    //srand(time(NULL)); // 用时间定随机数
    return rand() % max;
}

void MakeMove(struct Player *player, char symbol)
{
    system("clear");

    switch (symbol)
    {
    case 'w':
        player->x--;
        break;

    case 's':
        player->x++;
        break;

    case 'a':
        player->y--;
        break;

    case 'd':
        player->y++;
        break;
    default:
        break;
    }
    if (player->x < 0)
    {
        // player->x = 0; 
        player->x = Map_Size + player->x; ///////////
    }
    if (player->x >= Map_Size)
    {
        // player->x = Map_Size - 1;
        player->x = player->x % ( Map_Size);
    }

    if (player->y < 0)
    {
        // player->y = 0;
        player->y = Map_Size + player->y;
    }
    if (player->y >= Map_Size)
    {
        // player->y = Map_Size - 1;
        player->y = player->y%(Map_Size);
    }
}

// struct User *CreateUser(const char *username, const char *password)
// {
//     struct User *user = (struct User *)malloc(sizeof(struct User));

//     strcpy(user->username, username);
//     strcpy(user->password, password);
//     return user;
// }

// void FreeUser(struct User *user)
// {
//     if (user != NULL)
//     {
//         free(user);
//     }
// }

// static DLlist UserList;

int IsAccountEqual(const char *account, DLlist *list)
{
    // printf("%s %s\n",str1,str2);
    struct Node *TravelNode = list->head;
    while (TravelNode != NULL)
    {

        char *temp = (char *)TravelNode->data;
        char username[10];
        memset(username, 0, 10);
        int count = 0;
        int i = 0;
        if (temp[0] == ' ')
        {
            TravelNode = TravelNode->next;
            continue;
        }
        else
        {
            while (temp[i] != ' ')
            {
                count++;
                i++;
            }
            strncpy(username, temp, count);
            if (strcmp(username, account) == 0)
            {
                return false;
            }
        }
        TravelNode = TravelNode->next;
    }
    return true;
}

int regist(FILE *file, DLlist *list)
{
    system("clear");
    char account[20], passwd[20];
    memset(account, 0, 20);
    memset(passwd, 0, 20);
    printf("*********regist***********\n");
    printf("请输入你的账号:");
    scanf("%s", account);
    printf("请输入你的密码:");
    scanf("%s", passwd);

    if (IsAccountEqual(account, list) == true)
    {
        fprintf(file, "%s %s", account, passwd);
        fprintf(file, "\n");
        printf("注册成功\n");
        printf("你的账号为:%s,密码为:%s\n", account, passwd);
        struct User *user = CreateUser(account, passwd);
        InsertTail(&UserList, user);
        return true;
    }
    else
    {
        printf("用户名重名!\n");
        printf("请重新注册以登录\n");
    }
}

int sign_in(FILE *file, DLlist *list)
{
    char account[20], passwd[20];
    memset(account, 0, 20);
    memset(passwd, 0, 20);
    printf("*********sign_in***********\n");
    printf("请输入你的账号:");
    scanf("%s", account);
    printf("请输入你的密码:");
    scanf("%s", passwd);

    if (IsPassWdEqual(account, passwd, list) == true)
    {
        printf("******登录成功********\n");

        return true;
    }
    else
    {
        printf("账号密码不匹配,请重新登录\n");
        return false;
    }
}

int IsPassWdEqual(char *account, char *passwd, DLlist *list)
{
    struct Node *TravelNode = list->head;
    while (TravelNode != NULL)
    {
        struct User *user = (struct User *)TravelNode->data;

        if (strcmp(user->username, account) == 0 && strncmp(user->password, passwd, strlen(passwd) - 1) == 0)
        {
            return true;
        }

        TravelNode = TravelNode->next;
    }

    return false;
}
