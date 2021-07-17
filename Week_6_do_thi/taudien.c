#include<stdio.h>
#include<stdlib.h>
#include "Graphjrb.h"
#include <string.h>
typedef struct{
  char id[5];
  char name[20];
} taudien;

int search(taudien A[],int n, char *x){
  int i;
  for(i=0;i<n;i++){
    if(strcmp(x, A[i].name)==0)
      return i;
  }
  return -1;
}
int search2(taudien A[], int n, char *x){
  int i;
  for(i=0;i<n;i++){
    if(strcmp(x, A[i].id)==0)
      return i;
  }
}
int main(){
  int i,j=0, count, n, count2;
  taudien T[100];
  Graph tmp;
  Graph G= createGraph();
  char *output[100], c, A[101], B[100];
  FILE *fptr;
  fptr=fopen("taudien.txt", "r+");
  if(fptr == NULL) {
    printf("Cannot open file\n");
    return 1;
  }
  count = 0;
  while(1){
    fscanf(fptr, "%[^\n]%*c", A);
    if(strcmp(A, "LINE") == 0) break;
    count++;
  }
  // Count is correct (= 10)
  if(fseek(fptr, 0, SEEK_SET)!=0) {
    printf("Fseek failed.\n");
    return 1;
  }
  for(int i=0;i<count;i++){
    fscanf(fptr,"%[^=]%*c%[^\n]%*c", T[j].id, T[j].name);
    j++;
  }
  count2 = count;
  fgets(A, 100, fptr);
  count = 0;
  while(fgets(A, 100, fptr) != NULL) count++;
  // count is correct.
  if(fseek(fptr, 0 , SEEK_SET)!= 0){
    printf("Fseek failed\n");
    return 1;
    }
  while(1){
    fscanf(fptr, "%[^\n]%*c", A);
    if(strcmp(A, "LINE") == 0) break;
    }
  // FILE pointer's location is correct.
  for(i=0;i<count-1;i++){
    fscanf(fptr,"%[^=]%*c", A);
    fscanf(fptr, "%s%*c",A);
    while(1){
      fscanf(fptr, "%s", B);
      addEdge(G, strdup(A), strdup(B));
      strcpy(A, B);
      c=fgetc(fptr);
      if(c=='\n') break;
    }
  }
  printf("Enter name of Station: ");
  scanf("%[^\n]", A);
  j=search(T, count2, A);
  if(j==-1) printf("%s is not found\n", A);
  else{
    jrb_traverse(tmp, G){
      if(strcmp(T[j].id, jval_s(tmp->key)) == 0){
	printf("%s: ", T[j].name);
	n = getAdjacentVertices(G, jval_s(tmp->key), output);
	for(i=0;i<n;i++){
	  count= search2(T, count2, output[i]);
	  printf("%s ", T[count].name);
	}
	printf("\n");
      }
    }
  }
  dropGraph(G);
  fclose(fptr);
  return 0;
}
