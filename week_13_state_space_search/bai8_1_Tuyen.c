#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "dllist.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define TypeMove int

#define Queue Dllist

#define INFINITIVE_VALUE 1000000

typedef struct
{
  JRB edges;
  JRB vertices;
} Graph;

typedef struct State
{
  char pos;
  char board[10];
} State;

// Graph createGraph();
// void addVertex(Graph graph, int id, char *name);
// char *getVertex(Graph graph, int id);
// void addEdge(Graph graph, int v1, int v2, double weight);
// double getEdgeValue(Graph graph, int v1, int v2);
// int indegree(Graph graph, int v, int *output);
// int outdegree(Graph graph, int v, int *output);
// void dropGraph(Graph graph);

char *move(TypeMove typeMove, int vitri0, char state[])
{
  char tmp;
  char *reState = malloc(10 * sizeof(char));
  strcpy(reState, state);

  switch (typeMove)
  {
  case UP:
    if (vitri0 > 2)
    {
      tmp = reState[vitri0 - 3];
      reState[vitri0] = tmp;
      vitri0 -= 3;
      reState[vitri0] = '0';
    }
    break;
  case LEFT:
    if ((vitri0 != 0) && (vitri0 != 3) && (vitri0 != 6))
    {
      tmp = reState[vitri0 - 1];
      reState[vitri0] = tmp;
      vitri0--;
      reState[vitri0] = '0';
    }
    break;
  case RIGHT:
    if ((vitri0 != 2) && (vitri0 != 5) && (vitri0 != 8))
    {
      tmp = reState[vitri0 + 1];
      reState[vitri0] = tmp;
      vitri0++;
      reState[vitri0] = '0';
    }
    break;
  case DOWN:
    if (vitri0 < 6)
    {
      tmp = reState[vitri0 + 3];
      reState[vitri0] = tmp;
      vitri0 += 3;
      reState[vitri0] = '0';
    }
    break;
  }
  return reState;
}

int isEqualState(char state1[], char state2[])
{
  return strcmp(state1, state2) == 0 ? 1 : 0;
}

State createFirstState()
{
  State tmp;
  tmp.pos = 7;
  strcpy(tmp.board, "283164705");
  return tmp;
}

int indexOf0(char *state)
{
  for (int i = 0; i < 9; i++)
  {
    if (state[i] == '0')
      return i;
  }
}

int findFinalStateWithBFS(char finalState[], State firstState)
{
  Queue open = new_dllist(), close = new_dllist();
  Dllist howToRun = new_dllist();
  Dllist Node, ptr;
  int vitri0 = firstState.pos;
  char X[10];
  char *stateAfterMove;

  dll_append(open, new_jval_s(firstState.board));

  while (!dll_empty(open))
  {
    Node = dll_first(open);
    strcpy(X, jval_s(Node->val));

    if (isEqualState(X, finalState))
      return 1;
    else
    {
      for (int i = 1; i <= 4; i++)
      {
        stateAfterMove = move(i, vitri0, X);
        if (strcmp(stateAfterMove, X) != 0)
        {
          dll_traverse(ptr, open)
          {
            if (strcmp(jval_s(ptr->val), stateAfterMove) == 0)
              continue;
          }
          dll_traverse(ptr, close)
          {
            if (strcmp(jval_s(ptr->val), stateAfterMove) == 0)
              continue;
          }

        }
      }
    }
  }

  free_dllist(open);
  free_dllist(close);
  free_dllist(howToRun);
}

int main()
{
  Graph g = createGraph();
  State firstState = createFirstState();
  char finalState[10] = "123804765";

  // printf("%d - %s\n", move(DOWN), state.board);
  // findFinalStateWithBFS(finalState, firstState);

  printf("%s\n", move(UP, 6, "386124075"));
}

Graph createGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void addVertex(Graph g, int id, char *name)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node == NULL) // only add new vertex
    jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph g, int id)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node == NULL)
    return NULL;
  else
    return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2, double weight)
{
  JRB node, tree;
  if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
  {
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
      tree = make_jrb();
      jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }
    else
    {
      tree = (JRB)jval_v(node->val);
    }
    jrb_insert_int(tree, v2, new_jval_d(weight));
  }
}

double getEdgeValue(Graph graph, int v1, int v2)
{
  JRB node, tree;
  node = jrb_find_int(graph.edges, v1);
  if (node == NULL)
    return INFINITIVE_VALUE;
  tree = (JRB)jval_v(node->val);
  node = jrb_find_int(tree, v2);
  if (node == NULL)
    return INFINITIVE_VALUE;
  else
    return jval_d(node->val);
}

int indegree(Graph graph, int v, int *output)
{
  JRB tree, node;
  int total = 0;
  jrb_traverse(node, graph.edges)
  {
    tree = (JRB)jval_v(node->val);
    if (jrb_find_int(tree, v))
    {
      output[total] = jval_i(node->key);
      total++;
    }
  }
  return total;
}

int outdegree(Graph graph, int v, int *output)
{
  JRB tree, node;
  int total;
  node = jrb_find_int(graph.edges, v);
  if (node == NULL)
    return 0;
  tree = (JRB)jval_v(node->val);
  total = 0;
  jrb_traverse(node, tree)
  {
    output[total] = jval_i(node->key);
    total++;
  }
  return total;
}

void dropGraph(Graph graph)
{
  JRB node, tree;
  jrb_traverse(node, graph.edges)
  {
    tree = (JRB)jval_v(node->val);
    jrb_free_tree(tree);
  }
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
}