#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE  10000000

typedef struct {
    JRB edges; //cạnh
    JRB vertices; //đỉnh
} Graph;

typedef struct{
    JRB ten_tuyen;
    int weight;
}data;

data *p;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, char *v1, char *v2, char *cur_tuyen, data *p);
int getEdgeValue(Graph graph, char *v1, char *v2, char *cur_tuyen);
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void dropGraph(Graph graph);
//double shortestPath(Graph graph, int s, int t, int* path, int*length);
void DocFile(FILE *f, Graph graph);




int main()
{
    //  int i, length, path[100], s, t;
	//  double w;
	//  Graph g = createGraph();
	//  addVertex(g, 0, "V0");
	//  addVertex(g, 1, "V1");
	//  addVertex(g, 2, "V2");
	//  addVertex(g, 3, "V3");
	//  addEdge(g, 0, 1, 1);
	//  addEdge(g, 1, 2, 3);
	//  addEdge(g, 2, 0, 3);
	//  addEdge(g, 1, 3, 1);
	//  addEdge(g, 3, 2, 1);
	//  s = 0;
	//  t = 2;
	//  w = shortestPath(g, s, t, path, &length);
	//  if (w == INFINITIVE_VALUE)
	//  {
	//       printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
	//  }else
	//  {
	//       printf("Path from %s to %s (with total distance %f)\n", getVertex(g, s), getVertex(g, t), w);
	//       for (i=0; i<length; i++)
	//           printf(" => %s", getVertex(g, path[i]));
	//  }
	FILE *f;
	Graph g = createGraph();
	f = fopen("input1.txt","r");
	DocFile(f,g);
	display(g);
	fclose(f);
	dropGraph(g);
}

void DocFile(FILE *f, Graph g)
{
    data *p;
    p = malloc(sizeof(data));
	f = fopen("input1.txt", "r");
	char tmp[100];
	fgets(tmp, 100, f);
	char ten_ben_1[100];
	ten_ben_1[0] = '\0';
	char ten_tuyen[100];
	char ten_ben_2[100];
	ten_ben_2[0] = '\0';
	while(!feof(f))
	{
		fscanf(f, "%s", ten_tuyen);
		fscanf(f, "%s", tmp);//doc dau 2 cham
		fscanf(f, "%s", tmp);//doc cum dau tien cua ten ben
		while(1)
		{
			while(tmp[0] != '-' && tmp[0] != '.')
			{
				strcat(ten_ben_1, tmp);
				strcat(ten_ben_1, " ");
				fscanf(f, "%s", tmp);

			}
			tmp[0] = '\0';
			fscanf(f, "%s", tmp);
			while(tmp[0] != '-' && tmp[0] != '.')
			{
				strcat(ten_ben_2, tmp);
				strcat(ten_ben_2, " ");
				fscanf(f, "%s", tmp);
			}
			p->weight = 1;
			p->ten_tuyen = make_jrb();
			addEdge(g, ten_ben_1, ten_ben_2, ten_tuyen, p);
			if (tmp[0] == '.')
			{
			    ten_tuyen[0] = '\0';
			    ten_ben_1[0] = '\0';
                ten_ben_2[0] = '\0';
				break;
			}else
			{
				fseek(f, -((strlen(ten_ben_2) -1) + 2), SEEK_CUR);//vi luc nay ten_ben_2 co dau ' ' o cuoi
				fscanf(f, "%s", tmp);
			}
			ten_ben_1[0] = '\0';
			ten_ben_2[0] = '\0';
		}
	}
}

Graph createGraph()
{
	Graph g;
	g.edges = make_jrb();
	g.vertices = make_jrb();
	return g;
}

void addVertex(Graph g, int id, char* name)
{
	JRB node = jrb_find_int(g.vertices, id);
	if (node==NULL) // only add new vertex
		jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));   //key: id đỉnh, data:tên bến
}

char *getVertex(Graph g, int id) //lấy đỉnh
{
	JRB node = jrb_find_int(g.vertices, id); //tìm đỉnh trong graph
	if (node==NULL)
		return NULL;
	else
		return jval_s(node->val); //return tên biến
}

void addEdge(Graph graph, char *v1, char *v2, char *cur_tuyen, data *p)
{
	JRB node, tree;
	if (getEdgeValue(graph, v1, v2, cur_tuyen) == 0) //nếu khoảng cách = vô cùng
	{
		node = jrb_find_str(graph.edges, strdup(v1)); //tìm v1
		if (node==NULL) {
			tree = make_jrb();
			jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
		} else
		{
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_str(p->ten_tuyen, strdup(cur_tuyen), new_jval_s(strdup(cur_tuyen)));
		jrb_insert_str(tree, v2, new_jval_v((void *) p));
	}
}

int getEdgeValue(Graph graph, char *v1, char *v2, char *cur_tuyen)
{
	JRB node, tree;
	node = jrb_find_str(graph.edges, strdup(v1));
	if (node==NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	node = jrb_find_str(tree, strdup(v2));
	if (node==NULL)
		return 0;
	if(node != NULL) //da co v2, tim xem ten_tuyen da co trong data->ten_tuyen chua?
    {
        data *p;
        p = malloc(sizeof(data));
        p = (JRB) node->val.v;
        JRB tmp;
        tmp = jrb_find_str(p->ten_tuyen, strdup(cur_tuyen));
        if(tmp == NULL)
            return 0;
    }
    return 1;
}

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

//double shortestPath(Graph g, int s, int t, int* path, int*length)
//{
//	double distance[1000], min, w, total;
//	int previous[1000], tmp[1000];
//	int n, output[100], i, u, v, start;
//	Dllist ptr, queue, node;
//
//	for (i=0; i<1000; i++)
//		distance[i] = INFINITIVE_VALUE;
//	distance[s] = 0;
//	previous[s] = s;
//
//	queue = new_dllist();
//	dll_append(queue, new_jval_i(s));
//
//	while ( !dll_empty(queue) )
//	{
//		// get u from the priority queue
//		min = INFINITIVE_VALUE;
//		dll_traverse(ptr, queue)
//		{
//			u = jval_i(ptr->val);
//			if (min > distance[u])
//			{
//				min = distance[u];
//				node = ptr;
//			}
//		}
//		dll_delete_node(node);
//
//		if (u == t) break; // stop at target
//
//		n = outdegree(g, u, output);
//		for (i=0; i<n; i++)
//		{
//			v = output[i];
//			w = getEdgeValue(g, u, v);
//			if ( distance[v] > distance[u] + w )
//			{
//				distance[v] = distance[u] + w;
//				previous[v] = u;
//			}
//			dll_append(queue, new_jval_i(v));
//		}
//	}
//	total = distance[t];
//	if (total != INFINITIVE_VALUE)
//	{
//		tmp[0] = t;
//		n = 1;
//		while (t != s)
//		{
//			t = previous[t];
//			tmp[n++] = t;
//		}
//		for (i=n-1; i>=0; i--)
//			path[n-i-1] = tmp[i];
//		*length = n;
//	}
//	return total;
//}

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

void display(Graph g)
{
    JRB node1, node2, tree;
    jrb_traverse(node1, g.edges)
	{
		tree = (JRB) jval_v(node1->val);
		jrb_traverse(node2, tree)
		{
		    printf("%s\n", node2->key);
		}
	}
	jrb_free_tree(g.edges);
	jrb_free_tree(g.vertices);
}
