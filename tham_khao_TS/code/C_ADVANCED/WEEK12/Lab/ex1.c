#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../libfdr/jrb.h"
#include "../../libfdr/dllist.h"

#define INFINITIVE_VALUE 10000000

typedef struct
{
  JRB edges;
  JRB vertices;
} Graph;

typedef struct
{
  Graph graph;
  int rootID;
} HuffmanTree;

typedef Dllist PriorityQueue;

typedef struct
{
  int size;
  char bits[20]; // maximum 20 bits, it is safe enough
} Coding;

typedef struct
{
  int size;
  int *nodes;
} HuffmanTreeArray;

Graph createGraph();
void addVertex(Graph graph, int id, int letter);
int getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2, int weight);
int getEdgeValue(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
void dropGraph(Graph graph);

void add2Queue(PriorityQueue q, int graphnode, int frequence);
HuffmanTree makeHuffmanFromFile(char *inFile);
void createHuffmanTable(HuffmanTree htree, Coding htable[]);
HuffmanTreeArray tree2array(HuffmanTree tree);
void compressFile(char *, char *);

Graph createGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void addVertex(Graph g, int id, int letter)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node == NULL) // only add new vertex
    jrb_insert_int(g.vertices, id, new_jval_i(letter));
}

int getVertex(Graph g, int id)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node == NULL)
    return 0;
  else
    return jval_i(node->val);
}

void addEdge(Graph graph, int v1, int v2, int weight)
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
    jrb_insert_int(tree, v2, new_jval_i(weight));
  }
}

int getEdgeValue(Graph graph, int v1, int v2)
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
    return jval_i(node->val);
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

void add2Queue(PriorityQueue q, int graphnode, int frequence)
{
  Dllist node = dll_first(q);
  while (node != q)
  {
    // printf("Node %d %d\n", jval_iarray(dll_val(node))[0], jval_iarray(dll_val(node))[1] );
    if (frequence <= dll_val(node).iarray[1])
      break;
    node = dll_next(node);
  }
  if (node == q)
  {
    // printf("Node nil\n");
    dll_append(q, new_jval_iarray(graphnode, frequence));
  }
  else
  {
    // printf("Before %d %d\n", jval_iarray(dll_val(node))[0], jval_iarray(dll_val(node))[1] );
    dll_insert_b(node, new_jval_iarray(graphnode, frequence));
  }
}

HuffmanTree makeHuffmanFromFile(char *inFile)
{
  int lastNodeID = 0;
  HuffmanTree hTree;
  int i, fTable[256] = {};
  Dllist n1, n2;
  FILE *in;

  if ((in = fopen(inFile, "r")) == NULL) exit(1);

  char c;
  while (!feof(in))
  {
    if((c = fgetc(in)) != -1) fTable[c]++;
  }

  PriorityQueue queue = new_dllist();
  hTree.graph = createGraph();

  for (i = 0; i < 256; i++)
    if (fTable[i])
    {
      // make new graphNode to add to the priority queue
      lastNodeID++;
      addVertex(hTree.graph, lastNodeID, i);
      add2Queue(queue, lastNodeID, fTable[i]);
      // printf("last %d %c %d\n", lastNodeID, i, fTable[i]);
    }

  /*	for (n1 = dll_first(queue); n1!=queue; n1=dll_next(n1))
	{
		printf("%d %d\n", jval_iarray(dll_val(n1))[0], jval_iarray(dll_val(n1))[1]);
	}
*/
  // regroup nodes in priority queue
  for (;;)
  {
    n1 = dll_first(queue);
    if (n1 == queue)
      break;
    n2 = dll_next(n1);
    if (n2 == queue)
      break;
    // add new node in the graph
    lastNodeID++;
    addVertex(hTree.graph, lastNodeID, -1);
    addEdge(hTree.graph, lastNodeID, dll_val(n1).iarray[0], 0);
    addEdge(hTree.graph, lastNodeID, dll_val(n2).iarray[0], 1);
    //printf("last %d\n", lastNodeID);
    // modify the queue
    dll_delete_node(n1);
    dll_delete_node(n2);
    add2Queue(queue, lastNodeID, dll_val(n1).iarray[1] + dll_val(n2).iarray[1]);
  }
  n1 = dll_first(queue);
  if (n1 == queue)
    hTree.rootID = 0;
  else
    hTree.rootID = dll_val(n1).iarray[0];

  free_dllist(queue);
  fclose(in);

  return hTree;
}

