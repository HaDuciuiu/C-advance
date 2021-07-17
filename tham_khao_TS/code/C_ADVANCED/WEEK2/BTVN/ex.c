#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define RANDMAX 10
#define SMALL_NUMBER 20
#define HUGE_NUMBER 10000000

typedef union
{
    int i;
    long l;
    float f;
    double d;
    void *v;
    char *s;
    char c;
} Jval;

Jval new_jval_i(int i)
{
    Jval tmp;
    tmp.i = i;
    return tmp;
}

Jval new_jval_l(long l)
{
    Jval tmp;
    tmp.l = l;
    return tmp;
}

Jval new_jval_f(float f)
{
    Jval tmp;
    tmp.f = f;
    return tmp;
}

Jval new_jval_d(double d)
{
    Jval tmp;
    tmp.d = d;
    return tmp;
}

Jval new_jval_c(char c)
{
    Jval tmp;
    tmp.c = c;
    return tmp;
}

Jval new_jval_v(void *v)
{
    Jval tmp;
    tmp.v = v;
    return tmp;
}

Jval new_jval_s(char *s)
{
    Jval tmp;
    tmp.s = s;
    return tmp;
}

int jval_i(Jval j)
{
    return j.i;
}

long jval_l(Jval j)
{
    return j.l;
}

float jval_f(Jval j)
{
    return j.f;
}

double jval_d(Jval j)
{
    return j.d;
}

void *jval_v(Jval j)
{
    return j.v;
}

char *jval_s(Jval j)
{
    return j.s;
}

char jval_c(Jval j)
{
    return j.c;
}

void exch(void *buf, int i, int j)
{
    Jval tmp;
    memcpy(&tmp, buf + i * sizeof(Jval), sizeof(Jval));
    memcpy(buf + i * sizeof(Jval), buf + j * sizeof(Jval), sizeof(Jval));
    memcpy(buf + j * sizeof(Jval), &tmp, sizeof(Jval));
}

void sort_gen(Jval a[], int l, int r, int (*compare)(Jval *, Jval *))
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (compare(&a[++i], &a[r]) < 0)
            ;
        while (compare(&a[r], &a[--j]) < 0)
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a, i, j);
        if (compare(&a[i], &a[r]) == 0)
            exch(a, ++p, i);
        if (compare(&a[j], &a[r]) == 0)
            exch(a, --q, j);
    }
    exch(a, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        exch(a, k, j--);
    for (int k = r - 1; k >= q; k--)
        exch(a, k, i++);
    sort_gen(a, l, j, compare);
    sort_gen(a, i, r, compare);
}

int search_gen(Jval a[], int l, int r, Jval item, int (*compare)(Jval *, Jval *))
{
    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = compare(&item, a + i);
    if (res == 0)
        return i;
    else if (res > 0)
        return search_gen(a, i + 1, r, item, compare);
    else
        return search_gen(a, l, i - 1, item, compare);
}

// int *dumpArray(int *p, int size)
// {
//     int *array = (int *)malloc(size * sizeof(int));
//     memcpy(array, p, size * sizeof(int));
//     return array;
// }

Jval *create_array_i(int size)
{
    srand((int)time(0));
    Jval *array = (Jval *)malloc(size * sizeof(Jval));
    for (int i = 0; i < size; i++)
    {
        array[i] = new_jval_i(rand() % RANDMAX);
    }
    return array;
}

int compare_i(Jval *a, Jval *b)
{
    if (jval_i(*a) == jval_i(*b))
        return 0;
    return jval_i(*a) < jval_i(*b) ? -1 : 1;
}

void sort_i(Jval a[], int l, int r)
{
    sort_gen(a, l, r, compare_i);
}

int search_i(Jval a[], int l, int r, int x)
{
    return search_gen(a, l, r, new_jval_i(x), compare_i);
}

void print_arr_i(Jval a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", jval_i(a[i]));
    }
}

Jval *create_array_f(int size)
{
    srand((int)time(0));
    Jval *array = (Jval *)malloc(size * sizeof(Jval));
    for (int i = 0; i < size; i++)
    {
        array[i] = new_jval_f((float)rand() / RANDMAX);
    }
    return array;
}

int compare_f(Jval *a, Jval *b)
{
    if (jval_f(*a) == jval_f(*b))
        return 0;
    return jval_f(*a) < jval_f(*b) ? -1 : 1;
}

void sort_f(Jval a[], int l, int r)
{
    sort_gen(a, l, r, compare_f);
}

int search_f(Jval a[], int l, int r, float x)
{
    return search_gen(a, l, r, new_jval_f(x), compare_f);
}

void print_arr_f(Jval a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%f ", jval_f(a[i]));
    }
}

Jval *create_array_d(int size)
{
    srand((int)time(0));
    Jval *array = (Jval *)malloc(size * sizeof(Jval));
    for (int i = 0; i < size; i++)
    {
        array[i] = new_jval_d((double)rand() / RANDMAX);
    }
    return array;
}

int compare_d(Jval *a, Jval *b)
{
    if (jval_d(*a) == jval_d(*b))
        return 0;
    return jval_d(*a) < jval_d(*b) ? -1 : 1;
}

void sort_d(Jval a[], int l, int r)
{
    sort_gen(a, l, r, compare_d);
}

int search_d(Jval a[], int l, int r, double x)
{
    return search_gen(a, l, r, new_jval_d(x), compare_d);
}

void print_arr_d(Jval a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%lf ", jval_d(a[i]));
    }
}

int main()
{
    printf("Integer\n");
    Jval *a = create_array_i(SMALL_NUMBER);
    print_arr_i(a, SMALL_NUMBER);
    printf("\n\n");
    sort_i(a, 0, SMALL_NUMBER - 1);
    print_arr_i(a, SMALL_NUMBER);
    printf("\n\nFind 5 at %d\n\n", search_i(a, 0, SMALL_NUMBER - 1, 5));
    free(a);
    printf("-------------------------\n");
    printf("Float\n");
    a = create_array_f(SMALL_NUMBER);
    print_arr_f(a, SMALL_NUMBER);
    printf("\n\n");
    sort_f(a, 0, SMALL_NUMBER - 1);
    print_arr_f(a, SMALL_NUMBER);
    printf("\n\nFind 5 at %d\n\n", search_f(a, 0, SMALL_NUMBER - 1, 5));
    free(a);
}