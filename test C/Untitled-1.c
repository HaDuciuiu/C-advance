#include <stdio.h>
#include <string.h>

int main ()
{
   char str[50];

   strcpy(str,"Hoc C co ban va nang cao tai VietJack");
   puts(str);

   memset(str,'$',7);
   puts(str);
   
   return(0);
}