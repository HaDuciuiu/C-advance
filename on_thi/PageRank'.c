#include "PageRank.h"

Graph createGraph() // khoi tao do thi su dung cay jrb
{
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

void addVertex(Graph g, int id, char *name) // Them dinh
{
    JRB node = jrb_find_int(g.vertices, id);
    // find id in g.vertices
    if (node == NULL) //not found -> insert ; only add new id
        jrb_insert_int(g.vertices , id , new_jval_s(strdup(name));
}
// them canh
void addEdge(Graph g, int v1, int v2, double weight)
{
    JRB node, tree;
    node = jrb_find_int(g.edges, v1);
    if (node != NULL) //found id in the g.edges
    {
        tree = (JRB)jval_v(node->val);
    }
    else
    {
        tree = make_jrb();
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
    }
    jrb_insert_int(tree, v2, new_jval_i(weight));
}
//find name of website by id
char *getVertexName(Graph g, int id)
{
    JRB node;
    node = jrb_find_int(g.vertices, id);
    if (node == NULL) // Not found
        return NULL;
    else
    {
        return jval_s(node->val);
    }
}
// find id by name
int getVertexId(Graph g, char *name)
{
    JRB node;
    jrb_traverse(node, g.vertices)
    {
        if (strcmp(name, jval_s(node->val)) == 0)
            return jval_i(node->key);
        else
            return -1;
    }
}
// return the value of the edge v1-v2
double getEdgeValue(Graph g, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(g.edges, v1); // find vertice v1 in g.edges
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        node = jrb_find_int(tree, v2); // find vertice v2 in g.edges
        if (node == NULL)
            return -1;
        else
            return jval_d(node->val);
    }
}
/*
double getEdgeValue(Graph g, int v1, int v2) // kiem tra do dai khoang cach
{
    JRB node, l;

    if ((node = jrb_find_int(g.edges, v1)) != NULL)
    {
        if ((l = jrb_find_int((JRB)(jval_v(node->val)), v2)) != NULL)
            return jval_i(l->val);
        else
            return -1;
    }
    else
        return -1;
}
*/
// kiem tra duong di giua 2 dinh v1 v2
int hasEdge(Graph g, int v1, int v2)
{
    JRB node, tree;

    if ((node = jrb_find_int(g.edges, v1)) != NULL)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v2) != NULL)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

// ham tra ve tap dinh co canh di vao dinh v
int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        // voi moi dinh , tim dinh v co trong tap canh ke cua dinh do ko
        if (jrb_find_int(tree, v)) // neu v co trong tap ke cua dinh
        {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}
// ham tra ve tap dinh co canh noi ra cua dinh v
int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL) // ko co dinh v trong g.edges
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree) // duyet tap dinh ke cua dinh v
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}
// ham tra ve danh sach cac dinh co canh noi ra khoi dinh v
Dllist outgoingVertices(Graph g, int v)
{
    JRB node, tree, tmp;
    Dllist output = new_dllist();

    if ((node = jrb_find_int(g.edges, v)) == NULL)
        return output;
    tree = (JRB)jval_v(node->val);
    jrb_traverse(tmp, tree)
    {
        dll_append(output, tmp->key);
    }
    return output;
}
// ham tra ve tap dinh co canh noi vao dinh v
Dllist incomingVertices(Graph g, int v)
{
    JRB node, tree, tmp;
    Dllist output = new_dllist();

    jrb_traverse(node, g.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v) != NULL)
            dll_append(output, node->key);
    }
    return output;
}

void dropGraph(Graph g)
{
    JRB node;

    jrb_traverse(node, g.vertices)
    {
        free(jval_v(node->val));
    }
    jrb_free_tree(g.vertices);
    jrb_traverse(node, g.edges)
        jrb_free_tree((JRB)jval_v(node->val));
    jrb_free_tree(g.edges);
}

