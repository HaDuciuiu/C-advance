#include<stdio.h>
int main()
{
    int n , i;
    int index=0;
    int output[100];
    printf("Nhap vao mot so tu nhien : ");
    scanf("%d",&n);
    for(i=2;i<n;i++)
    {
        if(n%i==0)
        {
            output[index++] = i;
        }

    }
    for(i=0;i<index;i++)
    {
        printf("%d\t",output[index]);
    }
    printf("\n");
    return 0;
}