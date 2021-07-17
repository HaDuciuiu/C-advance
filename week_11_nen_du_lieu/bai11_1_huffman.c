#include <stdio.h>
#include <string.h>
#include "week4/jval.h"// add thu vien kem theo ca duong link den thu muc do
#include "week4/jrb.h"// add thu vien kem theo ca duong link den thu muc do
#define Max_kiTu 100
#include <stdlib.h>
#define INFINITIVE_VALUE 10000000
#define Max 100
int setD[Max]={};
int setParent[Max]={};
 
#define INFINITIVE_VALUE  10000000
 
typedef struct {
   JRB edges;
   JRB vertices;
} Graph;
// ham tao mot do thi g
Graph createGraph()
{
   Graph g; 
   g.edges = make_jrb();  
   g.vertices = make_jrb();  
   return g;
}
// ham them mot dinh
void addVertex(Graph g, int id, char* name)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) // only add new vertex 
         jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));            
}

// ham tim mot dinh
char *getVertex(Graph g, int id)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) 
        return NULL;
     else                
        return jval_s(node->val);
}     
// ham them mot canh vao do thi
void addEdge(Graph graph, int v1, int v2, double weight)
{
     JRB node, tree;
     if (getEdgeValue(graph, v1, v2)==INFINITIVE_VALUE)
     {
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
     }
}
// ham them mot canh co trong so vao do thi
double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
       return INFINITIVE_VALUE;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node==NULL)
       return INFINITIVE_VALUE;
    else
       return jval_d(node->val);       
}
// ham tra ve cac dinh co duong noi vao cua dinh v
int indegree (Graph graph, int v, int* output)
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
 
// ham tra ve danh sach cac dinh co canh noi ra khoi tu dinh v
int outdegree (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
}
 
 
typedef struct
{
  Graph graph;
  JRB root;
} HuffmanTree;
 
typedef struct
{
  char c;
  int soLan;
}kiTu;
 
kiTu day[Max_kiTu];
// ham sap xep ki tu cua mot mang a[] theo thu tu tang dan
void sapXep(char a[])
{
  int i,j;
  char tmp;
  for(i=0;i<strlen(a);i++)
    for(j=i;j<strlen(a);j++)
      {
	if(a[i]>a[j])
	  {
	    tmp=a[i];
	    a[i]=a[j];
	    a[j]=tmp;
	  }
      }
}

// ham tra ve tong cac phan tu
int totalPhanTu(char a[], int size)
{
  int i;
  int count=1;
  int j=0;
  sapXep(a);
  for(i=0;i<size;i++)
    {
      if(a[i]==a[i+1])
	  count++;
      else
	{
	  day[j].c=a[i];
	  day[j].soLan=count;
	  j++;
	  count=1;
v	}
    }
  return j;
}

// ham sap xep lai day
void sapXepLaiDay(int size)
{
  kiTu tmp;
  for(int i=0;i<size;i++)
    for(int j=i;j<size;j++)
      if(kiTu[i].soLuong>kiTu[j].soLuong)
	{
	  tmp=kiTu[i];
	  kiTu[i]=kiTu[j];
	  kiTu[j]=tmp;
	}
}