void printfVertex(int v)
{
    printf("%4d", v);
}
// ham duyet do thi theo chieu rong
void BFS(Graph g, int source, int dest, void (*f)(int key))
{
    JRB visited;
    Dllist q;
    Dllist n;
    Dllist adjs;
    int i, u;
    visited = make_jrb();
    adjs = new_dllist();
    dll_append(q, new_jval_i(source));
    while (!dll_empty(q))
    {
        n = dll_first(q);
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (jrb_find_int(visited, u) == NULL) // not found u in visited array
        {
            f(u); // tham dinh u
            // sau khi tham dinh u ta se them dinh u vao mang visited
            jrb_insert_int(visited, u, new_jval_i(1));
            adjs = outgoingVertices(u);
            dll_traverse(n, adjs)
            {
                // neu dinh n chua co trong cay visited hay dinh n chua tham
                if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
                    dll_append(q, dll_val(n));
                /*neu dinh n trung voi dinh dest thi co nghia la qua trinh 
                duyet ket thuc => khi do ta di giai phong cac danh sach
                da duoc cap phat*/
                if (jval_i(dll_val(n)) == dest)
                {
                    free_dllist(adjs);
                    jrb_free_tree(visited); // visited la mot cay jrb
                    free_dllist(q);
                    return;
                }
            }
            free_dllist(adjs);
        }
    }
    jrb_free_tree(visited);
    free_dllist(q);
}

// deepth traverser - duyet do thi theo chieu sau
void DFS(Graph g, int source, int dest, void (*f)(int key))
{
    JRB visited;
    Dllist q;
    Dllist n;
    Dllist adjs;
    int i, u;
    visited = make_jrb();
    adjs = new_dllist();
    dll_append(q, new_jval_i(source));
    while (!dll_empty(q))
    {
        n = dll_last(q);
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (jrb_find_int(visited, u) == NULL)
        {
            f(u); // tham dinh u
            jrb_insert_int(visited, u, new_jval_i(1));
            adjs = outgoingVertices(g, u);
            dll_rtraverse(n, adjs)
            {
                // neu dinh n chua duoc tham => them no vao hang doi uu tien
                if (jrb_insert_int(visited, jval_i(dll_val(n))) == NULL)
                    dll_append(q, dll_val(n));
                /*khi dinh trung voi dinh dest thi dung qua trinh duyet 
                va giai phong cac danh sach da cap phat*/
                if (jval_i(dll_val(n)) == dest)
                {
                    free_dllist(adjs);
                    jrb_free_tree(visited);
                    free_dllist(q);
                    return;
                }
            }
            free_dllist(adjs);
        }
    }
    free_dllist(q);
    jrb_free_tree(visited);
}
// ham kiem tra xem co mot vong tron trong do thi bat dau tu dinh v ko
int onCycle(Graph g, int v)
{
    JRB visited;
    Dllist q;
    Dllist n;
    Dllist adjs;
    int i, u;
    visited = make_jrb();
    q = new_dllist();
    /*Khong can khoi tao danh sach adjs vi trong ham outgoingVertices
    danh sach output da duoc khoi tao luon roi*/

    dll_append(q, new_jval_i(v));
    while (dll_empty(q))
    {
        n = dll_first(q);
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (jrb_find_int(visited, u) == NULL)
        {
            jrb_insert_int(visited, u, new_jval_i(1));
            adjs = outgoingVertices(g, u);
            dll_rtraverse(n, adjs)
            {
                if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
                    dll_append(visited, dll_val(n));
                if (hasEdge(g, jval_i(dll_val(n)), v)) // co vong tron
                {
                    free_dllist(adjs);
                    jrb_free_tree(visited);
                    free_dllist(q);
                    return 1;
                }
            }
            free_dllist(adjs);
        }
    }
    jrb_free_tree(visited);
    free_dllist(q);
    return 0;
}
// kiem tra do thi co chu trinh hay khong voi moi dinh
int isDAG(Graph g)
{
    JRB node;
    jrb_traverse(node, g.vertices)
    {
        if (onCycle(g, jval_i(node->key)))
            return 0;
    }
    return 1;
}
// ham tim website co diem quan trong thap nhat
Dllist dll_min(Dllist list, JRB cost, JRB visited)
{
    Dllist node;
    JRB node_g, node_m;
    int min = INFINITIVE_VALUE;
    // duyet cay jrb luu gia tri quan trong cua 1 website
    jrb_traverse(node_g, cost)
    {
        if (jval_i(node_g->val) < min && jrb_find_int(visited, jval_i(node_g->key)) == NULL)
        {
            min = jval_i(node_g->val);
            node_m = node_g;
        }
    }
    dll_traverse(node, list)
    {
        // tra ve node co cost min
        if (jval_i(dll_val(node)) == jval_i(node_m->key))
            ;
        return node;
    }
    if (min == INFINITIVE_VALUE)
        return NULL;
}

