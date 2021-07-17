#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct
{
    void *key;
    void *value;
} Entry;

typedef struct
{
    Entry *entries;
    int total;
    int size;
    Entry (*makeNode)(void *, void *);
    int (*compare)(void *, void *);
} SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void *, void *), int (*compare)(void *, void *))
{
    SymbolTable st;
    st.entries = (Entry *)malloc(INITIAL_SIZE * sizeof(Entry));
    st.total = 0;
    st.size = INITIAL_SIZE;
    st.makeNode = makeNode;
    st.compare = compare;
    return st;
}

void dropSymbolTable(SymbolTable *tab)
{
    tab->total = 0;
    tab->size = 0;
    tab->compare = NULL;
    tab->makeNode = NULL;
    free(tab->entries);
}

Entry makePhone(void *name, void *phone)
{
    Entry res;
    res.key = strdup((char *)name);
    res.value = malloc(sizeof(long));
    memcpy(res.value, phone, sizeof(long));
    return res;
}

int comparePhone(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

void exch(void *buf, int i, int j)
{
    Entry tmp;
    memcpy(&tmp, buf + i * sizeof(Entry), sizeof(Entry));
    memcpy(buf + i * sizeof(Entry), buf + j * sizeof(Entry), sizeof(Entry));
    memcpy(buf + j * sizeof(Entry), &tmp, sizeof(Entry));
}

void sort(SymbolTable *a, int l, int r)
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (a->compare(a->entries[++i].key, a->entries[r].key) < 0)
            ;
        while (a->compare(a->entries[r].key, a->entries[--j].key) < 0)
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a->entries, i, j);
        if (a->compare(a->entries[i].key, a->entries[r].key) == 0)
            exch(a->entries, ++p, i);
        if (a->compare(a->entries[j].key, a->entries[r].key) == 0)
            exch(a->entries, --q, j);
    }
    exch(a->entries, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        exch(a->entries, k, j--);
    for (int k = r - 1; k >= q; k--)
        exch(a->entries, k, i++);
    sort(a, l, j);
    sort(a, i, r);
}

int binarySearch(SymbolTable a, int l, int r, void *s)
{
    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = a.compare((char *)s, (char *)a.entries[i].key);
    if (res == 0)
        return i;
    else if (res > 0)
        return binarySearch(a, i + 1, r, s);
    else
        return binarySearch(a, l, i - 1, s);
}

void addEntry(void *key, void *value, SymbolTable *tab)
{
    sort(tab, 0, tab->total - 1);
    int i;
    if ((i = binarySearch(*tab, 0, tab->total - 1, key)) != -1)
    {
        tab->entries[i].value = value;
        return;
    }
    if (tab->total + 1 > tab->size)
    {
        tab->entries = (Entry *)realloc(tab->entries, (INITIAL_SIZE + INCREMENTAL_SIZE) * sizeof(Entry));
        tab->size += INCREMENTAL_SIZE;
    }

    tab->entries[tab->total++] = tab->makeNode(key, value);
}

Entry *getEntry(void *key, SymbolTable tab)
{
    int i;
    if ((i = binarySearch(tab, 0, tab.total - 1, key)) != -1)
    {
        return &(tab.entries[i]);
    }
    return NULL;
}

void printData(SymbolTable tab)
{
    for (int i = 0; i < tab.total; i++)
    {
        printf("%-25s %ld\n", (char *)tab.entries[i].key, *(long *)tab.entries[i].value);
    }
}

int main(int argc, char const *argv[])
{
    SymbolTable phoneBook = createSymbolTable(makePhone, comparePhone);

    long number = 983984775;
    char name[] = "Ta Tuan Anh";
    addEntry(name, &number, &phoneBook);
    number = 123456;
    addEntry("Do Quoc Huy", &number, &phoneBook);
    number = 123456;
    addEntry("ai do", &number, &phoneBook);
    number = 67989;
    addEntry("Do Quoc Huy", &number, &phoneBook);

    printData(phoneBook);

    printf("\n\n");
    Entry *result = getEntry("Do Quoc Huy",phoneBook);
	if (result) printf("%-25s %ld\n",(char*)result->key,*(long*)result->value);
	else printf("Khong tim thay\n");

    result = getEntry("Do Huy",phoneBook);
	if (result) printf("%-25s %ld\n",(char*)result->key,*(long*)result->value);
	else printf("Khong tim thay\n");
    printf("\n\n");

    dropSymbolTable(&phoneBook);

    return 0;
}
