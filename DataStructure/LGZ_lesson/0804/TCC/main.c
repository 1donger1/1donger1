#include <stdio.h>
#include <stdlib.h>
#include "MyString.h"
#include "LinkStack.h"
#include "LQueue.h"
#include "DoubleLinkList.h"
#define Max_Size 3
#define true 1
#define false 0

struct Car
{
    MyString name;
    double arriveTime;
    double leaveTime;
};

struct Car *CreateCar(const char *name, double arriveTime)
{
    struct Car *newCar = (struct Car *)malloc(sizeof(struct Car));
    if (newCar == NULL)
    {
        printf("Create malloc error\n");
        return NULL;
    }

    // Init_MyString(newCar->name, name);
    Initize(&newCar->name, name);
    newCar->arriveTime = arriveTime;
    return newCar;
};

void FreeCar(struct Car *car)
{
    if (car == NULL)
    {
        return;
    }
    FreeMystring(&car->name);
    free(car);
}

void Come_Car(LStack *CarStop, LQueue *pavement)
{
    char CarName[100] = {0};
    double arriveTime = 0.0;
    printf("请输入车牌号:");
    scanf("%s", CarName);
    printf("请输入到达时间:");
    scanf("%lf", &arriveTime);
    struct Car *newCar = CreateCar(CarName, arriveTime);

    if (newCar == NULL)
    {
        printf("Create car error!\n");
        return;
    }

    if (CarStop->stack.len < Max_Size)
    {
        Push(CarStop, newCar);
        printf("当前停车场未满，车辆|%s|停在了停车场的%d个位置\n", newCar->name.string, CarStop->stack.len);
    }
    else
    {
        QPush(pavement, newCar);
        printf("当前停车场已满，车辆|%s|停在了便道的%d个位置\n", newCar->name.string, pavement->queue.len);
    }
}

void Leave_Car(LStack *CarStop, LQueue *pavement)
{
    char CarName[100] = {0};
    printf("请输入要离开的车牌号:");
    scanf("%s", CarName);
    Init_MyString(LeaveCarName, CarName);

    LStack TempStack;
    InitLStack(&TempStack);

    double LeaveCarTime = 0;
    while (IsEmpty(CarStop) == false)
    {
        struct Car *car = (struct Car *)*Pop(CarStop);
        if (car->name.IsEqual(&car->name, &LeaveCarName) == true)
        {
            printf("请输入离开的时间内");
            scanf("%lf", &car->leaveTime);
            LeaveCarTime = car->leaveTime;
            printf("车辆%s将要离场,到达时间是%lf,离开时间是%lf,停车费用为%lf\n", car->name.string, car->arriveTime, car->leaveTime, (car->leaveTime - car->arriveTime) * 5);

            FreeCar(car);
            break;
        }
        Push(&TempStack, car);
    }

    while (IsEmpty(&TempStack))
    {
        Push(CarStop, *Pop(&TempStack));
    }
    if (CarStop->stack.len < Max_Size)
    {
        if (IsQEmpty(pavement) == false)
        {
            struct Car *car = (struct Car *)*LQPop(pavement);
            car->arriveTime = LeaveCarTime;
            Push(CarStop, car);
            printf("便道上的车|%s|进入了停车场，时间为%lf", car->name.string, car->arriveTime);
        }
    }
    else
    {
        printf("未找到输入的车牌！\n");
    }
}

void DisplayCarStop(LStack *carStop)
{
    LNode *TravePoint = carStop->stack.head;
    while (TravePoint != NULL)
    {
        struct Car *car = (struct Car *)TravePoint->data;
        printf("车牌:|%s| 到达时间:%lf\n ", car->name.string, car->arriveTime);
        TravePoint = TravePoint->next;
    }
    printf("\n");
}

void DisplayPavemen(LQueue *pavement)
{
    LNode *TravePoint = pavement->queue.head;
    while (TravePoint != NULL)
    {
        struct Car *car = (struct Car *)TravePoint->data;
        printf("车牌:|%s| 到达时间:%lf\n ", car->name.string, car->arriveTime);
        TravePoint = TravePoint->next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    LStack carStop;
    InitLStack(&carStop);

    LQueue pavement;
    InitLQueue(&pavement);

    int choice = 0;
    scanf("%d", &choice);
    printf("****************CarStop*********************\n");
    printf("1.车辆进入停车场\n");
    printf("2.车辆离开停车场\n");
    printf("3.显示停车场信息 \n");
    printf("4.显示通道信息\n");
    printf("5.退出系统\n");
    while (1)
    {
        switch (choice)
        {
        case 1:
            Come_Car(&carStop, &pavement);
            break;
        case 2:
            Leave_Car(&carStop, &pavement);
            break;
        case 3:
            DisplayCarStop(&carStop);
            break;
        case 4:
            DisplayPavemen(&pavement);
            break;
        case 5:
            LNode *TravePoint = pavement.queue.head;
            while (TravePoint != NULL)
            {
                struct Car *car = (struct Car *)TravePoint->data;
                FreeCar(car);
                TravePoint = TravePoint->next;
            }
            FreeQueue(&pavement);

            TravePoint = carStop.stack.head;
            while (TravePoint != NULL)
            {
                struct Car *car = (struct Car *)TravePoint->data;
                FreeCar(car);
                TravePoint = TravePoint->next;
            }
            FreeLStack(&carStop);
            return 0;
        default:
            break;
        }
    }
    return 0;
}