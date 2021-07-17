#include <stdio.h>
#include<stdlib.h>
#define MaxLength 100
// typedef struct sinhvien
// {
//     char id[10];
//     char name[30];
//     float grade;
// }SV;
typedef char ElementType;
typedef struct
{
    ElementType Elements[MaxLength];
    int Front, Rear;
} Queue;

void MakeNullQueue(Queue *Q)
{
    Q->Front = -1;
    Q->Rear = -1;
}

int EmptyQueue(Queue Q)
{
    return Q.Front == -1;
}

int FullQueue(Queue Q)
{
    // return (Q.Rear - Q.Front + 1) == MaxLength;
    return (Q.Rear - Q.Front + 1) % MaxLength == 0;
}

void EnQueue(ElementType X, Queue *Q)
{
    if (!FullQueue(*Q))
    {
        if (EmptyQueue(*Q))
        {
            Q->Front = 0;
        }

        Q->Rear = (Q->Rear + 1) % MaxLength;
        Q->Elements[Q->Rear] = X;

        // Q->Elements[++(Q->Rear)] = X;
    }
    else
    {
        printf("Queue is full!");
    }
}

ElementType DeQueue(Queue *Q)
{
    ElementType e;

    if (!EmptyQueue(*Q))
    {
        e = Q->Elements[Q->Front];
        // Q->Front++;
        Q->Front = (Q->Front + 1) % MaxLength;
        if (Q->Front > Q->Rear)
        {
            MakeNullQueue(Q);
        }
        return e;
    }
    else
    {
        printf("Queue is empty!");
    }
}
