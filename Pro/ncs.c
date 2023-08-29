#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>

#define SERVPORT 5001

#define SUCCESS 0
#define FAILURE -1
struct message
{
    int action;//表示消息的类型，可能的取值包括登录、注册、发送消息等；
    char id[20];
    char name[20];
    char password[20];
    char toid[20];//表示接收消息的用户ID
    char text[500];
    char filename[20];
    char fabulous[20];//表示点赞的用户名
    char V[20];//表示VIP用户的标识
    int flag;//表示消息的标识，用于标记消息是否已读、已删除等。
};
struct online
{
    int c_fd;
    char id[20];
    char V[20];
    int flag;
    struct online *next;
};

extern int flag;
extern struct online *head;

int insert_sql(struct message *msg)
{
    sqlite3 *database;
    // 打开名为 usr.db 的数据库，将指针保存到 database中
    int ret = sqlite3_open("usr.db", &database);
    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return FAILURE;
    }

    char *errmsg = NULL; // 定义指向错误信息的指针，初始化为 NULL
    char buf[100];       // 定义缓冲区 buf，用于存储 SQL 语句

    // 使用 sprintf 函数将插入数据的 SQL 语句存储到 buf 中
    sprintf(buf, "insert into usr values('%s','%s','%s');", msg->id, msg->name, msg->password);

    // 使用 sqlite3_exec 函数执行 SQL 语句，将错误信息保存到 errmsg 中
    ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("添加用户失败：%s\n", errmsg);
        return FAILURE;
    }

    sqlite3_close(database);

    return SUCCESS;
}


/**
 * @brief 将聊天记录插入到数据库中
 *
 * @param msg 一个指向 message 结构体的指针，包含聊天记录的相关信息
 * @return int 返回插入聊天记录操作的执行结果，SUCCESS表示插入成功，FAILURE表示插入失败
 */

/*这段代码定义了一个名为insert_view的函数，
函数的参数为一个指向message结构体的指针msg，
该函数的作用是向名为usr.db的数据库中插入一条聊天记录。

具体来说，这个函数的实现过程如下：

使用sqlite3_open函数打开名为usr.db的数据库，并将指针保存到database中；
如果打开数据库失败，则输出错误信息，并返回FAILURE；
使用sprintf函数将需要插入的聊天记录的信息，
即消息发送者的ID、消息接收者的ID和消息文本内容，格式化成SQL语句，保存在buf中；
使用sqlite3_exec函数执行SQL语句，将聊天记录插入到viewchat表中；
如果插入记录失败，则输出错误信息，并返回FAILURE；
使用sqlite3_close函数关闭数据库；
返回SUCCESS表示插入记录成功。
注意，在使用sprintf函数将需要插入的信息格式化成SQL语句时，存在SQL注入的风险。
建议使用参数化查询来防止SQL注入攻击。*/
int insert_view(struct message *msg)
{
    sqlite3 *database;
    int ret = sqlite3_open("usr.db", &database); // 打开名为 usr.db 的数据库，将指针保存到 database 中

    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return FAILURE;
    }

    char *errmsg = NULL;// 定义一个char类型的指针变量 errmsg，用于保存错误信息
    char buf[1024]; // 定义一个char类型的数组 buf，用于保存SQL语句字符串

    // 使用sprintf函数将需要插入的聊天记录的信息，即消息发送者的ID、消息接收者的ID和消息文本内容，格式化成SQL语句，保存在buf中
    sprintf(buf, "insert into viewchat values('%s','%s','%s');", msg->id, msg->toid, msg->text);

     // 使用sqlite3_exec函数执行SQL语句，将聊天记录插入到viewchat表中
    ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);

    if (ret != SQLITE_OK)// 如果插入记录失败
    {
        printf("添加用户失败：%s\n", errmsg);
        return FAILURE;
    }

    sqlite3_close(database);

    return SUCCESS;
}


/**
 * @brief 设置数据库，创建用户表和视图表
 *
 * @return int 返回设置数据库操作的执行结果，SUCCESS表示设置成功，FAILURE表示设置失败
 */

/*总体来说，这段代码是用来设置数据库的，
它通过打开数据库连接、执行SQL语句来创建用户表和视图表，从而实现了数据库的设置。
需要注意的是，在创建用户表时，使用了一个主键id来确保每个用户的唯一性；
在创建视图表时，将聊天记录分别保存了发送者id、接收者id和聊天内容。*/
int setup_sql()
{
    sqlite3 *database;

    int ret = sqlite3_open("usr.db", &database);

    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return FAILURE;
    }

    char *errmsg = NULL;

    // 定义创建视图表的 SQL 语句
    char *sql = "create table if not exists usr(id text primary key,name text,password text);";

    // 执行 SQL 语句，将错误信息保存到 errmsg 中
    ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("用户表创建失败：%s\n", errmsg);
        return FAILURE;
    }

    // 定义创建视图表的 SQL 语句
    char *ql = "create table if not exists viewchat(id text,toid text,chat text);";

    // 执行 SQL 语句，将错误信息保存到 errmsg 中
    ret = sqlite3_exec(database, ql, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("用户表创建失败：%s\n", errmsg);
        return FAILURE;
    }

    sqlite3_close(database);

    return SUCCESS;
}


