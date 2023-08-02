#include <stdio.h>

/*
 fprintf ( 文件指针，格式字符串，输出表列）；
fscanf ( 文件指针，格式字符串，输入表列）；

函数功能:
从磁盘文件中读入或输出字符

fprintf 和printf函数类似：
printf是将数据输出到屏幕上（标准输出），
fprintf函数是将数据输出到文件指针所指定的文件中。

fscanf和scanf 函数类似：
scanf是从键盘（标准输入）获取输入，
fscanf是从文件指针所标示的文件中获取输入。

*/

/*
 #include <stdio.h>
int fseek(FILE *stream, long offset, int whence);
功能：设置文件位置指针的偏移量
参数：
stream：文件指针
offset：偏移量
可正可负也可为0
whence：相对位置
SEEK_SET 文件起始位置
SEEK_CUR 文件当前位置
SEEK_END 文件末尾位置（最后一个字符后面一个位置）
返回值：
成功：0
失败：‐1

rewind(fp) <==> fseek(fp, 0, SEEK_SET);


*/

int main(int argc, char *argv[])
{

    FILE *fp;

    char ch1 = 'a', ch2;
    int num1 = 50, num2;
    char string1[20] = "string", string2[20];
    float score1 = 58.5, score2;

    if ((fp = fopen("/home/donger/QFphase/file_ch10_06.txt", "w+")) == NULL)
    {
        perror("fail to fopen");
        return -1;
    }

    fprintf(fp, "%c %d %s %f\n", ch1, num1, string1, score1);
    fseek(fp, 0, SEEK_SET);

    fscanf(fp, "%c %d %s %f\n", &ch2, &num2, &string2, &score2);
    printf("%c %d %s %f\n", ch2, num2, string2, score2);

    fclose(fp);

    return 0;
}
