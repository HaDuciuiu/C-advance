#include<stdio.h>
#include"jrb.h"
typedef JRB Graph;
// ham khoi tao mot dothi
Graph createGraph()
{
    Graph graph = make_jrb();
    return graph;
}
// ham add mot canh v1 , v2 vao do thi
void addEdge(Graph graph , int v1 , int v2)
{
    JRB node = jrb_find_int(graph,v1);
    Graph tree;
    if(node == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(graph,v1,new_jval_v(tree));
        jrb_insert_int(tree,v2,new_jval_i(1));
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
        jrb_insert_int(graph,v2,new_jval_v(tree));
        jrb_insert_int(tree,v1,new_jval_i(1));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_insert_int(tree,v1,new_jval_i(1));
    }
    
}
// ham lay ra cac dinh ke cua v trong do thi
int getAdjacentVertices(Graph graph, int v, int* output)
{
    Graph node = jrb_find_int(graph,v);
    Graph tree = (JRB)jval_v(node->val);
    int total = 0;
    jrb_traverse(node,tree)
        output[total++] = jval_i(node->key);
    return total;
}
// ham giai phong va xoa do thi
void dropGraph(Graph graph)
{
    Graph node;
    jrb_traverse(node , graph)
        jrb_free_tree(jval_v(node->val));
}

int main()
{
    int i, n, output[100];
    Graph g = createGraph();
    addEdge(g,0,1);   
    addEdge(g,0,2);
    addEdge(g,1,2);
    addEdge(g,1,3);
    n = getAdjacentVertices(g,1,output);
    if(n==0)
        printf("Khong co dinh ke cua nut 1\n");
    else {
        printf("Cac dinh ke cua nut 1 :\n");
        for(i=0;i<n;i++)
        {
           printf("%d\n",output[i]);
        }
    }
    dropGraph(g);
    return 0;
}