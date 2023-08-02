#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool Is_prime(int num)
{
    if (num <= 1)
    {
        return false;
    }

    // for (int i = 2; i <= sqrt(num); i++)//用<=是考虑质数可以是完全平方数
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    int i, k=0;
    for (i = 2; i <= 100; i++)
    {
        if(Is_prime(i))
        {
            printf("%3d", i);
            k++;
            if (k % 5 == 0)
            {
                printf("\n");
            }
        }
        
    }

        return 0;
}
