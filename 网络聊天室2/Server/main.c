//epoll + 多线程

#include "server.h"
#include "threadpool.h"
#define EPOLL_SIZE 1024

int main()
{
    int cfd;
    int sockfd;
    int epfd;

    socklen_t c_size;
    struct sockaddr_in c_addr;
    struct epoll_event event;
    struct epoll_event events[EPOLL_SIZE];

    sockfd = tcp_server_create();
    set_noblock(sockfd);//设置成非阻塞
    
    epfd = epoll_create(2000); //默认可以监听2000个用户

    if(epfd == -1)
    {
        perror("epoll创建失败!\n");
        exit(1);
    }
    event.events = EPOLLIN; //读
    event.data.fd = sockfd;

    //创建线程池
    threadpool_t * pool = threadpool_create(5, 10, 20);

    //首先需要监听sockfd,将sockfd扔进红黑树里
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);

    while(1)
    {
        int r_n = epoll_wait(epfd, events, EPOLL_SIZE, -1); //最多能接受到1024个变化,有变化回传到内核里

        for(int i = 0; i < r_n; i++)
        {
            if(events[i].events == EPOLLIN) //如果可读
            {
                if(events[i].data.fd == sockfd)//并且是客户端来连接
                {
                    c_size = sizeof(struct sockaddr_in);
                    cfd = accept(sockfd,(struct sockaddr *)&c_addr,&c_size); //sock设置成非阻塞之后，没有客户端之后accept不会阻塞
                    if(cfd < 0)
                    {
                        if(errno != EAGAIN && errno != EOWNERDEAD && errno != EINTR)
                        {
                            perror("accept error!\n");
                            exit(1);
                        }
                        continue;
                    }
                    printf("客户端IP:%s    PORT:%d 连接\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
                    set_noblock(cfd);
                    event.events = EPOLLIN | EPOLLET;
                    event.data.fd = cfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, cfd ,&event);

                    if(--r_n <= 0)
                    {
                        break;
                    }
                }
                else//客户端发数据
                {
                    #if 0 //循环服务器
                    pthread_t client_id;
                    int ret = pthread_create(&client_id, NULL, readevent, (void *)cfd);
                    if (ret != 0)
                    {
                        perror("pthread_create error");
                        return -1;
                    }
                    pthread_detach(client_id); // 线程分离
                    #endif
                    int cfd = events[i].data.fd;
                    threadpool_add_task(pool, readevent, (void*)&cfd);
                }
            }          
        }
    }
    return 0;
}