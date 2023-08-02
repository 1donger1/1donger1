#include <stdio.h>

typedef struct
{
    int num;
    char name[20];
    float score;
} STU;

int main(int argc, char *argv[])
{
    STU edu[3] = {{101, "lucy", 78}, {102, "Bob", 88}, {103, "Tom", 85}};

    int i;
    for (i = 0; i < 3; i++)
    {
        printf("%d-%s-%.2f\n", edu[i].num, edu[i].name, edu[i].score);
    }

    int j;
    float sum = 0;
    for (j = 0; j < 3; j++)
    {
        sum += edu[j].score;
    }
    printf("平均成绩 = %.2f\n", sum / 3);

    return 0;
}