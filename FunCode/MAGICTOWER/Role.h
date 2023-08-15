#ifndef __ROLE_H_
#define __ROLE_H_

#include "DynamicArray.h"
#include "MyString.h"
#include "DoubleLinkList.h"

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

struct User
{
    char username[20];
    char password[20];
};

void InitPlayer(struct Player *Player);
struct Monster *CreateMonster(const char *name, int HP, int attack);
struct Treasure *CreateTreasures(const char *name, int value);
void InitMonsters(DMArray *array);
void InitTreasures(DMArray *array);

struct User *CreateUser(const char *username, const char *password);
void FreeUser(struct User *user);

static DLlist UserList;

#endif