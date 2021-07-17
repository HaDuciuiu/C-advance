#include<stdio.h>
// ham doi cho hai so dang tong quat
void exch(void *buf , int size , int i, int j)
{
	int temp ; 
	temp = *((int*)buf +i);
	*((int*)buf + i) = *((int*)buf +j);
	*((int*)buf + j) = temp;
}
// ham so sanh dang tong quat
void sort(void* a, int size, int l, int r, int (*compare)(void*, void*)) {
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
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
	sort(a, size, l, j, compare);
	sort(a, size, i, r, compare);
}

int main()
{
	printf("Ham sap xep tong quat\n");
  return 0;
}

