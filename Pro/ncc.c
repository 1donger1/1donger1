#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#include<pthread.h>
#define SERVPORT 5001
 
struct message
{
    int action;//log 
    char id[20];
    char name[20];
    char password[20];
    char toid[20];
    char text[500];
    char filename[20];
    char fabulous[20];
    char V[20];
    int flag;
};
 

void display_line()
{
	system("clear");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
 
}
 
void Interface()
{
	display_line();
	printf("\t\t注册(reg)\n");
	printf("\n");
	printf("\t\t登陆(log)\n");
	printf("\n");
    printf("\t\t管理员登录(master)\n");
    printf("\n");
	printf("\t\t退出(end)\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t请输入指令:\n");
 
}
 
void masterface()
{
    display_line();
	printf("\t\t禁言(ban)\n");
	printf("\n");
	printf("\t\t解除禁言(unban)\n");
	printf("\n");
    printf("\t\t踢人(expel)\n");
    printf("\n");
	printf("\t\t退出(ex)\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t请输入指令:\n");
}
 
void ordface(struct message*msg)
{
 
	display_line();
	printf("\t\t-.- %s:\n", msg->id);
	printf("\n");
	printf("\t\t查看在线用户(on)\n");
	printf("\n");
	printf("\t\t群发消息(group)\n");
	printf("\n");
	printf("\t\t发送悄悄话(sto)\n");
	printf("\n");
	printf("\t\t删除聊天记录(clean)\n");
	printf("\n");
	printf("\t\t查看聊天记录(vchat)\n");
	printf("\n");
	printf("\t\t上传文件(wfile)\n");
	printf("\n");
	printf("\t\t下载文件(rfile)\n");
    printf("\n");
    printf("\t\t拍一拍(pat)\n");
    printf("\n");
    printf("\t\t注册VIP(vip)\n");
    printf("\n");
    printf("\t\t注销当前用户(off)\n");
	printf("\n");
	printf("\t\t退出当前账号(quit)\n");
	printf("\n");
	printf("\t\t请输入指令:\n");
   
}
 
void recv_file(struct message*msg)
{
	
	FILE* file = NULL;
 
	printf("///%s///",msg->name);
	file = fopen(msg->name ,"w");
   // file = fopen("2.c" ,"w");
	if(file == NULL)
	{
		printf("creatr file failure\n");
		perror("create");
		exit(-1);
	}
	printf("recv begin\n");
	
    fprintf(file,"%s",msg->text);
    // fprintf(file,"%c",buf[i]);
 
	fclose(file);
    
}
 
void short_s(struct message*msg)
{
    char buf[20] = {0};
    memset(buf,0,sizeof(buf));
    printf("\n\t\t请选择快捷语句(sen)或者表情(exp):");
    scanf("%s",buf);
    if(strcmp(buf,"sen") == 0)
    {
        memset(buf,0,sizeof(buf));
        printf("\n\t\t1.早上好！\n");
        printf("\n\t\t2.在吗?\n");
        printf("\n\t\t3.我想你了！\n");
        printf("\n\t\t请输入选择的句子序号:");
 
        scanf("%s",buf);
 
        if(strcmp(buf,"1") == 0)
        {
            strcpy(msg->text,"早上好！");
            printf("--%s--\n",msg->text);
        }
        else if(strcmp(buf,"2") == 0)
        {
            strcpy(msg->text,"在吗?");
            printf("--%s--\n",msg->text);
        }
        else if(strcmp(buf,"3") == 0)
        {
            strcpy(msg->text,"我想你了!\n");
            printf("--%s--\n",msg->text);
        }
 
    }
    else
    {
        memset(buf,0,sizeof(buf));
        printf("\n\t\t1.( *^o^* )\n");
        printf("\n\t\t2.(`皿´)\n");
        printf("\n\t\t3.( ๑ŏ ~ ŏ๑ )\n");
        printf("\n\t\t请输入选择的句子序号:");
 
        scanf("%s",buf);
 
        if(strcmp(buf,"1") == 0)
        {
            strcpy(msg->text,"( *^o^* )");
            printf("--%s--\n",msg->text);
        }
        else if(strcmp(buf,"2") == 0)
        {
            strcpy(msg->text,"(`皿´)");
            printf("--%s--\n",msg->text);
        }
        else if(strcmp(buf,"3") == 0)
        {
            strcpy(msg->text,"( ๑ŏ ~ ŏ๑ )\n");
            printf("--%s--\n",msg->text);
        }
 
    }
 
}
 
