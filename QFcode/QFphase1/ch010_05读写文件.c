#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int a;
    int b;
    char c;
} MSG;

void check(FILE *fp)
{
    if (fp == NULL)
    {
        perror("fail to fopen");
        exit(1);
    }
}

/*
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
功能：向文件中写入数据
参数：
ptr：要写入的数据
size：一次写入的字节数
nmemb：一共写入的次数
stream：文件指针
返回值：
成功：实际写入的次数
失败：0
*/
void test_fwrite(FILE *fp)
{
    fp = fopen("/home/donger/QFphase/file_r&w.txt", "a");
    check(fp);

    MSG msg[4] = {1, 2, 'a', 3, 4, 'b',
                  5, 6, 'c', 7, 8, 'd'};

    fwrite(msg, sizeof(MSG), 4, fp);

    fclose(fp);
}

/*
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
功能：从文件中读取数据
参数：
ptr：保存读取的数据
size：每次读取的字节数
nmemb：一共读取的次数
stream：文件指针
返回值：
成功：实际读取的次数（对象数、块数）
失败：0
如果文件内容读取完毕，返回0
*/
void test_fread(FILE *fp)
{
    fp = fopen("/home/donger/QFphase/file_r&w.txt", "r");
    check(fp);

    int num;
    char buf[128] = "";

    num = fread(buf, 10, 6, fp);
    printf("buf = %s\n", buf);
    printf("num = %d\n", num);

    fclose(fp);
}

int main(int argc, char *argv[])
{
    FILE *fp;

    test_fwrite(fp);
    test_fread(fp);

    return 0;
}
