#include <stdio.h>
#include <stdlib.h>

void check(FILE *fp)
{
    if (fp == NULL)
    {
        perror("fail to fopen");
        exit(1);
    }
}

/*
int fputs(const char *s, FILE *stream);
功能：向文件写入数据
参数：s：要写入的内容；stream：文件指针
返回值：
成功：写入文件内容的字节数
失败：EOF
*/
void test_puts(FILE *fp)
{
    fp = fopen("/home/donger/QFphase/file.txt", "a");
    check(fp);

    fputs("\n这是追加的\n", fp);

    fclose(fp);
}

/*
char *fgets(char *s, int size, FILE *stream);
功能：从文件中读取内容
参数：s：保存读取到的内容;size：每次读取的最大个数;stream：文件指针
返回值：
成功：读取的数据的首地址
失败：NULL
如果文件内容读取完毕，也返回NULL
注意：
从stream所指的文件中读取字符，在读取的时候碰到换行符或者是碰到文件的末尾停止读取，
或者是读取了size‐1个字节停止读取，在读取的内容后面会加一个\0,作为字符串的结尾


*/
void test_gets(FILE *fp)
{

    fp = fopen("/home/donger/QFphase/file_str.txt", "r");
    check(fp);

    char buf[32] = "";
    fgets(buf, 32, fp);
    printf("buf = %s\n", buf);

    fclose(fp);
}

int main(int argc, char *argv[])
{
    FILE *fp;

    test_puts(fp);
    test_gets(fp);

    return 0;
}