void getCode(int node, Graph g, int len, char code[], Coding htable[])
{
  int ch, k, i;
  int output[10];
  ch = getVertex(g, node);
  if (ch != -1)
  {
    htable[ch].size = len;
    memcpy(htable[ch].bits, code, len);
  }
  else
  {
    k = outdegree(g, node, output);
    for (i = 0; i < k; i++)
    {
      code[len] = getEdgeValue(g, node, output[i]);
      getCode(output[i], g, len + 1, code, htable);
    }
  }
}

void createHuffmanTable(HuffmanTree htree, Coding htable[])
{
  int i;
  char code[20];
  for (i = 0; i < 256; i++)
  {
    htable[i].size = 0;
  }
  if (htree.rootID == 0)
    return;
  getCode(htree.rootID, htree.graph, 0, code, htable);
}

void setRoot(int *cursor)
{
  *cursor = 0;
}

void goLeft(int *cursor)
{
  *cursor = 2 * (*cursor) + 1;
}

void goRight(int *cursor)
{
  *cursor = 2 * (*cursor) + 2;
}

HuffmanTreeArray tree2array(HuffmanTree htree)
{
  int i, k, maxlen, size, exp2, cursor;

  HuffmanTreeArray hArray;
  Coding hTable[256];

  createHuffmanTable(htree, hTable);

  maxlen = 0;
  for (i = 0; i < 256; i++)
    if (hTable[i].size > maxlen)
      maxlen = hTable[i].size;
  size = 1;
  exp2 = 1;
  for (i = 1; i <= maxlen; i++)
  {
    exp2 *= 2;
    size += exp2;
  }
  hArray.size = size;
  hArray.nodes = malloc(hArray.size * sizeof(int));
  for (i = 0; i < hArray.size; i++)
    hArray.nodes[i] = -1;
  for (i = 0; i < 256; i++)
  {
    setRoot(&cursor);
    if (hTable[i].size)
    {
      for (k = 0; k < hTable[i].size; k++)
      {
        if (hTable[i].bits[k] == 0)
          goLeft(&cursor);
        else
          goRight(&cursor);
      }
      if (cursor < hArray.size)
        hArray.nodes[cursor] = i;
    }
  }

  return hArray;
}

HuffmanTreeArray makeHuffmanTreeArray(Coding htable[])
{
	int i, k, maxlen, size, exp2, cursor;
	HuffmanTreeArray hArray;

	maxlen = 0;
	for (i = 0; i < 256; i++)
		if (htable[i].size > maxlen)
			maxlen = htable[i].size;
	size = 1;
	exp2 = 1;
	for (i = 1; i <= maxlen; i++)
	{
		exp2 *= 2;
		size += exp2;
	}
	hArray.size = size;
	hArray.nodes = malloc(hArray.size * sizeof(int));
	for (i = 0; i < hArray.size; i++)
		hArray.nodes[i] = -1;
	for (i = 0; i < 256; i++)
	{
		setRoot(&cursor);
		if (htable[i].size)
		{
			for (k = 0; k < htable[i].size; k++)
			{
				if (htable[i].bits[k] == 0)
					goLeft(&cursor);
				else
					goRight(&cursor);
			}
			if (cursor < hArray.size)
				hArray.nodes[cursor] = i;
		}
	}

	//printf("size = %d\n", hArray.size);
	/*for (i=0; i<hArray.size; i++) {
		if (hArray.nodes[i]==-1) printf("-");
		else printf("%c", hArray.nodes[i]);
	}
	printf("\n");
	*/

	return hArray;
}

void destroyHuffmanTreeArray(HuffmanTreeArray hTreeArr)
{
	free(hTreeArr.nodes);
}

void setBit(char *huffman, int nbit, int val)
{
	int i, byte, bit;
	byte = nbit / 8;
	bit = nbit % 8;
	if (val == 0)
	{
		huffman[byte] &= ~(1 << bit);
	}
	else
	{
		huffman[byte] |= (1 << bit);
	}
}

int getBit(char *huffman, int nbit)
{
	int i, byte, bit;
	byte = nbit / 8;
	bit = nbit % 8;
	i = huffman[byte] & (1 << bit);
	return i != 0;
}

void addHuffmanChar(char ch, Coding htable[], char *huffman, int *nbit)
{
	int i;
	for (i = 0; i < htable[ch].size; i++)
	{
		setBit(huffman, *nbit, htable[ch].bits[i]);
		(*nbit)++;
	}
}

void writeHuffmanTable(Coding htable[], FILE *f)
{
	int i, num = 0, n, k;
	char buffer[10];
	num = 0;
	for (i = 0; i < 256; i++)
	{
		if (htable[i].size > 0)
		{
			num++;
		}
	}
	printf("Num of chars: %d\n", num);
	fwrite(&num, sizeof(int), 1, f);
	for (i = 0; i < 256; i++)
	{
		if (htable[i].size > 0)
		{
			fputc(i, f);
			fwrite(&htable[i].size, sizeof(int), 1, f);
			printf("%c: %d bits\n", i, htable[i].size);
			for (k = 0; k < htable[i].size; k++)
				setBit(buffer, k, htable[i].bits[k]);
			n = htable[i].size / 8;
			if (htable[i].size % 8)
				n++;
			fwrite(buffer, n, 1, f);
		}
	}
}

