#ifndef __GRAPH_JRB_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"dllist.h"

#define INFINITIVE_VALUE 10000000

typedef struct
{
    JRB vertices;
    JRB edges;
}Graph;

Graph createGraph();

void addVertex(Graph g , int id , char *name);
// add edge with weight
void addEdge(Graph g , int v1 , int v2 , double weight);
// find name with id
char *getVertexName(Graph g , int id);

// get id by name
int getVertexId(Graph g , char *name);

// get the value of edge by two vertices of the edge
double getEdgeValue(Graph g , int v1 , int v2);

// check for has or hasn't the edge consume of two vertices v1 - v2
int hasEdge(Graph g , int v1 , int v2);

// find the set of vertices that incoming the vertice v
Dllist incomingVertices(Graph g , int v);

// find the set of vertices that outcoming the vertice v
Dllist outgoingVertices(Graph g , int v);

// find the set vertices that are indegree of vertice v
int indegree(Graph graph , int v , int *output);

// find the set vertices that are outdegree of vertice v
int outdegree(Graph graph , int v , int *output);

void dropGraph(Graph g);

// display a vertice in the format
void printfVertex(int v);
// breath traverser graph
void BFS(Graph g , int source , int dest , void (*f)(int key));
// void (*f)(int key) is a function pointer
// deepth traverser graph
void DFS(Graph g , int source , int dest , void (*f)(int key));
// check for : hasn't a cycle in the graph?
int isDAG(Graph g);
// find the webpage have minimum of linked
Dllist dll_min(Dllist list , JRB cost , JRB visited);
// find path form 2 webpages
Dllist findPath(JRB parent , int source , int dest);
// find the shortest path from source vertice to dest vertice
double shortestPath(Graph g , int source , int dest);
#endif