void *read_msg(void *arg)
{
    int c_fd = *((int*)arg);
    //char buf[1024] = {0};
    struct message MSG;
 
    while(1)
    {
        //memset(&MSG,0,sizeof(MSG));
        if(read(c_fd,&MSG,sizeof(MSG)) == 0)
        {
            printf("exit 服务器\n");
            pthread_exit(NULL);
        }
        
        switch(MSG.action)
        {
            case 1:
            {
                printf("\t\t这是您的帐号 id: %s\n\n",MSG.id);
                printf("\t\t登录成功\n");
                while(getchar()!='\n');
                
                sleep(3);
                
                Interface();
                break;
            
            }
            case -1:
            {
                printf("注册失败,该用户已经注册\n");
                sleep(1);
                Interface();
                break;
            }
            case 2:
            {
               
                printf("登录成功\n");
                sleep(1);
                ordface(&MSG);
                
                break;
            
            }
            case -2:
            {
               
                printf("该用户已在线,请不要重复登录\n");
                sleep(1);
                Interface();
                break;
            
            }
            case -4:
            {
               
                printf("用户%s还没有注册\n",MSG.id);
                sleep(2);
                Interface();
                break;
            
            }
            case 4:
            {
                printf("用户%s密码输入错误\n",MSG.id);
                sleep(2);
                Interface();
                break;
            
            }
            case -3:
            {
                printf("%s 离线\n",MSG.toid);
                sleep(1);
                break;
            }
            case 3:
            {
                //printf("%s",MSG.fabulous);
                if(strcmp(MSG.fabulous ,"1") == 0)
                {
                    printf("\t\t%s拍了拍你\n",MSG.id);
                }
                else
                {
                    if(MSG.flag == 1)
                    {
                        printf("%s被管理员禁言\n",MSG.id);
                    }
                    else if(MSG.flag == -1)
                    {
                        printf("%s被管理员解除禁言了\n",MSG.id);
                        printf("%s 向 %s 发送了: %s\n",MSG.id,MSG.toid,MSG.text);
                    }
                    else
                    {
                        printf("%s 向 %s 发送了: %s\n",MSG.id,MSG.toid,MSG.text);
                    }
                }
                break;
            }
            case 5:
            {
                
                if(MSG.flag == 1)
                {
                    printf("%s被管理员禁言了\n",MSG.id);
                }
                else if(MSG.flag == -1)
                {
                    printf("%s被管理员解除禁言了\n",MSG.id);
                    printf("%s 向群发送了:%s\n",MSG.id,MSG.text);
                }
                else
                {
                    printf("%s 向群发送了:%s\n",MSG.id,MSG.text);
                }
                break;
            }
            case 6:
            {
                printf("%s 在线\n",MSG.text);
                break;
            }
            case -6:
            {
                printf("帐号注销成功\n再见\n");
                sleep(2);
                //exit(0);
                break;
            }
            case 7:
            {
                printf("%s 退出\n",MSG.id);
                sleep(2);
                Interface();
                break;
            }
            case 8:
            {
                printf("管理员登录成功\n");
                sleep(2);
                masterface();
                break;
            }
            case -8:
            {
                printf("管理员登录失败\n");
                sleep(2);
                Interface();
                break;
            }
            case 9:
            {
                printf("\n\t\t管理员将 %s 禁言\n",MSG.id);
                break;
            }
            case -9:
            {
                printf("\n\t\t%s 是VIP成员,无法禁言\n",MSG.id);
                break;
            }
            case 10:
            {
                printf("管理员将 %s 解除禁言\n",MSG.id);
                break;
            }
            case 11:
            {
                printf("%s被踢下线\n",MSG.id);
                break;
            }
            case -11:
            {
                printf("%s是VIP无法踢除\n",MSG.id);
                break;
            }
            case 12:
            {
                printf("\n%s send to %s: %s\n",MSG.id,MSG.toid,MSG.text);
                break;
            }
            case 13:
            {
                printf("聊天记录已清空\n");
                break;
            }
            case 14:
            {
                recv_file(&MSG);
                break;
            }
            case 15:
            {
                //w_file(c_fd);
                printf("%s上传成功\n",MSG.filename);
                break;
            }
            case 16:
            {
                printf("\n\t\t退出成功\n\t\t再见\n");
                exit(0);
                break;
            }
            case 17:
            {
                printf("\t\t你拍了拍%s\n",MSG.toid);
                break;
            }
            case 18:
            {
                printf("管理员退出成功\n");
                sleep(1);
                Interface();
                break;
            }
            case 19:
            {
                //printf("**%s**",MSG.V);
                printf("\t\t成功注册VIP\n");
                break;
            }
 
        }
 
    }
}
 

