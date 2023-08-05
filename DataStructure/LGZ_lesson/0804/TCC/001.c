while (1)
{
    int choice;
    printf("********************carStop*******************\n");
    printf("1.车辆进入停车场\n");
    printf("2.车辆离开停车场\n");
    printf("3.显示停车场信息\n");
    printf("4.显示便道信息\n");
    printf("5.退出系统\n");
    scanf("%d", &choice);
    {
        struct Node *TravelPoint;
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
            DisplayPavement(&pavement);
            break;
        case 5:
            TravelPoint = pavement.queue.head;
            while (TravelPoint != NULL)
            {
                struct Car *car = (struct Car *)TravelPoint->data;
                FreeCar(car);
                TravelPoint = TravelPoint->next;
            }
            FreeQueue(&pavement);
            TravelPoint = carStop.stack.head;
            while (TravelPoint != NULL)
            {
                struct Car *car = (struct Car *)TravelPoint->data;
                FreeCar(car);
                TravelPoint = TravelPoint->next;
            }
            FreeLStack(&carStop);
            break;
        default:
            break;
        }
    }
}
