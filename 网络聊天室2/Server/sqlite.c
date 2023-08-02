#include "server.h"
#include "cmd.h"

sqlite3 *Create_Sqlite(void)
{
    sqlite3 * datebase;
	int ret = sqlite3_open("chat.db", &datebase);
	if(ret != SQLITE_OK)
	{
		printf("数据库打开失败\n");
		return NULL;
	}
	printf("数据库打开成功!\n");
	return datebase;
}

int Save_User(userinfo *user, sqlite3 *datebase)
{
    //打开表
	char *errmsg = NULL;
    char sql[128];
    sprintf(sql, "create table if not exists user(username TEXT,account TEXT,password TEXT,is_admin INTEGER,is_slience INTEGER)");
	int ret = sqlite3_exec(datebase, sql, NULL, NULL, &errmsg);
	if(ret != SQLITE_OK)
	{
		printf("打开表失败\n");
		printf("sqlite3_exec: %s\n",errmsg);
		return -1;
	}
	//printf("打开表成功\n");
	
	//判断表中是否已存在相同账号名
	char **resultp = NULL;
	int nrow,ncolumn;
    sprintf(sql, "select account from user");
	ret = sqlite3_get_table(datebase, sql, &resultp, &nrow, &ncolumn, &errmsg);
	
	//ret = sqlite3_exec(datebase, sql, NULL, NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("数据库操作失败\n");
		printf("sqlite3_get_table: %s\n",errmsg);
		return -1;
	}

	for (int i = 0; i < nrow; i++) 
	{
		const char* existingAccount = resultp[(i + 1) * ncolumn]; // 获取第 i 行、account 字段的值
		
		// 进行比较，如果存在相同账号，则返回相应的错误码或进行其他处理
		if (strcmp(existingAccount, user->id) == 0)
		{
			printf("已存在相同的账号: %s\n", existingAccount);
			return SAVEERROR;
    	}
	}

	sprintf(sql,"INSERT INTO user (username, account, password, is_admin, is_slience) VALUES ('%s', '%s', '%s' ,0 ,0)",user->name, user->id, user->passwd);
	ret = sqlite3_exec(datebase, sql, NULL, NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("数据库操作失败\n");
		printf("sqlite3_get_table: %s\n",errmsg);
		return -1;
	}
	else
	{
		printf("插入新用户成功!\n");
		return REGSUCCESS;
	}
	return INSERTERROR;
}


