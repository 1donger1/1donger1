// #include <stdio.h>
// #include <stdlib.h>

// #define ElementType int
// #define MAX 10

// // 栈满情况(rear+1) % MAX == front(有个位置用不了);栈空条件:front == rear

// // 若一定要将队列用满，则需要条件判断，设置标识位
// // rear % MAX == front &&flag == 1;
// // front == rear &&flag == 0;

// struct Queue
// {
//     ElementType data[MAX];
//     int front;
//     int rear;
//     int len;
//     ElementType frontData;
// };

// int InitQueue(struct Queue *q)
// {
//     q->front = 0;
//     q->rear = 0;
//     q->len = 0;
//     // int flag = 0;//
// }

// void push(struct Queue *q, ElementType element)
// {
//     // if(q->rear == q->front && q->flag == 1)//
//     if (q->len == MAX)
//     {
//         printf("the queue is full!\n");
//         return;
//     }
//     q->data[q->rear] = element;
//     q->rear++;
//     q->rear = q->rear % MAX;
//     q->len++;
// }

// ElementType *Pop(struct Queue *q)
// {   
//     // if(q->rear==q->front&&q->flag==0)//
//     if (q->len == 0)
//     {
//         printf("the queue is empty!\n");
//         return NULL;
//     }

//     q->frontData = q->data[q->front];
//     q->len--;
//     q->front++;
//     q->front = q->front % MAX;
//     return &q->frontData;
// }