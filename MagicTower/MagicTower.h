#ifndef __MAGICTOWER_H_
#define __MAGICTOWER_H_
#include"MyString.h"
#define Map_Size 5 //定义地图大小


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
    int isAlive; // still alive
};

struct Treasure
{
    MyString name;
    int value;
    int x;
    int y;
};

void InitPlayer(struct Player* Player);
int GetRandNumber(int max);//获得随机值
struct Monster * CreateMonster(const char* name,int HP,int attack);
struct Treasure * CreateTreasure(const char* name,int value);
void InitMonster(struct DynamicArray *array);
void InitTreasuers(struct DynamicArray *array);
void MakeMove(struct Player *player,char symbol);
int Battle(struct Player *player,struct Monster* monster);
void InitBoard(char (*p)[Map_Size]);//用数组指针指向二维数组
void PrintMap(char (*p)[Map_Size],struct Player *player);


#endif