#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INITIAL 100
#define INCREMENTAL 10
typedef struct{
	char name[80];
	long number;
}PhoneEntry;
typedef struct
{
	PhoneEntry *entries;
	int total;
   	int size;
}PhoneBook;
// ham tao mot danh ba
PhoneBook createPhoneBook()
{
	PhoneBook Book;
	Book.size = INITIAL;
	Book.total = 0;
	Book.entries = (PhoneEntry*)malloc((Book.size)*sizeof(PhoneEntry));
	return Book;	
}
// ham xoa 1 phonebook
void dropPhoneBook(PhoneBook *Book)
{
	while(Book->entries!=NULL)
		free(Book->entries);
}

void addPhoneNumber(long number,char *name,PhoneBook *Book)
{
	int i,dem=0;
	for(i=0;i<Book->total;i++)
	{
		if(strcmp(name,Book->entries[i].name)==0)
		{
			Book->entries[i].number = number;
			dem = 1;
		}
		if(Book->total<INITIAL&&dem==0)
		{
			Book->entries[Book->total].number=number;
      		strcpy(Book->entries[Book->total].name,name);
      		Book->total++;
		}
		else if(Book->total==Book->size)
      	{
		    Book->entries=(PhoneEntry*)realloc(Book->entries,(Book->size+INCREMENTAL)*sizeof(PhoneEntry));
		  
		    Book->size=Book->size+INCREMENTAL;
		    Book->entries[Book->total].number=number;
		    strcpy(Book->entries[Book->total].name,name);
		    Book->total++;
      	}
	}
}
// tim so dien thoai
char *getPhoneNumber(long number, PhoneBook* Book)
{
  int i;
  for(i=0;i<Book->total;i++)
    {
      if(number==Book->entries[i].number)
		return Book->entries[i].name;
    }
  return NULL;
}
// ham tim kiem nhi phan


int main()
{
	long p_number;
	char name[80];
	PhoneBook Book;
	Book = createPhoneBook();
	int i;
	for(i=0;i<INITIAL;i++)
	{
		printf("\nNhap ten thu %d: ",i+1);
		gets(Book.entries[i].name);
		if(strcmp(Book.entries[i].name,"0")==0)
			break;
		printf("\nNhap phone number thu %d: ",i+1);
		scanf("%lf%*c",&Book.entries[i].number);
	}
	// them vao
	printf("Nhap ten: ");
	gets(name);
	printf("Nhap so dien thoai: \n");
	scanf("%lf",p_number);
	addPhoneNumber(p_number,name,&Book);
	// tim kiem
	long s_number;
	printf("Nhap vao so dien thoai can tim kiem : ");
	scanf("%lf",&s_number);
	if(getPhoneNumber(s_number,&Book)==NULL)
	{
		printf("Khong tim thay\n");
	}
	else
	{
		printf("%s\n",getPhoneNumber(s_number,&Book));
	}
  return 0;
}

