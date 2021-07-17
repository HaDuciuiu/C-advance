#include<stdio.h>
void fun(int a)
{
	printf("gia tri cua a la: %d\n",a);
}
int main()
{
	// fun_ptr la con tro ham tro toi ham fun
	void(*fun_ptr)(int) = &fun;// nho phai gan gia tri cho con tro ham
	/*
	Dong lenh tren tuong ung voi hai dong sau:
	void (*fun_ptr)(int);
	fun_ptr = &fun;
	*/
	// goi ham fun bang cach dung con tro ham fun_ptr
	(*fun_ptr)(10);// cau lenh tuong duong voi fun(10)
  return 0;
}