/*
其中，主要包括以下几个步骤：

打开名为 usr.db 的 SQLite3 数据库，将指针保存到 database 中；
准备 SQL 查询语句 "select * from viewchat;"，并执行查询；
遍历查询结果，将查询结果中的发送方ID、接收方ID和聊天信息分别赋值给消息结构体中的 id、toid 和 text 字段；
将消息结构体通过套接字发送给客户端；
等待一段时间，避免发送过快。
值得注意的是，函数中的 sqlite3_close(database); 并没有被执行，应该将其放到 return 语句前面，以确保函数返回前关闭数据库连接。
*/

//这段代码主要实现了查询视图表中的聊天信息，并将其发送给客户端。
int inquire_nocb(int connfd, struct message *MSG)
{
    sqlite3 *database;                           // SQLite3 数据库指针
    char *sql = NULL;                            // SQL语句指针
    char **azresult = NULL;                      // 查询结果指针
    char *errmsg = NULL;                         // 错误信息指针
    int n_row, n_col;                            // 行数和列数
    int i;                                       // 循环计数器
    int ret = sqlite3_open("usr.db", &database); // 打开数据库

    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return FAILURE;
    }

    sql = "select * from viewchat;"; // 查询语句

    // 执行查询语句
    ret = sqlite3_get_table(database, sql, &azresult, &n_row, &n_col, &errmsg);

    if (SQLITE_OK != ret)
    {
        printf("get tabble error! %s\n", errmsg);
        return FAILURE;
    }

    // printf("n_row = %d  n_col = %d\n",n_row,n_col);

    // printf("the result of inquire is:\n");

    for (i = n_col; i < (n_row + 1) * n_col; i++) // 遍历查询结果
    {
        // printf("%10s",azresult[i]);
        // memset(MSG,0,sizeof(struct message));
        MSG->action = 12; // 设置消息类型为聊天信息
        if (i % 3 == 0)
        {
            strcpy(MSG->id, azresult[i]); // 将查询结果中的发送方ID赋值给消息结构体中的id字段
                                          // printf("%s",MSG->id);
        }
        if (i % 3 == 1)
        {
            strcpy(MSG->toid, azresult[i]); // 将查询结果中的接收方ID赋值给消息结构体中的toid字段
                                            // printf("%s",MSG->toid);
        }
        if (i % 3 == 2)
        {
            strcpy(MSG->text, azresult[i]);             // 将查询结果中的聊天信息赋值给消息结构体中的text字段
                                                        // printf("%s",MSG->text);
            write(connfd, MSG, sizeof(struct message)); // 将消息发送给客户端
        }
        sleep(0.1); // 等待一段时间，避免发送过快

        /*if((i + 1) % n_col == 0)
        {
            printf("\n");
        }*/
    }
    return SUCCESS;

    sqlite3_close(database);
}

void del_fromsql(struct message *msg)
{
    sqlite3 *database;
    int ret = sqlite3_open("usr.db", &database); // 打开数据库连接
    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return;
    }

    char *errmsg = NULL;
    char buf[100];

    // 构造删除指定id的用户的SQL语句
    sprintf(buf, "delete from usr where id = '%s'", msg->id);

    // 执行SQL语句
    ret = sqlite3_exec(database, buf, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("删除用户失败：%s\n", errmsg);
        return;
    }

    sqlite3_close(database);
    return;
}

int find_id(struct message *msg) // 查找用户id是否存在于数据库
{
    sqlite3 *database;
    int ret = sqlite3_open("usr.db", &database);
    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return FAILURE;
    }

    // 定义指针数组和变量来存储查询结果
    char *errmsg = NULL;
    char **resultp = NULL;
    int nrow, ncolumn;

    // 查询数据库中的所有id
    char *sql = "select id from usr;";
    ret = sqlite3_get_table(database, sql, &resultp, &nrow, &ncolumn, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("用户查找失败：%s\n", errmsg);
        return FAILURE;
    }

    // 遍历查询结果，查找是否有与msg中的id匹配的记录
    int i;
    for (i = 0; i < (nrow + 1) * ncolumn; i++)
    {
        if (strcmp(resultp[i], msg->id) == 0)
            return SUCCESS;
    }
    return FAILURE;
}

