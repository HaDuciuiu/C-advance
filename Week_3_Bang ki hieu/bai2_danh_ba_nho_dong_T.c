#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10
 
typedef struct
{
    char name[80];
    long number;
} PhoneEntry;
 
typedef struct
{
    PhoneEntry *entries;
    int total;
    int size;
} PhoneBook;
 
void exch(void *buf, int i, int j)
{
    PhoneEntry tmp;
    memcpy(&tmp, buf + i * sizeof(PhoneEntry), sizeof(PhoneEntry));
    memcpy(buf + i * sizeof(PhoneEntry), buf + j * sizeof(PhoneEntry), sizeof(PhoneEntry));
    memcpy(buf + j * sizeof(PhoneEntry), &tmp, sizeof(PhoneEntry));
}
 
int compare_s(char *a, char *b)
{
    if (strcmp(a, b) == 0)
        return 0;
    return strcmp(a, b) < 0 ? -1 : 1;
}
 
void sort(PhoneBook *a, int l, int r, int (*compare)(char *, char *))
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (compare(a->entries[++i].name, a->entries[r].name) < 0)
            ;
        while (compare(a->entries[r].name, a->entries[--j].name) < 0)
            if (j == l)
                break;
        if (i >= j)
            break;
        exch(a->entries, i, j);
        if (compare(a->entries[i].name, a->entries[r].name) == 0)
            exch(a->entries, ++p, i);
        if (compare(a->entries[j].name, a->entries[r].name) == 0)
            exch(a->entries, --q, j);
    }
    exch(a->entries, i, r);
    j = i - 1;
    i = i + 1;
    int k;
    for ( k = l; k <= p; k++)
        exch(a->entries, k, j--);
    for ( k = r - 1; k >= q; k--)
        exch(a->entries, k, i++);
    sort(a, l, j, compare);
    sort(a, i, r, compare);
}
 
PhoneBook createPhoneBook()
{
    PhoneBook p;
    p.entries = (PhoneEntry *)malloc(INITIAL_SIZE * sizeof(PhoneEntry));
    p.total = 0;
    p.size = INITIAL_SIZE;
    return p;
}
 
void dropPhoneBook(PhoneBook *book)
{
    book->total = 0;
    book->size = 0;
    free(book->entries);
}
 
int binarySearch(PhoneBook a, int l, int r, char *name, int (*compare)(char *, char *))
{
    int i, res;
    if (r < l)
        return -1;
    i = (l + r) / 2;
    res = compare(name, a.entries[i].name);
    if (res == 0)
        return i;
    else if (res > 0)
        return binarySearch(a, i + 1, r, name, compare);
    else
        return binarySearch(a, l, i - 1, name, compare);
}
 
void addPhoneNumber(long number, char *name, PhoneBook *book)
{
    int i;
    if ((i = binarySearch(*book, 0, book->total - 1, name, compare_s)) != -1)
    {
        book->entries[i].number = number;
        return;
    }
    if (book->total + 1 > book->size)
    {
        book->entries = (PhoneEntry *)realloc(book->entries, (INITIAL_SIZE + INCREMENTAL_SIZE) * sizeof(PhoneEntry));
        book->size += INCREMENTAL_SIZE;
    }
 
    strcpy(book->entries[book->total].name, name);
    book->entries[book->total].number = number;
    book->total++;
}
 
long getPhoneNumber(char *name, const PhoneBook *book)
{
    int i;
    if ((i = binarySearch(*book, 0, book->total - 1, name, compare_s)) != -1)
    {
        return book->entries[i].number;
    }
    return -1;
}
 
void printData(PhoneBook book)
{
	int i;
    for (i = 0; i < book.total; i++)
    {
        printf("%s %ld\n", book.entries[i].name, book.entries[i].number);
    }
}
 
int main(int argc, char const *argv[])
{
    PhoneBook pb = createPhoneBook();
    int ch;
    PhoneEntry tmp;
    long numPhone;
 
    while (1)
    {
        printf("----------------------\n"
               "1. Add contact\n"
               "2. Get contact\n"
               "3. Print Data\n"
               "4. DropPhoneBook and Exit\n"
               "-> Select: ");
        scanf("%d%*c", &ch);
        switch (ch)
        {
        case 1:
            printf("----------------------\nAdd contact %d\n", pb.total + 1);
            printf("Name: ");
            scanf("%[^\n]%*c", tmp.name);
            printf("Phone Number: ");
            scanf("%ld%*c", &tmp.number);
            addPhoneNumber(tmp.number, tmp.name, &pb);
            sort(&pb, 0, pb.total - 1, compare_s);
            break;
        case 2:
            printf("----------------------\n");
            printf("Name: ");
            scanf("%[^\n]%*c", tmp.name);
            if ((numPhone = getPhoneNumber(tmp.name, &pb)) != -1)
            {
                printf("SDT cua %s la: %ld\n", tmp.name, numPhone);
            }
            else
                printf("Khong co sdt cua nguoi nay!\n");
            break;
        case 3:
            printf("----------------------\nPrint Data\n\n");
            printData(pb);
            break;
        case 4:
            printf("----------------------\nDrop PhoneBook and Exit\n");
            dropPhoneBook(&pb);
            exit(0);
            break;
        default:
            printf("Vui long nhap dung!!!\n");
            break;
        }
    }
 
    return 0;
}

