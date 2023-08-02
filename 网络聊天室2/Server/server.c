#include "server.h"
#include "cmd.h"

Onlineuser *onlineuser;
int count;

void * readevent(void *arg)
{
    printf("服务器正在处理请求...\n");
    int cfd = *(int*)arg;
	userinfo *user = (userinfo *)malloc(sizeof(userinfo));
	while (1)
	{
		//从客户端读取数据
        memset(user, 0, sizeof(userinfo));
		int ret = recv(cfd, user, sizeof(userinfo), 0);

		if (ret == -1)
		{
            perror("read error");
            break;
        }
		// 代表客户端退出
		if (ret == 0)
		{
            DeleteNode(onlineuser,cfd);
            count--;
			printf("客户端退出\n");
			break;
		}
        user->cfd = cfd;
        printf("用户请求指令:%d\n", user->cmd);
		switch (user->cmd)
		{
		case USERREGISTER: // 注册
			Regist(user);
			break;
		case LOGIN: //登录
            Login(user);
            break;
        case CHATONE: //私聊
            Chat_One(user);
            break;
        case CHATALL: //群聊
            Chat_All(user);
            break;
        case SEARCHONLINEUSER: //查看在线用户
            Search_Online_User(user);
            break;
        case ADMREQUEST: //申请管理员
            Adm_Request(user);
            break;
        case LOGOFFUSER:
            Log_Off(user);
            break;
        case SLIENCEUSER: //禁言
            Slience_User(user);
            break;
        case UNBANUSER:
            Unban_User(user);
            break;

        case SENDFILE:
            Send_File(user);
            break;

        case READERROR:
        {
            Onlineuser *tmp = onlineuser->next;
            while(tmp != NULL)
            {
                if(strcmp(tmp->name, user->toname) == 0)
                {
                    user->cmd = READERROR;
                    write(tmp->cfd, user, sizeof(userinfo));
                }
                tmp = tmp->next;
            }

            break;
        }
        case RECVSUCCESS:
        {
            Onlineuser *tmp = onlineuser->next;
            while(tmp != NULL)
            {
                if(strcmp(tmp->name, user->toname) == 0)
                {
                    user->cmd = RECVSUCCESS;
                    write(tmp->cfd, user, sizeof(userinfo));
                }
                tmp = tmp->next;
            }
            break;
        }
        default:
            break;
        }
	}
}

int tcp_server_create()//服务器创建
{
    onlineuser = (Onlineuser *)malloc(sizeof(Onlineuser));
    onlineuser->next = NULL;

    int sockfd;

    socklen_t c_size;
    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) //非阻塞
    {
        perror("socket error");
        exit(1);
    }
    printf("create sockfd success!\n");

    int opt = 1;
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));//设置套接字可以重复使用端口号
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    //s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sockfd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr)) != 0)
    {
        perror("bind error");
        exit(1);
    }
    printf("bind success!\n");
    if(listen(sockfd,20) != 0)
    {
        perror("listen error");
        exit(1);
    }
    printf("listen success!\n");
    return sockfd;
}

int read_noblock(int cfd,userinfo *user,size_t size) //非阻塞的读
{
    int r_n;

    while(r_n = read(cfd, user, size))
    {
        if(r_n < 0)
        {
            if(errno != EAGAIN && errno != EOWNERDEAD && errno != EINTR)
            {
                perror("recv error");
                exit(1);
            }
            continue;
        }
        if(r_n == 0)
        {
            printf("client is close!\n");
        }   
        else 
        {
            break;
        }
    }
    return r_n;
}

int read_block(int cfd,userinfo *user,size_t size) //阻塞的读
{
    int r_n;

    while(r_n = read(cfd,user,size))
    {
        if(r_n < 0)
        {
            perror("recv error");
            exit(1);
        }
        if(r_n == 0)
        {
            printf("client is close!\n");
        }   
        else 
        {
            break;
        }
    }
    return r_n;
}

void set_noblock(int cfd)
{
    int flags = fcntl(cfd,F_GETFL);
    flags = flags | O_NONBLOCK;
    fcntl(cfd,F_SETFL,flags);
}

void Regist(userinfo *user)
{
    //printf(" %s 进行注册.\n", user->name);

	//用户账号和密码保存在数据库中
	sqlite3 *datebase = Create_Sqlite();
	if (datebase == NULL)
	{
		errno = CREATEERROR;
		perror("Create_Sqlite");
	}

	int flag = Save_User(user, datebase);

	if (flag == INSERTERROR)
	{
		user->cmd = INSERTERROR; //保存失败
	}
	else if (flag == SAVEERROR)
	{
		user->cmd = SAVEERROR;
	}
    else if (flag == REGSUCCESS)
    {
        user->cmd = REGSUCCESS;
    }
	sqlite3_close(datebase);
	write(user->cfd, user, sizeof(userinfo));
}


static int flag = 0;

