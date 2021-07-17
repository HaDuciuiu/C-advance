#ifndef __GRAPH_JRB_H__
#include <stdlib.h>
#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
#include "string.h"

#define INFINITIVE_VALUE 10000000

typedef struct
{
    JRB vertices;
    JRB edges;
} Graph;

Graph createGraph();
void addVertex(Graph g, int id, char *name);
void addEdge(Graph g, int v1, int v2, double weight);

char *getVertexName(Graph g, int id);
int getVertexId(Graph g, char *name);
double getEdgeValue(Graph g, int v1, int v2);
int hasEdge(Graph g, int v1, int v2);

Dllist incomingVertices(Graph g, int v);
Dllist outgoingVertices(Graph g, int v);

int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);

void dropGraph(Graph g);

void printfVertex(int v);
void BFS(Graph g, int source, int dest, void (*f)(int key));
void DFS(Graph g, int source, int dest, void (*f)(int key));
int isDAG(Graph g);
Dllist dll_min(Dllist list, JRB cost, JRB visited);
Dllist findPath(JRB parent, int source, int dest);
double shortestPath(Graph g, int source, int dest);

#endif
