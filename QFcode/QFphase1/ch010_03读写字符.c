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
 int fputc(int c, FILE *stream);
功能：向文件指针标识的文件中写入一个字符
参数：c：要写入的字符;stream：指定的文件指针
返回值：
成功：要写入的字符
失败：EOF
*/
void test_puts(FILE *fp)
{
    fp = fopen("/home/donger/QFphase/file.txt", "a");
    check(fp);

    // rewind(fp);
    fputc('\n', fp);
    fputc('a', fp);
    fputc('p', fp);
    fputc('p', fp);

    fclose(fp);
}

/*
int fgetc(FILE *stream);
功能：从文件指针标识的文件中读取一个字符
返回值：
成功：读取的字符
失败：EOF
如果文件读取完毕，也会返回EOF
*/

/*
void rewind(FILE *stream);
功能：将文件位置定位到起始位置
参数：stream：文件指针
返回值：无
*/
void test_getc(FILE *fp)
{

    fp = fopen("/home/donger/QFphase/file.txt", "r");
    check(fp);

    int c;

    // 读取单个字符
    c = fgetc(fp);
    printf("c = [%c] - %d\n", c, c);
    rewind(fp);

    printf("- - - - - - - - - -\n");

    // 读取全文
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c", c);
    }
    printf("\n");

    fclose(fp);
}

int main(int argc, char *argv[])
{
    FILE *fp;

    test_puts(fp);

    test_getc(fp);

    return 0;
}
