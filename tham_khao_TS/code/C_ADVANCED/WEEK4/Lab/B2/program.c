#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libfdr/jrb.h"
#include "../libfdr/fields.h"

int main(){
    JRB t = make_jrb(), tmp;
    int i, so_nguyen = 0;
    unsigned int so_luong = 0;
    printf("Ban muon nhap bao nhieu so nguyen? ");
    scanf("%d%*c", &so_luong);

    for (int i = 0; i < so_luong; i++)
    {
        printf("Nhap so nguyen thu %d: ", i + 1);
        scanf("%d%*c", &so_nguyen);
        jrb_insert_int(t, so_nguyen, new_jval_i(so_nguyen));
    }

    printf("Day so da duoc sap xep:\n");
    jrb_traverse(tmp, t){
        printf("%2d\n", tmp->val.i);
    }
    
    jrb_free_tree(t);
}