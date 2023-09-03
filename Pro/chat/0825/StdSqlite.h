#ifndef _STDSQLITE_H_
#define _STDSQLITE_H_

struct StdSqlite;
typedef struct StdSqlite SQL;

SQL *InitSqlite(const char *filename);

void CreateTable(SQL *s, const char *tableName, char **prolist, int row);

void DeleteTable(SQL *s, const char *tableName);

void InsertData(SQL *s, const char *tableName, char **values, int size);

void DeleteData(SQL *s, const char *tableName, const char *where);

void UpdateData(SQL *s, const char *tableName, const char *Setvalue, const char *where);

void GetTableInfo(SQL *s, const char *tableName, char ***result, int *row, int *column);

void SelectInfo(SQL *s, const char *sql, char ***result, int *row, int *column);

void FreeInfoResult(char **result);

int GetTableLen(SQL *s, const char *tableName);

int IsTableEmpty(SQL *s, const char *tableName);

void FreeSqlite(SQL *s);

#endif