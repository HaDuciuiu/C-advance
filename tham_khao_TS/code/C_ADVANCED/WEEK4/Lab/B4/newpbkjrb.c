#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../libfdr/jrb.h"
#include "../../../libfdr/jval.h"

typedef struct
{
    char name[30];
    long phone;
} contact;

int main()
{
    JRB t = make_jrb(), tmp;
    int menu = 0, n, sum, i;
    char name[30], c;
    long phone;

    FILE *fp = fopen("danhba.dat", "rb");
    contact ct;
    fseek(fp, 0, SEEK_END);
    sum = ftell(fp) / sizeof(contact);
    rewind(fp);

    for (i = 0; i < sum; ++i)
    {
        fread(&ct, sizeof(contact), 1, fp);
        jrb_insert_str(t, strdup(ct.name), new_jval_l(ct.phone));
        printf("%s\t%ld\n", ct.name, ct.phone);
    }

    while (menu != 4)
    {
        printf("1. Insert\n2. Delete\n3. Edit\n4. Exit\nEnter menu: ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("Enter name: ");
            c = getchar();
            gets(name);
            tmp = jrb_find_str(t, name);

            if (tmp == NULL)
            {
                printf("Enter phone number: ");
                scanf("%ld", &phone);
                jrb_insert_str(t, strdup(name), new_jval_l(phone));
            }
            else
            {
                printf("Contact existed\n");
                break;
            }

            printf("Successful\n");
            break;
        case 2:
            printf("Enter name: ");
            c = getchar();
            gets(name);
            tmp = jrb_find_str(t, name);
            if (tmp == NULL)
            {
                printf("Contact doesnt exist\n");
                break;
            }
            else
                jrb_delete_node(tmp);
            printf("Successful\n");
            break;
        case 3:
            printf("Enter name: ");
            c = getchar();
            gets(name);
            tmp = jrb_find_str(t, name);
            if (tmp == NULL)
            {
                printf("Contact doesnt exist\n");
                break;
            }
            else
            {
                printf("Enter phone: ");
                scanf("%ld", &phone);
                tmp->val = new_jval_l(phone);
                printf("Succesful\n");
            }
            break;
        case 5:
            jrb_traverse(tmp, t)
                printf("%s\t%ld\n", jval_s(tmp->key), jval_l(tmp->val));
        }
    }
    fclose(fp);
    fp = fopen("danhba.dat", "wb");
    jrb_traverse(tmp, t)
    {
        strcpy(ct.name, jval_s(tmp->key));
        ct.phone = jval_l(tmp->val);
        fwrite(&ct, sizeof(contact), 1, fp);
    }
    fclose(fp);
    return 0;
}
