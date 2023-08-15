#include "Role.h"
#include "Func.h"
#include "string.h"

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

    Initialize(&monster->name, name);

    // 不能超过边界范围
    monster->x = GetRandNumber(Map_Size);
    monster->y = GetRandNumber(Map_Size);

    // printf("%s %d %d\n", monster->name.string, monster->x, monster->y);

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

struct User *CreateUser(const char *username, const char *password)
{
    struct User *user = (struct User *)malloc(sizeof(struct User));

    strcpy(user->username, username);
    strcpy(user->password, password);
    return user;
}

void FreeUser(struct User *user)
{
    if (user != NULL)
    {
        free(user);
    }
}