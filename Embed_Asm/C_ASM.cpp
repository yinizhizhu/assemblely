// C_ASM.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>

	const unsigned int SIZE=30;
	int myarray[SIZE];
	int iSize = SIZE;

int c_min_para()
{
__asm {
/*   求数组中的最小值*/
	mov ecx,iSize    //可以使用C的注释符号
	jecxz minexit	;个数为0，返回
	dec ecx
	//lea esi,myarray //
	mov esi, offset myarray
	mov eax,[esi]
	jecxz minexit	//个数为1，返回
minlp:	add esi,4
	cmp eax,[esi]	//比较两个数据的大小
	jle nochange
	mov eax,[esi]	//取得较小值
nochange:	loop minlp
minexit:
       }
}
int c_min_para(int inum,int iarray[])
{
__asm {
/*   求数组中的最小值*/
	mov ecx,inum    //可以使用C的注释符号
	jecxz minexit	;个数为0，返回
	dec ecx
	mov esi,iarray
	mov eax,[esi]
	jecxz minexit	//个数为1，返回
minlp:	add esi,4
	cmp eax,[esi]	//比较两个数据的大小
	jle nochange
	mov eax,[esi]	//取得较小值
nochange:	loop minlp
minexit: 
       }
}

int show()
{
__asm
{
	mov eax, 10
}
}
int main(void)
{
	int i;
	printf("\r\n------ c_min_para-------\r\n data array:");
	for(i=0;i<iSize;i++)
	{
		myarray[i] = iSize/2-i;
		printf("\t %d",myarray[i]);
	}
	i = c_min_para(iSize,myarray);
	printf("\r\n Result of c_min_para(iSize,myarray):   %d",i);
  
	i = c_min_para();			
	printf("\r\n Result of c_min_para():   %d",i);
	//system("pause");

	i = show();
	printf("\n\nThe eax is 10, whether is it?\n");

	if (i==10)
		printf("Yes, it is!!!!\n");
	else
		printf("No, it isn't.\n");
	printf("It's %d\n", i);
	return 0;
}
