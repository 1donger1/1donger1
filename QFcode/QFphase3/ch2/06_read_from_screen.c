#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// 使用read函数从终端读取数据

//使用0这个文件描述符从终端读取数据
//如果终端输入的字节数大于第三个参数对应的字节数，则只会读取第三个对应的字节数，返回值也是与第三个参数一致

//如果终端输入的字节数小于第三个参数，则只会读取输入的数据加上换行符，返回值就是实际输入的数据+1
int main(int argc, char *argv[])
{
    ssize_t bytes;
    char str[32] = "";
    if((bytes = read(0, str, 6)) == -1)
    {
        perror("fail to read");
        return -1;
    }

    printf("str = [%s]\n", str);
    printf("bytes = %ld\n", bytes);

    return 0;
}