#include <stdio.h>
#include <stdlib.h>

/*
两个乒乓球队进行比赛，各出三人。
甲队为a,b,c三人，乙队为x,y,z三人。已抽签决定比赛名单。
有人向队员打听比赛的名单。a说他不和x比，c说他不和x,z比，
请编程序找出三队赛手的名单。
*/

// int main(int argc, char *argv[])
// {
//     char team1[3] = {'a', 'b', 'c'};
//     char team2[3] = {'x', 'y', 'z'};
//     char result[3][2];

//     int i, j, k = 0;
//     for (i = 0; i < 3; i++)
//     {

//         for (j = 0; j < 3; j++)
//         {
//             if ((team1[i] == 'a' && team2[j] == 'x') || (team1[i] == 'c' && (team2[j] == 'x' || team2[j] == 'z')))
//             {
//                 continue;
//             }

//             result[k][0] = team1[i];
//             result[k][1] = team2[j];
//             k++;
//         }
//     }
//     printf("比赛顺序为：\n");
//     for (i = 0; i < 3; i++)
//     {
//         printf("%c---%c\n", result[i][0], result[i][1]);
//     }

//     return 0;
// }

//  Created by www.runoob.com on 15/11/9.
//  Copyright © 2015年 菜鸟教程. All rights reserved.
//

int main()
{
    char i, j, k;
    for (i = 'x'; i <= 'z'; i++)
    {
        for (j = 'x'; j <= 'z'; j++)
        {
            if (i != j)
            {
                for (k = 'x'; k <= 'z'; k++)
                {
                    if (i != k && j != k)
                    {
                        if (i != 'x' && k != 'x' && k != 'z')
                        {
                            printf("顺序为：a--%c\tb--%c\tc--%c\n", i, j, k);
                        }
                    }
                }
            }
        }
    }
}