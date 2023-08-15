#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Interface.h"
#include "DynamicArray.h"
#include "DoubleLinkList.h"
#include "Role.h"
#include "Func.h"
#include "Game.h"
#include "time.h"


int main(int argc, char *argv[])
{
    srand(time(NULL)); // 用时间定随机数
    system("clear");

    FILE *file = fopen("file.txt", "a+"); // 存用户注册信息
    if (file == NULL)
    {
        printf("file open fail!\n");
    }

    char ContentTemp[100] = {0}; // 静态链表存所有用户信息
    while (fgets(ContentTemp, 100, file) != NULL)
    {
        char *Line = (char *)malloc(strlen(ContentTemp) + 1);
        strcpy(Line, ContentTemp);
        char *username = strtok(Line, " ");
        char *userpasswd = strtok(NULL, " ");
        struct User *user = CreateUser(username, userpasswd);
        InsertTail(&UserList, user);
    }

    WelCome();
    // int pagechoice;
    // scanf("%d", &pagechoice);
    // getchar();
    // while(1)
    // {
    //     switch(pagechoice)
    //     {
    //         case 1:

    //     }
    // }

    char board[Map_Size][Map_Size];
    InitBoard(board);

    struct Player player;
    InitPlayer(&player);

    DMArray monsters = {NULL, 10, 0};
    InitMonsters(&monsters);

    DMArray treasures = {NULL, 10, 0};
    InitTreasures(&treasures);

    while (1)
    {
        PrintMap(board, &player);
        printf("你当前所在的位置是<%d,%d>\n", player.x + 1, player.y + 1);
        for (int i = 0; i < monsters.len; i++)
        {
            struct Monster *monster = (struct Monster *)monsters.dp[i];
            if (monster->HP > 0 && monster->x == player.x && monster->y == player.y)
            {
                if (Battle(&player, monster) == false)
                {
                    printf("Game Over!");
                    break;
                }
            }
        }
        if (player.HP == 0)
        {
            break;
        }
        printf("请选择你要进行的移动(输入'w','a','s','d'):");
        printf("\n");
        char choice;
        scanf("%c", &choice);
        MakeMove(&player, choice);
        // system("clear");
    }

    for (int i = 0; i < monsters.len; i++)
    {
        struct Monster *monster = (struct Monster *)monsters.dp[i];
        free(monster->name.string);
        free(monster);
    }

    free(monsters.dp);

    return 0;
}