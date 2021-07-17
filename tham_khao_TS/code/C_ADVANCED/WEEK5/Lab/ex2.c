#include <stdio.h>
#include <stdlib.h>
#include "../../bt/inc/btree.h"

int list(BTA *btact)
{
	int status = 0,
		count = 0;
	BTint val;
	char key[ZKYLEN];

	while (status == 0)
	{
		status = bnxtky(btact, key, &val);
		if (status == 0)
		{
			printf("Name: %s, SDT = " ZINTFMT "\n", key, val);
			count++;
		}
	}
	if ((status == 0 || status == QNOKEY))
		printf("%d keys listed\n", count);
	return ((status == 0 || status == QNOKEY) ? 0 : status);
}
BTA *btfile;

int main(int argc, char const *argv[])
{
	btinit();
	btfile = btcrt("phonebook", 0, FALSE);
	int ch;
	char name[32];
	int sdt;
	int returnCode;
	while (1)
	{
		printf(" --------------MENU--------------- \n"
			   "|1. Them mot thong tin lien lac     |\n"
			   "|2. Tim kiem theo ten                    |\n"
			   "|3. Hien thi toan bo danh ba          |\n"
			   "|4. Xoa mot thong tin lien lac       |\n"
			   "|5. Thoat                                        |\n "
			   " --------------------------------------- \n"
			   "-> Select: ");
		scanf("%d%*c", &ch);

		switch (ch)
		{
		case 1:
			printf("Name: ");
			scanf("%[^\n]%*c", name);
			printf("SDT: ");
			scanf("%d%*c", &sdt);
			binsky(btfile, name, sdt);
			printf("Insert Key Thanh Cong!\n");
			break;
		case 2:
			printf("Find Name: ");
			scanf("%[^\n]%*c", name);
			returnCode = bfndky(btfile, name, &sdt);
			if (returnCode == 0)
			{
				printf("SDT cua %s la: %d", name, sdt);
			}
			else if (returnCode == QNOKEY)
			{
				printf("Not found!!!\n");
				continue;
			}
			break;
		case 3:
			btpos(btfile, 1);
			printf("LIST:\n");
			list(btfile);
			break;
		case 4:
			printf("Delete Name: ");
			scanf("%[^\n]%*c", name);
			bdelky(btfile, name);
			printf("Xoa thanh cong!\n");
			break;
		case 5:
			printf("\t Bye! Bye!\n");
			btcls(btfile);
			exit(0);
			break;
		default:
			printf("Vui long nhap lua chon tu 1-4!!!\n");
			break;
		}
	}
	return 0;
}
