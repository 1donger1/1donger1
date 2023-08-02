#include <stdio.h>

typedef struct stu
{
    char a : 6;
    char b : 1;
    char c : 2;
    char d : 1;
    char e : 2;
    //char f : 0;
    char g : 4;
}STU;

int main(int argc, char *argv[])
{
    STU s;
    printf("sizeof(s) = %ld\n", sizeof(s));
    return 0;
}

