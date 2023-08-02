#include "LinkStack.h"
#include <stdio.h>
#include <stdlib.h>


int IsNum(char c)
{
    if (c <= '9' && c >= '0')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int IsOper(char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '=':
        return true;
    default:
        return false;
    }
}

int Operate(int prev, int next, char symbol)
{
    switch (symbol)
    {
    case '+':
        return prev + next;
    case '-':
        return prev - next;
    case '*':
        return prev * next;
    case '/':
        if (next == 0)
        {
            printf("devide zero!\n");
            exit(-1);
        }
        return prev / next;
    default:
        break;
    }
}

char Precade(char ch1, char ch2)
{
    char pre[7][7] = {
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '<', '<', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'>', '>', '>', '>', '<', '>', '>'},
        {'<', '<', '<', '<', '<', '=', '0'},
        {'>', '>', '>', '>', '0', '=', '0'},
        {'0', '0', '0', '0', '0', '0', '='},
    };
    int i = 0, j = 0;
    switch (ch1)
    {
    case '-':
        i = 0;
        break;
    case '*':
        i = 1;
        break;
    case '/':
        i = 2;
        break;
    case '(':
        i = 3;
        break;
    case ')':
        i = 4;
        break;
    case '+':
        i = 5;
        break;
    case '=':
        i = 6;
        break;
    default:
        break;
    }

    switch (ch2)
    {
    case '+':
        j = 0;
        break;
    case '-':
        j = 1;
        break;
    case '*':
        j = 2;
        break;
    case '/':
        j = 3;
        break;
    case '(':
        j = 4;
        break;
    case ')':
        j = 5;
        break;
    case '=':
        j = 6;
        break;
    default:
        break;
    }

    return pre[i][j];
}

int main(int argc, char *argv[])
{
#if 0
    LStack stack;
    InitLStack(&stack);

    for (int i = 0; i < 10; i++)
    {
        Push(&stack, i + 1);
    }

    while (GetTop(&stack) != NULL)
    {
        printf("%d ", *Pop(&stack));
    }
    printf("\n");
#endif
#if 0
    LStack stack;
    InitLStack(&stack);
    int num = 0;
    int n = 0;

    printf("please input a number:");
    scanf("%d", &num);

    printf("please input a system n:");
    scanf("%d", &n);

    while (num != 0)
    {
        Push(&stack, num % n);
        num /= n;
    }

    while (IsEmpty(&stack) == false)
    {
        printf("%d", *Pop(&stack));
    }
    printf("\n");
#endif
#if 1
    LStack Num;
    InitLStack(&Num);
    LStack OPer;
    InitLStack(&OPer);

    char str[100] = {0};
    scanf("%s", str);
    int i = 0;
    while (str[i] != '\0')
    {
        if (IsOper(str[i]) == true)
        {
            if (IsEmpty(&OPer) == true)
            {
                Push(&OPer, str[i]);
                i++;
            }
            else
            {
                char symbol = Precade(GetTop(&OPer)->data, str[i]);
                switch (symbol)
                {
                case '<':
                    Push(&OPer, str[i]);
                    i++;
                    break;
                case '>':
                    int next = *Pop(&Num);
                    int prev = *Pop(&Num);
                    char s = *Pop(&OPer);
                    Push(&Num, Operate(prev, next, s));
                    break;
                case '=':
                    Pop(&OPer);
                    i++;
                    break;
                default:
                    break;
                }
            }
        }
        else if (IsNum(str[i]))
        {
            int num = str[i] - '0';
            Push(&Num, num);
            i++;
            while (IsNum(str[i]))
            {
                // Push(&Num, num);
                // i++;
                // while (IsNum(str[i]))
                // {
                int higher = *Pop(&Num);
                Push(&Num, higher * 10 + str[i] - '0');
                i++;
                // }
            }
        }
        else if (str[i] == ' ')
        {
            while (str[i] == ' ')
            {
                i++;
            }
        }
    }

    printf("the answer is %d\n", GetTop(&Num)->data);

#endif
    
    return 0;
}

