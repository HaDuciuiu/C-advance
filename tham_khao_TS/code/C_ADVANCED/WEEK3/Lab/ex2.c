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

int sequentialSearch(PhoneBook book, char *name)
{
    int i;
    for (int i = 0; i < book.total; i++)
    {
        if (strcmp(book.entries[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addPhoneNumber(long number, char *name, PhoneBook *book)
{
    int i;
    if ((i = sequentialSearch(*book, name)) != -1)
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
    if ((i = sequentialSearch(*book, name)) != -1)
    {
        return book->entries[i].number;
    }
    return -1;
}

void printData(PhoneBook book)
{
    for (int i = 0; i < book.total; i++)
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
            break;
        case 2:
            printf("----------------------\n");
            printf("Name: ");
            scanf("%[^\n]%*c", tmp.name);
            if((numPhone = getPhoneNumber(tmp.name, &pb)) != -1){
                printf("SDT cua %s la: %ld\n", tmp.name, numPhone);
            }
            else printf("Khong co sdt cua nguoi nay!\n");
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
