#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define RANDMAX 11
#define SMALL_NUMBER 20
#define HUGE_NUMBER 10000000

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
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
			while (list[i] > pivot);
			do
				j--;
			while (list[j] < pivot);
			if (i < j)
				swap(&list[i], &list[j]);
		} while (i < j);

		swap(&list[left], &list[j]);
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
		while (a[++i] > a[r])
			;
		while (a[r] > a[--j])
			if (j == l)
				break;
		if (i >= j)
			break;
		swap(&a[i], &a[j]);
		if (a[i] == a[r])
			swap(&a[++p], &a[i]);
		if (a[j] == a[r])
			swap(&a[--q], &a[j]);
	}
	swap(&a[i], &a[r]);
	j = i - 1;
	i = i + 1;
	for (int k = l; k <= p; k++)
		swap(&a[k], &a[j--]);
	for (int k = r - 1; k >= q; k--)
		swap(&a[k], &a[i++]);
	sort3way(a, l, j);
	sort3way(a, i, r);
}

void printArr(int list[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", list[i]);
	}
}

int *createArray(int size)
{
	srand((int)time(0));
	int *array = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % RANDMAX;
	}
	return array;
}

int *dumpArray(int *p, int size)
{
	int *array = (int *)malloc(size * sizeof(int));
	memcpy(array, p, size * sizeof(int));
	return array;
}

int intCompare(void const *x, void const *y)
{
	int m, n;
	m = *((int *)x);
	n = *((int *)y);
	if (m == n)
		return 0;
	return m > n ? -1 : 1;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	for (i = 0; i < n - 1; i++)
	{

		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;
		swap(&arr[min_idx], &arr[i]);
	}
}

int main()
{
	int *a = createArray(HUGE_NUMBER), *b = dumpArray(a, HUGE_NUMBER), *c = dumpArray(a, HUGE_NUMBER);
	clock_t start, end;
	double cpu_time_used;

	printf("------------------------------\n");
	printf("> Sort3Way with array a <\n");
	start = clock();
	sort3way(a, 0, HUGE_NUMBER - 1);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Run in %f seconds.\n", cpu_time_used);

	printf("------------------------------\n");
	printf("> QSort with array b <\n");
	start = clock();
	qsort(b, HUGE_NUMBER, sizeof(int), intCompare);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Run in %f seconds.\n", cpu_time_used);

	printf("------------------------------\n");
	printf("> Selection sort with array c <\n");
	start = clock();
	selectionSort(c, HUGE_NUMBER);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Run in %f seconds.\n", cpu_time_used);
	printf("------------------------------\n");
}