/*
这段代码定义了一个函数find_np，用于查找是否存在与消息中相同的用户id和密码。该函数的输入参数是一个指向消息结构体的指针msg，返回值为整型。

函数内部先打开名为usr.db的SQLite3数据库，如果打开失败则返回FAILURE。然后定义了几个指针变量用于保存查询结果和错误信息，以及两个整型变量nrow和ncolumn用于保存查询结果的行数和列数。

接着，构造了一个查询SQL语句，用于查询usr表中的所有信息。然后调用sqlite3_get_table函数执行查询，将结果保存在resultp指向的指针中，并将行数和列数保存在nrow和ncolumn中，同时将错误信息保存在errmsg指向的指针中。如果执行查询失败，则返回FAILURE。

最后，函数通过遍历查询结果，找到与消息中相同的id和password。如果找到了，则返回SUCCESS，否则返回FAILURE。
*/
int find_np(struct message *msg) // 查找是否存在与消息中相同的用户id和密码
{
    sqlite3 *database;
    int ret = sqlite3_open("usr.db", &database);
    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return FAILURE;
    }

    char *errmsg = NULL;
    char **resultp = NULL;
    int nrow, ncolumn;

    // 构造SQL语句，查询usr表中的所有信息
    char *sql = "select * from usr";
    ret = sqlite3_get_table(database, sql, &resultp, &nrow, &ncolumn, &errmsg);
    if (ret != SQLITE_OK)
    {
        printf("用户查找失败：%s\n", errmsg);
        return FAILURE;
    }

    int i;
    // 遍历查询结果，找到与消息中相同的id和password
    for (i = 0; i < (nrow + 1) * ncolumn; i++)
    {
        if (strcmp(resultp[i], msg->id) == 0 &&
            strcmp(resultp[i + 1], msg->password) == 0)
            return SUCCESS;
    }
    return FAILURE;
}

void insert_online(struct online *user)
{

    user->next = head;
    head = user;
}

/*msg：指向消息结构体的指针，用于指定需要检查的用户ID
head：指向在线用户链表的头指针*/
int check_ifonline(struct message *msg, struct online *head)
{
    struct online *p = head;
    while (p != NULL)
    {
        if (strcmp(msg->id, p->id) == 0)
        {
            return SUCCESS;
        }
        else
        {
            p = p->next;
        }
    }
    return FAILURE;
}

void reg(int connfd, struct message *MSG)
{
    printf("正在查找该用户是否被注册...\n");
    if (find_id(MSG) == SUCCESS)
    {
        //	printf("用户%s已经被注册\n",MSG->id);
        MSG->action = -1;// 在消息结构体中添加-1标志，表示用户已被注册
    }
    else if (FAILURE == insert_sql(MSG))
    {
        printf("数据库添加失败\n");
        MSG->action = -1;// 在消息结构体中添加-1标志，表示数据库添加失败
    }
    else
    {
        MSG->action = 1;
        printf("数据库添加成功\n");
    }
    // printf("4");
    write(connfd, MSG, sizeof(struct message));// 将消息结构体发送给客户端
    // printf("3");
}

void logged(int connfd, struct message *MSG)
{
    printf("正在查找该用户有没有注册...\n");

    // 判断用户是否已经注册
    if (find_id(MSG) == SUCCESS)
    {
        // 判断用户密码是否正确
        if (find_np(MSG) == SUCCESS)
        {
            // 判断用户是否已经在线
            if (check_ifonline(MSG, head) == SUCCESS)
            {
                MSG->action = -2;// 用户已经登陆过了，设置消息的操作码为 -2
                // printf("用户%s已经登陆过了\n",MSG->id);
            }
            else
            {
                //	printf("该用户是普通用户\n");
                // 用户为普通用户，将其加入在线用户列表中
                // 新建在线用户并插入在线用户列表中
                struct online *user;
                user = (struct online *)malloc(sizeof(struct online));
                user->c_fd = connfd;
                strcpy(user->V, "0");
                user->flag = 0;
                strcpy(user->id, MSG->id);
                insert_online(user);
                MSG->action = 2;// 设置消息的操作码为 2，表示用户登陆成功
                // printf("用户%s登陆成功\n",MSG->id);
            }
        }
        else
        {
            MSG->action = 4;
            // 密码输入错误，设置消息的操作码为 4
            // printf("用户%s密码输入错误\n",MSG->id);
        }
    }
    else
    {
        MSG->action = -4;
        // 用户还没有注册，设置消息的操作码为 -4
        // printf("用户%s还没有注册\n",MSG->id);
    }

    write(connfd, MSG, sizeof(struct message));// 将处理后的消息发送给客户端
}


