#include<stdio.h>
#include<stdlib.h>
#include "Graphjrb.h"

Graph createGraph(){
  return make_jrb();
}

int adjacent(Graph G, char *v1, char *v2){
  JRB tmp;
  tmp = jrb_find_str(G, v1);
  if(!tmp)
    return 0;
  tmp = (JRB)jval_v(tmp->val);
  if(jrb_find_str(tmp, v2))
    return 1;
  else
    return 0;
}

void addEdge(Graph g, char *v1, char *v2){
  JRB node, tree;
  if(!adjacent(g, v1, v2)){
    node = jrb_find_str(g, v1);
    if(!node){
      tree = make_jrb();
      jrb_insert_str(g, v1, new_jval_v(tree));
      jrb_insert_str(tree, v2, new_jval_i(1));
    } else{
      tree = (JRB)jval_v(node->val);
      jrb_insert_str(tree, v2, new_jval_i(1));
    }
  }
  if(!adjacent(g, v2, v1)){
    node = jrb_find_str(g, v2);
    if(!node){
      tree = make_jrb();
      jrb_insert_str(g, v2, new_jval_v(tree));
      jrb_insert_str(tree, v1, new_jval_i(1));
    } else{
      tree = (JRB)jval_v(node->val);
      jrb_insert_str(tree, v1, new_jval_i(1)); 
    }
  }
}


int getAdjacentVertices(Graph G, char *v, char **output){
  JRB tmp, ga;
  int total = 0;
  tmp = jrb_find_str(G, v);
  if(!tmp)
    return 0;
  tmp = (JRB)jval_v(tmp->val);
  jrb_traverse(ga, tmp){
    output[total++] = jval_s(ga->key);
  }
  return total;
}

void dropGraph(Graph G){
  if(G==NULL){
    printf("Graph is empty\n");
    return;
  }
  JRB tmp;
  jrb_traverse(tmp, G)
    jrb_free_tree((JRB)jval_v(tmp->val));
  jrb_free_tree(G);
}
