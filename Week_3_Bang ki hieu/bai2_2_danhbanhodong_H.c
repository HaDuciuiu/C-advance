#include <stdio.h>
//#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10
#define MaxName 80
 
 
typedef struct
{
  long number;
  char name[MaxName];
}PhoneEntry;
 
typedef struct
{
  PhoneEntry *entries;
  int total;
  int size;
}PhoneBook;
 
PhoneBook createPhoneBook()
{
  PhoneBook book;
  //book=(PhoneBook)malloc(sizeof(PhoneBook));
  book.entries=(PhoneEntry*)malloc(INITIAL_SIZE*sizeof(PhoneEntry));
  book.size=INITIAL_SIZE;
  book.total=0;
  return book;
}
 
void dropPhoneBook(PhoneBook* book)
{
  free(book->entries);
}
 
void addPhoneNumber(char *name,long number,PhoneBook* book)
{
  int i,done;
  done=0;// bien done de kiem tra xem khach hang da duoc them vao danh ba chua
  for(i=0;i<book->total;i++)
    {
      if(strcmp(name,book->entries[i].name)==0)//neu co ten do trong danh ba roi thi thay the ten moi
	{
	  book->entries[i].number=number;// thay the ten cu thanh ten moi
	  done=1;
	}
    }
  if(done==0&&book->total<book->size)// neu chua co ten khach hang trong danh ba
    {
      book->entries[book->total].number=number;
      strcpy(book->entries[book->total].name,name);
      book->total++;
    }
  else if(book->total==book->size)
      {
     book->entries=(PhoneEntry*)realloc(book->entries,(book->size+INCREMENTAL_SIZE)*sizeof(PhoneEntry));
  
      book->size=book->size+INCREMENTAL_SIZE;
      book->entries[book->total].number=number;
      strcpy(book->entries[book->total].name,name);
      book->total++;
      }
}
char *getPhoneNumber(long number, PhoneBook* book)// tim kiem so trong danh ba
{
  int i;
  for(i=0;i<book->total;i++)
    {
      if(number==book->entries[i].number)
	return book->entries[i].name;
    }
  return NULL;
}
 
 
 
int main()
{
  int i;
  PhoneBook book;
  PhoneEntry *entry;
  book=createPhoneBook();
  printf("Tao danh ba : \n");
  addPhoneNumber("Hung",999999,&book);
  addPhoneNumber("Le",9757575,&book);
  addPhoneNumber("Khanh",34856,&book);
  addPhoneNumber("Tien",12345,&book);
  addPhoneNumber("Nhung",19048,&book);
  for(i=0;i<book.total;i++)
    printf("%s: %ld\n",book.entries[i].name,book.entries[i].number);
  if(getPhoneNumber(34856,&book)==NULL)
    printf("Khong co\n");
  else
    printf("So 34856 co Ten:%s\n",getPhoneNumber(34856,&book));
}
