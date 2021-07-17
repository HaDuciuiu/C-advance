#include<stdio.h>
#define MaxLength 100
typedef int ElType;
typedef struct
{
    ElType Elements[MaxLength];
    int Front , Rear;
}Queue;
void makeNull_Queue(Queue *Q)
{
    Q->Front = -1;
    Q->Rear = -1;
}
int Empty_Queue(Queue Q)
{
    return Q.Front ==-1;
}
int Full_Queue(Queue Q)
{
    return(Q.Rear - Q.Front +1)==MaxLength;
}
void EnQueue(ElType X , Queue *Q)
{
    if(!Full_Queue(*Q))
    {
        if(Empty_Queue(*Q))
            Q->Front =0;
        Q->Rear = Q->Rear+1;
        Q->Elements[Q->Rear] = X;
    }
    else printf("Queue da day\n");
}
ElType DeQueue(Queue *Q)
{
    ElType x;
    if(!Empty_Queue(*Q))
    {
        x = Q->Elements[Q->Front];
        Q->Front = Q->Front +1;
        if(Q->Front>Q->Rear)
        makeNull_Queue(Q);
        // Queue tro thanh rong
    }

    else printf("Queue bi rong\n");
    return x;
}