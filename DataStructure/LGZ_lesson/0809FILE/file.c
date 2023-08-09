#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// /**
//  * @brief
//  * @param 文件路径(绝对路径)，直接写文件名，就是本文件夹路径
//  * @param r:只读，r+:读写，w:只写,a:追加写,a+追加读写
//  * @return r:文件不存在则返回空， w:文件不存在则创建，存在则清空
// */
// FILE *fopen(const char *pathname, const char *mode);
struct stu
{
    int id;
    int score;
};

int main(int argc, char *argv[])
{
    FILE *file = fopen("file.txt", "r+");
    if (file == NULL)
    {
        printf("file open fail!\n");
    }
    else
    {
        printf("file open success!\n");
    }

    char c = 0;
    // while ((c = fgetc(file)) != EOF)
    // {
    //     printf("%c", c);
    // }

    // char *str = "donger";
    // while (*str != '\0')
    // {
    //     fputc(*str, file);
    //     str++;
    // }
    // fputc('c', file);

    // // char str[100] = {0};
    // char str[100] = "nanjing";
    // // fgets(str, 20, file);//fgts读到换行符结束，或者读够字符量结束
    // fputs(str,file);
    // printf("read data is %s\n",str);

    // struct stu stu1 = {1, 100};
    // struct stu stu2 ;
    // // struct stu stu2 = stu1;
    // fwrite(&stu1, sizeof(struct stu), 1, file);
    // fseek(file, 0, SEEK_SET);

    // fread(&stu2, sizeof(struct stu), 1, file);
    // printf("read data %d %d\n",stu2.id, stu2.score);

    // fread(&stu1, sizeof(struct stu), 1, file);
    // printf("read data %d %d\n", stu1.id, stu1.score);

    // // int num = 0;
    // // char temp[20] = {0};
    // // fscanf(file, "%d %s", &num, temp);
    // // printf("%d %s\n", num, temp);
    // fprintf(file, "the student id is %d, score is %d\n", stu1.id, stu1.score);

    // fseek(file, 4, SEEK_SET);
    fseek(file, 0, SEEK_END);
    // char temp[10] = {0};
    // fgets(temp, 5, file);
    printf("%ld\n", ftell(file));

    fclose(file);
    return 0;
}
