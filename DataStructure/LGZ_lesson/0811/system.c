#include "SystemHead.h"

int main(int argc, char *argv[])
{
    // system("ls -ah");
    // system("cp test test.txt");

    char temp[20] = {0};
    char name[10] = {0};
    scanf("%s", name);
    sprintf(temp, "mkdir %s", name);
    // sprintf(temp, "rm -f %s", name);
    system(temp);

    return 0;
}