#include <stdio.h>
#include <stdlib.h>
#include "../../libfdr/dllist.h"
#define SIZE_MAX 6

typedef struct
{
    int *matrix;
    int sizemax;
} Graph;

typedef Dllist Queue;

Queue q;

void printVertex(int v)
{
     printf("%4d", v);
}

Graph createGraph(int sizemax)
{
    Graph graph;
    graph.sizemax = sizemax;
    graph.matrix = (int *)calloc(sizemax * sizemax, sizeof(int));
    return graph;
}

void addEdge(Graph g, int v1, int v2)
{
    g.matrix[v1 * g.sizemax + v2] = g.matrix[v2 * g.sizemax + v1] = 1;
}

int adjacent(Graph g, int v1, int v2)
{
    if (g.matrix[v1 * g.sizemax + v2] == 1)
    {
        return 1;
    }

    return 0;
}

int *getAdjacentVertices(Graph g, int v1, int *nFind)
{
    *nFind = 0;
    int *output = (int *)malloc(sizeof(int));
    for (int i = 0; i < g.sizemax; i++)
    {
        if (g.matrix[v1 * g.sizemax + i] == 1)
        {
            output = (int *)realloc(output, (++(*nFind)) * sizeof(int));
            output[(*nFind) - 1] = i;
        }
    }
    return output;
}

void dropGraph(Graph g)
{
    free(g.matrix);
    g.sizemax = 0;
}

void Enqueue(Queue *q, Jval jval)
{
    dll_append(*q, jval);
}

int Dequeue(Queue *q)
{
    Queue tmp = dll_first(*q);
    int v = jval_i(tmp->val);
    dll_delete_node(tmp);
    return v;
}

void BFS(Graph g, int start, int stop, void (*func)(int))
{
    int *visited = (int *)calloc(g.sizemax, sizeof(int));
    // int *grayNode = (int *)calloc(g.sizemax, sizeof(int));
    int u;
    int *adj;
    int nFind = 0;

    Enqueue(&q, new_jval_i(start));
    // grayNode[s] = 1;

    while (!dll_empty(q))
    {
        u = Dequeue(&q);
        if (visited[u] == 0)
        {
            func(u);
            visited[u] = 1;
            if(u == stop) return;
            adj = getAdjacentVertices(g, u, &nFind);

            for (int i = 0; i < nFind; i++)
            {
                if (visited[adj[i]] == 0)
                {
                    Enqueue(&q, new_jval_i(adj[i]));
                }
            }
            free(adj);
        }
    }

    free(visited);
}

int main(int argc, char const *argv[])
{
    Graph g = createGraph(SIZE_MAX);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    q = new_dllist();

    printf("BFS: ");
    BFS(g, 1, -1, printVertex);

    printf("\n");

    dropGraph(g);

    return 0;
}