// ham tim duong di tu dinh source den dest
Dllist findPath(JRB parent, int source, int dest)
{
    JRB node;
    node = jrb_find_int(parent, dest); // tim dest trong cay parent
    Dllist path;
    path = new_dllist();
    dll_prepend(path, new_jval_i(dest));
    // ham dll_prepend la ham them vao dau danh sach lien ket
    // duyet tu dinh dest den dinh source
    while (jval_i(node->val) != source)
    {
        dll_prepend(path, jval_i(node->val));
        node = jrb_find_int(parent, jval_i(node->val));
    }
    dll_prepend(path, new_jval_i(source));
    return path;
}

// ham tim duong di ngan nhat giua hai website
double shortestPath(Graph g, int source, int dest)
{
    JRB visited = make_jrb();
    JRB cost = make_jrb();
    JRB parent = make_jrb();
    JRB node;
    Dllist q = new_dllist();
    Dllist path;
    Dllist n;
    Dllist adjs;
    int i, u, k;
    dll_append(q, new_jval_i(source)); // them source vao hang doi
    jrb_traverse(node, g.vertices)
    {
        jrb_insert_int(cost, jval_i(node->key), new_jval_i(INFINITIVE_VALUE));
    }
    jrb_find_int(cost, source)->val = new_jval_i(0);
    while (1)
    {
        n = dll_min(q, cost, visited);
        if (n == NULL)
        {
            printf("-1 . Route not found\n");
            jrb_free_tree(visited);
            jrb_free_tree(cost);
            jrb_free_tree(parent);
            free_dllist(q);
            return u;
        }
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (u == dest)
            break;
        k = jval_i(jrb_find_int(cost, u)->val); // gia tri cost cua u
        jrb_insert_int(visited, u, new_jval_i(1));
        adjs = outgoingVertices(g, u);
        dll_traverse(n, adjs)
        {
            if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
            {
                node = jrb_find_int(cost, jval_i(dll_val(n)));
                // tim gia tri cost cua node n sau do gan vao node
                i = getEdgeValue(g, u, jval_i(dll_val(n)));
                if (jval_i(node->val) > i + k)
                {
                    node->val = new_jval_i(i + k);
                    node = jrb_find_int(parent, jval_i(dll_val(n)));
                    if (node == NULL)
                    {
                        jrb_insert_int(parent, jval_i(dll_val(n)), new_jval_i(u));
                        node = jrb_find_int(parent, jval_i(dll_val(n)));
                    }
                    else
                        node->val = new_jval_i(u);
                }
                dll_append(q, dll_val(n));
            }
        }
        free_dllist(adjs);
    }
    u = jval_i(jrb_find_int(cost, dest)->val);
    // gan gia tri cost cua dest vao bien u
    printf("Do dai duong di la : %d\nDuong di : ", u);
    path = findPath(parent, source, dest);
    dll_traverse(n, path)
    {
        printf("%s\n", getVertexName(g, jval_i(dll_val(n))));
    }
    printf("\n");
    jrb_free_tree(visited);
    jrb_free_tree(cost);
    jrb_free_tree(parent);
    free_dllist(q);
    free_dllist(path);
    return u;
}
// thuat toan sap xep topo - topologicalSort
void topologicallSort(Graph g)
{
    JRB visited = make_jrb();
    Dllist q = new_dllist();
    Dllist n;
    Dllist adjs;
    Dllist topo = new_dllist();
    int i, u;
    if (!isDAG(g)) // neu g ko phai do thi co huong ko chu trinh
    {
        printf("Graph is not DAG!\n");
        free_dllist(adjs);
        jrb_free_tree(visited);
        free_dllist(q);
        free_dllist(topo);
        return;
    }
    // con neu g la do thi co huong ko chu trinh - isDAG
    dll_append(q, new_jval_i(0));
    while (!dll_empty(q))
    {
        n = dll_first(q);
        u = jval_i(dll_val(n));
        dll_delete_node(n);
        if (!jrb_find_int(visited, u) == NULL)
        {
            dll_prepend(topo, new_jval_i(u));
            jrb_insert_int(visited, u, new_jval_i(1));
            // danh dau dinh u da duoc tham
            adjs = outgoingVertices(g, u);
            dll_rtraverse(n, adjs)
            {
                if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
                    dll_append(q, dll_val(n));
            }
            free_dllist(adjs);
        }
    }
    dll_traverse(n , topo)
    {
        printf("%5d",jval_i(dll_val(n)));
    }
    printf("\n");
    jrb_free_tree(visited);
    free_dllist(q);
    free_dllist(topo);
}
