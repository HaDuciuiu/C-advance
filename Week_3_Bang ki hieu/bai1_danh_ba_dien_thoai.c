#include<stdio.h>
#include<string.h>
#define MAX_PHONE_NUMBER 1000
typedef struct{
	char name[80];
	long number;
}PhoneEntry;
typedef struct{
	PhoneEntry entries[MAX_PHONE_NUMBER];
	int total;
}PhoneBook;
void addPhoneNumber(long number,char *name,PhoneBook *Book)
{
	int i,dem=0;
	if(Book->total>=MAX_PHONE_NUMBER)
	{
		printf("Danh ba day\n");
		return;
	}
	for(i=0;i<Book->total;i++)
	{
		if(strcmp(name,Book->entries[i].name)==0)
		{
			Book->entries[i].number = number;
			dem = 1;
		}
		if(Book->total<MAX_PHONE_NUMBER&&dem==0)
		{
			Book->entries[Book->total].number=number;
      		strcpy(Book->entries[Book->total].name,name);
      		Book->total++;
		}
	}
}

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


int main()
{
	long p_number;
	char name[80];
	PhoneBook *Book;
	int i;
	for(i=0;i<MAX_PHONE_NUMBER;i++)
	{
		printf("Nhap ten thu %d: ",i+1);
		gets(Book->entries[i].name);
		printf("Nhap phone number thu %d: ",i+1);
		scanf("%lf",Book->entries[i].number);
	}
	// them vao
	printf("Nhap ten: ");
	gets(name);
	printf("Nhap so dien thoai: \n");
	scanf("%lf",p_number);
	addPhoneNumber(p_number,name,Book);
	// tim kiem
	long s_number;
	printf("Nhap vao so dien thoai can tim kiem : ");
	scanf("%lf",&s_number);
	if(getPhoneNumber(s_number,Book)==NULL)
	{
		printf("Khong tim thay\n");
	}
	else
	{
		printf("%s\n",getPhoneNumber(s_number,Book));
	}
  return 0;
}

