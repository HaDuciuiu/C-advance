#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libfdr/jrb.h"
#include "../libfdr/fields.h"

int main()
{
    JRB t = make_jrb(), tmp;
    int ch;
    char name[25];
    long sdt;
    //     int i, so_nguyen = 0;
    //     unsigned int so_luong = 0;
    //     printf("Ban muon nhap bao nhieu so nguyen? ");
    //     scanf("%d%*c", &so_luong);

    //     for (int i = 0; i < so_luong; i++)
    //     {
    //         printf("Nhap so nguyen thu %d: ", i + 1);
    //         scanf("%d%*c", &so_nguyen);
    //         jrb_insert_int(t, so_nguyen, new_jval_i(so_nguyen));
    //     }

    //     printf("Day so da duoc sap xep:\n");
    //     jrb_traverse(tmp, t){
    //         printf("%2d\n", tmp->val.i);
    //     }

    //     jrb_free_tree(t);

    while (1)
    {
        printf(" ----------------------\n"
               "|1. Thêm danh bạ       |\n"
               "|2. Xoá danh bạ        |\n"
               "|3. Sửa sdt            |\n"
               "|4. Thoat              |\n"
               " ----------------------\n"
               "-> Select: ");
        scanf("%d%*c", &ch);

        switch (ch)
        {
        case 1:
            printf(">>Thêm danh bạ<<\n");
            printf("Nhập tên: ");
            scanf("%[^\n]%*c", name);
            if (jrb_find_str(t, name) != NULL)
            {
                printf("Đã có tên người này trong danh bạ!!!\n");
                break;
            }
            printf("SĐT: ");
            scanf("%ld%*c", &sdt);
            jrb_insert_str(t, name, new_jval_l(sdt));
            break;
        case 2:
            printf(">>Xóa danh bạ<<\n");
            printf("Nhập tên cần xóa: ");
            scanf("%[^\n]%*c", name);
            if ((tmp = jrb_find_str(t, name)) == NULL)
            {
                printf("Không có tên người này trong danh bạ!!!\n");
                break;
            }
            jrb_delete_node(tmp);
            break;
        case 3:
            printf(">>Sủa danh bạ<<\n");
            printf("Nhập tên cần sửa số điện thoại: ");
            scanf("%[^\n]%*c", name);
            if ((tmp = jrb_find_str(t, name)) == NULL)
            {
                printf("Không có tên người này trong danh bạ!!!\n");
                break;
            }
            jrb_delete_node(tmp);
            printf("Nhập SĐT: ");
            scanf("%ld%*c", &sdt);
            jrb_insert_str(t, name, new_jval_l(sdt));
            break;
        case 4:
            jrb_free_tree(t);
            exit(0);
            break;
        default:
            printf("Vui long nhap tu 1-4!!!\n");
            break;
        }
    }
}