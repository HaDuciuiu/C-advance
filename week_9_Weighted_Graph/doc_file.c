#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct diem
{
    char tuyen_bus[3];
    char diem_bus[200];
}Diem;

int main()
{
    FILE *f;
    int so_dong = 1;
    char dong[5000];
    f = fopen("Xebuyt.txt","r");
    Diem A;
    int i,j;
    if(f==NULL)
    {
        printf("loi\n");
        exit(0);
    }
    while(1)
    {
        if(so_dong%2!=0)
        {
            fscanf(f,"%s%*c",A.tuyen_bus);
            //A.tuyen_bus[strlen(A.tuyen_bus)-1] = '\0';
            printf("%s\n",A.tuyen_bus);
            so_dong+=1;
        }
        else
        {
            fscanf(f,"%[^\n]%*c",dong);
            //dong[strlen(dong)-1] = '\0';
            printf("%s\n",dong);
            so_dong+=1;
        }
        if(feof(f))
        {
            break;
        }
    }
    printf("hi\n");
    /*for(i=0;i<=so_dong;i+=2)
    {
        int index = 0;
        char **b = (char **)malloc(100*sizeof(char));;
        char *p;
        p = strtok(dong,"-");
        while(p != NULL)
        {
            b[index] = p;
            index++;
            p = strtok(NULL, "-"); //cat chuoi tu vi tri dung lai truoc do
        }
        for(i=0;i<index-1;i++)
        {
            printf("\n%s ", b[i]);
        }
        printf("\n"); 
    }
    */
    return 0;
}