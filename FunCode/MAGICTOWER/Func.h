#ifndef __FUNC_H_
#define __FUNC_H_
#define Map_Size 5 // 定义地图大小

#include "Role.h"
#include "DoubleLinkList.h"


int GetRandNumber(int max);
void MakeMove(struct Player *player, char symbol);


int IsAccountEqual(const char *account, DLlist *list);
int regist(FILE *file, DLlist *list);
int sign_in(FILE *file, DLlist *list);
int IsPassWdEqual(char *account, char *passwd, DLlist *list);
#endif