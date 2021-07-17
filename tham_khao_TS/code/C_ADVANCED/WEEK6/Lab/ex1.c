#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *matrix;
    int sizemax;
} Graph;

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
    int *output = (int *) malloc(sizeof(int));
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

int main(int argc, char const *argv[])
{
    int n, *output;
    scanf("%d", &n);
    Graph g = createGraph(n);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    n = 0;
    output = getAdjacentVertices(g, 1, &n);
    if (n == 0)
    {
        printf("Khong co dinh ke cua nut 1\n");
    }
    else
    {
        printf("Cac dinh ke cua nut 1: \n");
        for (int i = 0; i < n; i++)
        {
            printf("%5d", output[i]);
        }
    }

    printf("\n");

    dropGraph(g);
    free(output);

    return 0;
}