/**

@brief 查找在线用户链表中是否存在要发送消息的目标用户，若存在则发送消息给目标用户并返回其套接字描述符

@param toid 要发送消息的目标用户ID

@param MSG 待发送的消息结构体

@param connfd 发送消息的客户端套接字描述符

@return int 若查找成功则返回目标用户的套接字描述符，否则返回FAILURE
*/
int f_id(char *toid, struct message *MSG, int connfd)
{
    // 若在线用户链表为空则返回FAILURE
    if (head == NULL)
    {
        // printf("++");
        return FAILURE;
    }
    // printf("\n-%s-\n",toid);
    struct online *temp = head;
    while (temp != NULL)
    {
        // printf("-%s-",toid);
        // printf("+%s+",temp->id);
        // 比较在线用户链表中的用户ID和目标用户ID是否相同
        if (strcmp(toid, temp->id) == 0)
        {
            // printf("\nqq%dqq\n",temp->c_fd);

            // 如果相同，则设置消息结构体的action为3，并将消息存入发送历史记录中
            MSG->action = 3;
            // MSG->flag = temp->flag;

            insert_view(MSG);
            // printf("%s\n",MSG->text);
            // 发送消息给目标用户
            write(temp->c_fd, MSG, sizeof(struct message));
            // 将发送的消息也发送给发送消息的客户端
            write(connfd, MSG, sizeof(struct message));
            // 返回目标用户的套接字描述符
            return temp->c_fd;
        }
        else
        {
            temp = temp->next;
        }
    }
    // printf("//");
    //在线用户链表中没有找到目标用户
    return FAILURE;
}


/**该函数主要实现了私聊功能。函数首先遍历在线用户列表，查找发送方是否在线。如果发送方在线，则将消息类型设置为私聊消息，并将发送方的在线状态设置为消息的标志位。如果发送方不在线，则向发送方发送消息。

接着，函数调用 f_id 函数查找接收方是否在线。如果接收方在线，则向接收方和发送方都发送私聊消息。如果接收方不在线，则将消息类型设置为接收方不在线，并向发送方发送消息。

注：f_id 函数实现了查找指定用户是否在线的功能。

/*************************/
/*这段代码是私聊消息处理函数。以下是详细的中文注释：

定义一个整数类型变量c_fd，用于存储消息目标用户的连接套接字描述符

创建一个在线用户结构体指针temp，初始化为在线用户链表的头结点

遍历在线用户链表，查找消息发送者是否在线

如果找到了消息发送者

设置消息操作类型为私聊消息

将消息发送者的身份标识保存到消息结构体中

如果消息发送者是管理员

直接将消息返回给消息发送者

否则（如果消息发送者是普通用户）

查找消息目标用户是否在线

如果未找到，设置操作类型为用户不在线

将操作结果返回给消息发送者

如果未找到消息发送者，则不进行任何操作
*/
void privatechat(int connfd, struct message *MSG)
{
    int c_fd;// 定义一个整数类型变量c_fd，用于存储消息目标用户的连接套接字描述符

    /*变量c_fd用于存储私聊消息接收者的文件描述符（file descriptor），
    它是一个整型数值。在私聊消息中，我们需要找到接收者对应的在线用户节点，
    获取该节点中的文件描述符，然后将私聊消息发送给该文件描述符对应的客户端。
    因此，变量c_fd被定义为一个整型，用于存储接收者的文件描述符，方便后续使用。*/
    
    // printf("%s",MSG->toid);
    // printf("***%d***",MSG->flag);
    // printf("%s",MSG->id);
    struct online *temp = head;// 创建一个在线用户结构体指针temp，初始化为在线用户链表的头结点

    while (temp != NULL)// 遍历在线用户链表，查找消息发送者是否在线
    {
        // printf("-%s-",toid);
        // printf("+%s+",temp->id);
        if (strcmp(MSG->id, temp->id) == 0) // 如果找到了消息发送者
        {
            // printf("\nqq%dqq\n",temp->c_fd);

            MSG->action = 3;// 设置消息类型为私聊消息
            MSG->flag = temp->flag;// 将消息发送者的身份标识保存到消息结构体中
            if (MSG->flag == 1)// 如果消息发送者是管理员
            {
                write(connfd, MSG, sizeof(struct message));
                break;
            }
            else// 如果消息发送者是普通用户
            {
                // 查找消息目标用户是否在线，如果未找到，设置操作类型为用户不在线
                if ((c_fd = f_id(MSG->toid, MSG, connfd)) == FAILURE)
                {
                    MSG->action = -3;// 设置消息类型为接收方不在线

                    write(connfd, MSG, sizeof(struct message));  // 将操作结果返回给消息发送者
                }

                break;
            }
        }
        else
        {
            temp = temp->next;// 继续查找下一个在线用户
        }
    }

    /* if((c_fd = f_id(MSG->toid,MSG,connfd)) == FAILURE)
     {
         MSG->action = -3;
         write(connfd,MSG,sizeof(struct message));
     }*/
    /*else
    {
        printf("\n%d\n",c_fd);
        MSG->action = 3;
        printf("%s\n",MSG->text);
        write(c_fd,MSG,sizeof(struct message));

    }*/
}


