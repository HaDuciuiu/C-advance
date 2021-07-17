#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
typedef int element;
// ham khoi tao mang du lieu
int *createArray(int size)
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
void exch(int a[],int i,int j)
{
    int temp;
    temp = a[i];
    a[i]= a[j];
    a[j]= temp;
}
// ham swap
void swap(int *A , int *B)
{
    int temp;
    temp = *A;
    *A = *B;
    *B = temp;
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
// thuat toan 3_wayquicksort
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
    for( k=l;k<=p;k++) exch(a,k,j--);
    for( k=r-1;k>=q;k--) exch(a,k,i++);
    sort3way(a,l,j);
    sort3way(a,i,r);
}
// ham dumArray sao chep mang A sang mang B
int *dumArray(int *A,int size)
{
    int *B = (int*)malloc(size*sizeof(int));
    memcpy(B,A,size*sizeof(int));
    return B;
}
// Thuat toan sap xep chon selection sort
void selection_sort(element a[], int n)
{ 
    int i, j, min, tmp;
    for (i = 0; i < n-1; i++)
    {
        min = i;
        for (j = i+1; j <=n-1 ; j++)
            if ( a[j]< a[min])
                min = j;
        tmp= a[i];
        a[i]= a[min];
        a[min] = tmp;
    }
}
// ham in ra mang 
void printArray(int A[],int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        printf("%d\n",A[i]);
    }
}
int main()
{
    int *A,*B,*C,*A1,*A2;
    int size = 1000000;
    int small_size=10;
    int i;
    A = createArray(size);
    B = dumArray(A,size);
    C = dumArray(A,size);
    A1 = createArray(small_size);
    A2 = dumArray(A1,small_size);
    clock_t start , end;
    double time;
    sort3way(A1,0,small_size -1);
    printf("Mang ban dau:\n");
    printArray(A2,small_size);
    printf("Mang sau khi sap xep:\n");
    printArray(A1,small_size);
    printf("Thuat toan sap xep 3wayquicksort:\n");
    start = clock();
    sort3way(A,0,size-1);
    end = clock();
    time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Thoi gian chay cua thuat toan 3wayquicksort la: %lf\n",time);
    printf("Thuat toan 3wayquicksort : \n");
    start = clock();
    quicksort(B,0,size-1);
    end = clock();
    time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Thoi gian chay cua thuat toan 2wayquicksort la : %lf \n",time);
    printf("Thuat toan sap xep chon :\n");
    start = clock();
    selection_sort(C,size-1);
    end = clock();
    time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Thoi gian chay cua thuat toan selection sort la: %lf\n",time);
    return 0;
}
