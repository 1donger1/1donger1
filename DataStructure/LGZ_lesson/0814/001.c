/**
 * IPC(inter process communication):进程间通信
 * 数据传输
 * 资源共享
 * 消息通知
 * 进程控制
 *
 *
 * 1.管道：无名管道，有名管道
 * (1)无名管道
 * 特点：
 *      a.半双工
 *      b.一头进，一头出，先进先出
 *      c.管道的数据只能读一次
 *      d.管道没有名字
 * (2)有名管道
 * int mkfifo(const char *__path, mode_t __mode)
 * 特点:
 *      a.有可见的本地文件
 *      b.完全不相关的两个程序能够进行通信
 *      c.这个文件不会被删除，下次可以继续进行使用
 * 2.消息队列: 消息的链表
 * 特点:
 *      a.有类型的
 *      b.有格式的
 *
 * 创建一个IPC键值
 * key_t ftok(const char *__pathname, int __proj_id)
 *
 * int msgget(key_t __key, int __msgflg)
 * __msgflg:访问权限
 *      a.IPC_CREAT | 0777
 *      b.返回值int:消息队列的唯一标识符
 *
 * ssize_t msgsnd(int __msqid, const void *__msgp, size_t __msgsz, int __msgflg)
 *  __msgflg:标识位
 *      a.IPC_NOWAIT:非阻塞
 *      b.0:阻塞
 *
 * int msgctl(int __msqid, int __cmd, struct msqid_ds *__buf)
 * cmd:
 *      IPC_SET:设置消息队列的属性
 *      IPC_STAT:获取属性
 *      IPC_RMID:删除消息队列
 * struct msqid_ds *__buf:
 *      存储消息队列的属性
 *
 * 3.信号
 * 4.信号量
 * 5.共享内存
 * 6.网络通信
 **/