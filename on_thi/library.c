#include "library.h"

Graph createGraph() // Tao mot cay
{
  Graph g;
  g.vertices = make_jrb();
  g.edges = make_jrb();
  return g;
}

void addVertex(Graph g, int id, char *name) // Them dinh
{
  JRB node = jrb_find_int(g.vertices, id);

  if (node == NULL)
    jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

void addEdge(Graph g, int v1, int v2, double weight) // Them canh
{
  JRB node, l;

  node = jrb_find_int(g.edges, v1);
  if (node != NULL)
  {
    l = (JRB)jval_v(node->val);
    jrb_insert_int(l, v2, new_jval_i(weight));
  }
  else
  {
    l = make_jrb();
    jrb_insert_int(l, v2, new_jval_i(weight));
    jrb_insert_int(g.edges, v1, new_jval_v(l));
  }

}

char *getVertexName(Graph g, int id) // tim kiem theo id
{
  JRB node = jrb_find_int(g.vertices, id);

  if (node != NULL)
    return jval_s(node->val);
  else
    return NULL;
}

int getVertexId(Graph g, char *name) // tim kiem theo ten
{
  JRB i;

  jrb_traverse(i, g.vertices)
  {
    if (strcmp(name, jval_s(i->val)) == 0)
      return jval_i(i->key);
  }
  return -1;
}

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

int hasEdge(Graph g, int v1, int v2) //kiem tra co duong di di giua 2 dinh
{
  JRB node;

  if ((node = jrb_find_int(g.edges, v1)) != NULL)
  {
    if (jrb_find_int((JRB)(jval_v(node->val)), v2) != NULL)
      return 1;
    else
      return 0;
  }
  else
    return 0;
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

Dllist outgoingVertices(Graph g, int v) //cac
{
  JRB node, l, i;
  Dllist output = new_dllist();

  if ((node = jrb_find_int(g.edges, v)) == NULL)
    return output;

  l = (JRB)jval_v(node->val);
  jrb_traverse(i, l)
  {
    dll_append(output, i->key);
  }
  return output;
}

Dllist incomingVertices(Graph g, int v)
{
  JRB node, l, i;
  Dllist output = new_dllist();

  jrb_traverse(node, g.edges)
  {
    l = (JRB)jval_v(node->val);
    if (jrb_find_int(l, v) != NULL)
      dll_append(output, node->key);
  }
  return output;
}

void dropGraph(Graph g)
{
  JRB i;

  jrb_traverse(i, g.vertices)
  {
    free(jval_v(i->val));
  }
  jrb_free_tree(g.vertices);

  jrb_traverse(i, g.edges)
      jrb_free_tree((JRB)jval_v(i->val));
  jrb_free_tree(g.edges);
}

void printfVertex(int v)
{
  printf("%4d", v);
}

void BFS(Graph g, int source, int dest, void (*f)(int key))
{
  JRB visited = make_jrb();
  Dllist q = new_dllist();
  Dllist n;
  Dllist adjs;
  int i, u;

  dll_append(q, new_jval_i(source));
  while (!dll_empty(q))
  {
    n = dll_first(q);
    u = jval_i(dll_val(n));
    dll_delete_node(n);
    if (jrb_find_int(visited, u) == NULL)
    {
      f(u);
      jrb_insert_int(visited, u, new_jval_i(1));
      adjs = outgoingVertices(g, u);

      dll_traverse(n, adjs)
      {
        if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
          dll_append(q, dll_val(n));
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
  jrb_free_tree(visited);
  free_dllist(q);
}

void DFS(Graph g, int source, int dest, void (*f)(int key))
{
  JRB visited = make_jrb();
  Dllist q = new_dllist();
  Dllist n;
  Dllist adjs;
  int i, u;

  dll_append(q, new_jval_i(source));
  while (!dll_empty(q))
  {
    n = dll_last(q);
    u = jval_i(dll_val(n));
    dll_delete_node(n);
    if (jrb_find_int(visited, u) == NULL)
    {
      f(u);
      jrb_insert_int(visited, u, new_jval_i(1));
      adjs = outgoingVertices(g, u);

      dll_rtraverse(n, adjs)
      {
        if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
          dll_append(q, dll_val(n));
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
  jrb_free_tree(visited);
  free_dllist(q);
}

int onCycle(Graph g, int v)
{
  JRB visited = make_jrb();
  Dllist q = new_dllist();
  Dllist n;
  Dllist adjs;
  int i, u;

  dll_append(q, new_jval_i(v));
  while (!dll_empty(q))
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
          dll_append(q, dll_val(n));
        if (hasEdge(g, jval_i(dll_val(n)), v))
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

Dllist dll_min(Dllist list, JRB cost, JRB visited)
{
  Dllist node;
  JRB node_g, node_m;
  int min = INFINITIVE_VALUE;
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
    if (jval_i(dll_val(node)) == jval_i(node_m->key))
      return node;
  }
  if (min == INFINITIVE_VALUE)
    return NULL;
}

Dllist findPath(JRB parent, int source, int dest)
{
  JRB node = jrb_find_int(parent, dest);
  Dllist path = new_dllist();
  dll_prepend(path, new_jval_i(dest));
  while (jval_i(node->val) != source)
  {
    dll_prepend(path, node->val);
    node = jrb_find_int(parent, jval_i(node->val));
  }
  dll_prepend(path, new_jval_i(source));
  return path;
}

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
  dll_append(q, new_jval_i(source));
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
      printf("-1 .ROUTE NOT FOUND\n");
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

    k = jval_i(jrb_find_int(cost, u)->val); //gia tri cua cost u
    jrb_insert_int(visited, u, new_jval_i(1));
    adjs = outgoingVertices(g, u);
    dll_traverse(n, adjs)
    {
      if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
      {
        node = jrb_find_int(cost, jval_i(dll_val(n))); //gia tri cua cost node
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

  printf("Do dai duong di la: %d\nDuong di: ", u);
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

// void topologicalSort(Graph g)
// {
//     JRB visited = make_jrb();
//     Dllist q = new_dllist();
//     Dllist n;
//     Dllist adjs;
//     Dllist topo = new_dllist();
//     int i, u;
//     if (!isDAG(g))
//     {
//         printf("Graph is not DAG!\n");
//         free_dllist(adjs);
//         jrb_free_tree(visited);
//         free_dllist(q);
//         free_dllist(topo);
//         return;
//     }
//     dll_append(q, new_jval_i(0));
//     while (!dll_empty(q))
//     {
//         n = dll_first(q);
//         u = jval_i(dll_val(n));
//         dll_delete_node(n);
//         if (jrb_find_int(visited, u) == NULL)
//         {
//             dll_prepend(topo, new_jval_i(u));

//             jrb_insert_int(visited, u, new_jval_i(1));
//             adjs = outgoingVertices(g, u);

//             dll_rtraverse(n, adjs)
//             {
//                 if (jrb_find_int(visited, jval_i(dll_val(n))) == NULL)
//                     dll_append(q, dll_val(n));
//             }
//             free_dllist(adjs);

//         }
//     }
//     dll_traverse(n, topo)
//     {
//         printf("%4d", jval_i(dll_val(n)));
//     }
//     printf("\n");
//     jrb_free_tree(visited);
//     free_dllist(q);
//     free_dllist(topo);
// }