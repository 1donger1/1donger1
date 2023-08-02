/*
题目：企业发放的奖金根据利润提成。

利润(I)低于或等于10万元时，奖金可提10%；
利润高于10万元，低于20万元时，低于10万元的部分按10%提成，高于10万元的部分，可提成7.5%；
20万到40万之间时，高于20万元的部分，可提成5%；
40万到60万之间时高于40万元的部分，可提成3%；
60万到100万之间时，高于60万元的部分，可提成1.5%；
高于100万元时，超过100万元的部分按1%提成。
从键盘输入当月利润I，求应发放奖金总数？

程序分析：请利用数轴来分界，定位。注意定义时需把奖金定义成双精度浮点(double)型。
*/
#include <stdio.h>

#if 0
int main(int argc, char *argv[])
{
    double bonus;
    double bonus1, bonus2, bonus3, bonus4;
    printf("请输入您的金额：\n");
    scanf("%lf", &bonus);

    if (bonus <= 100000)
    {
        bonus = bonus * (1 + 0.1);
        printf("您的奖金为:%lf\n", bonus);
    }
    else if (bonus > 100000 && bonus <= 200000)
    {
        bonus1 = 100000 * 0.1 + (bonus - 100000) * (1 + 0.075);
        printf("您的奖金为:%lf\n", bonus1);
    }
    else if (bonus > 200000 && bonus <= 400000)
    {
        bonus2 = (bonus - 200000) * (1 + 0.005);
        printf("您的奖金为:%lf\n", bonus2);
    }
    else if (bonus > 400000 && bonus <= 600000)
    {
        bonus3 = (bonus - 400000) * (1 + 0.003);
        printf("您的奖金为:%lf\n", bonus3);
    }
    else if (bonus > 600000 && bonus <= 1000000)
    {
        bonus3 = (bonus - 600000) * (1 + 0.015);
        printf("您的奖金为:%lf\n", bonus3);
    }
    else if (bonus > 1000000)
    {
        bonus3 = (bonus - 1000000) * (1 + 0.01);
        printf("您的奖金为:%lf\n", bonus3);
    }

    return 0;
}
#endif

int main(int argc, char *argv[])
{
    double money;
    double bonus, bonus1, bonus2, bonus4, bonus6, bonus10;
    printf("你的净利润为:\n");
    scanf("%lf", &money);

    bonus1 = 100000 * 0.1;
    bonus2 = bonus1 + 100000 * 0.075;
    bonus4 = bonus2 + 200000 * 0.05;
    bonus6 = bonus4 + 200000 * 0.03;
    bonus10 = bonus6 + 400000 * 0.015;

    if(money <= 100000)
    {
        printf("第一档:\n");
        bonus = money * 0.1;
    }
    else if(money <= 200000)
    {
        printf("第二档:\n");
        bonus = bonus1 + (money - 100000) * 0.075;
    }
    else if(money <= 400000)
    {
        printf("第三档:\n");
        bonus = bonus2 + (money - 200000) * 0.05;
    }
    else if(money <= 600000)
    {
        printf("第四档:\n");
        bonus = bonus4 + (money - 400000) * 0.03;
    }
    else if(money <= 1000000)
    {
        printf("第五档:\n");
        bonus = bonus6 + (money - 600000) * 0.015;
    }
    else if (money > 1000000)
    {
        printf("第六档:\n");
        bonus = bonus10 + (money - 1000000) * 0.01;
    }
    
    printf("提成为:bonus = %lf\n", bonus);


    return 0;
}