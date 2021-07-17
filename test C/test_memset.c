#include <stdio.h>
#include <string.h>

int main ()
{
   char str[50];

   strcpy(str,"Hoc C co ban va nang cao tai VietJack");
   puts(str);

   memset(str,'$',7);
   /*
   Ham memset sao chep 7 ki $ vao mang str tinh tu ki tu dau tien*/
   puts(str);
   
   return(0);
}