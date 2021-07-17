#include<stdio.h>
#include"jrb.h"
// chuong trinh minh hoa cho cac ham trong jrb tree
int main()
{
    // minh họa các hàm khởi tạo
    Jval j;// Jval la mot kieu du lieu hop(union)
    j.i = 4;
    printf("Gia tri vua khoi tao cho truong int la : %d\n",j.i);
    j = new_jval_i(5);// ham nay khoi tao gia tri cho truong int cua bien j co gia tri 5
    printf("Gia tri vua khoi tao cho truong int la : %d\n",j.i);
    j = new_jval_f(3.14);
    printf("Gia tri vua khoi tao cho truong float la : %f\n"j.f);
    j = new_jval_c('A');
    printf("Gia tri vua khoi tao cho truong char la : %c\n",j.c);
    j = new_jval_s("Co gang nhe!");
    printf("Gia tri vua khoi tao cho truong string la : %s\n",j.s);

    return 0;
}