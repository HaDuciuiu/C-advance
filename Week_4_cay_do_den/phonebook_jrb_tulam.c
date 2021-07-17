#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"jrb.h" // goi thu vien jrb.h de lam viec voi cay do den

int main()
{
	int i , n;
	long sdt;
	char name[80];
	JRB book , node;
	
	book = make_jrb(); // ham khoi tao mot cay jrb moi
	/* cac ham insert ben duoi la ham insert kieu string , co cac doi so la:
	1. JRB tree : ten cay jrb ma mk tao ra
	2. char *key : ten cua khoa - khoa kieu string
	3. Jval jval : gia tri cua khoa kieu Jval , duoc khoi tao qua cac ham khoi tao co san (o duoi so dien thoai la kieu
	long nen dung ham new_jval_l(1 gia tri kieu long) de khoi tao
	*/
	jrb_insert_str(book, strdup("Dung"), new_jval_l(983456789));
    jrb_insert_str(book, strdup("Thang"), new_jval_l(945678978));
    jrb_insert_str(book, strdup("Huong"), new_jval_l(123456789));
    jrb_insert_str(book, strdup("Anh"), new_jval_l(983984775));
    
    do
    {
    	printf("1. Add phone\n 2.Search phone \n 3.Print list\n 4.Exit \n 5. Your choice\n");
    	scanf("%d%*c",&n);
    	switch(n)
    	{
    		case 1:
    			printf("Name: ");
    			gets(name);
    			printf("Number: ");
    			scanf("%d",&sdt);
    			node = jrb_find_str(book,name);
    			/*Ta tim mot node trong cay jrb voi cac khoa nhu sau:
				1. book - ten cua cay jrb ta da tao ra
				2. name - khoa ta can tim trong cay jrb do(trong truong hop nay la book)*/
				if(node!=NULL)
				{
					// overwrite the value of this node - ghi de gia tri cua node nay
					node->val = new_jval_l(sdt);
				}
				else
				{
					// not found -> insert a new entry
					jrb_insert_str(book,name,new_jval_l(sdt));
					/*Ham insert kieu string ben tren co cac doi so sau:
					1. book : ten cua cay jrb mk tao ra
					2. name : khoa moi chua co trong cay jrb do
					3. sdt : vi bien duoc them vao phai co kieu jval nen ta can ham khoi tao kieu long cho sdt nhu tren*/
				}
				break;
			
			case 2:
				printf("Name : ");
				gets(name);
				node = jrb_find_str(book , name);
				/*Ham find kieu string co cac doi so sau :
				1. book - ten cua cay jrb ma mk can tim khoa name
				2. name - gia tri khoa mk can tim*/
				if(node == NULL)
				{
					printf("Not found number for %s\n",name);	
				}
				else
				{
					printf("Phone number of %s is %d\n",name,jval_l(node->val));
					/*Ta phai su dung ham jval_l de chuyen gia tri mot bien kieu jval ve kieu long
					Cu the : node->val dang co gia tri kieu jval , mk dung ham jval_l() de tra ve gia tri kieu
					long cho bien node->val roi in ra-----ok*/
				}
				break;
			case 3:
				jrb_traverse(node,book)// ben trong ham nay nhu mot vong lap for
					printf("%-15s%10d\n",jval_s(node->key),jval_l(node->val));
				/*Tat ca hai truong khoa(key) va gia tri(val) cua mot node deu co kieu jval nen de in ra hay lam viec 
				voi cac loai %s , %d ta phai su dung ham jval_s(), jval_l(), ... de tra ve cac gia tri phu hop kieu
				char va long thong thuong -----ok*/
				break;
			case 4:
				jrb_traverse(node,book)
					free(jval_s(node->key));
				jrb_free_tree(book);// ham jrb_free_tree dung de free ca cay jrb mk tao voi tham so la ten cay jrb do
				break;
		}
    	
	}while(n!=4);
	/*Note : Lam viec voi cay jrb thi ten cac ham thuong co cau truc nhu sau:
	jrb_chuc nang cua ham_kieu lam viec -------------fighting!!!
	*/
  return 0;
}

