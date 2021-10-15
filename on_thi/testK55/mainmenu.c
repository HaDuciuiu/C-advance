#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directed_graph.h"

void cau2(Graph g);
void recursionDFSnguoc(Graph g, int source, JRB visited, Dllist stack);
void cau4(Graph g);
int timeMaxRecursion(Graph g, int dest);
void cau5(Graph g);
int main()
{
  int key;
  char A[100], B, C;
  Graph g = createGraph();
  JRB node;
  Dllist nodedll;
  FILE *ptr;
  int edge, source, dest, time;
  while (1)
  {
    printf("\n\nChuong trinh quan ly cong viec\n"
           "1.Doc tep du lieu, in ra tong so nut va so cung cua do thi topo\n"
           "2.Nhap vao mot cong viec va in ra thong bao\n"
           "3.Thuc hien cong viec\n"
           "4.In mot thu tu sap xep cong viec thu tu truoc->sau\n"
           "5.Nhap vao cong viec, in ra thoi gian hoan thanh toi thieu\n"
           "6.Kiem tra do thi co phai la DAG\n"
           "7.Thoat va giai phong bo nho\n"
           "Choose: ");
    scanf("%d%*c", &key);
    switch (key)
    {
    case 1:
      printf("Input file name: ");
      scanf("%s%*c", A);
      if ((ptr = fopen(A, "r")) == NULL)
      {
        printf("File %s is not exist!\n", A);
        return 1;
      }
      fgets(A, 100, ptr);
      C = A[strlen(A) - 2];
      fseek(ptr, SEEK_SET, 0);
      edge = 0;
      while (!feof(ptr))
      {
        fscanf(ptr, "%s%*c%*c", A);
        dest = atoi(&A[1]);
        addVertex(g, dest, A);
        fscanf(ptr, "%c", &B);

        while ((B != C) && (!feof(ptr)))
        {
          fscanf(ptr, "%[^-]%*c%d", A, &time);
          source = atoi(&A[1]);
          addVertex(g, source, A);
          addEdge(g, source, dest, time);
          edge++;
          fscanf(ptr, "%c", &B);
        }
      }
      fclose(ptr);
      source = 0;
      jrb_traverse(node, g.vertices)
      {
        source++;
      }
      printf("So cong viec: %d\nSo cung cua do thi topo: %d\n", source, edge);
      break;
    case 2:
      cau2(g);
      break;
    case 3:
      printf("Co muon thuc hien lai cong viec 3 nua khong? (y/n)\n");
      scanf("%c%*c", &B);
      if (B == 'y')
      {
        cau2(g);
      }
      else if (B == 'n')
      {
        cau4(g);
      }
      else
      {
        printf("Chi duoc chon y hoac n\n");
      }
      break;
    case 4:
      cau4(g);
      break;
    case 5:
      cau5(g);
      break;
    case 6:
      printf("%s\n", isDAG(g) ? "Hop le!" : "Khong hop le!");
      break;
    case 7:
      dropGraph(g);
      return 0;

    default:
      printf("Please choose only 1-7\n");
      break;
    }
  }
}
void cau2(Graph g)
{
  char name[100];
  int id, n;
  Dllist list, nodedll;
  JRB visited = make_jrb();
  printf("Nhap ten cong viec: ");
  scanf("%s%*c", name);
  id = getVertexId(g, name);
  if (id == -1)
  {
    printf("Cong viec khong co trong chuong trinh\n");
    return;
  }
  n = incomingVerticesNumber(g, id);
  printf("I. So luong cong viec can phai lam ngay truoc la: %d cong viec\n", n);
  list = incomingVertices(g, id);
  printf("List cong viec: ");
  dll_traverse(nodedll, list)
  {
    printf("%s ", getVertexName(g, jval_i(dll_val(nodedll))));
  }
  printf("\n\n");
  free_dllist(list);

  list = new_dllist();
  recursionDFSnguoc(g, id, visited, list);
  n = 0;
  dll_delete_node(dll_last(list));
  dll_traverse(nodedll, list)
  {
    n++;
  }
  printf("II. So luong tat ca cong viec phai lam truoc la: %d cong viec\n", n);

  printf("List tat ca cong viec: ");
  dll_traverse(nodedll, list)
  {
    printf("%s ", getVertexName(g, jval_i(dll_val(nodedll))));
  }
  printf("\n");
  free_dllist(list);
  jrb_free_tree(visited);
}

void recursionDFSnguoc(Graph g, int source, JRB visited, Dllist stack)
{
  Dllist queue, node;
  if (jrb_find_int(visited, source) == NULL)
  {
    jrb_insert_int(visited, source, new_jval_i(1));
    queue = incomingVertices(g, source);
    dll_rtraverse(node, queue)
        recursionDFSnguoc(g, jval_i(dll_val(node)), visited, stack);
    dll_append(stack, new_jval_i(source));

    free_dllist(queue);
  }
}

void cau4(Graph g)
{
  Dllist list, nodedll;
  list = topologicalSort(g);
  dll_traverse(nodedll, list)
  {
    printf("%s ", getVertexName(g, jval_i(dll_val(nodedll))));
  }
  printf("\n");
}

void cau5(Graph g)
{
  JRB node;
  int id;
  jrb_traverse(node, g.vertices)
  {
    id = jval_i(node->key);
    printf("%s: %d\n", getVertexName(g, id), timeMaxRecursion(g, id));
  }
}

int timeMaxRecursion(Graph g, int dest)
{
  Dllist list, nodedll;
  int max = 0, source, value;
  if (incomingVerticesNumber(g, dest) == 0)
  {
    return max;
  }
  list = incomingVertices(g, dest);
  dll_traverse(nodedll, list)
  {
    source = jval_i(dll_val(nodedll));
    value = timeMaxRecursion(g, source) + getEdgeValue(g, source, dest);
    if (value > max)
    {
      max = value;
    }
  }
  free_dllist(list);
  return max;
}