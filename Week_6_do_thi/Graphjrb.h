#include "jrb.h"
typedef JRB Graph;

Graph createGraph();
int adjacent(Graph G, char *v1, char *v2);
void addEdge(Graph graph, char *v1, char *v2);
int getAdjacentVertices(Graph graph, char *v, char **output);
void dropGraph(Graph G);
