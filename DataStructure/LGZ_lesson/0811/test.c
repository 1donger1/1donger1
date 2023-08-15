#include "SystemHead.h"

int main(int argc, char *argv[])
{
    printf("USER= %s\n", getenv("USER"));   
    printf("PASSWD= %s\n", getenv("PASSWD"));   
    
    return 0;
}