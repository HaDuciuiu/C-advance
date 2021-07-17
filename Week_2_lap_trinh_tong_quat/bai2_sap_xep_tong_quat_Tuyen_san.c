#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZEMAX 10000000
#define SMALL_SIZE 20
#define RANDMAX 11

int int_compare(void const *x, void const *y)
{
    int m = *((int *)x);
    int n = *((int *)y);
    if (m == n)
        return 0;
    return m > n ? 1 : -1;
}
// ham doi cho hai phan tu 
void exch(void *buf, int size, int i, int j)
{
    int temp;
    temp = *((int *)buf + i);
    *((int *)buf + i) = *((int *)buf + j);
    *((int *)buf + j) = temp;
}

void sapxep(void *a, int l, int r, void (*sort)(int *, int, int))
{
    sort((int *)a, l, r);
}

int *createArray(int size) //tao mang ngau nhien
{
    int *p = (int *)malloc(sizeof(int) * size);
    srand(time(NULL));
    int i;
    for ( i = 0; i < size; i++)
    {
        p[i] = rand() % RANDMAX;
    }
    return p;
}

int *dumpArray(int *a, int size) //coppy tu mang a vào p
{
    int *p = (int *)malloc(size * sizeof(int));
    memcpy(p, a, size * sizeof(int));
    return p;
}

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
void printArr(int a[], int size)
{
	int i;
    for ( i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
}

void selectionSort(int arr[], int n)
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

        // Ðoi cho phan tu nho nhat voi phan tu dau tien
        exch(arr, sizeof(int), min_idx, i);
    }
}

int main()
{
    int *a = createArray(SMALL_SIZE), *b = dumpArray(a, SMALL_SIZE);

    printf("-> Mang a, b ban dau: \n");
    printf("+ Mang a:\n");
    printArr(a, SMALL_SIZE);
    printf("\n");
    printf("+ Mang b:\n");
    printArr(b, SMALL_SIZE);
    printf("\n\n");
    printf("Sap xep hai mang a, b: \n");
    sapxep(a, 0, SMALL_SIZE - 1, sort2way);
    printf("+ Mang a:\n");
    printArr(a, 20);
    printf("\n");
    sapxep(b, 0, SMALL_SIZE - 1, sort3way);
    printf("+ Mang b:\n");
    printArr(b, 20);
    printf("\n");
    printf("----------------------\n");
    free(a);
    free(b);

    printf("-> Sap xep 2 mang a, b voi 10 trieu phan tu:\n");
    a = createArray(SIZEMAX), b = dumpArray(a, SIZEMAX);

    printf("+ Sort2way\n");
    clock_t begin = clock(); //ghi lai thoi gian dau
    //sort2way(a, 0, SIZEMAX-1);
    sapxep(a, 0, SIZEMAX - 1, sort2way);
    clock_t end = clock(); //ghi lai thoi gian luc sau
    printf("Time run: %fs\n",(float)(end-begin)/CLOCKS_PER_SEC);
    printf("+ Sort3way\n");
    begin = clock(); //ghi lai thoi gian dau
    //sort3way(b, 0, SIZEMAX-1);
    sapxep(b, 0, SIZEMAX - 1, sort3way);
    end = clock(); //ghi lai thoi gian luc sau
    printf("Time run: %fs\n",(float)(end-begin)/CLOCKS_PER_SEC);
    free(a);
    free(b);
    return 0;
}
