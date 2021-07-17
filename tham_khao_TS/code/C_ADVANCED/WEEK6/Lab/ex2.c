#include "../../libfdr/jrb.h"
#include <stdio.h>
#include <stdlib.h>
typedef JRB Graph;

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

int main(int argc, char const *argv[])
{
    Graph g = createGraph();
    int *output, n = 0;

    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);

    output = getAdjacentVertices(g, 1, &n);

    printf("Cac dinh ke voi dinh 1: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%5d", output[i]);
    }

    dropGraph(g);

    printf("\n");
    return 0;
}
