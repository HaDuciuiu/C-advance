#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"jrb.h"
#include"dllist.h"

#define INFINITIVE 10000000 // mot gia tri vo cung
// khoi tao mot cau truc graph
typedef struct 
{
    JRB vertices;// tap dinh
    JRB edges;// tap canh
}Graph;

// khai bao cac nguyen mau ham
Graph createGraph(); // ham tao mot do thi
void addVertex(Graph graph, int id , char *name);// ham them mot dinh vao do thi
char *getVertex(Graph graph,int id);// ham lay ra mot canh
void addEgde(Graph graph,int v1 , int v2 , double weight);// ham add mot canh vao do thi
double getEgdeValue(Graph graph, int v1 , int v2);// ham tra ve gia tri theo value
int indegree(Graph graph, int v , int *output); // ham tra ve tap cac dinh co duong di vao dinh v
int outdegree(Graph graph , int v , int *output );// ham tra ve tap cac dinh co duong di ra tu dinh v
void dropGraph(Graph graph);// ham giai phong do thi
double shortestPath(Graph graph , int s , int v , int *path , int *length);// ham tim duong di ngan nhat giua mot nguon va mot dich
int main()
{
    int i , length , path[100] , s , t;
    double w;
    Graph g = createGraph();// tao mot do thi g
    addVertex(g,0,"V0");// them dinh V0 co khoa la 0
    addVertex(g,1,"V1");// them dinh V1 co khoa la 1
    addVertex(g,2,"V2");// them dinh V2 co khoa la 2
    addVertex(g,3,"V3");// them dinh V3 co khoa la 3
    //addVertex(g,4,"V4");// them dinh V4 co khoa la 4
    addEgde(g,0,1,1); // add canh 0-1 voi trong so la 1
    addEgde(g,1,2,3); // add canh 1-2 voi trong so la 3
    addEgde(g,2,0,3); // add canh 2-0 voi trong so la 3
    addEgde(g,1,3,1); // add canh 1-3 voi trong so la 1 
    addEgde(g,3,2,1); // add canh 3-2 voi trong so la 1
    s= 0 ;
    t = 2;
    w = shortestPath(g,s,t,path,&length); // tim duong di ngan nhat tu s den t
    if(w==INFINITIVE)
    {
        printf("No path from %s to %s \n",getVertex(g,s),getVertex(g,t));// tim luon s va t trong g
    }
    else
    {
        printf("path from %s to %s(with total distance %f) : \n",getVertex(g,s),getVertex(g,t),w);
        for(i=0;i<length;i++)
        {
            printf("=> %s ",getVertex(g,path[i]));
        }
    }
    dropGraph(g);
    //getch();// lenh nay dung de doi man hinh de xem ket qua khi chay chuong trinh nhung gio khong can thiet nua
    return 0;
}
Graph createGraph()
{
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

void addVertex(Graph g , int id , char *name)
{
    JRB node = jrb_find_int(g.vertices,id);// tim kiem dinh co khoa la id trong tap dinh g.vertices
    if(node == NULL)// only add new vertex -> chi them vao dinh moi
        jrb_insert_int(g.vertices,id,new_jval_s(strdup(name)));// them mot dinh kieu int vao tap dinh g.vertices - la mot cay jrb
}

char *getVertex(Graph g , int id)
{
    JRB node = jrb_find_int(g.vertices,id);// tim id trong tap dinh g.vertices
    if(node==NULL)
        return NULL;
    else
        return new_jval_s(node->val);// tra ve gia tri jval kieu string
}

void addEgde(Graph g,int v1 , int v2 , double weight)
{
    JRB node , tree;
    if(getEgdeValue(g,v1,v2)==INFINITIVE) // neu tim canh cua trong so v1v2 khong co
    {
        node = jrb_find_int(g.edges,v1);// tim v1 trong tap canh g.edges
        if(node == NULL)
        {
            tree = make_jrb();
            /*Neu chua co dinh v1 trong tap dinh thi tao ra mot cay moi tree*/
            jrb_insert_int(g.edges,v1,new_jval_v(tree)));// them dinh v1 va cay tree vao g.edges
        }
        else
        {
            tree = (JRB)jval_v(node->value);// ep kieu tree ve dang cay JRB
        }
        jrb_insert_int(tree,v2,new_jval_d(weight));// them dinh v2 vao tree kem them trong so weight
    }
}

