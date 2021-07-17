#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jrb.h"
#include "dllist.h"
#define INFINITIVE_VALUE 10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, char *bus_name_i, JRB busname);
int getEdgeValue(Graph graph, int v1, int v2);
int getEdge_Name(Graph graph, int v1, int v2, char *output[]); 
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
void dropGraph(Graph graph);
double shortestPath(Graph graph, int s, int t, int* path, int*length);

int main(int argc, char **argv)
{
   	Graph g = createGraph();
	IS is;
	int i, j, length, path[1000];
    int w; // trong so
	char name1[100]; // Name of station 1
    char name2[100]; // Name of station 2
	JRB busname;
	char *output[100];

	/* ---------------Doc FILE----------------- */ 

	if (argc != 2) { fprintf(stderr, "usage: printwords filename\n"); exit(1); }
	
	/*  Error check. */

	is = new_inputstruct(argv[1]);
	if (is == NULL) {
		perror(argv[1]);
		exit(1);
	}

	int ID = 1; // tong so dinh
	int m,n;
	while (get_line(is) >= 0)
	{
		int count = 0; // so dau '-' trong 1 dong
		for (i = 2; i < is->NF ; i++) {
			busname = (JRB) make_jrb();
			if (count % 2 == 0) {
				name1[0] = '\0';
				strcpy(name1, is->fields[i]);
				for (j = i+1 ; j < is->NF; j++) {
                	if (strcmp(is->fields[j], "-") == 0) break; 
                	strcat(name1, " ");
                    strcat(name1, is->fields[j]);
				}
				//printf("%d\n", j);
				if (!getVertex_Key(g,ID,name1)) {addVertex(g,ID,name1); ID++;}
				n = getVertex_Key(g,ID,name2); m = getVertex_Key(g,ID,name1);
				if (count != 0) {
					addEdge(g,n,m,is->fields[0],busname);
					printf("[BEN %d] %s", m, name1);
				} else printf("[BEN %d] %s", m, name1);
				if (j != is->NF) printf(" - "); else printf("\n");
			}
			if (count % 2 == 1) {
				name2[0] = '\0';
				strcpy(name2, is->fields[i]); 
				for (j = i+1 ; j < is->NF; j++) {
                    if (strcmp(is->fields[j], "-") == 0) break;
                    strcat(name2, " ");
                    strcat(name2, is->fields[j]);
                }
				if (!getVertex_Key(g,ID,name2)) {addVertex(g,ID,name2); ID++;}
				m = getVertex_Key(g,ID,name1); n = getVertex_Key(g,ID,name2);
				addEdge(g,m,n,is->fields[0],busname);
				printf("[BEN %d] %s\n", n, name2);
			}
			count++;
            i = j++;
		}
	}

	printf("-----------------------Map-----------------------\n");
	char option[100];
	while(1) {
		printf("\nContinue? (Yes = 1 || No = 0): "); 
		gets(option);
		if (strcmp(option,"0") == 0) return;
		if (strcmp(option,"0") != 0 && strcmp(option,"1") != 0) {printf("Typing Error!!!"); continue;}
		while(1) {
			printf("-> Enter start: "); gets(name1); 
			if(!getVertex_Key(g,ID,name1)) printf("No bus stop found?? Try Again\n");
			else {printf("%d\n", getVertex_Key(g,ID,name1)); break;}
		}
		while(1) {
			printf("-> Enter stop: "); gets(name2);
			if (!getVertex_Key(g,ID,name2)) printf("No bus stop found?? Try Again\n");
			else {printf("%d\n", getVertex_Key(g,ID,name2)); break;}
		}
		int m = getVertex_Key(g,ID,name1); int n = getVertex_Key(g,ID,name2);
		w = shortestPath(g, m, n, path, &length);
		if (w == INFINITIVE_VALUE)
		{
			printf("-> [MISSING DATA] No bus from %s to %s\n", name1, name2);
		}else
		{
			printf("Path from %s to %s (with number of bus stop %d)\n", name1, name2, w);
			printf(" => %s", getVertex(g, path[0]));
			for (i=1; i<length; i++) {
				printf(" ==(");
				int total = getEdge_Name(g, path[i-1], path[i], output);
				for (j = 0; j < total; j++) printf("[%s]", output[j]);
				printf(")=> ");
				printf("%s", getVertex(g, path[i]));
			}
		}
		printf("\n");
	}

	/*--------------------------Test---------------------------*/
	/*printf("Start: "); gets(name1); i = getVertex_Key(g,ID,strdup(name1)); printf("%d\n", i);
	printf("Stop: "); gets(name2); j = getVertex_Key(g,ID,strdup(name2)); printf("%d\n", j);
	int total = getEdge_Name(g, i, j, output); printf("%d\n", total);
	for (i = 0; i < total; i++) {
		printf("%s\n", output[i]);
	}*/

	dropGraph(g);
	return 0;
}

