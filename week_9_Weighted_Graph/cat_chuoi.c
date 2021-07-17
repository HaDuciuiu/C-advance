#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  
int main()
{
        int index = 0;
        int i;
        char *a = (char *)malloc(100*sizeof(char));
        char **b = (char **)malloc(100*sizeof(char));;
        printf ("Nhap vao chuoi can dao nguoc: ");
        fflush(stdin);
        gets(a);
  
        char *p;
        p = strtok(a, ",. "); //cat chuoi bang cac ky tu ,. va space
        while(p != NULL)
        {
                b[index] = p;
                index++;
                p = strtok(NULL, ",. "); //cat chuoi tu vi tri dung lai truoc do
        }
        for (i = index-1; i>=0; i--) //in ra cac tu theo thu tu dao nguoc
                printf ("\n%s ", b[i]);
        printf ("\n");
 
        return 0;
}