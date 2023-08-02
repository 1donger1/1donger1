#include "client.h"
#include "cmd.h"

int Slience_Flag = 0;

char myname[32]; //自己的名字

int Connect_Server(void)
{
	//创建套接字
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
	{
		perror("socket error");
		return -1;
	}
	//链接服务器
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_aton("127.0.0.1", &(addr.sin_addr));

	int ret = connect(client_socket, (struct sockaddr *)&addr, sizeof(addr));
	if (ret == -1)
	{
		perror("connect error");
		return -1;
	}
	printf("成功连接到服务器 : %s\n", inet_ntoa(addr.sin_addr));

	return client_socket;
}

int Ask_server(int client_socket)
{
    int opt;
	int ret;
	while (1)
	{
		main_menu();
		printf("请输入您要做操作\n");
		scanf("%d", &opt);
		if(opt != 1 && opt != 2 && opt != 3)
		{
			continue;
		}
		switch (opt)
		{
		    case 1:regist(client_socket); //注册
		    	break;
			case 2:login(client_socket); //登录
				break;
			case 3:exit(0);
				break;
			default:printf("请输入正确的选项！");
				break;
		}
	}
}

void print_menu(const char* title, const char* options[], int num_options) 
{
    int max_length = strlen(title);
    for (int i = 0; i < num_options; i++) 
	{
        int length = strlen(options[i]);
        if (length > max_length) 
		{
            max_length = length;
        }
    }
    max_length += 4;

    printf(COLOR_CYAN SYMBOL_CORNER_TOP_LEFT);
    for (int i = 0; i < max_length - 11; i++) 
	{
        printf(SYMBOL_LINE_H);
    }
    printf(SYMBOL_CORNER_TOP_RIGHT "\n");
    
    printf(SYMBOL_LINE_V " %-*s " SYMBOL_LINE_V "\n", max_length - 16, title);
    
    for (int i = 0; i < num_options; i++) 
	{
        printf(SYMBOL_LINE_V " %-*s " SYMBOL_LINE_V "\n", max_length - 16, options[i]);
    }
    
    printf(SYMBOL_CORNER_BOTTOM_LEFT);
    for (int i = 0; i < max_length-11; i++) 
	{
        printf(SYMBOL_LINE_H);
    }
    printf(SYMBOL_CORNER_BOTTOM_RIGHT "\n" COLOR_RESET);
}

