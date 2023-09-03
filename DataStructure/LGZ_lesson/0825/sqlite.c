#include<sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    sqlite3 *db;
    if(sqlite3_open("test.db", &db) != SQLITE_OK)
    {
        printf("open error:%s\n",sqlite3_errmsg(db));//输出数据库指针操作最近的一次错误信息
    }
    
    printf("open database success!\n");

    // char tableName[20] = {0};
    // scanf("%s", tableName);
    char sql[100] = {0};
    sprintf(sql, "update stu set score = 1314 where name = 'other';");


    if(sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("exec error:%s\n", sqlite3_errmsg(db)); // 输出数据库指针操作最近的一次错误信息
    }

    sqlite3_close(db);

    return 0;
}