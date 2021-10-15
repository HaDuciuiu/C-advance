#include <stdio.h>
#include "directed_graph.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printWeb(Graph g, int id);
int getLinkOutNumber(Graph g, int id);
int getLinkInNumber(Graph g, int id);
void cau1(Graph g);
double getRank(int id, JRB rank);
JRB PageRank(Graph g, JRB rank_old);
void cau2(Graph g, JRB tree_rank);
int isnumber(char *A);
void cau3(Graph g, JRB tree_rank);
int main()
{
  int key, check = 0;
  int n, i;
  int a, b;
  Graph g = createGraph();
  FILE *ptr;
  JRB tree_rank = make_jrb(), node;
  double rank;
  char A[100], B, D[100];
  Dllist list;
  while (1)
  {
    printf("\n-------PageRank-------\n"
           "1.Doc du lieu va in theo yeu cau\n"
           "2.Thuc hien PageRank\n"
           "3.Thuc hien PageRank m lan\n"
           "4.In ra webpage chi co link den, in ra spambot\n"
           "5.In ra khoang cach nho nhat giua 2 web\n"
           "6.Thoat va giai phong bo nho\n"
           "Choose: ");
    scanf("%d%*c", &key);
    printf("\n");
    switch (key)
    {
    case 1:
      if ((ptr = fopen("webpages.txt", "r")) == NULL)
      {
        printf("File webpages.txt is not exist!\n");
        return 1;
      }
      check = 1;
      fscanf(ptr, "%d%*c", &n);
      printf("Webpages number: %d\n", n);
      for (i = 0; i < n; i++)
      {
        fscanf(ptr, "%s%d%*c", A, &a);
        addVertex(g, a, A);
        printf("%-80s%d\n", A, a);
      }
      fclose(ptr);
      if ((ptr = fopen("pageConnections.txt", "r")) == NULL)
      {
        printf("File pageConnections.txt is not exist!\n");
        return 1;
      }
      fscanf(ptr, "%d%*c", &n);    
      for (i = 0; i < n; i++)
      {
        B = '1';
        fscanf(ptr, "%d", &a);
        while (B != '\n')                    
        {                                  
          fscanf(ptr, "%c", &B);            
          if (B == '\n' || feof(ptr))      
            break;
          fscanf(ptr, "%d", &b);
          addEdge(g, a, b, 1);
        }
      }
      fclose(ptr);
      cau1(g);
      break;
    case 2:
      jrb_traverse(node, g.vertices)
      {
        jrb_insert_int(tree_rank, jval_i(node->key), new_jval_d(1));
      }
      tree_rank = PageRank(g, tree_rank);
      cau2(g, tree_rank);
      break;
    case 3:
      printf("Nhap m: ");
      scanf("%d%*c", &n);
      for (i = 0; i < n; i++)
      {
        tree_rank = PageRank(g, tree_rank);
      }
      printf("3 webpage quan trong nhat la:\n");
      cau3(g, tree_rank);
      break;
    case 4:
      printf("Web chi co lien ket den:\n");
      jrb_traverse(node, g.vertices)
      {
        if (getLinkOutNumber(g, jval_i(node->key)) == 0)
        {
          printWeb(g, jval_i(node->key));
        }
      }
      printf("\nSpambot:\n");
      jrb_traverse(node, g.vertices)
      {
        if (getLinkInNumber(g, jval_i(node->key)) == 0)
        {
          printWeb(g, jval_i(node->key));
        }
      }
      break;
    case 5:
      printf("Input souce: ");
      scanf("%[^\n]%*c", A);
      printf("Input dest: ");
      scanf("%[^\n]%*c", D);
      a = atoi(A);
      b = atoi(D);
      printf("Result: ");
      if (check == 0)
      {
        printf("Khong ton tai du lieu doc vao\n");
        break;
      }
      else if (a == b)
      {
        printf("-1\n");
        break;
      }
      else if (!isnumber(A))
      {
        printf("Source khong hop le!\n");
        break;
      }
      else if (!isnumber(D))
      {
        printf("Dest khong hop le!\n");
        break;
      }
      i = (int)shortestPath(g, a, b);
      if (i == INFINITIVE_VALUE)
        printf("Khong ton tai duong di tu webpage id: %d den webpage id: %d\n", a, b);
      else
        printf("%d\n", i);
      break;
    case 6:
      dropGraph(g);
      jrb_free_tree(tree_rank);
      return 0;

    default:
      printf("Please choose only 1-6\n");
      break;
    }
  }
}

