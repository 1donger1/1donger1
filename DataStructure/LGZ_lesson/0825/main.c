#include <stdio.h>
#include <stdlib.h>
#include "StdSqlite.h"

int main(int argc, char *argv[])
{
    SQL *s = InitSqlite("test.db");

    char *prolist[] = {"id", "integer primary key", "name", "text"};
    CreateTable(s, "user", prolist, sizeof(prolist) / sizeof(prolist[0]) / 2);

    char *value1[] = {"1", "'DONGER'"};
    InsertData(s, "user", value1, sizeof(value1) / sizeof(value1[0]));

    char *value2[] = {"2", "'donger'"};
    InsertData(s, "user", value2, sizeof(value2) / sizeof(value2[0]));

    char *value3[] = {"3", "'Nan'"};
    InsertData(s, "user", value3, sizeof(value3) / sizeof(value3[0]));

    char *value4[] = {"4", "'Ji'"};
    InsertData(s, "user", value4, sizeof(value4) / sizeof(value4[0]));

    // DeleteData(s, "test", "id = 1");

    // UpdateData(s, "test", "name = 'NAN'","id = 3");

    // printf("Table len = %d\n",GetTableLen(s, "test"));//获取长度
    
    return 0;
}