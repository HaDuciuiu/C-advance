#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
typedef struct 
{
    int *matrix;
    int sizemax;
}Graph;
// ham khoi tao mot ma tran
Graph createGraph(int sizemax)
{
    Graph graph;
    graph.matrix = (int*)calloc((sizemax*sizemax),sizeof(int));
    graph.sizemax = sizemax;
    return graph;
}
// ham them mot canh vao do thi
void addEdge(Graph graph,int v1,int v2)
{
    graph.matrix[v1*graph.sizemax+v2] = 1;
    graph.matrix[v2*graph.sizemax+v1] = 1;

}
// ham kiem tra hai dinh v1 , v2 co ke nhau khong
int adjacent(Graph graph , int v1 ,int v2)
{
    if(graph.matrix[v1*graph.sizemax+v2]==1)
        return 1;
    return 0;
}
// ham tra ve tap cac dinh ke
int getAdjacentVertices(Graph graph, int vertex, int* output)
{
    int i,dem=0;
    for(i=0;i<graph.sizemax;i++)
    {
        if(graph.matrix[vertex*graph.sizemax+i]==1)
        {
            output[dem] = i ;
            dem++;
        }
    }
    return dem;
}
// ham giai phong bo nho
void dropGraph(Graph graph)
{
    free(graph.matrix);
}
// ham duyet cay theo chieu rong
void BFS(Graph graph , int s)
{
    int visited[graph.sizemax];
    int i;
    for(i=0;i<graph.sizemax;i++)
    {
        visited[i] = -1;
    }
    Queue Q;
    makeNull_Queue(&Q);
    EnQueue(s,&Q);
    int adj[graph.sizemax];
    while (!Empty_Queue(Q))
    {
        int u = DeQueue(&Q);
        if(visited[u]!=-1)
        {
            int dem = getAdjacentVertices(graph,u,adj);
            visited[u] = 1;
            for(i=0;i<dem;i++)
            {
                int v = adj[i];
                if(visited[v]==-1) {
                    EnQueue(v,&Q);
                    printf("%d\n",v);
                } 
            }
        }
    }
    

}

int main()
{
    int i, n, output[100];
    Graph g = createGraph(100);
    addEdge(g,0,1);   
    addEdge(g,0,2);
    addEdge(g,1,2);
    addEdge(g,1,3);
    addEdge(g,0,4);
    addEdge(g,2,3);
    //n = getAdjacentVertices(g,1,output);
    /*if(n==0)
        printf("Khong co dinh ke cua nut 1\n");
    else {
        printf("Cac dinh ke cua nut 1 :\n");
        for(i=0;i<n;i++)
        {
           printf("%d\n",output[i]);
        }
    }*/
    BFS(g,1);
    dropGraph(g);
    return 0;
}