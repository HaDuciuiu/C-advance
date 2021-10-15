#include <stdio.h>
#include <stdlib.h>

#include "PageRank.h"
// ham tim gia tri nho nhat cua mot mang so
int Min(int A[], int n)
{
    int min = A[0], i;
    for (i = 1; i < n; i++)
    {
        if (min > A[i])
        {
            min = A[i];
        }
    }
    return min;
}
// ham tim gia tri lon nhat cua mot mang so
int Max(int A[], int n)
{
    int max = A[0], i;
    for (i = 1; i < n; i++)
    {
        if (max < A[i])
            max = A[i];
    }
    return max;
}
// ham sap xep chon
void selection_sort(double A[], int n)
{
    int min, i, j;
    double tmp;
    for (i = 0; i < n - 2; i++)
    {
        min = i;
        for (j = i; j <= n - 1; j++)
        {
            if (A[min] > A[j])
                min = j;
        }
        tmp = A[i];
        A[i] = A[min];
        A[min] = tmp;
    }
}
// ham doc file theo dinh dang de bai
void readFile(Graph g, FILE *ptr, FILE *fptr, int *n, JRB Path)
{
    if (ptr == NULL || fptr == NULL)
    {
        printf("Cannot open file\n");
        exit(0);
    }
    int a, m, B, A[50];
    int i = 0, j = 0;
    char c;
    char s[250];
    fscanf(ptr, "%d%*c", n);
    while (fscanf(ptr, "%s%d%*c", s, &a) == 2)
    {
        addVertex(g, a, s);
        // them mot dinh voi khoa la id cua website , gia tri la ten web
        jrb_find_int(Path, a, new_jval_i(1));
        // them id cua website vao Path
        printf("%s\t%d\n", s, a);
    }
    fscanf(fptr, "%d%*c", &m); // doc so luong website
    while (j != m)
    {
        fscanf(fptr, "%d%c", &B, &c);
        while (fscanf(fptr, "%d%c", &A[i], &c) == 2)
        {
            printf("%d\t", A[i]);
            addEdge(g, B, A[i], 1);
            i++;
            if (c != ' ')
                break;
        }
        i = 0;
        j++;
    }
}
// thuat toan pageRank
void pageRank(Graph g, JRB Path)
{
    JRB p, node1, node;
    int M[10], M1[10];
    int n, n1, i, id, id1, j = 0;
    double val[10];
    jrb_traverse(p, g.vertices)
    {
        id = jval_i(p->key);
        n = indegree(g, id, M);
        /*lay ra tap dinh co canh di vao dinh id , gan so luong vao bien n
        va cac dinh indegree luu trong mang M*/
        val[j] = 0;
        for (i = 0; i < n; i++)
        {
            id1 = M[i];
            n1 = outdegree(g, id1, M1);
            /*lay ra tap dinh co canh di ra dinh id , gan so luong vao 
            bien n1 va cac outdegree duoc luu trong mang M1*/
            node1 = jrb_find_int(Path, id1);
            val[j] += jval_d(node1->val) / n1;
        }
        j++;
        /*
        node = jrb_find_int(Path , id);
        jrb_delete_node(node);
        jrb_insert_int(Path , id , new_jval_d(val));
        */
    }
    i = 0;
    jrb_traverse(node, Path)
    {
        id = jval_i(node->key);
        jrb_delete_node(node); // xoa node ra khoi cay Path
        jrb_insert_int(Path, id, new_jval_i(val[i]));
        // sau khi xoa lai them lai dinh id voi gia tri val[i] vao Path
        i++;
    }
}
int main()
{
    FILE *ptr, *fptr;
    Dllist list;
    JRB node, p, Path;
    double top3[10]; // phuc vu viec tim top 3 web quan trong nhat
    int id1, id2;
    Path = make_jrb();
    int choose, n, m;
    int A[10], M[10], j, i = 0;
    Graph g = createGraph();
    do
    {
        printf("\n======== MENU ========\n"
               "1. \n"
               "2. \n"
               "3. \n"
               "4. \n"
               "5. \n"
               "6. \n"
               "--> Choose ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            ptr = fopen("webpages.txt", "r");
            fptr = fopen("pageConnection.txt", "r");
            readFile(g, ptr, fptr, &n, Path);
            jrb_traverse(node, g.edges)
            {
                A[i] = indegree(g, jval_i(node->key), M);
                i++;
                // gan so luong indegree cua tung node vao mang A[i]
            }
            printf("\n");
            //printf("%d\t%d\n\n", Min(A, i), Max(A, i));
            jrb_traverse(p, g.edges)
            {
                if (indegree(g, jval_i(p->key), M) == Min(A, i))
                {
                    printf("Website co it lien ket den nhat : %s\n", getVertexName(g, jval_i(p->key)));
                }
                if (indegree(g, jval_i(p->key), M) == Max(A, i))
                {
                    printf("Website co nhieu lien ket den nhat : %s\n", getVertexName(g, jval_i(p->key)));
                }
            }
            fclose(fptr);
            fclose(ptr);
            break;
        case 2:
            pageRank(g, Path); // thuc hien thuat toan pageRank 1 lan
            int idMax, idMin;
            double min = 99999;
            double max = 0;
            jrb_traverse(node, Path)
            {
                if (max < jval_d(node->val))
                {
                    max = jval_d(node->key);
                    // gan lai cost cua node.key cho max
                    idMax = jval_i(node->key)
                }
                if (min > jval_d(node->val))
                {
                    min = jval_d(node->key);
                    // gan lai cost cua node.key cho min
                    idMin = jval_i(node->key);
                }
            }
            printf("Web co trong so PR cao nhat:\n");
            printf("%s\n", getVertexName(g, idMax));
            printf("Web co trong so PR thap nhat:\n");
            printf("%s\n", getVertexName(g, idMin));
            // In ra cac cost
            jrb_traverse(p, Path)
            {
                printf("%lf\t", jval_d(p->val));
            }
            break;
        case 3:

            j = 0;
            printf("Nhap so lan su dung thuat toan PageRank: ");
            scanf("%d", &m);
            for (i = 0; i < m; i++)
            {
                pageRank(g, Path);
            }
            // cho cac cost cua
            jrb_traverse(node, Path)
            {
                top3[j] = jval_d(node->val);
                j++;
            }
            selection_sort(top3, n);
            // sap xep chon mang top3 theo thu tu tang dan
            printf("top 3 web duoc truy cap nhieu nhat la: \n");
            for (i = 0; i < 2; i++)
            {
                printf("%s", getVertexName(g, top3[j - i]));
            }

            /* for (i = 0; i < n; i++)
            {
                printf("%lf\t", top3[i]);
            } */
            break;
        case 4:
            j = 0, i = 0;
            jrb_traverse(p, g.edges)
            {
                if (indegree(g, jval_i(p->key), M) != 0 && outdegree(g.edges, jval_i(p->key), M) == 0)
                {
                    j++; // luu tru so luong
                }
                if (indegree(g.edges, jval_i(p->key), M) == 0 && outdegree(g.edges, jval_i(p->key), M) != 0)
                {
                    i++;
                }
            }
            printf("So luong webpage chi co lien ket den, nhung khong co lien ket ra la %d\n", j);
            printf("So luong webpage chi co lien ket ra, nhung khong co lien ket den la %d\n", i);
            break;
        case 5:

            printf("id1 : ");
            scanf("%d", &id1);
            printf("id2 : ");
            scanf("%d", &id2);
            if (id1 == id2)
            {
                printf("-1");
            }
            else
            {
                if (jrb_find_int(Path, id1) == NULL || jrb_find_int(Path, id2) == NULL)
                {
                    printf("-1");
                    break;
                }
                else
                {
                    shortestPath(g, id1, id2);
                }
            }
            break;

        case 6:
            dropGraph(g);
            exit(0);
            break;
        default:
            break;
        }
    } while (choose != 6);

    return 0;
}

//gcc -I ../Libfdr/ -o GK GK.c graph_jrb.c ../Libfdr/libfdr.a
// ./GK
int main()
{
    return 0;
}