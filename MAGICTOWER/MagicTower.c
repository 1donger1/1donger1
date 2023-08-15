#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MyString.h"
#include "DynamicArray.h"
#include "MagicTower.h"
#define Map_Size 5 // 定义地图大小
#define ture 1
#define false 0

void InitPlayer(struct Player *Player)
{
    Player->HP = 100;
    Player->attack = 999;
    Player->x = 0;
    Player->y = 0;
}

int GetRandNumber(int max) // 获得随机值
{
    return rand() % max;
}

struct Monster *CreateMonster(const char *name, int HP, int attack)
{
    struct Monster *monster = (struct Monster *)malloc(sizeof(struct Monster));
    if (monster == NULL)
    {
        printf("Create Monster Error!\n");
        return NULL;
    }

    monster->HP = HP;
    monster->attack = attack;
    Initialize(&monster->name, name); // 在MyString.c文件中用Initialize函数将怪兽的名字赋给怪兽

    monster->x = GetRandNumber(Map_Size);
    monster->y = GetRandNumber(Map_Size);

    return monster;
}

struct Treasure *CreateTreasure(const char *name, int value)
{
    struct Treasure *treasure = (struct Treasure *)malloc(sizeof(struct Treasure));
    if (treasure == NULL)
    {
        printf("Create treasure Error!\n");
        return NULL;
    }

    Initialize(&treasure->name, name);
    treasure->value = value;

    treasure->x = GetRandNumber(Map_Size);
    treasure->y = GetRandNumber(Map_Size);

    return treasure;
}

void InitMonster(struct DynamicArray *array)
{
    if (ArrayInit(array) == false)
    {
        return;
    }

    InsertArray(array, CreateMonster("巨龙", 100, 20)); // 在名为monsters动态数组结构体中插入CreateMonster函数创建的怪兽信息
    InsertArray(array, CreateMonster("食人魔", 50, 10));
    InsertArray(array, CreateMonster("食人魔", 50, 10));
    InsertArray(array, CreateMonster("食人魔", 50, 10));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
}

void InitTreasuers(struct DynamicArray *array)
{
    if (ArrayInit(array) == false)
    {
        return;
    }
    // 将CreateTreasures()返回值插入数组
    InsertArray(array, CreateTreasures("宝藏", 100));
    InsertArray(array, CreateTreasures("珍珠", 50));
    InsertArray(array, CreateTreasures("珍珠", 50));
    InsertArray(array, CreateTreasures("珍珠", 50));
    InsertArray(array, CreateTreasures("药品", 20));
    InsertArray(array, CreateTreasures("药品", 20));
    InsertArray(array, CreateTreasures("药品", 20));
    InsertArray(array, CreateTreasures("药品", 20));
    InsertArray(array, CreateTreasures("药品", 20));
}

void MakeMove(struct Player *player, char symbol)
{
    system("clear");

    switch (symbol)
    {
    case 'w':
        player->y--;
        break;

    case 's':
        player->y++;
        break;

    case 'a':
        player->x--;
        break;

    case 'd':
        player->x++;
        break;
    default:
        break;
    }
    if (player->x < 0)
    {
        player->x = Map_Size + player->x;
    }
    if (player->x >= Map_Size)
    {
        player->x = player->x % (Map_Size);
    }

    if (player->y < 0)
    {
        player->y = Map_Size + player->y;
    }
    if (player->y >= Map_Size)
    {
        player->y = player->y % (Map_Size);
    }
}

int Battle(struct Player *player, struct Monster *monster)
{
    // system("clear");
    printf("您遭遇了|%s| 血量: |%d| 攻击: %d\n", monster->name.string, monster->HP, monster->attack);
    printf("****************************************\n");
    printf("                 开始战斗                \n");
    printf("****************************************\n");
    while (player->HP > 0 && monster > 0)
    {
        // printf("您遭遇了|%s| 血量：|%d| 攻击力： |%d|\n", monster->name.string, monster->HP, monster->attack);
        printf("请选择你要执行的行为：\n");
        printf("1、普通攻击\n");
        printf("2、暴击\n");
        printf("3、逃跑\n");
        int choice;
        scanf("%d", &choice);
        while(getchar() != '\n')
            ;
        if (choice == 1 || choice == 2 || choice == 3)
        {
            switch (choice)
            {
            case 1:
                player->HP -= monster->attack;
                monster->HP -= player->attack;
                printf("|%s|对你造成了%d伤害\n", monster->name.string, monster->attack);
                printf("你对|%s|造成了%d伤害\n", monster->name.string, player->attack);
                break;

            case 2:
                if (GetRandNumber(2) == 1)
                {
                    printf("|%s|对你造成了%d伤害\n", monster->name.string, monster->attack);
                    printf("你对|%s|造成了%d伤害\n", monster->name.string, player->attack * 2);
                    player->HP -= monster->attack;
                    monster->HP -= player->attack * 2;
                }
                else
                {
                    printf("|%s|对你造成了%d伤害\n", monster->name.string, monster->attack);
                    printf("暴击失败！ 无法发动攻击！\n");
                    player->HP -= monster->attack;
                }
                break;

            case 3:
                if (GetRandNumber(2) == 1)
                {
                    printf("逃跑成功\n");
                    return ture;
                }
                else
                {
                    printf("逃跑失败\n");
                    printf("%s对你造成了%d伤害\n", monster->name.string, monster->attack);
                    player->HP -= monster->attack;
                }
                break;
            default:
                break;
            }
        }
        else
        {
            printf("输入的选项有误,请输入1-3之间的数字\n");
            continue;
        }

        if (player->HP <= 0)
        {
            printf(("你被|%s|击败了！\n"), monster->name.string);
            player->HP = 0;
            return false;
        }

        if (monster->HP <= 0)
        {
            printf(("你击败了|%s|!\n"), monster->name.string);
            monster->HP = 0;
            return ture;
        }
    }
    printf("*****************************end****************************\n");
}

void InitBoard(char (*p)[Map_Size]) // 用数组指针指向二维数组
{
    for (int i = 0; i < Map_Size; i++)
    {
        for (int j = 0; j < Map_Size; j++)
        {
            p[i][j] = '-';
        }
    }
}

void PrintMap(char (*p)[Map_Size], struct Player *player)
{
    InitBoard(p);

    p[player->y][player->x] = 'x'; //

    printf("     ");
    for (int i = 0; i < Map_Size; i++)
    {
        printf(" %4d", i + 1);
    }
    printf("\n");
    for (int i = 0; i < Map_Size; i++)
    {
        printf(" %4d", i + 1);
        for (int j = 0; j < Map_Size; j++)
        {
            printf(" %4c", p[i][j]); //
        }
        printf("\n");
    }
}
