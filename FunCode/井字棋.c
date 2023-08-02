#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#define Size 3
#define true 1
#define false 0

// 初始化3*3的棋盘
void InitBoard(char (*Board)[Size])
{
    int i, j;
    for (i = 0; i < Size; i++)
    {
        for (j = 0; j < Size; j++)
        {
            Board[i][j] = ' ';
        }
    }
}

void PrintBoard(char (*Board)[Size])
{
    printf("\n");
    int i, j;
    for (i = 0; i < Size; i++)
    {
        for (j = 0; j < Size; j++)
        {
            printf("%c ", Board[i][j]);
            if (j < Size - 1)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < Size - 1)
        {
            printf("--|--|--\n");
        }
    }
}

bool MakeMove(char (*Board)[Size], int row, int column, char Player)
{
    if (row < 0 || row > Size || column < 0 || column > Size)
    {
        printf("Invalid move! please try again!\n");
        return false;
    }

    if (Board[row][column] != ' ')
    {
        printf("This place has been placed!\n");
        printf("Try again!\n");
        return false;
    }

    Board[row][column] = Player;
    return true;
}

int CheckIsWin(char (*Board)[Size], char player)
{
    int i, j;

    // 对于一行而言
    for (i = 0; i < Size; i++)
    {
        if (Board[i][0] == player && Board[i][1] == player && Board[i][2] == player)
        {
            printf("player %c is win!\n", player);
            return true;
        }
    }

    // 对于列而言
    for (i = 0; i < Size; i++)
    {
        if (Board[0][i] == player && Board[1][i] == player && Board[2][i] == player)
        {
            printf("player %c is win!\n", player);
            return true;
        }
    }

    // 对于主对角线
    if (Board[0][0] == player && Board[1][1] == player && Board[2][2] == player)
    {
        printf("player %c is win!\n", player);
        return true;
    }

    // 对于副对角线
    if (Board[0][2] == player && Board[1][1] == player && Board[2][0] == player)
    {
        printf("player %c is win!\n", player);
        return true;
    }
}

bool CheckIsDraw(char (*Board)[Size])
{
    int i, j;
    for (i = 0; i < Size; i++)
    {
        for (j = 0; j < Size; j++)
        {
            if (Board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    char Board[Size][Size] = {0};
    InitBoard(Board);

    char player = 'X'; // 玩家使用标记-X
    while (1)
    {
        PrintBoard(Board);
        printf("player %c please enter your place:", player);

        int row = 0, col = 0;

        scanf("%d%d", &row, &col); // scanf忽略空格、制表符、换行符等

        // sleep(3);
        if (MakeMove(Board, row - 1, col - 1, player) == false)
        {
            continue;
        }

        if (CheckIsWin(Board, player) == true)
        {
            PrintBoard(Board);
            break;
        }

        if (CheckIsDraw(Board) == true)
        {
            PrintBoard(Board);
            printf("the result is draw! game over!\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
    return 0;
}