void compressFile(char *inFile, char *outFile){
  int nbit, size, n;
  char *huffman;
  char i;

  FILE *in, *out;

  Coding hTable[256];

  if ((in = fopen(inFile, "r")) == NULL) exit(1);
  if ((out = fopen(outFile, "wb")) == NULL) exit(1);

  fseek(in, 0, SEEK_END);
  size = ftell(in) / sizeof(char);

  printf("Input: %d bytes\n", size);

  if (size==0) return;

  HuffmanTree htree = makeHuffmanFromFile(inFile);
  createHuffmanTable(htree, hTable);
  HuffmanTreeArray huffmanTreeArray = tree2array(htree);

  fseek(out, 0, SEEK_SET);
  fwrite("HM", 2, 1, out);
  writeHuffmanTable(hTable, out);

  fseek(in, 0, SEEK_SET);
  nbit = 0;
	huffman = malloc(size);
	while ((i = fgetc(in)) != -1)
	{
		addHuffmanChar(i, hTable, huffman, &nbit);
	}
	fwrite(&nbit, sizeof(int), 1, out);
	n = nbit / 8;
	if (nbit % 8)
		n++;
	fwrite(huffman, n, 1, out);
	free(huffman);
  printf("Compressed: %d bytes\n", n);

  destroyHuffmanTreeArray(huffmanTreeArray);

  fclose(in);
  fclose(out);
}

void decompressFile(char *input, char *output)
{
	HuffmanTree htree;
	HuffmanTreeArray hArray;
	Coding htable[256] = {};
	int i, k, n = 0, nbit, size, ch, cursor;
	char bits[10];
	char code[2];

	FILE *f1, *f2;

	char *huffman;

	f1 = fopen(input, "rb");
	if (f1 == NULL)
	{
		perror("Can not open input file\n");
		exit(2);
	}

	fread(code, 2, 1, f1);
	if (code[0] != 'H' && code[1] != 'M')
	{
		perror("Bad format\n");
		exit(2);
	}

	/* read huffman code into table */
	fread(&n, sizeof(int), 1, f1);
	printf("Read huffman table: %d chars\n", n);
	for (i = 0; i < 256; i++)
		htable[i].size = 0;
	for (i = 0; i < n; i++)
	{
		ch = fgetc(f1);
		fread(&nbit, sizeof(int), 1, f1);
		printf("%c: %d bits\n", ch, nbit);
		htable[ch].size = nbit;
		k = nbit / 8;
		if (nbit % 8)
			k++;
		fread(bits, k, 1, f1);
		for (k = 0; k < nbit; k++)
			htable[ch].bits[k] = getBit(bits, k);
	}
	hArray = makeHuffmanTreeArray(htable);

	f2 = fopen(output, "w+b");
	if (f2 == NULL)
	{
		perror("Can not open output file\n");
		exit(2);
	}

	/* read huffman data */
	fread(&nbit, sizeof(int), 1, f1);
	size = nbit / 8;
	if (nbit % 8)
		size++;
	huffman = (char *)malloc(size);
	printf("Read huffman data: %d chars\n", size);
	fread(huffman, size, 1, f1);
	setRoot(&cursor);
	for (i = 0; i < nbit; i++)
	{
		if (getBit(huffman, i) == 0)
			goLeft(&cursor);
		else
			goRight(&cursor);
		if (cursor >= hArray.size)
		{
			perror("Decompress error\n");
			exit(1);
		}
		if (hArray.nodes[cursor] != -1)
		{
			fputc(hArray.nodes[cursor], f2);
			setRoot(&cursor);
		}
	}
	free(huffman);
	destroyHuffmanTreeArray(hArray);

	fclose(f1);
	fclose(f2);
}

int main(int argc, char const *argv[])
{
  FILE *in, *out;

  if (argc != 3)
  {
    printf("Thieu tham so!\n");
    return 1;
  }

  printf("Dang nen file!\n");

  compressFile(argv[1], argv[2]);

  printf("Nen file thanh cong!\n\n\n");

  printf("Giai nen file\n");

  char uncompressFile[20];

  sprintf(uncompressFile, "%s_uncompress.txt", argv[2]);

  decompressFile(argv[2], uncompressFile);

  printf("Giai nen file thanh cong!\n");

  return 0;
}