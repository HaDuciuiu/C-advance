#include "../../libfdr/jrb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../libfdr/dllist.h"
#define SIZE_MAX 6
#define MAX 30
#define INFINITIVE_VALUE 10000000
typedef Dllist Queue;

Queue q;

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

int readDataFromFile(char *filename, Graph g, int *v)
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

void BFS(Graph g, int start, int dest, int v, int pred[], int dist[])
{
    int *visited = (int *)calloc(v, sizeof(int));
    int u;
    int adj[MAX];
    int nFind = 0;

    for (int i = 0; i < v; i++)
    {
        dist[i] = INFINITIVE_VALUE;
        pred[i] = -1;
    }

    dist[start] = 0;
    visited[start] = 1;
    Enqueue(&q, new_jval_i(start));

    while (!dll_empty(q))
    {
        u = Dequeue(&q);
        nFind = getAdjacentVertices(g, u, adj);

        for (int i = 0; i < nFind; i++)
        {
            if (visited[adj[i]] == 0)
            {
                visited[adj[i]] = 1;
                dist[adj[i]] = dist[u] + 1;
                pred[adj[i]] = u;
                Enqueue(&q, new_jval_i(adj[i]));

                if (adj[i] == dest)
                    return;
            }
        }
    }
    free(visited);
}

int main(int argc, char const *argv[])
{
    Graph g = createGraph();

    int n, v, length;

    char noiDi[MAX], noiDen[MAX];
    int start, dest;

    q = new_dllist();
    readDataFromFile("data.txt", g, &v);

    int pred[v];
    int dist[v];
    int tmp[MAX], path[MAX];

    printf("Nhap noi di: ");
    scanf("%[^\n]%*c", noiDi);
    printf("Nhap noi den: ");
    scanf("%[^\n]%*c", noiDen);

    JRB temp;
    jrb_traverse(temp, g.vertices)
    {
        if (strcmp(jval_s(temp->val), noiDi) == 0)
        {
            start = jval_i(temp->key);
        }
        else if (strcmp(jval_s(temp->val), noiDen) == 0)
        {
            dest = jval_i(temp->key);
        }
    }

    BFS(g, start, dest, v, pred, dist);

    int total = dist[dest];
    if (total != INFINITIVE_VALUE)
    {
        tmp[0] = dest;
        n = 1;
        while (dest != start)
        {
            dest = pred[dest];
            tmp[n++] = dest;
        }
        for (int i = n - 1; i >= 0; i--)
            path[n - i - 1] = tmp[i];
        length = n;
    }

    printf("Duong di ngan nhat tu %s den %s la: ", noiDi, noiDen);
    for (int i = 0; i < length; i++)
    {
        printf("%s ", getVertex(g, path[i]));
    }

    printf("\n");
    dropGraph(g);
    free_dllist(q);

    return 0;
}