/***********************************************************************************/
void groupchat(int connfd, struct message *MSG)
{
    struct online *p = head;
    int c_fd; // 客户端文件描述符
    while (p != NULL)
    {
        insert_view(MSG);// 将消息插入聊天记录链表中
        MSG->action = 5;// 消息动作标志设置为群聊
        c_fd = p->c_fd;// 获取客户端文件描述符
        MSG->flag = flag;// 消息标志设置为通知类型
        write(c_fd, MSG, sizeof(struct message));// 向客户端发送消息
        p = p->next;// 指向下一个在线用户
    }
}

void online(int connfd, struct message *MSG)
{
    struct online *p = head;
    int c_fd = connfd;// 当前客户端文件描述符
    memset(MSG->text, 0, sizeof(MSG->text));
    while (p != NULL)
    {
        MSG->action = 6; // 消息动作标志设置为在线用户列表
        // c_fd = p->c_fd;
        // printf("%s is online",p->id);
        // memset(&MSG->text,0,sizeof(MSG->text));
        strcat(MSG->text, p->id);// 将在线用户ID拼接到消息文本末尾
        strcat(MSG->text, "   ");
        p = p->next;
    }
    write(c_fd, MSG, sizeof(struct message));
    // printf("%s",MSG->text);
}
 
void release_link()
{
    struct online *tmp = NULL;
    tmp = head;

    while (head != NULL)
    {
        tmp = head;
        head = (head)->next;
        free(tmp);
    }

    if (head == NULL)
    {
        printf("link is emtpy\n");
        return;
    }
}


/**
 * @brief 从链表中删除一个在线节点
 * 
 * @param connfd 连接描述符
 * @param msg 包含要删除节点的 ID 信息的消息结构体
 * @return int 返回被删除节点对应的连接描述符，如果未找到对应节点返回 FAILURE
 */
int delete(int connfd, struct message *msg)
{
    struct online *q = NULL;// 保存前一个节点指针
    struct online *p = NULL;// 保存当前节点指针
    p = head; // 初始化为链表头节点
    int c_fd;// 保存被删除节点的连接描述符

    if (NULL == head)// 判断链表是否为空
    {
        printf("link is empty !\n");
        return FAILURE;
    }

    if (head != NULL)// 链表不为空
    {

        while (p != NULL)
        {
            if (strcmp(msg->id, p->id) == 0) // 找到要删除的节点
            {
                if (p == head)// 要删除的节点是头节点
                {
                    c_fd = p->c_fd;// 保存连接描述符
                    head = p->next;// 修改头节点指向下一个节点
                    free(p); // 释放要删除节点的内存
                    return c_fd;// 返回被删除节点的连接描述符
                    break;
                }
                else// 要删除的节点不是头节点
                {
                    c_fd = p->c_fd; // 保存连接描述符
                    q->next = p->next;// 修改前一个节点的指针，指向下一个节点
                    free(p);// 释放要删除节点的内存
                    return c_fd; // 返回被删除节点的连接描述符
                    break;
                }
            }
            else // 当前节点不是要删除的节点
            {
                q = p;
                p = p->next;
            }
        }
    }
    else// 链表为空
    {
        printf("no such node!\n");
    }
    return FAILURE;
}


/**
 * @brief 下线函数，将在线列表中指定的节点删除并通知对应客户端下线
 * 
 * @param connfd 连接描述符
 * @param MSG 包含要下线节点的 ID 信息的消息结构体
 */
void offline(int connfd, struct message *MSG)
{
    int c_fd;// 保存被删除节点的连接描述符
    c_fd = delete (connfd, MSG);// 删除在线列表中指定的节点，并返回连接描述符
    MSG->action = 7;// 设置消息的动作为下线
    write(c_fd, MSG, sizeof(struct message));// 向对应客户端发送下线消息
}


/**
 * @brief 离线函数，将客户端从在线列表和数据库中删除并通知客户端成功离线
 * 
 * @param connfd 连接描述符
 * @param MSG 包含要离线节点的 ID 信息的消息结构体
 */
void off(int connfd, struct message *MSG)
{
    // release_link();// 可能是释放链表内存的函数
    del_fromsql(MSG);// 从数据库中删除对应节点
    MSG->action = -6; // 设置消息的动作为离线成功
    write(connfd, MSG, sizeof(struct message));// 向客户端发送离线成功消息
}


