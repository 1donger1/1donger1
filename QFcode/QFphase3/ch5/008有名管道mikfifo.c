#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

/*有名管道的创建
 方法1：用过shell命令mkfifo创建有名管道
        mkfifo 文件名
 方法2：使用函数mkfifo
    #include <sys/types.h>
    #include <sys/stat.h>
    int mkfifo(const char *pathname, mode_t mode);
    功能：创建一个有名管道，产生一个本地文件系统可见的文件pathname
    参数：
        pathname：有名管道创建后生成的文件，可以带路径
        mode：管道文件的权限，一般通过八进制数设置即可，例如0664
    返回值：
        成功：0
        失败：‐1
*/

int main(int argc, char *argv[])
{
    // 通过mikfifo函数创建有名管道
    if (mkfifo("008-file", 0664) == -1)
    {
        // printf("errno = %d\n", errno);//17-->EEXIST
        //  如果管道文件已经存在，不需要报错退出，直接使用即可。
        //  在使用 pipe 函数时，它会在管道文件已经存在的情况下正确返回管道的文件描述符，并不会导致错误。
        //  因此，我们无需在错误输出之前进行任何处理，直接调用 pipe 函数即可。
        if (errno != EEXIST)
        {
            perror("fail to mikfifo\n");
            exit(1);
        }
    }

    return 0;
}