#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    sqlite3 *db;
    if (sqlite3_open("test.db", &db) != SQLITE_OK)
    {
        printf("open error:%s\n", sqlite3_errmsg(db)); // 输出数据库指针操作最近的一次错误信息
    }

    printf("open database success!\n");

    char sql[100] = {0};
    sprintf(sql, "select *from stu;");
    char **result;
    int row, column;
    if (sqlite3_get_table(db, sql, &result, &row, &column, NULL) != SQLITE_OK)
    {
        printf("get_table error:%s\n", sqlite3_errmsg(db)); // 输出数据库指针操作最近的一次错误信息
    }
    for (int i = 0; i <= row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("|%s|", result[i * column + j]);
        }
        printf("\n");
    }
    
    sqlite3_free_table(result);

    sqlite3_close(db);

    return 0;
}