void Login(userinfo *user)//用户登录
{
    printf("用户登录...\n");
    //打开数据库进行账号和密码的匹配
    sqlite3 *database;
    sqlite3_open("chat.db", &database);
    char sql[1000];
    sprintf(sql, "SELECT * FROM user WHERE account ='%s' AND password ='%s'", user->id, user->passwd);
    printf("sql = %s\n", sql);
    char *errmsg;
    int ret = sqlite3_exec(database, sql, callback, user, &errmsg);
    if (flag == 0)
    {
        user->cmd = LOGINERROR;
        write(user->cfd, user, sizeof(userinfo));
    }
    flag = 0;
    printf("flag = %d\n", flag);
    printf("当前在线人数:%d\n", count);
}


int callback(void *data, int argc, char **argv, char **azColName) 
{
    flag ++;
    userinfo *user = (userinfo *)data;
    // 通过回调函数判断查询结果是否为空

    int isAdmin = atoi(argv[3]); // 获取admflag字段的值并转换为整数
    int isSlience = atoi(argv[4]);

    Onlineuser *p = onlineuser->next;
    while(p !=NULL)
    {
        if(strcmp(user->id, p->account) == 0)
        {
            user->cmd = HAVELOGIN;
            write(user->cfd, user, sizeof(userinfo));
            return;
        }
        p = p->next;
    }

    if (isAdmin == 1) 
    {
        //账号是管理员账号
        user->cmd = ADMLOGIN;
        strcpy(user->name, argv[0]);
        write(user->cfd, user, sizeof(userinfo));
        count ++;
    }
    else 
    {
        //账号不是管理员账号
        user->cmd = USERLOGIN;
        user->isSlience = isSlience;
        strcpy(user->name, argv[0]);
        write(user->cfd, user, sizeof(userinfo));
        count ++;
    }
    //将用户加入在线用户链表
    Onlineuser *tmp = (Onlineuser *)malloc(sizeof(Onlineuser));
    tmp->admflag = isAdmin;
    tmp->slienceflag = isSlience;
    strcpy(tmp->account, argv[1]);
    strcpy(tmp->name, user->name);
    tmp->cfd = user->cfd;
    tmp->next = onlineuser->next;
    onlineuser->next = tmp;

    return 0;
}

void Chat_One(userinfo* user)
{
    printf("处理私聊中...\n");
    char buf[128];
    Onlineuser *tmp = onlineuser->next;
    while(tmp != NULL)
    {
        if((strcmp(user->toname, tmp->name) == 0) && (strcmp(user->name, tmp->name) != 0)) //发送对象不是自己
        {
            sprintf(buf, "收到来自%s的信息:%s。",user->name, user->msg);
            memset(user->msg, sizeof(user->msg), 0);
            strcpy(user->msg, buf);
            user->cmd = CHATONE;
            write(tmp->cfd, user, sizeof(userinfo));
            return;
        }
        tmp = tmp->next;
    }
    sprintf(buf, "发送失败，用户不存在！");
    memset(user, sizeof(userinfo), 0);
    strcpy(user->msg, buf);
    user->cmd = SENDONEERROR;
    write(user->cfd, user, sizeof(userinfo));
}



void Chat_All(userinfo *user)
{
    printf("处理群聊中...\n");
    char buf[128];
    Onlineuser *tmp = onlineuser->next;
    while(tmp != NULL)
    {
        if(strcmp(tmp->name, user->name) != 0)
        {
            sprintf(buf, "%s群发信息:%s。",user->name, user->msg);
            memset(user->msg, sizeof(user->msg), 0);
            strcpy(user->msg, buf);
            user->cmd = CHATALL;
            strcpy(user->toname, "全体成员");
            write(tmp->cfd, user, sizeof(userinfo));
        }
        tmp = tmp->next;
    }
}

