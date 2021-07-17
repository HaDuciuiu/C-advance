#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct diem
{
    char tuyen_bus[10];// lưu số xe bus
    char *diem_bus[100];// lưu địa điểm bus
}Diem;

int main()
{
    FILE *f;

    f = fopen("Xe_buyt_1.txt","r");
    Diem A[100];// lưu số xe buýt và lộ trình
    char road[500];// lưu xâu lộ trình đọc từ file
    int i=0;// đếm số xe buýt
    if(f==NULL)
    {
        printf("loi\n");
        exit(0);
    }
    while(!feof(f))
    {
        fscanf(f,"%s%*c",A[i].tuyen_bus);
        fscanf(f,"%[^\n]", str);
        char *token;// lưu địa điểm đón buýt
        token = strtok(str, " - ");// bỏ lí tự " - " ra khỏi chuỗi
   
        /* duyet qua cac token con lai */
        int j = 0;
        while( token != NULL ) 
        {
            trim(token);
            strcpy(A[i].diem_bus[j],token);
            token = strtok(NULL," - ");// bỏ lí tự " - " ra khỏi chuỗi
            j++;
        }
        // dòng này không xóa
        // cắt kích thước của A[i].diem_bus xuống cho đủ dùng thôi
        i++;
    }
    int k,h;
    for(k = 0;k<i;k++) {
        for(h=0;h<j;h++)
        {
            printf("%s - %s\n");
        }
    }

    return 0;
}