/**
 * @brief 管理员登录函数，根据客户端提供的账号和密码验证管理员身份
 * 
 * @param connfd 连接描述符
 * @param MSG 包含管理员账号和密码的消息结构体
 */
void adm(int connfd, struct message *MSG)
{
    // struct master m;
    // printf("1.%s",m.id);
    // printf("2.%s",MSG->id);
    if (strcmp(MSG->id, "root") == 0)// 如果输入账号为 "root"
    {
        if (strcmp(MSG->password, "123") == 0)// 并且输入密码为 "123"
        {
            MSG->action = 8; // 设置消息的动作为管理员登录成功
            write(connfd, MSG, sizeof(struct message)); // 向客户端发送管理员登录成功消息
        }
        else
        {
            MSG->action = -8; // 设置消息的动作为管理员登录失败
            write(connfd, MSG, sizeof(struct message));// 向客户端发送管理员登录失败消息
        }
    }
    else
    {
        MSG->action = -8; // 设置消息的动作为管理员登录失败
        write(connfd, MSG, sizeof(struct message));// 向客户端发送管理员登录失败消息
    }
}


/**
 * @brief 禁言指定账号的用户
 * 
 * @param connfd 连接描述符
 * @param MSG 包含需要禁言的用户账号的消息结构体
 */
void ban(int connfd, struct message *MSG)
{
    struct online *temp = head;
    // printf("1");
    if (head == NULL)
    {

        return;
    }

    while (temp != NULL)
    {
        // printf("2");
        if (strcmp(MSG->id, temp->id) == 0)// 如果找到了需要禁言的用户
        {
            // printf("3");
            if (strcmp(temp->V, "1") == 0)// 如果该用户已经被禁言
            {
                MSG->action = -9;// 设置消息的动作为禁言失败
                // printf("4");
                write(connfd, MSG, sizeof(struct message));// 向管理员发送禁言失败消息
                break;
            }
            else
            {
                // printf("5");
                // temp->flag =1;
                temp->flag = 1; // 在用户的在线信息中设置禁言标志
                MSG->flag = 1;// 在需要发送的消息中设置禁言标志
                MSG->action = 3;// 设置消息的动作为禁言成功
                printf("/%d/", MSG->flag);
                write(temp->c_fd, MSG, sizeof(struct message));// 向该用户发送禁言成功消息

                break;
            }
        }
        else
        {
            temp = temp->next;
        }
    }
}

/*这个函数实现了“解禁”某个被禁言的客户端用户的功能。
具体来说，函数会遍历在线用户链表，找到与给定消息中相同id的在线用户，
然后将该用户的flag设置为0，表示已经解禁。接着向该用户发送一条消息，
告知其已经被解禁，并将消息发送给管理员，告知解禁成功。*/
void unban(int connfd, struct message *MSG)
{
    struct online *temp = head; // 从头结点开始遍历在线用户链表

    if (head == NULL)
    {

        return;
    }

    while (temp != NULL)
    {

        if (strcmp(MSG->id, temp->id) == 0)// 找到与消息中相同id的在线用户
        {
            // 将该用户的flag设置为0，表示已经解禁
            temp->flag = 0;

            // 向该用户发送一条消息，告知其已经被解禁
            MSG->flag = -1; 
            write(temp->c_fd, MSG, sizeof(struct message));

             // 向管理员发送一条消息，告知解禁成功
            MSG->action = 9;
            write(connfd, MSG, sizeof(struct message));

            break;
        }
        else
        {
            temp = temp->next;
        }
    }
}

/**
 * @brief 该函数实现了将某个用户从聊天室中踢出的功能。
 * 首先，使用一个指针temp遍历在线用户链表，找到需要被踢出的用户。
 * 如果找到了该用户，则判断该用户是否被禁言。如果该用户被禁言，则向管理员发送错误提示信息，否则向管理员发送成功提示信息并将该用户从在线用户链表中删除。
 * 最后，调用offline函数实现将该用户踢出聊天室的功能。
 * @param connfd 与客户端建立的socket连接的文件描述符。
 * @param MSG 指向一个结构体的指针，包含了与客户端交互的消息内容。
 */
void expel(int connfd, struct message *MSG)
{
    struct online *temp = head;
    while (temp != NULL)
    {
        // printf("-%s-",toid);
        // printf("+%s+",temp->id);
        if (strcmp(MSG->id, temp->id) == 0)
        {
            if (strcmp(temp->V, "1") == 0)
            {
                MSG->action = -11;
                write(connfd, MSG, sizeof(struct message));
                break;
            }
            else
            {
                MSG->action = 11;
                write(connfd, MSG, sizeof(struct message));
                offline(connfd, MSG);

                break;
            }
        }
        else
        {
            temp = temp->next;
        }
    }
}


