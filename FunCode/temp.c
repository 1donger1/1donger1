#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../MyLibrary/DynamicArray/DynamicArray.h"
#include "../MyLibrary/Mysort/Mysort.h"
#include "../MyLibrary/MyString/MyString.h"

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
        printf("Create Monster Error!\n");
        return NULL;
    }

    monster->HP = HP;
    monster->attack = attack;
    Initize(&monster->name, name); // 在MyString.c文件中用Initize函数将怪兽的名字赋给怪兽

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

    Initize(&treasure->name, name);
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
    InsertArray(array, CreateMonster("食人魔1", 20, 10));
    InsertArray(array, CreateMonster("食人魔2", 20, 10));
    InsertArray(array, CreateMonster("食人魔3", 20, 10));
    InsertArray(array, CreateMonster("哥布林", 10, 5));
    InsertArray(array, CreateMonster("哥布林", 10, 5));
    InsertArray(array, CreateMonster("哥布林", 10, 5));
    InsertArray(array, CreateMonster("张硕", 1, 5));
    InsertArray(array, CreateMonster("洪伟", 1, 1));
}

void InitTreasuers(struct DynamicArray *array)
{
    if (ArrayInit(array) == false)
    {
        return;
    }
    InsertArray(array, CreateTreasure("法拉利", 100));
    InsertArray(array, CreateTreasure("美国美女", 50));
    InsertArray(array, CreateTreasure("法国美女", 50));
    InsertArray(array, CreateTreasure("日本美女", 50));
    InsertArray(array, CreateTreasure("真香槟", 20));
    InsertArray(array, CreateTreasure("假香槟", 20));
    InsertArray(array, CreateTreasure("不真不假香槟", 20));
    InsertArray(array, CreateTreasure("半真半假香槟", 20));
    InsertArray(array, CreateTreasure("小香槟", 20));
}

void MakeMove(struct Player *player, char symbol)
{
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
        player->x = 0;
    if (player->x >= Map_Size)
        player->x = Map_Size - 1;
    if (player->y < 0)
        player->y = 0;
    if (player->y >= Map_Size)
        player->y = Map_Size - 1;
}

int Battle(struct Player *player, struct Monster *monster)
{
    system("clear");
    printf("您遭遇了|%s| 血量: |%d| 攻击: %d", monster->name.string, monster->HP, monster->attack);
    printf("****************************************\n");
    printf("                 开始战斗                \n");
    printf("****************************************\n");
    while (player->HP > 0 && monster > 0)
    {
        printf("您遭遇了|%s| 血量：|%d| 攻击力： |%d|\n", monster->name.string, monster->HP, monster->attack);
        printf("请选择你要执行的行为：\n");
        printf("1、普通攻击\n");
        printf("2、暴击\n");
        printf("3、逃跑\n");
        int choice;
        scanf("%d", &choice);
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

int main()
{
    srand(time(NULL)); // 使每时每刻的随机值都不一样
    system("clear");
    printf("*********************************************************\n");
    printf("****************欢迎来到缅甸！ 我的小baby*******************\n");
    printf("*********************************************************\n");

    char board[Map_Size][Map_Size]; // 用二维数组定义地图的大小
    InitBoard(board);

    struct Player player; // 创建一个名为player、struct Player类型的变量
    InitPlayer(&player);  // 取这个名为player的地址在InitPlayer函数中给他赋值

    struct DynamicArray monsters = {NULL, 10, 0}; // 创建一个名为monsters的动态数组结构体，并将他动态数组指针置空、在堆上申请10个单位空间、0个元素
    InitMonster(&monsters);

    struct DynamicArray treasures = {NULL, 10, 0};
    InitMonster(&treasures);

    // PrintMap(board,&player);

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
                    break;
                }
            }
        }

        if (player.HP == 0)
            break;

        printf("请选择你要进行的移动(输入'w','s','a','d'):");
        printf("\n");
        char choice;
        scanf("%c", &choice);
        MakeMove(&player, choice);
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