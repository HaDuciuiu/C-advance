#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	int * matrix;
	int sizemax;
} Graph;

Graph createGraph(int sizemax);
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int* output);
void dropGraph(Graph graph);

int main()
{
    int i, n, output[100];
    Graph g = createGraph(100);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    n = getAdjacentVertices (g, 1, output);
    if (n==0)
       printf("No adjacent vertices of node 1\n");
    else
    {   
       printf("Adjacent vertices of node 1:", n);
       for (i=0; i<n; i++)
           printf("%5d", output[i]);
    }
    dropGraph(g);
    getch();   
}

Graph createGraph(int sizemax)
{
   Graph g;
   g.sizemax = sizemax;
   g.matrix = (int*) malloc(sizemax*sizemax*sizeof(int));
   return g;
}

void addEdge(Graph graph, int v1, int v2)
{
     graph.matrix[v1*graph.sizemax+v2] = 1;
     graph.matrix[v2*graph.sizemax+v1] = 1;
}

int adjacent(Graph graph, int v1, int v2)
{
     return graph.matrix[v1*graph.sizemax+v2];       
}

int getAdjacentVertices (Graph graph, int v, int* output)
{
    int total = 0, i;   
    for (i=0; i<graph.sizemax; i++)
       if (adjacent(graph, v, i)) 
          output[total++] = i;
    return total;   
}

void dropGraph(Graph graph)
{
    free(graph.matrix);
    graph.matrix = NULL;
    graph.sizemax = 0;
}

