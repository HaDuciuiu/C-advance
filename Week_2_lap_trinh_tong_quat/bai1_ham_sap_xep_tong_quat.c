#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
typedef int element;
void qsort(void *buf,size_t num,size_t size,int (*compare)(void const *,void const *));
// ham swap
void swap(int *x,int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
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
// ham compare tong quat
int int_compare(void const* x, void const *y) 
{
	int m, n;
	m = *((int*)x);
	n = *((int*)y);
	if (m == n) return 0;
	return m > n ? 1 : -1;
}
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
void exch(int a[],int size,int i,int j)
{
    int temp;
    temp = a[i];
    a[i]= a[j];
    a[j]= temp;
}
// thuat toan sap xep tong quat 
void sort3way_TQ(void* a, int size, int l, int r,int (*compare)(void const*, void const*)) 
{
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1) 
	{
		while (compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
		while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )
		if (j == l) break;
		if (i >= j) break;
		exch(a, size, i, j);
		if (compare((char*)a+i*size, (char*)a+r*size)==0)
		   exch(a, size, ++p, i);
		if (compare((char*)a+j*size, (char*)a+r*size)==0)
		   exch(a, size, --q, j);
	}
	exch(a, size, i, r);
	j = i - 1;
	i = i + 1;
	int k;
	for ( k = l ; k <= p; k++) exch(a, size, k, j--);
	for ( k = r-1; k >= q; k--) exch(a, size, k, i++);
	sort3way_TQ(a, size, l, j, compare);
	sort3way_TQ(a, size, i, r, compare);
}
int main()
{
	int *A;
	int size=1000000;
	clock_t start,end;
	double time;
	A = createArray(size);
	start = clock();
	sort3way_TQ(A,size,0,size-1,int_compare);
	end = clock();
	time = (double)(end - start)/CLOCKS_PER_SEC;
	printf("Thoi gian cua thuat toan sap xep 3wayquicksort : %lf\n",time);
  	return 0;
}

