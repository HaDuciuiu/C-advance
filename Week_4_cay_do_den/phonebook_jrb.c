#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "jrb.h"


int main()
{
    int i, n;
    long sdt;
    char name[80];
    JRB book, node;
    
    book = make_jrb();
    jrb_insert_str(book, strdup("Dung"), new_jval_l(983456789));
    jrb_insert_str(book, strdup("Thang"), new_jval_l(945678978));
    jrb_insert_str(book, strdup("Huong"), new_jval_l(123456789));
    jrb_insert_str(book, strdup("Anh"), new_jval_l(983984775));
    
    do
    {
        //system("cls");
        printf("1.Add phone\n2.Search phone\n3.Print list\n4.Exit\nYour choice:");
        scanf("%d%*c",&n);
        switch(n){
              case 1:
                   //fflush(stdin);
                   printf("Name:");
                   gets(name);
                   fflush(stdin);
                   printf("Number:");
                   scanf("%d",&sdt);
                   node = jrb_find_str(book, name);
                   /*Ham tim kiem kieu string ben tren se tim xem khoa nao co gia tri la name roi tra ve node co
				   gia tri la name day cho node node => khi can thay doi value(val) cua node co khoa la name ta se
				   tac dong vao node->val*/
                   if (node!=NULL) {
                      // overwrite the value of this node - ghi de gia tri cua node nay      
                      node->val = new_jval_l(sdt);
					  // ghi de ta se ghi de len node tim thay name - nhu giai thich ben tren       
                   } else {
                      // not found, insert a new entry
                      jrb_insert_str(book, strdup(name), new_jval_l(sdt));    
                   }
                   break;
              case 2:
                   //fflush(stdin);
                   printf("Name:");
                   gets(name);
                   node = jrb_find_str(book, name);;
                   if (node==NULL) printf("Not found number for %s!\n", name);
                   else printf("Phone number of %s is %d", name, jval_l(node->val));
                   getch();
                   break;
              case 3:
                   jrb_traverse(node, book)
                       printf("%-15s%10d\n", jval_s(node->key), jval_l(node->val));
                   getch();
                   break;
              case 4:         
                   jrb_traverse(node, book)
                       free(jval_s(node->key));
                   jrb_free_tree(book);
                   break;
          }
     }while(n!=4);
     return 0;
}

