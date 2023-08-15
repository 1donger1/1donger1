#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "DynamicArray.h"
#include "Mysort.h"
#include "MyString.h"
#include <time.h>
#include "Interface.h"

#define Map_Size 5 // 定义地图大小
#define ture 1
#define false 0

struct Player
{
    int HP;
    int attack;
    int x;
    int y;
};

struct Monster
{
    MyString name;
    int HP;
    int attack;
    int x;
    int y;
};

struct Treasure
{
    MyString name;
    int value;
    int x;
    int y;
};

void InitPlayer(struct Player *Player)
{
    Player->HP = 100;
    Player->attack = 999;
    Player->x = 0;
    Player->y = 0;
}

int GetRandNumber(int max)
{
    return rand() % max;
}

struct Monster *CreateMonster(const char *name, int HP, int attack)
{
    struct Monster *monster = (struct Monster *)malloc(sizeof(struct Monster));
    if (monster == NULL)
    {
        printf("CreateMonster malloc fail\n");
        return NULL;
    }

    monster->HP = HP;
    monster->attack = attack;
    // Init_MyString(monster->name, name);
    Initialize(&monster->name, name);

    // 不能超过边界范围
    monster->x = GetRandNumber(Map_Size);
    monster->y = GetRandNumber(Map_Size);

    return monster;
}

struct Treasure *CreateTreasures(const char *name, int value)
{
    struct Treasure *treasure = (struct Treasure *)malloc(sizeof(struct Treasure));
    if (treasure == NULL)
    {
        printf("CreateMonster malloc fail\n");
        return NULL;
    }

    // Init_MyString(monster->name, name);
    Initialize(&treasure->name, name);
    treasure->value = value;

    // 不能超过边界范围
    treasure->x = GetRandNumber(Map_Size);
    treasure->y = GetRandNumber(Map_Size);
    return treasure;
}

void InitMonsters(DMArray *array)
{
    if (ArrayInit(array) == false)
    {
        return;
    }

    // 将CreateMonster()返回值插入数组
    InsertArray(array, CreateMonster("巨龙", 100, 20));
    InsertArray(array, CreateMonster("食人魔", 50, 10));
    InsertArray(array, CreateMonster("食人魔", 50, 10));
    InsertArray(array, CreateMonster("食人魔", 50, 10));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
    InsertArray(array, CreateMonster("哥布林", 20, 5));
}

void InitTreasures(DMArray *array)
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
    switch (symbol)
    {
    case 'w':
        (player->x--)%Map_Size;
        break;

    case 's':
        (player->x++)%Map_Size;
        break;

    case 'a':
        (player->y--) % Map_Size;
        break;

    case 'd':
        (player->y++) % Map_Size;
        break;
    default:
        break;
    }
    if (player->x < 0)
    {
        player->x = 0 - player->x;///////////
    }
    if (player->x >= Map_Size)
    {
        player->x = Map_Size - 1;
    }

    if (player->y < 0)
    {
        player->y = 0 - player->y;
    }
    if (player->y >= Map_Size)
    {
        player->y = Map_Size - 1;
    }
}
int Battle(struct Player *player, struct Monster *monster)
{
    printf("1您遭遇了|%s| 血量:|%d| 攻击力:|%d|\n", monster->name.string, monster->HP, monster->attack);
    // printf("*********************************************************************\n");
    // printf("---------------------------------------------------------------------\n");
    // printf("                         开始战斗！                                   \n");
    // printf("---------------------------------------------------------------------\n");
    // printf("*********************************************************************\n");
     Start_Battle();
    while (player->HP > 0 && monster->HP > 0)
    {
        // printf("2您遭遇了|%s| 血量:|%d| 攻击力:|%d|\n", monster->name.string, monster->HP, monster->attack);

        printf("请选择您要执行的行为:\n");
        printf("1.普通攻击\n");
        printf("2.暴击\n");
        printf("3.逃跑\n");

        int choice;
        scanf("%d", &choice);
        // printf("---------------------------------------------------------------------\n");
        // printf("                         战斗报告！                                   \n");
        // printf("---------------------------------------------------------------------\n");
        Battle_Report();
        switch (choice)
        {
        case 1:
            player->HP -= monster->attack;
            monster->HP -= player->attack;
            printf("%s|对你造成了%d伤害\n", monster->name.string, monster->attack);
            printf("你对%s|造成了%d伤害\n", monster->name.string, player->attack);
            break;
        case 2:
            if (GetRandNumber(2) == 1)
            {
                printf("%s|对你造成了%d伤害\n", monster->name.string, monster->attack);
                printf("你对%s|造成了%d伤害\n", monster->name.string, player->attack * 2);
                player->HP -= monster->attack;
                monster->HP -= player->attack * 2;
            }
            else
            {
                printf("|%s|对你造成了|%d|伤害\n", monster->name.string, monster->attack);
                printf("暴击失败！无法发动攻击！\n");
                player->HP -= monster->attack;
            }
        case 3:
            if (GetRandNumber(2) == 1)
            {
                printf("逃跑成功！\n");
                return true;
            }
            else
            {
                printf("逃跑失败！\n");
                printf("|%s|对你造成了|%d|伤害\n", monster->name.string, monster->attack);
                player->HP -= monster->attack;
            }

        default:
            break;
        }

        if (player->HP <= 0)
        {
            printf("你被|%s|击败了！\n", monster->name.string);
            player->HP = 0;
            return false;
        }
        if (monster->HP <= 0)
        {
            monster->HP = 0;
            printf("你击败了|%s|!\n", monster->name.string);
            return true;
        }
        // printf("-------------------------战斗结束！-----------------------------------\n");
        // printf("---------------------------------------------------------------------\n");
        Battle_End();
    }
    // system("clear");
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
    p[player->x][player->y] = 'X';
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
            printf(" %4c", p[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL)); // 用时间定随机数
    system("clear");

    WelCome();
    // printf("---------------------------------------------------------------------\n");
    // printf("                        欢迎来到魔塔世界                               \n");
    // printf("---------------------------------------------------------------------\n");
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