void printWeb(Graph g, int id)
{
  printf("%-80s%d\n", getVertexName(g, id), id);
}

int getLinkOutNumber(Graph g, int id)
{
  Dllist list, nodedll;
  int n = 0;
  list = outgoingVertices(g, id);
  dll_traverse(nodedll, list)
  {
    n++;
  }
  free_dllist(list);
  return n;
}

int getLinkInNumber(Graph g, int id)
{
  Dllist list, nodedll;
  int n = 0;
  list = incomingVertices(g, id);
  dll_traverse(nodedll, list)
  {
    n++;
  }
  free_dllist(list);
  return n;
}

void cau1(Graph g)
{
  JRB node;
  int max = 0, min = INFINITIVE_VALUE, link;

  jrb_traverse(node, g.vertices)
  {
    link = getLinkOutNumber(g, jval_i(node->key));
    if (link > max)
      max = link;
    if (link < min)
      min = link;
  }

  printf("\nId trang web co nhieu lien ket nhat la:\n");
  jrb_traverse(node, g.vertices)
  {
    link = getLinkOutNumber(g, jval_i(node->key));
    if (link == max)
      printWeb(g, jval_i(node->key));
  }

  printf("\n\nId trang web co it lien ket nhat la:\n");
  jrb_traverse(node, g.vertices)
  {
    link = getLinkOutNumber(g, jval_i(node->key));
    if (link == min)
      printWeb(g, jval_i(node->key));
  }
  printf("\n\n");
}
double getRank(int id, JRB rank)
{
  JRB node;
  jrb_traverse(node, rank)
  {
    if (jval_i(node->key) == id)
    {
      return jval_d(node->val);
    }
  }
  return INFINITIVE_VALUE;
}

JRB PageRank(Graph g, JRB rank_old) //Khó để thả đổi giá trị val của toàn bộ cây JRB
{                                   //Nên phải free jrb cũ và cho return jrb mới
  Dllist list, nodedll;
  JRB node;
  JRB rank_new = make_jrb();
  double rank;
  int id;
  jrb_traverse(node, rank_old)
  {
    rank = 0;
    list = incomingVertices(g, jval_i(node->key));
    dll_traverse(nodedll, list)
    {
      id = jval_i(dll_val(nodedll));
      rank = rank + getRank(id, rank_old) / getLinkOutNumber(g, id);
    }
    jrb_insert_int(rank_new, jval_i(node->key), new_jval_d(rank));
    free_dllist(list);
  }
  jrb_free_tree(rank_old);
  return rank_new;
}
void cau2(Graph g, JRB tree_rank)
{
  JRB node;
  double rank, rank_max = 0, rank_min = INFINITIVE_VALUE;
  int id, id_max, id_min;
  jrb_traverse(node, tree_rank)
  {
    id = jval_i(node->key);
    rank = jval_d(node->val);
    if (rank > rank_max)
      rank_max = rank;
    if (rank < rank_min)
      rank_min = rank;
  }
  printf("\nRank max: \n");
  jrb_traverse(node, tree_rank)
  {
    id = jval_i(node->key);
    rank = jval_d(node->val);
    if (rank == rank_max)
      printWeb(g, id);
  }
  printf("\n\nRank min: \n");
  jrb_traverse(node, tree_rank)
  {
    id = jval_i(node->key);
    rank = jval_d(node->val);
    if (rank == rank_min)
      printWeb(g, id);
  }
  printf("\n");
}

int isnumber(char *A)
{
  for (int i = 0; i < strlen(A); i++)
  {
    if (!isdigit(A[i]))
      return 0;
  }
  return 1;
}

void cau3(Graph g, JRB tree_rank)
{
  int count = 0;
  JRB tree_rank_temp = make_jrb(), node;
  double rank, rank_max;
  jrb_traverse(node, tree_rank)
  {
    jrb_insert_int(tree_rank_temp, jval_i(node->key), new_jval_d(jval_d(node->val)));
  }
  while (count != 3)
  {
    rank_max = 0;
    jrb_traverse(node, tree_rank_temp)
    {
      rank = jval_d(node->val);
      if (rank > rank_max)
        rank_max = rank;
    }
    jrb_traverse(node, tree_rank_temp)
    {
      rank = jval_d(node->val);
      if (rank == rank_max)
      {
        printWeb(g, jval_i(node->key));
        count++;
        node->val = new_jval_d(-1);
        break;
      }
    }
  }
  jrb_free_tree(tree_rank_temp);
}