/**
 * @brief 这个函数是调用inquire_nocb函数实现查询聊天对象是否在线的功能，
 * 这个功能应该是给VIP用户使用的，可以与离线用户聊天。
 * @param connfd 连接套接字描述符。
 * @param MSG 指向message结构体的指针，包含了查询对象的id和需要执行的动作。
 */
void vchat(int connfd, struct message *MSG)
{
    inquire_nocb(connfd, MSG);
}

void clean(int connfd, struct message *MSG)
{
    sqlite3 *database;
    char *sql = NULL;

    char *errmsg = NULL;

    int ret = sqlite3_open("usr.db", &database);

    if (ret != SQLITE_OK)
    {
        printf("打开数据库失败\n");
        return;
    }

    // 构造 SQL 语句以删除查看聊天表中的所有行
    sql = "delete from viewchat;";

    //执行SQL语句
    ret = sqlite3_exec(database, sql, NULL, NULL, &errmsg);

    //如果删除成功，请发送一条消息，指示成功
    if (ret != SQLITE_OK)
    {
        printf("清除失败：%s\n", errmsg);
        return;
    }

    sqlite3_close(database);
    MSG->action = 13;
    write(connfd, MSG, sizeof(struct message));
}


/*这个函数用于将指定的文件内容发送给客户端。
它首先打开要传输的文件，然后循环读取文件内容并将其写入到消息结构体中，最后发送消息结构体到客户端。
如果文件打开失败，则输出错误信息并返回。函数类型被设置为文件传输*/
void wfile(int connfd, struct message *MSG)
{

    printf("%s", MSG->name);// 输出要传输的文件名
    MSG->action = 14;// 设置消息类型为文件传输
    FILE *file = fopen(MSG->name, "r"); // 打开要传输的文件
    // FILE* file = fopen("2.c","r");

    if (file == NULL)// 若文件打开失败
    {
        // printf("error");
        perror("create");
    }

    while (!feof(file))// 循环读取文件内容
    {
        printf("send");
        fread(MSG->text, 1, sizeof(MSG->text), file);// 从文件读取内容到消息结构体

        write(connfd, MSG, sizeof(struct message));// 发送消息结构体到客户端
    }

    fclose(file);
}

void recv_file(int connfd, struct message *MSG)
{

    FILE *fp = NULL;

    printf("%s", MSG->filename);
    fp = fopen(MSG->filename, "w");// 打开文件，文件名为客户端传来的文件名
    // fp = fopen("s.c","w");
    if (fp == NULL)
    {
        printf("creatr fp failure\n");
        perror("create");
        exit(0);
    }

    printf("recv begin\n");

    fprintf(fp, "%s", MSG->text);// 将客户端传来的文件内容写入文件

    fclose(fp);
    strcpy(MSG->text, MSG->filename); // 将文件名赋给消息的文本部分
    groupchat(connfd, MSG); // 将该消息发送给所有在线用户
}


/**
 * @brief 该函数用于给指定用户发送点赞消息。




该函数没有处理目标用户不在线的情况。
 * 
 * @param connfd 客户端套接字描述符。
 * @param msg 指向 struct message 结构体的指针，存储了点赞消息的相关信息。
函数流程：
@brief 遍历在线用户列表 head。
若找到目标用户，则将点赞消息的相关信息写入 msg 中，包括将 msg->fabulous 设为 "1"，将 msg->text 设为 "hello"。
将消息通过 write 函数发送给目标用户。
等待 3 秒。
将 msg->action 设为 17，代表点赞消息发送成功，通过 write 函数将消息发送给客户端。

 */
