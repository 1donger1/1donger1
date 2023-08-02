#include <stdio.h>

/*
FILE *fopen(const char *path, const char *mode);
 功能：创建或者打开一个文件
 参数：
 path：文件名，如果只写文件名，默认就是当前路径，也可以添加路径
 mode：文件权限
 r 只读，如果文件不存在则报错
 r+ 读写，如果文件不存在则报错
 w 只写，如果文件不存在则创建，如果文件存在则清空
 w+ 读写，如果文件不存在则创建，如果文件存在则清空
 a 只写，如果文件不存在则创建，如果文件存在则追加
 a+ 读写，如果文件不存在则创建，如果文件存在则追加
返回值：
成功：文件指针
失败：NULL
*/

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen("/home/donger/QFphase/file.txt", "w");

    if (fp == NULL)
    {
        perror("fail to fopen");
        return -1;
    }

    fclose(fp);

    return 0;
}
