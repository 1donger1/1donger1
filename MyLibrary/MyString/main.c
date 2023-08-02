#include <stdio.h>
#include "MyString.h"

int main(int argc, char *argv[])
{
    Init_MyString(obj, "hello world");
    Init_MyString(obj2, "hello");

    obj.InsertStr(&obj, "donger", 3);

    if (obj.IsContain(&obj, "hello"))
    {
        printf("contains\n");
    }
    else
    {
        printf("not contains\n");
    }

    obj.Print(obj);

    return 0;
}