void DeleteNode(Onlineuser *user, int cfd)
{
    Onlineuser* current = user;
    Onlineuser* previous = NULL;

    // 遍历链表查找目标节点
    while (current != NULL) 
    {
        if (current->cfd == cfd)
        {
            // 找到目标节点
            if (previous == NULL) 
            {
                // 目标节点为头节点
                user = current->next;
            } 
            else 
            {
                // 目标节点为非头节点
                previous->next = current->next;
            }
            printf("找到该用户:%s\n", current->name);
            free(current);
            printf("已删除用户 %d 。\n", cfd);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void Search_Online_User(userinfo *user)
{
    Onlineuser *tmp = onlineuser->next;
    char buf[1024];
    sprintf(user->msg, "当前在线人数%d,当前在线人姓名:",count);
    write(user->cfd, user, sizeof(userinfo));
    while(tmp != NULL)
    {
        memset(user->msg, sizeof(user->msg), 0);
        strcpy(user->msg, tmp->name);
        user->cmd = SEARCHONLINEUSER;
        write(user->cfd, user, sizeof(userinfo));
        tmp = tmp->next;
    }
}

void Adm_Request(userinfo *user)
{
    int choice;
    printf("用户%s申请管理员身份,是否同意（1/2）?\n", user->name);
    

    while(1)
    {
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            Agree_Request(user);
            return;
        case 2:
            user->cmd = REFUSQADMREQUEST;
            write(user->cfd, user, sizeof(userinfo));
            return;
        default:
            printf("请选择正确的选项！\n");
            break;
            
        }
    
    }
}

void Agree_Request(userinfo *user)
{
    sqlite3 *database = Create_Sqlite();
    char *errmsg = NULL;
    char sql[128];
    sprintf(sql, "UPDATE user SET is_admin = 1 WHERE username = '%s'", user->name);
	int ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
	if(ret != SQLITE_OK)
	{
		printf("修改失败\n");
		printf("sqlite3_exec: %s\n",errmsg);
		user->cmd = SQLITEREFUSEADM;
        write(user->cfd, user, sizeof(userinfo));
        return;
	}
    printf("修改成功！\n\n");
    user->cmd = ADMSUCCESS;
    write(user->cfd, user, sizeof(userinfo));
}

void Log_Off(userinfo *user)
{
    Onlineuser *tmp = onlineuser->next;
    int cfd;
    int flag = 0;
    while(tmp != NULL)
    {
        if(!strcmp(tmp->name, user->toname) && !tmp->admflag)
        {
            cfd = tmp->cfd;
            //close(tmp->cfd);
        }
        if(!strcmp(tmp->name, user->toname) && tmp->admflag)
        {
            user->cmd = ADMACCOUNT;
            write(user->cfd, user, sizeof(userinfo));
            return;

        }
        tmp = tmp->next;
    }
    DeleteNode(onlineuser, cfd);
    count --;

    user->cmd = LOGOFFUSER;
    write(cfd, user, sizeof(userinfo));
    user->cmd = LOGOFFSUCCESS;
    write(user->cfd, user, sizeof(userinfo));
}

void Slience_User(userinfo *user)
{
    Onlineuser *tmp = onlineuser;
    char sql[64];
    char *errmsg = NULL;
    while(tmp != NULL)
    {
        if(strcmp(tmp->name, user->toname) == 0 && (tmp->admflag != 1))
        {
            if(tmp->slienceflag == 1)
            {
                user->cmd = REPEATSILENCE;
                write(user->cfd, user, sizeof(userinfo));
                return;
            }
            sprintf(sql, "UPDATE user SET is_slience = 1 WHERE username = '%s'", tmp->name);
            sqlite3 *database = Create_Sqlite();
            //printf("打开表成功！\n");
            int ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
            //printf("ret = %d\n", ret);
            if(ret != SQLITE_OK)
            {
                printf("打开表失败\n");
                printf("sqlite3_exec: %s\n",errmsg);
                user->cmd = SLIENCEFAIL;
                write(user->cfd, user, sizeof(userinfo));
                return;
            }
            tmp->slienceflag = 1;
            user->cmd = SLIENCEUSER;
            write(tmp->cfd, user, sizeof(userinfo));

            user->cmd = SLIENCESUCCESS;
            write(user->cfd, user, sizeof(userinfo));
            return;
        }
        if(strcmp(tmp->name, user->toname) == 0 && tmp->admflag == 1)
        {
            user->cmd = SLIENCEADM;
            write(user->cfd, user, sizeof(userinfo));
            return;
        }
        tmp = tmp->next;
    }
    user->cmd = SLIENCEUSERERROR;
    write(user->cfd, user, sizeof(userinfo));
}

void Unban_User(userinfo *user)
{
    Onlineuser *tmp = onlineuser;
    char sql[64];
    char *errmsg = NULL;
    while(tmp != NULL)
    {
        if(strcmp(tmp->name, user->toname) == 0 && (tmp->slienceflag == 1))
        {
            printf("找到该用户！");
            sprintf(sql, "UPDATE user SET is_slience = 0 WHERE username = '%s'", tmp->name);
            sqlite3 *database = Create_Sqlite();
            int ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
            if(ret != SQLITE_OK)
            {
                printf("打开表失败\n");
                printf("sqlite3_exec: %s\n",errmsg);
                user->cmd = UNBANUSER; //解禁失败
                write(user->cfd, user, sizeof(userinfo));
                return;
            }
            tmp->slienceflag = 0;
            user->cmd = UNBANSUCCESS;
            write(user->cfd, user, sizeof(userinfo));
           
            user->cmd = HAVEBINUNBAN;
            write(tmp->cfd, user, sizeof(userinfo));
            return;
        }
        if(strcmp(tmp->name, user->toname) == 0 && tmp->slienceflag == 0)
        {
            //没有被禁言
            user->cmd = HAVENTBENBAN;
            write(user->cfd, user, sizeof(userinfo));
            return;
        }
        tmp = tmp->next;
    }
    user->cmd = UNBANSERERROR;
    write(user->cfd, user, sizeof(userinfo));
}

void Send_File(userinfo *user)
{
    Onlineuser *tmp = onlineuser->next;
    while(tmp != NULL)
    {
        if(strcmp(tmp->name, user->toname) == 0)
        {
            user->cmd = SENDFILE;
            write(tmp->cfd, user, sizeof(userinfo));
            return;
        }
        tmp = tmp->next;
    }
    user->cmd = FILEERROR;
    write(user->cfd, user, sizeof(userinfo));
}