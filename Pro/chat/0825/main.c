#include <stdio.h>
#include <stdlib.h>
#include "StdSqlite.h"

int main(int argc, char *argv[])
{
    SQL *s = InitSqlite("test.db");

    // char *prolist[] = {"id", "integer", "name", "text"};
    // CreateTable(s, "test", prolist, sizeof(prolist) / sizeof(prolist[0]) / 2);

    // char *value[] = {"1", "'DONGER'"};
    // char *value[] = {"2", "'donger'"};
    // char *value[] = {"3", "'Nan'"};
    // InsertData(s, "test", value, sizeof(value) / sizeof(value[0]));

    // DeleteData(s, "test", "id = 1");

    // UpdateData(s, "test", "name = 'NAN'","id = 3");

    printf("Table len = %d\n",GetTableLen(s, "test"));//获取长度
    
    return 0;
}