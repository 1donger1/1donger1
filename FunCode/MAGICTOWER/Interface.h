#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "DynamicArray.h"
#include "Role.h"
#define Map_Size 5 // 定义地图大小

void WelCome();
void Start_Battle();
void Battle_Report();
void Battle_End();

void InitBoard(char (*p)[Map_Size]);
void PrintMap(char (*p)[Map_Size], struct Player *player);

#endif
