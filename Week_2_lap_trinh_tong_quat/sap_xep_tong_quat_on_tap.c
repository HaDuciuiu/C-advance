#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZEMAX  10000000
#define SMALL_SIZE 20
#define RANDMAX 11
// ham doi cho hai so 
void exch(void *buf , int size , int i, int j)
{
	int temp ; 
	temp = *((int*)buf +i);
	*((int*)buf + i) = *((int*)buf +j);
	*((int*)buf + j) = temp;
}
// ham sap xep tong quat 
void sapxep(void *a, int l, int r, void (*sort)(int *, int, int))
{
    sort((int *)a, l, r);
}
// ham tao mang ngau nhien
int *createArray(int size)
{
	int *A = (int *)malloc(size*sizeof(int));
	srand((int)time(0));
	int i;
	for(i=0;i<size;i++)
	{
		A[i] = rand() % RANDMAX;
	}
	return A;
}
// ham copy du lieu 
int *dumArray(int *A,int size)
{
	int *B = (int*)malloc(size*sizeof(int));
	memcpy(B,A,size*sizeof(int));
	// ham memcpy copy n bytes du lieu tu mang A sang mang B
	return B;
}
// ham sap xep nhanh
void sort2way(int list[], int left, int right)
{
    int pivot, i, j;
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = list[left];
        do
        {
            do
                i++;
            while (list[i] < pivot);
            do
                j--;
            while (list[j] > pivot);
            if (i < j)
                exch(list, sizeof(int), i, j);
        } while (i < j);

        exch(list, sizeof(int), left, j);
        sort2way(list, left, j - 1);
        sort2way(list, j + 1, right);
    }
}
// ham sap xep 3way_quicksort
void sort3way(int a[], int l, int r)
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (a[++i] < a[r])
            ;
        while (a[r] < a[--j])
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a, sizeof(int), i, j);
        if (a[i] == a[r])
            exch(a, sizeof(int), ++p, i);
        if (a[j] == a[r])
            exch(a, sizeof(int), --q, j);
    }
    exch(a, sizeof(int), i, r);
    j = i - 1;
    i = i + 1;
    int k;
    for ( k = l; k <= p; k++)
        exch(a, sizeof(int), k, j--);
    for (k = r - 1; k >= q; k--)
        exch(a, sizeof(int), k, i++);
    sort3way(a, l, j);
    sort3way(a, i, r);
}
//ham in ra mang
void printArray(int A[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%d\n",A[i]);
	}
}
// ham sap xep chon selection
void selectionSort(int arr[],int n)
{
	int i, j, min_idx;
    // Di chuyen ranh gioi cua mang da sap xep và chua sap xep
    for (i = 0; i < n - 1; i++)
    {
        // Tim phan tu nho nhat trong mang chua sap xep
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Doi cho phan tu nho nhat voi phan tu dau tien
        exch(arr, sizeof(int), min_idx, i);
    }
}
int main()
{
	int *A,*B;
	A = createArray(SMALL_SIZE);
	B = dumArray(A,SMALL_SIZE);
	printf("\nMang A,B da tao ban dau :\n");
	printf("Mang A :\n");
	printArray(A,SMALL_SIZE);
	printf("Mang B:\n");
	printArray(B,SMALL_SIZE);
	printf("\nSap xep hai mang A,B:\n");
	sapxep(A,0,SMALL_SIZE-1,sort2way);
	printArray(A,SMALL_SIZE);
	sapxep(B,0,SMALL_SIZE-1,sort3way);
	printArray(B,SMALL_SIZE);
	printf("\n=====================================================================================================\n");
	free(A);
	free(B);
	printf("Sap xep hai mang A , B voi 10000000 phan tu\n");
	A = createArray(SIZEMAX);
	B = dumArray(A,SIZEMAX);
	printf("\n=========================================SORT2WAY=======================================================\n");
	clock_t start = clock();// ghi lai thoi gian dau
	sapxep(A,0,SIZEMAX - 1,sort2way);
	clock_t end = clock();// ghi lai thoi gian sau
	printf("Time run : %f\n",(float)(end-start));
	printf("\n=========================================SORT3WAY===================================================\n");
	start = clock();
	sapxep(B,0,SIZEMAX-1,sort3way);
	end = clock();
	printf("Time run : %f\n",(float)(end -start));
	free(A);
	free(B);
	return 0;
}
