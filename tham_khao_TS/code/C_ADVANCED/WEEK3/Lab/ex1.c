#include <stdio.h>
#include <string.h>
#define MAX_PHONE_NUMBER 1000

typedef struct
{
    char name[80];
    long number;
} PhoneEntry;

typedef struct
{
    PhoneEntry entries[MAX_PHONE_NUMBER];
    int total;
} PhoneBook;

void addPhoneNumber(long number, char *name, PhoneBook *book)
{
    for (int i = 0; i < book->total; i++)
    {
        if (strcmp(book->entries[i].name, name) == 0)
        {
            book->entries[i].number = number;
            return;
        }
    }
    strcpy(book->entries[book->total].name, name);
    book->entries[book->total].number = number;
    book->total++;
}

long getPhoneNumber(char *name, const PhoneBook *book)
{
    for (int i = 0; i < book->total; i++)
    {
        if (strcmp(book->entries[i].name, name) == 0)
        {
            return book->entries[i].number;
        }
    }
    return -1;
}

void loadData(PhoneBook *book)
{
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
    {
        printf("Loi: khong the mo file\n");
        return;
    }

    PhoneEntry tmp;
    while (!feof(f))
    {
        fscanf(f, "%s %d\n", tmp.name, &tmp.number);
        addPhoneNumber(tmp.number, tmp.name, book);
    }

    fclose(f);
}

void printData(PhoneBook book)
{
    for (int i = 0; i < book.total; i++)
    {
        printf("%s %d\n", book.entries[i].name, book.entries[i].number);
    }
}

int main(int argc, char const *argv[])
{
    PhoneBook pb;
    pb.total = 0;
    long numPhone;

    printf("----------------------------\n");
    loadData(&pb);
    printf("Load data success!\n");
    printf("----------------------------\n");
    printf("Print Data\n");
    printData(pb);
    printf("----------------------------\n");
    printf("Nhap so dien thoai moi la 1665842 cho Nguyen_Van_B\n\n");
    addPhoneNumber(1665842, "Nguyen_Van_B", &pb);
    printf("Print Data\n");
    printData(pb);
    printf("----------------------------\n");
    printf("Get Phone Number of Vu_Van_C\n");
    if ((numPhone = getPhoneNumber("Vu_Van_C", &pb)) != -1)
    {
        printf("So dien thoai cua Vu_Van_C: %d\n", numPhone);
    }
    else
        printf("Khong co so dien thoai cua Vu_Van_C\n");
    return 0;
}
