#include <signal.h>
#include <stdio.h>
//#include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>
/*
int sigemptyset(sigset_t *set);
功能：将信号集 set 初始化为空集，即清空信号集中的所有信号。
返回值：若成功执行，返回 0；若出现错误，返回 -1。
------------------------------------------------------------------
int sigfillset(sigset_t *set);
功能：将信号集 set 设置为包含所有信号。
返回值：若成功执行，返回 0；若出现错误，返回 -1。
------------------------------------------------------------------
int sigismember(const sigset_t *set, int signum);
功能：检查信号 signum 是否在信号集 set 中。
参数：
const sigset_t *set：指向要检查的信号集的指针。
int signum：要检查的信号编号。
返回值：若信号 signum 存在于信号集 set 中，返回 1；若不存在，返回 0；若出现错误，返回 -1。
------------------------------------------------------------------
int sigaddset(sigset_t *set, int signum);
功能：将信号 signum 加入信号集 set 中。
参数：
sigset_t *set：指向要修改的信号集的指针。
int signum：要添加的信号编号。
返回值：若成功执行，返回 0；若出现错误，返回 -1。
------------------------------------------------------------------
int sigdelset(sigset_t *set, int signum);
功能：从信号集 set 中移除信号 signum。
参数：
sigset_t *set：指向要修改的信号集的指针。
int signum：要移除的信号编号。
返回值：若成功执行，返回 0；若出现错误，返回 -1。

这些函数在处理信号集时非常有用，可以用于初始化、设置、清空、查询和修改信号集。
sigset_t 是一个数据类型，用来表示信号集，通常是一个位向量。
在使用这些函数之前，通常需要通过 sigemptyset 初始化一个空的信号集，并通过 sigaddset 或 sigfillset 将信号添加到信号集中。
然后可以使用 sigismember 来检查特定信号是否在信号集中，使用 sigdelset 删除信号，以及其他操作。
*/

int main(int argc, char *argv[])
{
    // 创建一个信号集
    sigset_t set;
    int ret = 0;

    // 初始化一个空的信号集
    sigemptyset(&set);

    // 判断SIGINT信号是否在信号集中
    ret = sigismember(&set, SIGINT);
    if (ret == 0)
    {
        printf("SIGINT is not a member of sigprocmask \nret = %d\n", ret);
    }

    // 将指定的信号添加到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    ret = sigismember(&set, SIGINT);
    if (ret == 1)
    {
        printf("SIGINT is a member of sigprocmask \nret = %d\n", ret);
    }

    return 0;
}