#include "Game.h"
#include "Func.h"
#include "Interface.h"

int Battle(struct Player *player, struct Monster *monster)
{
    // system("clear");
    printf("您遭遇了|%s| 血量:|%d| 攻击力:|%d|\n", monster->name.string, monster->HP, monster->attack);
    Start_Battle();

    while (player->HP > 0 && monster->HP > 0)
    {
        printf("请选择您要执行的行为:\n");
        printf("1.普通攻击\n");
        printf("2.暴击\n");
        printf("3.逃跑\n");

        int choice;
        scanf("%d", &choice);
        getchar();


        // Battle_Report();
        system("clear");

        if (choice == 1 || choice == 2 || choice == 3)
        {
            Battle_Report();

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
                break;
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
        }
        else
        {
            printf("输入的选项有误,请输入1-3之间的数字\n");
            continue;
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

        Battle_End();
    }
    // system("clear");
}