#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Week_4_cay_do_den/jrb.h"
#include"Week_4_cay_do_den/dllist.h"

#define INFINITIVE 10000000 // mot gia tri vo cung
// khoi tao mot cau truc graph
typedef struct 
{
    JRB vertices;// tap dinh
    JRB edges;// tap canh
}Graph;

// khai bao cac nguyen mau ham
Graph createGraph(); // ham tao mot do thi
void addVertex(Graph graph, int id , char name);// ham them mot dinh vao do thi
char *getVertex(Graph graph,int id);// ham lay ra mot canh
void addEgde(Graph graph,int v1 , int v2 , double weight);// ham add mot canh vao do thi
double getEgdeValue(Graph graph, int v1 , int v2);// ham tra ve gia tri theo value
int main()
{
    return 0;
}