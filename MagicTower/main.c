#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MyString.h"
#include "DynamicArray.h"
#include "MagicTower.h"
#include "StdFile.h"
#include "LoginSignup.h"
#include <string.h>
#include <unistd.h>
#define Map_Size 5 // 定义地图大小
#define true 1
#define false 0

int main()
{
    srand(time(0));
    char board[Map_Size][Map_Size]; // 用二维数组定义地图的大小
    InitBoard(board);

    struct Player player; // 创建一个名为player、struct Player类型的变量
    InitPlayer(&player);  // 取这个名为player的地址在InitPlayer函数中给他赋值

    DMArray monsters = {NULL, 10, 0}; // 创建一个名为monsters的动态数组结构体，并将他动态数组指针置空、在堆上申请10个单位空间、0个元素
    InitMonster(&monsters);

    DMArray treasures = {NULL, 10, 0};
    InitTreasuers(&treasures);

    DLlist GameUserData;
    InitDLlist(&GameUserData);

    char *num = (char *)malloc(sizeof(char));
    char *ID = (char *)malloc(sizeof(char) * 10);
    char *PWD = (char *)malloc(sizeof(char) * 10);

    srand(time(NULL)); // 使每时每刻的随机值都不一样
    system("clear");
    printf("**********************************************************\n");
    printf("**********************欢迎来到魔塔！***********************\n");
    printf("**********************************************************\n");
    printf("***********************按1注册****************************\n");
    printf("***********************按2登录****************************\n");
    printf("**********************************************************\n");

    printf("您的选择是：");
    int choice;
    while (1)
    {
        scanf("%d", &choice);
        while (getchar() != '\n')
            ;
        switch (choice)
        {
        case 1: // 注册
            system("clear");
            printf("这就为您注册帐号!\n");
            printf("输入帐号:");
            scanf("%s", ID);
            while (getchar() != '\n')
                ;
            printf("输入密码:");
            scanf("%s", PWD);
            while (getchar() != '\n')
                ;

            SignUp(ID, PWD);

            break;
        case 2: // 登录
            // system("clear");
            printf("输入您的账号:");
            scanf("%s", ID);
            while (getchar() != '\n')
                ;
            printf("请输入密码:");
            scanf("%s", PWD);
            while (getchar() != '\n')
                ;

            DLlist *list = GetLineFromFile("UserInfo.txt");
            DBTravel(list, StrTok, &GameUserData);
            if (Login(ID, PWD, &GameUserData) == true)
            {
                int choice_mode;
                printf("请输入你的选项\n");
                printf("1.新游戏\n");
                printf("2.载入游戏\n");
                scanf("%d", &choice_mode);
                switch (choice_mode)
                {
                case 1:
                    printf("开始游戏吧!\n");
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
                                    printf("Game over!\n");
                                    // free(monsters.dp);  // Free monsters here
                                    // monsters.dp = NULL; // Set the pointer to NULL
                                    FreeArray(&monsters);
                                    break;
                                }
                            }
                        }

                        if (player.HP == 0)
                        {
                            break;
                        }

                        // printf("\n");
                        printf("/**输入'q'保存并退出**/\n");
                        printf("请选择你要进行的移动(输入'w','s','a','d'):");

                        char choice;
                        scanf(" %c", &choice);

                        if (choice == 'q')
                        {
                            SaveGameProgress(&player, &monsters, "game_progress.txt");
                            printf("游戏已保存,退出成功!\n");
                            exit(1);
                        }

                        MakeMove(&player, choice);
                    }

                    for (int i = 0; i < monsters.len; i++)
                    {
                        struct Monster *monster = (struct Monster *)monsters.dp[i];
                        free(monster->name.string);
                        free(monster);
                    }
                    free(monsters.dp);
                    break;
                case 2:
                    if (LoadGameProgress(&player, &monsters, "game_progress.txt"))
                    {
                        printf("游戏进度载入成功！\n");
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
                                        printf("Game over!\n");
                                        // free(monsters.dp);  // Free monsters here
                                        // monsters.dp = NULL; // Set the pointer to NULL
                                        // FreeArray(&monsters);

                                        break;
                                    }
                                }
                            }

                            if (player.HP == 0)
                            {
                                break;
                            }

                            printf("请选择你要进行的移动(输入'w','s','a','d'):\n");
                            char choice;
                            scanf(" %c", &choice); // 注意前面的空格，用于吸收上一次输入的换行符

                            MakeMove(&player, choice);
                        }
                        printf("游戏结束。\n");
                        break;
                    }
                    else
                    {
                        printf("游戏进度载入失败，可能是没有存档。\n");
                    }
                    break;
                }
            }
            else
            {
                printf("用户或密码错误,请按2重试!\n");
                continue;
            }
        default:
            printf("输入的选项有误,请输入合法选项!\n");
            continue;
        }
    }
}
