#include <sqlite3.h>   // 包含SQLite数据库的头文件
#include <stdio.h>     // 包含标准输入输出函数的头文件
#include <stdlib.h>    // 包含通用工具函数的头文件
#include <string.h>    // 包含字符串处理函数的头文件
#include "StdSqlite.h" // 包含自定义的头文件 "StdSqlite.h"

#define true 1
#define false 0

struct StdSqlite
{
    sqlite3 *db; // SQLite数据库连接句柄
};

// 初始化SQLite数据库，打开指定文件的数据库连接
SQL *InitSqlite(const char *filename)
{
    SQL *s = (SQL *)malloc(sizeof(SQL)); // 分配内存来存储SQL结构体
    if (s == NULL)
    {
        printf("fail to InitSqlite\n"); // 内存分配失败的错误处理
        return NULL;
    }
    if (sqlite3_open(filename, &s->db) != SQLITE_OK) // 打开数据库文件，将连接句柄保存到s->db
    {
        printf("open %s error:%s\n", filename, sqlite3_errmsg(s->db)); // 打开数据库失败的错误处理
        free(s);                                                       // 释放之前分配的内存
        return NULL;
    }

    return s; // 返回初始化后的SQL结构体指针
}

// 创建数据库表格
void CreateTable(SQL *s, const char *tableName, char **prolist, int row)
{
    char property[1024] = {0}; // 用于存储表格属性的字符串
    for (int i = 0; i < row; i++)
    {
        strcat(property, prolist[i * 2]); // 将属性名添加到property字符串
        strcat(property, " ");
        strcat(property, prolist[i * 2 + 1]); // 将属性类型添加到property字符串

        if (i != row - 1)
        {
            strcat(property, ","); // 如果不是最后一个属性，添加逗号分隔符
        }
    }
    char sql[4096] = {0};                                      // 用于存储SQL语句的字符串
    sprintf(sql, "create table %s(%s);", tableName, property); // 格式化创建表格的SQL语句
    // printf("sql:%s\n", sql);                                   // 打印生成的SQL语句
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("create table error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 删除数据库表格
void DeleteTable(SQL *s, const char *tableName)
{
    char sql[4096] = {0};
    sprintf(sql, "drop table %s;", tableName);

    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("DeleteTable error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 插入数据到表格
void InsertData(SQL *s, const char *tableName, char **values, int size)
{
    char valueList[1024] = {0};
    for (int i = 0; i < size; i++)
    {
        strcat(valueList, values[i]);
        if (i != size - 1)
        {
            strcat(valueList, ",");
        }
    }

    char sql[4096] = {0};                                             // 用于存储SQL语句的字符串
    sprintf(sql, "insert into %s values(%s);", tableName, valueList); // 格式化插入数据的SQL语句
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("insert data error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 删除数据
void DeleteData(SQL *s, const char *tableName, const char *where)
{
    char sql[4096] = {0}; // 用于存储SQL语句的字符串
    if (where == NULL)
    {
        sprintf(sql, "delete from %s;", tableName); // 格式化删除数据的SQL语句
    }
    else
    {
        sprintf(sql, "delete from %s where %s;", tableName, where); // 格式化带条件删除数据的SQL语句
    }
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("delete data error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 更新数据
void UpdateData(SQL *s, const char *tableName, const char *Setvalue, const char *where)
{
    char sql[4096] = {0};                                                    // 用于存储SQL语句的字符串
    sprintf(sql, "update  %s set %s where %s;", tableName, Setvalue, where); // 格式化更新数据的SQL语句
    if (sqlite3_exec(s->db, sql, NULL, NULL, NULL) != SQLITE_OK)
    {
        printf("updateData error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 获取表格信息
void GetTableInfo(SQL *s, const char *tableName, char ***result, int *row, int *column)
{
    char sql[4096] = {0}; // 用于存储SQL语句的字符串
    sprintf(sql, "select *from %s;", tableName);

    if (sqlite3_get_table(s->db, sql, result, row, column, NULL) != SQLITE_OK)
    {
        printf("GetTableInfo error:%s", sqlite3_errmsg(s->db));
    }
}

// 执行查询操作
void SelectInfo(SQL *s, const char *sql, char ***result, int *row, int *column)
{
    if (sqlite3_get_table(s->db, sql, result, row, column, NULL) != SQLITE_OK)
    {
        printf("GetTabelLen error:%s\n", sqlite3_errmsg(s->db));
    }
}

// 释放查询结果
void FreeInfoResult(char **result)
{
    sqlite3_free_table(result);
}

// 获取表格长度
int GetTableLen(SQL *s, const char *tableName)
{
    char sql[4096] = {0};
    sprintf(sql, "select count(*) from %s;", tableName);

    char **result;
    int row, column;
    if (sqlite3_get_table(s->db, sql, &result, &row, &column, NULL) != SQLITE_OK)
    {
        printf("GetTabelLen error:%s\n", sqlite3_errmsg(s->db));
    }

    int len = atoi(result[column]);
    sqlite3_free_table(result);

    return len;
}

// 判断表格是否为空
int IsTableEmpty(SQL *s, const char *tableName)
{
    if (GetTableLen(s, tableName) > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// 释放SQLite数据库资源
void FreeSqlite(SQL *s)
{
    if (s == NULL)
    {
        return; // 如果传入的SQL结构体为空，直接返回
    }
    sqlite3_close(s->db); // 关闭数据库连接
    free(s);              // 释放存储SQL结构体的内存
}
