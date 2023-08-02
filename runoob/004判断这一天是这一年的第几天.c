#include <stdio.h>
#include <stdlib.h>

// 输入某年某月某日，判断这一天是这一年的第几天？

int main(int argc, char *argv[])
{
    int year, month, day;
    int sumday = 0;

    int monthday[12] = {
        31,
        28,
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30,
        31};
    printf("请输入年、月、日，格式为年，月，日(2023,6,19):");
    scanf("%d,%d,%d", &year, &month, &day);

    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
    {
        monthday[1] = 29;
    }

    int i = 1;
    for (i = 0; i < month - 1; i++)
    {
        sumday += monthday[i];
    }

    sumday += day;

    printf("%d\n", sumday);

    return 0;
}
