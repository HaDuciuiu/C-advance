#include "../../libfdr/jrb.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../libfdr/dllist.h"
#define SIZE_MAX 6
typedef Dllist Queue;

typedef JRB Graph;

Queue q;

void printVertex(int v)
{
     printf("%4d", v);
}

Graph createGraph()
{
    Graph g = make_jrb();
    return g;
}

void addEdge(Graph g, int v1, int v2)
{
    JRB Node = jrb_find_int(g, v1);
    JRB tree;
    if (Node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(g, v1, new_jval_v(tree));
    }
    else
    {
        tree = (JRB)jval_v(Node->val);
    }
    jrb_insert_int(tree, v2, new_jval_i(1));

    Node = jrb_find_int(g, v2);
    if (Node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(g, v2, new_jval_v(tree));
    }
    else
    {
        tree = (JRB)jval_v(Node->val);
    }
    jrb_insert_int(tree, v1, new_jval_i(1));
}

int *getAdjacentVertices(Graph g, int v1, int *nFind)
{
    *nFind = 0;
    int *output;
    JRB Node = jrb_find_int(g, v1);
    if (Node == NULL)
    {
    }
    else
    {
        output = (int *)malloc(sizeof(int));
        JRB tree = (JRB)jval_v(Node->val);
        jrb_traverse(Node, tree)
        {
            output = (int *)realloc(output, (++(*nFind)) * sizeof(int));
            output[(*nFind) - 1] = jval_i(Node->key);
        }
    }

    return output;
}

void dropGraph(Graph g)
{
    JRB Node;
    jrb_traverse(Node, g)
        jrb_free_tree(jval_v(Node->val));

    jrb_free_tree(g);
}

void BFS(Graph g, int start, int stop, void (*func)(int))
{
    int *visited = (int *)calloc(SIZE_MAX, sizeof(int));
    int u;
    int *adj;
    int nFind = 0;

    Enqueue(&q, new_jval_i(start));

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
    Graph g = createGraph();

    q = new_dllist();

    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);

    printf("BFS: ");
    BFS(g, 1, 2, printVertex);

    printf("\n");
    dropGraph(g);

    return 0;
}
