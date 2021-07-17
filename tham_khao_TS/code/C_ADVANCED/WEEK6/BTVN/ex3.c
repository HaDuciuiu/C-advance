#include "../../libfdr/jrb.h"
#include "../../libfdr/dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

char *getVertex(Graph graph, int id)
{
    JRB Node = jrb_find_int(graph.vertices, id);

    if (Node != NULL)
    {
        return jval_s(Node->val);
    }
}

void addEdge(Graph g, int v1, int v2)
{
    JRB Node = jrb_find_int(g.edges, v1);
    JRB tree;
    if (Node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
    }
    else
    {
        tree = (JRB)jval_v(Node->val);
    }
    jrb_insert_int(tree, v2, new_jval_i(1));

    Node = jrb_find_int(g.edges, v2);
    if (Node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(g.edges, v2, new_jval_v(tree));
    }
    else
    {
        tree = (JRB)jval_v(Node->val);
    }
    jrb_insert_int(tree, v1, new_jval_i(1));
}

int getAdjacentVertices(Graph g, int v1, int output[])
{
    int nFind = 0;
    JRB Node = jrb_find_int(g.edges, v1), Node_Temp;
    if (Node != NULL)
    {
        JRB tree = (JRB)jval_v(Node->val);
        jrb_traverse(Node, tree)
        {
            output[nFind++] = jval_i(Node->key);
        }
    }

    return nFind;
}

void dropGraph(Graph g)
{
    JRB tmp, tree;
    jrb_traverse(tmp, g.edges)
    {
        tree = (JRB)jval_v(tmp->val);
        jrb_free_tree(tree);
    }

    jrb_free_tree(g.edges);
    jrb_free_tree(g.vertices);
}

int readDataFromFile(char *filename, Graph g)
{
    int line = 0;
    char tmp[15], u[30], p[30], q[30], *token;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Error!!!\n");
        return 1;
    }
    else
    {
        while (!feof(f))
        {
            fscanf(f, "%[^\n]%*c", u);
            if (strcmp(u, "[STATIONS]") != 0)
            {
                if (strcmp(u, "[LINES]") != 0)
                {
                    sscanf(u, "%[^=]=%[^\n]%*c", p, q);
                    if (!line)
                    {
                        jrb_insert_int(g.vertices, p[1] - '0', new_jval_s(strdup(q)));
                    }
                    else
                    {
                        Dllist tmp;
                        char data[20];
                        Dllist dl = new_dllist();
                        token = strtok(q, " ");
                        // loop through the string to extract all other tokens
                        while (token != NULL)
                        {
                            dll_append(dl, new_jval_s(strdup(token))); //printing each token
                            token = strtok(NULL, " ");
                        }

                        for (tmp = dl->flink; tmp != dl->blink; tmp = tmp->flink)
                        {
                            addEdge(g, jval_s(tmp->val)[1] - '0', jval_s(tmp->flink->val)[1] - '0');
                        }

                        free_dllist(dl);
                    }
                }
                else
                {
                    line = 1;
                    continue;
                }
            }
        }
        fclose(f);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    Graph g = createGraph();
    int output[MAX];

    readDataFromFile("data.txt", g);

    char tmp[30], name[30];
    printf("Lay Ten Cac Nha Ga Ngay Canh Cua: ");
    scanf("%s%*c", tmp);

    int labelVertexFind = -1;

    JRB temp;
    jrb_traverse(temp, g.vertices)
    {
        if (strcmp(jval_s(temp->val), tmp) == 0)
        {
            labelVertexFind = jval_i(temp->key);
            break;
        }
    }

    if (labelVertexFind != -1)
    {
        int n = getAdjacentVertices(g, labelVertexFind, output);
        if (n > 0)
        {
            for (int i = 0; i < n; i++)
            {
                printf("%s ", getVertex(g, output[i]));
            }
        }
        else
        {
            printf("Khong co dinh ke nao cua %s\n", tmp);
        }
    }
    else
    {
        printf("Dinh khong ton tai!!!\n");
    }

    dropGraph(g);

    printf("\n");
    return 0;
}