Graph createGraph()
{
   Graph g; 
   g.edges = make_jrb();  
   g.vertices = make_jrb();  
   return g;
}

void addVertex(Graph g, int id, char* bus_stop)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL) // only add new vertex
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(bus_stop)));            
}

char *getVertex(Graph g, int id)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL) 
    	return NULL;
    else                
        return jval_s(node->val);
}     

int getVertex_Key(Graph g, int total_ID, char *bus_stop)
{
	JRB node;
	int i;
	for (i = 1; i < total_ID; i++)
		if (strcasecmp(getVertex(g,i),strdup(bus_stop)) == 0) return i;
	return 0;
}

void addEdge(Graph graph, int v1, int v2, char *bus_name_i, JRB busname)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL) {
        tree = make_jrb();
       	jrb_insert_int(graph.edges, v1, new_jval_v(tree));
		//jrb_insert_int(busname, strdup(bus_name_i), new_jval_s(strdup(bus_name_i)));
    	//jrb_insert_int(tree, v2, new_jval_v(busname));
    } else
    {
        tree = (JRB) jval_v(node->val);  
	}	
	node = jrb_find_int(tree, v2);
	if (node == NULL) {
		jrb_insert_int(busname, strdup(bus_name_i), new_jval_s(strdup(bus_name_i)));
    	jrb_insert_int(tree, v2, new_jval_v(busname));
	} else 
	{
		JRB busname = (JRB) jval_v(node->val);
		jrb_insert_str(busname, strdup(bus_name_i), new_jval_s(strdup(bus_name_i)));
		//jrb_insert_int(tree, v2, new_jval_v(busname));
	}
}

int getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
       	return INFINITIVE_VALUE;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
      	return INFINITIVE_VALUE;
    else
       	return 1;     
}

int getEdge_Name(Graph graph, int v1, int v2, char *output[])
{
    JRB node, tree;
	int total = 0;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
       	return NULL;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
      	return NULL;
    else {
		JRB busname = (JRB) jval_v(node->val);
		jrb_traverse(node, busname)
		{
			output[total] = malloc(sizeof(char) * strlen(jval_s(node->key)));
			strcpy(output[total], jval_s(node->key));
			total++;
		}
	}
	return total;
}

int indegree (Graph graph, int v, int* output) // KO dung den
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
    if (node == NULL)
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

double shortestPath(Graph g, int s, int t, int *path, int *length)
{
	int distance[1000], min, w, total;
	int previous[1000], tmp[1000], visit[1000];
	int n, output[100], i, u, v, start;
	Dllist ptr, queue, node;

	for (i=0; i<1000; i++)
	distance[i] = INFINITIVE_VALUE;
	distance[s] = 0;
	previous[s] = s;
	visit[s]=1;
		
	queue = new_dllist();
	dll_append(queue, new_jval_i(s));

	while ( !dll_empty(queue) )
	{
		// get u from the priority queue   
		min = INFINITIVE_VALUE;   
		dll_traverse(ptr, queue)
		{
			u = jval_i(ptr->val);              
			if (min > distance[u])
			{
				min = distance[u];
				node = ptr;
			}                 
		}
		u = jval_i(node->val);
		visit[u] = 1;
		dll_delete_node(node);
		
		if (u == t) break; // stop at t
		
		n = outdegree(g, u, output);
		for (i=0; i<n; i++)
		{
			v = output[i];
			w = getEdgeValue(g, u, v);
			if ( distance[v] > distance[u] + w )
			{    
				distance[v] = distance[u] + w;
				previous[v] = u;
			}
			if (visit[v] == 0) dll_append(queue, new_jval_i(v));
		}
	}
	total = distance[t];
	if (total != INFINITIVE_VALUE)
	{
		tmp[0] = t;
		n = 1;              
		while (t != s)
		{
			t = previous[t];
			tmp[n++] = t;
		}
		for (i=n-1; i>=0; i--)
			path[n-i-1] = tmp[i];
		*length = n;                
	}
	return total;   
}

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