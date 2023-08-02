#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct stu
{
    int id;
    char name[32];
    char gender;
    int age;
};

int main(int argc, char *argv[])
{
    struct stu *s;
    s = (struct stu *)malloc(sizeof(struct stu));

    s->id = 20183310;
    strcpy(s->name, "donger");
    s->gender = 'M';
    s->age = 24;

    printf("%d - %s - %c - %d\n", s->id, s->name, s->gender, s->age);

    return 0;
}