double getEgdeValue(Graph g , int v1 , int v2)
{
    JRB node , tree;
    node = jrb_insert_int(g.edges , v1); // tim dinh v1 trong tap canh
    if(node == NULL)
        return INFINITIVE;
    tree = (JRB)jval_v(node->val);// ep kieu gia tri cua node->val ve kieu jrb
    node = jrb_find_int(tree , v2);// tim v2 trong tree
    if(node == NULL)
        return INFINITIVE;
    else
        return jval_d(node->val);

}

int indegree(Graph g , int v , int *output)
{
    JRB node , tree;
    int total = 0 ; // bien total luu tong so cac dinh co duong di vao dinh v
    jrb_traverse(node,g.edges) // duyet tap dinh
    {
        tree = (JRB)jrb_val(node->val);
        if(jrb_find_int(tree,v))// neu tim thau dinh v trong tree
        {
            output[total] = jval_i(node->key);// them khoa vao mang output
            total++;

        }
    }
    return total;
}

int outdegree(Graph g , int v , int *output)
{
    JRB node , tree;
    int total;
    node = jrb_find_int(g.edges,v);// tim dinh v trong tap canh g.edges
    if(node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);// lay gia tri node->val ep ve kieu JRB roi gan no vao tree
    total = 0;
    jrb_traverse(node , tree) // duyet cay
    {
        output[total] = jval_i(node->key); // them khoa va mang output
        total++;
    }
    return total;

}

double shortestPath(Graph g , int s , int t , int *path , int *length)
{
    double distance[1000] , min , w , total;
    int previous[1000] , tmp[1000];
    int n , output[100] , i , u , v , start;
    Dllist ptr , queue , node;
    for(i=0 ; i< 1000 ; i++)
        distance[i] = INFINITIVE;
    distance[s] = 0;
    previous[s] = s;
    
    queue = new_dllist();// tao mot queue
    dll_append(queue,new_jval_i(s));// them s-nguyen vao queue

    while(!dll_empty(queue))// khi queue chua rong
    {
        // get u from the priority queue -> lay u ra tu hang doi uu tien
        min = INFINITIVE;
        dll_traverse(ptr,queue)// duyet hang doi qua con tro ptr - kien thuc giong mon C basic
        {
            u = jval_v(ptr->val);// gan gia tri tro boi con tro ptr cho u
            if(min>distance[u])
            {
                min = distance[u];
                node = ptr;// gan con tro ptr vao node
            }
        }
        dll_delete_node(node);// giai phong node
        if(u == t) // stop at t -> dung lai o t
            break;
        n = outdegree(g,u,output);
        for(i=0;i<n;i++)
        {
            v = output[i];
            w = getEgdeValue(g,u,v);
            if(distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
            dll_append(queue,new_jval_i(v)) // them dinh v vao queue
        }
    }
    total = distance[t];
    if(total != INFINITIVE)
    {
        tmp[0] = t;
        n = 1;
        if(t != s)
        {
            t = previous[t];
            tmp[n++] = t;
        }
        for(i = n-1 ; i> 0 ; i--)
        {
            path[n-i-1] = tmp[i];
        }
        *length = n;
    }
    return total;
}

void dropGraph(Graph g)
{
    JRB node , tree;
    jrb_traverse(node ,g.edges) // duyet tap canh g.edges bang bien node
    {
        tree = (JRB)jval_v(node->val);// lay gia tri cua node->value ep ve kieu JRB roi gan cho tree
        jrb_free_tree(tree);// giai phong tree
    }
    jrb_free_tree(g.edges); // giai phong tap canh
    jrb_free_tree(g.vertices); // giai phong tap dinh
}