#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef int element;
// ham khoi tao mang du lieu
int *creatArray(int size)
{
	srand((int)time(0));
	int *A = (int*)malloc(size*sizeof(int));
	int i;
	for(i=0;i<size;i++)
	{
		A[i] = rand() % 10;
	}
	return A;
}
// ham doi cho hai phan tu
void exch(int a[],int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
// ham swap - dung cho 2-wayquicksort
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
// thuat toan quicksort
void quicksort(element list[], int left,int right)
{
  int pivot, i, j;
  element temp;
  if (left < right) {
    i = left;    j = right+1;
    pivot = list[left];
    do {
      do i++; while (list[i]< pivot);
      do j--; while (list[j] > pivot);
      if (i < j) swap(&list[i], &list[j]);
    } while (i < j);
    swap(&list[left], &list[j]);
    quicksort(list, left, j-1);
    quicksort(list, j+1, right);
  }
}
// thuat toan 3-way quicksort
void sort3way(int a[],int l , int r)
{
    if(r<=l) return;
    int i = l-1,j=r;
    int p= l-1 , q =r;
    while(1)
    {
        while(a[++i]<a[r]);
        while(a[r]<a[--j]) if(j==l) break;
        if(i>=j) break;
        exch(a,i,j);
        if(a[i]==a[r])exch(a,++p,i);
        if(a[j]==a[r])exch(a,--q,j);
    }
    exch(a,i,r);
    j=i-1;
    i=i+1;
    int k;
    for(k=l;k<=p;k++) exch(a,k,j--);
    for(k=r-1;k>=q;k--) exch(a,k,i++);
    sort3way(a,l,j);
    sort3way(a,i,r);
}
//ham dumArray cho phep sao chep mang A sang mang B
int *dumArray(int *A, int size)
{
	int *B = (int*)malloc(size*sizeof(int));
	memcpy(B,A,size*sizeof(int));// vi kich thuoc cua A la size*sizeof(int) - quy doi ra bytes
	return B;
}
void printArr(int Arr[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%d\n",Arr[i]);
	}
}
int main()
{
	int *A , *B ,*A1,*A2;
	int i;
	int size = 10000000;// kich thuoc nay thay doi tuy ban
	int small_size = 20;
	A1 = creatArray(small_size);
	A2 = dumArray(A1,small_size);// copy mang A1 sang mang A2 nho ham dumArray
	sort3way(A1,0,small_size-1);
	printArr(A2,small_size);//in ra mang A2 de biet duoc mang ban dau
	printf("Mang sau khi duoc sap xep:\n");
	printArr(A1,small_size);
	A = creatArray(size);
	B = dumArray(A,size);
	clock_t start,end;
	start = clock();
	quicksort(A,0,size-1);
	end = clock();
	double time;
	time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Run in %f seconds.\n",time);
	printf("\n Thuat toan Sort3Way:\n");
	start = clock();
	sort3way(B,0,size- 1);
	end = clock();
	time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Run in %f seconds.\n", time);
	printf("\n----------------------------\n");
  return 0;
}