int main(int argc,char ** argv)
{
    int sockfd,id;
    struct sockaddr_in servaddr;

    char cmd[20]  = {0};
    struct message MSG;
 
    if(argc != 2)
    {
        printf("usage:server address!\n");
        exit(0);
        
    }
 
    sockfd = socket(AF_INET,SOCK_STREAM,0);
 
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVPORT);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
   
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    Interface();
    pthread_t tid;
    
    pthread_create(&tid,NULL,read_msg,(void *)&sockfd);
 

    while(1)
    {   
        memset(cmd,0,sizeof(cmd));
        //memset(&MSG,0,sizeof(MSG));
        printf("\t\t");
        scanf("%s",cmd);
        if(strcmp(cmd,"reg") == 0)
        {
            MSG.action = 1;
            printf("\t\t请输入姓名:");
            scanf("%s",MSG.name);
	        printf("\n");
	        printf("\t\t请输入密码:");
	        scanf("%s",MSG.password);
            printf("\n");
            srand((unsigned int)time(0));
            id = rand() %1000;
            sprintf(MSG.id,"%d",id);
            write(sockfd,&MSG,sizeof(MSG));
            sleep(3);
            Interface();
            
              
        }
        else if(strcmp(cmd,"log") == 0)
        {
            MSG.action = 2;
            printf("\t\t请输入id:");
            scanf("%s",MSG.id);
	        printf("\n");
	        printf("\t\t请输入密码:");
	        scanf("%s",MSG.password);
            printf("\n");
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
            
              
        }
        else if(strcmp(cmd,"sto") == 0)
        {
            MSG.action = 3;
            printf("\n\t\t请输入对方id:");                                  
            scanf("%s",MSG.toid);

	        while(1)
            {
            printf("\n\t\t请输入消息:(q!退出)\n");
	        printf("\n如果想输入快捷语句,请输入(u!)\n");
            scanf("%s",MSG.text);
            if(strcmp(MSG.text,"q!") == 0)
            {
                break;
            }
            if(strcmp(MSG.text,"u!") == 0)
            {
                short_s(&MSG);
            }
            write(sockfd,&MSG,sizeof(MSG));
 
            sleep(1);
            }
        }
        else if(strcmp(cmd,"group") == 0)
        {
            MSG.action = 5;
            
	        printf("\t\t请输入消息:\n");
            printf("\n如果想输入快捷语句,请输入(u!)\n");
	        scanf("%s",MSG.text);
            
            if(strcmp(MSG.text,"u!") == 0)
            {
                short_s(&MSG);
            }
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"on") == 0)
        {
            MSG.action = 6;
            printf("\n");
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"off") == 0)
        {
            MSG.action = -6;
            printf("\n");
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"quit") == 0)
        {
            MSG.action = 7;
            printf("\n");
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"master") == 0)
        {
            MSG.action = 8;
            printf("\t\t请输入管理员账户:");
            scanf("%s",MSG.id);
            printf("\n");
            printf("\t\t请输入管理员密码:");
            scanf("%s",MSG.password);
            printf("\n");
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"ban") == 0)
        {
            MSG.action = 9;
            printf("\n\t\t请输入禁言的 id:");
            scanf("%s",MSG.id);
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"unban") == 0)
        {
            MSG.action = 10;
            printf("\n\t\t请输入解除禁言的 id:");
            scanf("%s",MSG.id);
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"expel") == 0)
        {
            MSG.action = 11;
            printf("\n\t\t请输入踢下线的 id:");
            scanf("%s",MSG.id);
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"vchat") == 0)
        {
            MSG.action = 12;
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"clean") == 0)
        {
            MSG.action = 13;
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
        }
        else if(strcmp(cmd,"rfile") == 0)
        {
            MSG.action = 14;
            printf("\n\t\t请输入下载的文件名:");
           // scanf("%s",MSG.filename);
         //   printf("%s",MSG.filename);
            scanf("%s",MSG.name);
            //strcpy(MSG.name,"he");
            write(sockfd,&MSG,sizeof(MSG));
            //sleep(1);
        }
        else if(strcmp(cmd,"wfile") == 0)
        {
    
            MSG.action = 15;
            printf("\n\t\t请输入上传的文件名:");
            scanf("%s",MSG.filename);
            printf("%s",MSG.filename);
	        FILE* file = fopen(MSG.filename,"r");
	        if(file == NULL)
            {
                printf("打开失败！\n");
                //exit(0);
            }
            while(!feof(file))
	        {
                fread(MSG.text,1,sizeof(MSG.text),file);
       
		        write(sockfd,&MSG,sizeof(MSG));
	        }
	
	        fclose(file);
        }
        else if(strcmp(cmd,"end") == 0)
        {
            MSG.action = 16;
            
            write(sockfd,&MSG,sizeof(MSG));
            //sleep(1);
        }
        else if(strcmp(cmd,"pat") ==0)
        {
            MSG.action = 17;
            printf("\n\t\t请输入你拍一拍的id:");
            scanf("%s",MSG.toid);
            write(sockfd,&MSG,sizeof(MSG));
            
  
        }
        else if(strcmp(cmd,"ex") ==0)
        {
            MSG.action = 18;
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
            
        }
         else if(strcmp(cmd,"vip") ==0)
        {
            MSG.action = 19;
            strcpy(MSG.V,"1");
            write(sockfd,&MSG,sizeof(MSG));
            sleep(1);
 
        } 
        else
        {
            printf("\n\t\t输入指令错误,请重新输入:\n");
            printf("\t\t");
            
        }
    }
    close(sockfd);
 
    return 0;
}