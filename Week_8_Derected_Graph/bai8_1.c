#include<stdio.h>
#include"jrb.h"
/*phai de y hai kieu ham sau
*/ 
typedef struct 
{
    JRB edges;
    JRB vertices;
}Graph;
Graph createGraph();
void addVertex(Graph graph , int id , char *name);
char *getVertex(Graph graph , int id);
void addEdge(Graph graph , int v1 ,int v2);
int hasEdge(Graph graph , int v1 ,int v2);// kiem tra co canh (co huong) noi hai dinh khong
int indegree(Graph graph , int v ,int *output);// dem xem co bao nhieu canh co huong di vao
int outdegree(Graph graph , int v ,int *output);// dem xem co bao nhieu canh co huong di ra
int DAG(Graph graph);// ham kiem tra xem do thi co lien thong hay khong
void dropGraph(Graph graph);// giai phong

int main()
{
    return 0;
}

Graph createGraph()
{
    Graph graph ;
    graph.edges = make_jrb();// ham khoi tao mot cay jrb moi luu so canh
    graph.vertices = make_jrb();// ham khoi tao mot cay jrb luu so dinh
    return graph;
}
// ham them vao mot dinh
void addVertex(Graph graph , int id , char *name)
{
    JRB node = jrb_find_int(graph.vertices,id);
    Graph tree;
    if(node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.vertices,id,new_jval_i(name));// day la ham them mot dinh vao cay
    }
}
// ham tim mot dinh thong qua id
char *getVertex(Graph graph,int id)
{
    JRB node = jrb_find_int(graph.vertices,id);
    if(node != NULL)
    {
        //printf("%d co name la : %s\n",id,node->val);
        return jval_s(node->val);

    }
    else
    {
        printf("Khong tim thay\n");
    }
}
// ham them mot canh vao cay
void addEdge(Graph graph , int v1 , int v2)
{
    JRB node = jrb_find_int(graph.vertices,v1);
    Graph tree;
    if(node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.edges,v1,new_jval_v(tree));
        jrb_insert_int(tree,v2,new_jval_i(1));// neu co canh thi la 1
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree,v2,new_jval_i(1));
    }
    node = jrb_find_int(graph,v2);
    if(node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph.edges,v2,new_jval_v(tree));
        jrb_insert_int(tree,v1,new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree,v1,new_jval_i(1));
    }
    
}
// ham kiem tra xem co canh khong
int hasEgde(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.vertices, v1);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
       return 0;
    else
       return 1;       
}
// ham kiem tra co bao nhieu canh di vao
int indegree(Graph graph , int v , int *output)
{
    JRB tree, node;
    int total = 0;   
    jrb_traverse(node, graph.edges)
    {
       tree = (JRB) jval_v(node->val);
       if (jrb_find_int(tree, v))
       {
          output[total] = jval_i(node->key);
          total++;
       }                
    }
    return total;  
}

// ham kiem ta co bao nhieu canh di ra (ban chat giong ham duyet cac dinh ke)
int outdegree(Graph graph,int v,int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.vertices, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);// mang output luu lai nhung gia tri nao ke voi node
       total++;                
    }
    return total;   
}
// ham kiem tra xem do thi co lien thong hay khong
int DAG(Graph graph)
{
   int visited[1000];
   int n, output[100], i, u, v, start;
   Dllist node, stack;
   JRB vertex;
   
   jrb_traverse(vertex, graph.vertices)
   {
       memset(visited, 0, sizeof(visited));

       start = jval_i(vertex->key);              
       stack = new_dllist();
       dll_append(stack, new_jval_i(start));
    
       while ( !dll_empty(stack) )
       {
          node = dll_last(stack);
          u = jval_i(node->val);
          dll_delete_node(node);
          if (!visited[u])
          {
              visited[u] = 1;
              n = outdegree(graph, u, output);
              for (i=0; i<n; i++)
              {
                  v = output[i];
                  if ( v == start ) // cycle detected 
                     return 0;
                  if (!visited[v])    
                    dll_append(stack, new_jval_i(v));
              }
          }           
       }
   }
   return 1; // no cycle    
}

// ham giai phong do thi
void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