//客户端主界面
void main_menu(void)
{
	const char* title = COLOR_BOLD "               START MODE                  ";
    const char* options[] = {
        "              欢迎使用苏嵌聊天室           ",
        "                 1.注册                    ",
        "                 2.登录                    ",
        "                 3.退出                    ",
        "                  END                      "
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    
    print_menu(title, options, num_options);
}



void regist(int client_socket) //注册
{
    struct userinfo user;
	user.cmd = USERREGISTER; //注册协议
    user.cfd = client_socket;
	printf("注册,请输入账号: ");
	scanf("%s", user.id);
	// while (getchar() != '\n');
	printf("注册,请输入密码: ");
	scanf("%s", user.passwd);
	// while (getchar() != '\n');
	printf("注册,请输入姓名: ");
	scanf("%s", user.name);
	// while (getchar() != '\n');
	write(client_socket, &user, sizeof(user));

	read(client_socket, &user, sizeof(user));
	
	if (user.cmd == REGSUCCESS)
	{
		printf("注册成功！\n");
	}
	else if (user.cmd == SAVEERROR)
	{
		printf("用户账号存在,注册失败！\n");
	}
	else if(user.cmd == INSERTERROR)
	{
		printf("系统繁忙,注册失败！\n");
    }
}

void login(int client_socket)
{
	userinfo user;
	user.cmd = LOGIN;

	printf("请输入账号:");
	scanf("%s",user.id);
	while (getchar() != '\n');
	printf("请输入密码:");
	hide_passwd(user.passwd);
	putchar(10);

	write(client_socket, &user, sizeof(user));

	read(client_socket, &user, sizeof(user));

	Slience_Flag = user.isSlience;

	if(user.cmd == ADMLOGIN)
	{
		strcpy(myname, user.name);
		adm_login(client_socket);
	}
	else if(user.cmd == USERLOGIN)
	{
		strcpy(myname, user.name);
		user_login(client_socket);
	}
	else if(user.cmd == LOGINERROR)
	{
		printf("请检查你的账号或者密码\n");
		return;
	}
	else if(user.cmd == HAVELOGIN)
	{
		printf("该账号用户已经登录\n");
		return;
	}
	else
	{
		printf("未知错误!\n");
		return;
	}

}

void hide_passwd(char *passwd)//隐藏密码
{
	int i = 0;
	system("stty -icanon"); //设置一次性读完操作，即getchar()不用回车也能获取字符
	system("stty -echo");	//关闭回显，即输入任何字符都不显示
	while (i < 16)
	{
		passwd[i] = getchar(); //获取键盘的值到数组中
		if (i == 0 && passwd[i] == 127)
		{
			i = 0; //若开始没有值，输入删除，则，不算值
			passwd[i] = '\0';
			continue;
		}
		else if (passwd[i] == 127)
		{
			printf("\b \b"); //若删除，则光标前移，输空格覆盖，再光标前移
			passwd[i] = '\0';
			i = i - 1; //返回到前一个值继续输入
			continue;  //结束当前循环
		}
		else if (passwd[i] == '\n') //若按回车则，输入结束
		{
			passwd[i] = '\0';
			break;
		}
		else
		{
			printf("*");
		}
		i++;
	}
	system("stty echo");   //开启回显
	system("stty icanon"); //关闭一次性读完操作，即getchar()必须回车才能获取字符
}

void adm_menu() {
    printf(COLOR_CYAN SYMBOL_DOUBLE_CORNER_TOP_LEFT "══════════ ADMI MODE ══════════" SYMBOL_DOUBLE_CORNER_TOP_RIGHT "\n");
    printf(SYMBOL_DOUBLE_LINE_V "   %s       1.私聊       %s        " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "   %s       2.群聊       %s        " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "   %s       3.查看在线用户  %s     " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "   %s       4.踢出在线用户  %s     " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "   %s       5.禁言       %s        " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "   %s       6.解禁       %s        " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "   %s       7.查看聊天记录 %s      " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
	printf(SYMBOL_DOUBLE_LINE_V "   %s       8.发送在线文件  %s     " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_CORNER_BOTTOM_LEFT "═══════════════════════════════" SYMBOL_DOUBLE_CORNER_BOTTOM_RIGHT "\n" COLOR_RESET);
}

void user_menu() {
    printf(COLOR_GREEN SYMBOL_DOUBLE_CORNER_TOP_LEFT "══════════ USER MODE ══════════" SYMBOL_DOUBLE_CORNER_TOP_RIGHT "\n");
    printf(SYMBOL_DOUBLE_LINE_V "    %s       1.私聊             %s " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "    %s       2.群聊             %s " SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "    %s       3.查看在线用户      %s" SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "    %s       4.请求管理员身份    %s" SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_LINE_V "    %s       5.查看聊天记录      %s" SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
	printf(SYMBOL_DOUBLE_LINE_V "    %s       6.发送在线文件      %s" SYMBOL_DOUBLE_LINE_V "\n", COLOR_BOLD, COLOR_RESET);
    printf(SYMBOL_DOUBLE_CORNER_BOTTOM_LEFT "═══════════════════════════════" SYMBOL_DOUBLE_CORNER_BOTTOM_RIGHT "\n" COLOR_RESET);
}

void adm_login(int client_socket)
{
	printf("管理员用户登录成功！\n");
	pthread_t read_id;
	pthread_create(&read_id, NULL, readMsg, (void *)client_socket);
	pthread_detach(read_id); //等待线程分离

	int cmd;
	while(1)
	{	
		adm_menu();
		printf("请输入需要执行的操作:\n");
		scanf("%d", &cmd);

		switch(cmd)
		{
		case 1: //私聊
			chat_one(client_socket);
			break;

		case 2: //群聊
			chat_all(client_socket);
			break;

		case 3: //查看在线用户
			search_online_user(client_socket);
			break;
		case 4: //踢出在线用户
			logoff_user(client_socket);
			break;
		case 5: //禁言
			slience_user(client_socket);
			break;

		case 6: //解禁
			unban_user(client_socket);
			break;
		
		case 7: //查找聊天记录
			search_chat();
			break;

		case 8: //发送文件
			send_file(client_socket);
			break;
		default:
			break;
		}
	}	

}

void user_login(int client_socket)
{
	printf("普通用户登录成功！\n");
	pthread_t read_id;
	pthread_create(&read_id, NULL, readMsg, (void *)client_socket);
	pthread_detach(read_id); //等待线程分离

	int cmd;
	while(1)
	{	
		user_menu();
		printf("请输入需要执行的操作:\n");
		scanf("%d", &cmd);

		switch(cmd)
		{
		case 1: //私聊
		{
			if(Slience_Flag == 1)
			{
				printf("您已被禁言!\n");
				break;
			}
			chat_one(client_socket);
			break;
		}
		
		case 2: //群聊
		{
			if(Slience_Flag == 1)
			{
				printf("您已被禁言!\n");
				break;
			}
			chat_all(client_socket);
			break;
		}

		case 3: //查看在线用户
			search_online_user(client_socket);
			break;

		case 4: //请求成为管理员
			adm_request(client_socket);
			break;

		case 5:
			search_chat();
			break;

		case 6: //发送文件
			send_file(client_socket);
			break;

		default:
			break;
			
		}
	}	

}

void *readMsg(void *arg)
{
	int cfd = (int)arg;
	userinfo user;

	while(1)
	{
		bzero(&user, sizeof(user));
		int ret = read(cfd, &user, sizeof(userinfo));
		if (ret == -1)
		{
			perror("read");
			break;
		}

		user.cfd = cfd;

		switch(user.cmd)
		{
		case CHATONE: //私聊
			printf("%s\n",user.msg);
			save_Chat(&user);
			break;

		case SENDONEERROR: //用户不存在
			printf("%s\n",user.msg);
			break;

		case CHATALL: //群聊
			printf("%s\n",user.msg);
			save_Chat(&user);
			break;
		
		case SEARCHONLINEUSER:
			printf("%s\n", user.msg);
			break;

		case REFUSQADMREQUEST:
			printf("请求管理员失败！\n");
			break;

		case SQLITEREFUSEADM:
			printf("服务器同意请求，数据库操作失败，请重新请求!\n");
			break;

		case ADMSUCCESS:
			printf("请求成功，请重新登录进入管理员界面!\n");
			break;
		case LOGOFFUSER:
			printf("你已被管理员强制踢下线！\n");
			exit(0);

		case SLIENCEUSER:
			printf("你已被管理员禁言!\n");
			Slience_Flag = 1;
			break;

		case HAVEBINUNBAN:
			printf("您已被解禁!\n");
			Slience_Flag = 0;
			break;
			
		case FILEERROR:
			printf("发送文件对象不存在或者不在线!\n");
			break;
		
		case SENDFILE:
			revc_flie(&user);
			break;

		case READERROR:
			printf("对方拒绝接收文件!");
			break;
		
		case RECVSUCCESS:
			printf("对方接收文件成功\n");
			break;

		case SLIENCESUCCESS:
			printf("禁言成功!\n");
			break;

		case SLIENCEFAIL:
			printf("禁言失败,系统出错!\n");
			break;

		case SLIENCEUSERERROR:
			printf("禁言用户不存在！\n");
			break;
		case SLIENCEADM:
			printf("您不能禁言管理员!\n");
			break;

		case REPEATSILENCE:
			printf("该用户已被禁言!\n");
			break;

		case UNBANSERERROR:
			printf("解禁用户不存在!\n");
			break;

		case UNBANSUCCESS:
			printf("解禁成功!\n");
			break;

		case HAVENTBENBAN:
			printf("该用户没有被禁言!\n");
			break;

		default:
			break;
		}
	}
}

void chat_one(int client_socket)
{
	userinfo user;
	user.cmd = CHATONE;
	printf("请输入私聊对象的姓名:");
	scanf("%s", user.toname);
	while (getchar() != '\n');

	printf("请输入要发送的内容:");
	scanf("%s", user.msg);
	while (getchar() != '\n');

	strcpy(user.name, myname);
	write(client_socket, &user, sizeof(userinfo));
}
//创建数据库用于保存聊天记录
sqlite3 * Create_user_sqlite(userinfo * user)
{
	sqlite3 * datebase;
	char name[32];
	sprintf(name ,"%s.db",user->name);
	int ret = sqlite3_open(name, &datebase);
	
	return datebase;
}

void save_Chat(userinfo *user)
{
	sqlite3 * datebase = Create_user_sqlite(user);
	//打开表
	char *errmsg = NULL;
	char sql[128] = "create table if not exists chat(时间 TEXT,发送者 TEXT,接收者 TEXT,内容 TEXT)";
	int ret = sqlite3_exec(datebase, sql, NULL, NULL, &errmsg);
	if(ret != SQLITE_OK)
	{
		return ;
	}
	
	time_t t;
	t = time(&t);
	char time[100];
	strcpy(time,ctime(&t));
	int len = strlen(time);
	time[len-1] = '\0';      //去掉回车 

	sprintf(sql,"insert into chat values('%s','%s','%s','%s')",time ,user->name ,user->toname ,user->msg);
	ret = sqlite3_exec(datebase, sql, NULL, NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("插入数据失败\n");
		return ;
	}
	printf("聊天记录已保存!\n");
	sqlite3_close(datebase);
}

void chat_all(int client_socket)
{
	userinfo user;
	user.cmd = CHATALL;

	printf("请输入要发送的内容:");
	scanf("%s", user.msg);
	while (getchar() != '\n');

	strcpy(user.name, myname);
	write(client_socket, &user, sizeof(userinfo));
}

void search_online_user(int client_socket)
{
	userinfo user;
	user.cmd = SEARCHONLINEUSER;

	write(client_socket, &user, sizeof(userinfo));
}

void adm_request(int client_socket)  //申请成为管理员
{
	userinfo user;
	user.cmd = ADMREQUEST;
	strcpy(user.name, myname);

	write(client_socket, &user, sizeof(userinfo));
	printf("请求已经发出，请留意服务器回复！\n");
}

void logoff_user(int client_socket)  //踢出在线用户
{
	userinfo user;
	user.cmd = LOGOFFUSER;
	printf("请输出踢出对象的名字：");
	scanf("%s", user.toname);
	write(client_socket, &user, sizeof(userinfo));

	memset(&user, sizeof(user), 0);
	read(client_socket, &user, sizeof(user));
	switch(user.cmd)
	{
	case LOGOFFSUCCESS:
		printf("踢出用户成功!\n");
		break;

	case ADMACCOUNT:
		printf("踢出失败，对方是管理员！\n");
		break;

	default:
		printf("对方不存在或者未登录!\n");
		break;
	}
}

void slience_user(int client_socket)
{
	
	userinfo user;
	user.cmd = SLIENCEUSER;
	printf("请输入需要禁言对象的姓名：");
	scanf("%s", user.toname);
	write(client_socket, &user, sizeof(userinfo));
}

void unban_user(int client_socket)
{
	userinfo user;
	user.cmd = UNBANUSER;
	printf("请输入需要解除禁言对象的姓名：");
	scanf("%s", user.toname);
	write(client_socket, &user, sizeof(userinfo));
}

void search_chat()
{
	userinfo user;
    strcpy(user.name, myname);  // 假设已经定义了 myname 变量

    sqlite3 *database = Create_user_sqlite(&user);
    if (database == NULL) 
	{
        printf("数据库连接失败\n");
        return;
    }

    char *errmsg = NULL;
    char buf[200] = "CREATE TABLE IF NOT EXISTS chat (时间 TEXT, 发送者 TEXT, 接收者 TEXT, 内容 TEXT)";
    int ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK) 
	{
        printf("打开表失败: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(database);
        return;
    }

    char **result;
    int nrow, ncolumn;
    char *sql = "SELECT * FROM chat";
    ret = sqlite3_get_table(database, sql, &result, &nrow, &ncolumn, &errmsg);
    if (ret != SQLITE_OK) 
	{
        printf("数据库操作失败: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(database);
        return;
    }

    for (int i = 0; i < nrow + 1; i++)
	 {
        for (int j = 0; j < ncolumn; j++) 
		{
			if(i == 0)
			{
				printf("%-35s", result[i * ncolumn + j]);
			}
            else
			{
				printf("%-30s", result[i * ncolumn + j]);
			}
        }
        printf("\n");
    }

    sqlite3_free_table(result);
    sqlite3_close(database);
}

void send_file(int client_socket) 
{
    userinfo user;
    user.cmd = SENDFILE;
    strcpy(user.name, myname);

    char path[32];
    printf("请输入文件路径:");
    scanf("%s", path);

    printf("请输入发送对象的姓名:");
    scanf("%s", user.toname);

    int file = open(path, O_RDONLY);  // 使用 open 函数打开文件
    if (file == -1) {
        printf("无法打开文件\n");
        return;
    }

    off_t file_size = lseek(file, 0, SEEK_END);  // 定位到文件末尾获取文件大小
    lseek(file, 0, SEEK_SET);  // 重置文件指针到文件开头

    // 通过 read 读取整个文件内容
    ssize_t result = read(file, user.buf, file_size);
    if (result != file_size) 
	{
        printf("读取文件失败\n");
        close(file);
        return;
    }

    printf("获取文件成功!\n");

    printf("buf = %s\n", user.buf);

    write(client_socket, &user, sizeof(user));

    close(file);
}

void revc_flie(userinfo *user)
{
	// int choice;
	// printf("%s给你发送文件，请选择是否接收（1/2）？\n",user->name);
	// scanf("%d", &choice);


	// if(choice == 2)
	// {
	// 	user->cmd = READERROR;
	// 	strcpy(user->toname, user->name);
	// 	write(user->cfd,user, sizeof(userinfo));
	// }
	// else
	// {
	FILE *file = fopen("recv.txt", "a");
	if (file == NULL) 
	{
		printf("无法打开文件\n");
	} 
	else 
	{
		fprintf(file, "%s", user->buf);  // 使用 fprintf 函数以文本方式写入数据
		fclose(file);

		strcpy(user->toname, user->name);
		user->cmd = RECVSUCCESS;
		write(user->cfd, user, sizeof(userinfo));
	}
}