#include<stdio.h>
#include"jrb.h"
#include"dllist.h"
typedef struct {
   JRB edges;
   JRB vertices;
} Graph;
// ham dua ra cac canh di vao dinh v
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
// ham dua ra cac canh di ra khoi dinh v
void topologicalSort(Graph graph , int *output , int *n)
{
    Dllist Q = new_dllist();
    jrb_traverse(n,graph.vertices)// duyet dinh n trong tap cac dinh
    {
        if(indegree(graph,n,output)==0)
        {
            enqueue(n,Q);
        }

    }


}
int main()
{
    return 0;
}