void fab(int connfd, struct message *msg)
{

    printf("1");
    struct online *temp = head;
    while (temp != NULL)
    {
        // printf("-%s-",toid);
        // printf("+%s+",temp->id);
        if (strcmp(msg->toid, temp->id) == 0)
        {
            // printf("\nqq%dqq\n",temp->c_fd);
            msg->action = 3;
            // msg->flag = temp->flag;
            printf("*%d*", msg->action);
            strcpy(msg->fabulous, "1");// 将点赞信息置为1
            strcpy(msg->text, "hello");
            printf("%s", msg->fabulous);
            // printf("%s\n",MSG->text);
            write(temp->c_fd, msg, sizeof(struct message)); // 发送点赞消息给接收者

            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    sleep(3);// 为了更好地展示点赞效果，让主动点赞用户等待3秒钟
    msg->action = 17;// 回复点赞结果给主动点赞用户
    write(connfd, msg, sizeof(msg));
}

void VIP(int connfd, struct message *msg)
{
    msg->action = 19; // 设置消息类型为VIP
    struct online *temp = head;// 定义在线用户列表头指针
    while (temp != NULL)
    {

        if (strcmp(msg->id, temp->id) == 0)// 找到对应的在线用户
        {

            // temp->V = msg->V;
            strcpy(temp->V, "1");// 将该用户的 VIP 标识设置为 1
            strcpy(msg->V, "1"); // 将消息中的 VIP 标识也设置为 1
            printf("*%s*", msg->V);
            write(connfd, msg, sizeof(struct message)); // 发送设置成功的消息给客户端
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
}

/*这段代码实现了一个线程函数 thread_func，
它在收到客户端发送的消息后，根据 MSG.action 字段的不同，调用不同的函数进行处理。
*/
void *thread_func(void *arg)
{
    int connfd, n;
    struct message MSG;

    connfd = *((int *)arg);// 获取传递进来的参数

    while (1)
    {
        memset(&MSG, 0, sizeof(MSG)); // 初始化消息
        n = read(connfd, &MSG, sizeof(MSG));// 读取客户端传来的消息

         // 如果读取到的字节数为0，说明客户端已经断开连接
        if (0 == n)
        {
            printf("客户端离线!\n");

            pthread_exit(NULL);// 退出线程
            //  printf("1");
        }

        // 根据收到的消息类型，调用相应的处理函数
        switch (MSG.action)
        {
        case 1:
        {
            reg(connfd, &MSG);
            break;
        }
        case 2:
        {
            logged(connfd, &MSG);
            break;
        }
        case 3:
        {
            privatechat(connfd, &MSG);
            break;
        }
        case 5:
        {
            groupchat(connfd, &MSG);
            break;
        }
        case 6:
        {
            online(connfd, &MSG);
            break;
        }
        case -6:
        {
            off(connfd, &MSG);
            break;
        }
        case 7:
        {
            offline(connfd, &MSG);
            break;
        }
        case 8:
        {
            adm(connfd, &MSG);
            break;
        }
        case 9:
        {
            ban(connfd, &MSG);
            break;
        }
        case 10:
        {
            unban(connfd, &MSG);
            break;
        }
        case 11:
        {
            expel(connfd, &MSG);
            break;
        }
        case 12:
        {
            vchat(connfd, &MSG);
            break;
        }
        case 13:
        {
            clean(connfd, &MSG);
            break;
        }
        case 14:
        {
            wfile(connfd, &MSG);
            break;
        }
        case 15:
        {
            recv_file(connfd, &MSG);
            break;
        }
        case 16:
        {
            MSG.action = 16;
            write(connfd, &MSG, sizeof(MSG));
            break;
        }
        case 17:
        {
            fab(connfd, &MSG);
            break;
        }
        case 18:
        {
            MSG.action = 18;
            write(connfd, &MSG, sizeof(MSG));
            break;
        }
        case 19:
        {
            VIP(connfd, &MSG);
            break;
        }
        }
    }

    close(connfd);
}


int flag = 0;
struct online *head = NULL;


int main()
{
    int ret;

    int i = 0;

    pthread_t a_thread;

    // 声明socket相关变量
    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;// 服务端和客户端地址结构体
    socklen_t clilen;

    // 数据库链接初始化
    setup_sql();

    // 创建socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0); // 创建 TCP 协议的 socket
    if (listenfd == -1)
    {
        perror("socket");
        return -1;
    }
    // 绑定IP和端口号
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVPORT);// 设置服务端口号
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);// INADDR_ANY 表示绑定所有可用的本地 IP 地址

    // 设置socket选项,用于重用端口
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定 socket 到指定地址和端口号
    ret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if (ret == -1)
    {
        perror("bind");
        return -1;
    }
    // 监听端口，等待客户端连接
    ret = listen(listenfd, 10);// 允许连接请求队列的长度为10
    if (ret == -1)
    {
        perror("listen");
        return -1;
    }

    printf("等待客户端连接.......\n");

    // 进入循环等待客户端连接
    while (1)
    {
        clilen = sizeof(cliaddr);

        for (; i < 10; i++)
        {
            // 接收客户端连接
            connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

            if (connfd == -1)
            {
                perror("accept");
                return -1;
            }

            printf("成功接收一个客户端: %s\n", inet_ntoa(cliaddr.sin_addr));

            // 创建线程处理客户端请求
            if (pthread_create(&a_thread, NULL, thread_func, (void *)&connfd) != 0)
            {
                printf("create fail error !\n");
                exit(-1);
            }
        }

        // 当客户端已满时退出循环
        if (i == 10)
        {
            printf("客户端已满！\n");
            break;
        }
    }
    // 关闭监听socket
    pthread_detach(a_thread);
    close(listenfd);

    return 0;
}