// C_ASM.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>
#include <time.h>

extern "C" int asm_sum_para(unsigned int,int *);
//extern  int asm_sum_para(unsigned int,int *);

extern "C" int asm_sum_no_para(unsigned int,int *);
extern "C" int asm_min_para(unsigned int,int *);

extern "C" unsigned int  asm_var1;
//extern "C" unsigned char asm_var2;
extern "C" unsigned char asm_var2[];
//extern "C" unsigned char *asm_var2;
extern "C" unsigned int asm_var3;
extern "C" char *asm_ptr;

extern "C"{
 int  c_var1=10,c_var2=20;
 int  c_min_para(int,int *);
}
 int  c_min_para(int,int *);

extern int c_sum_para(int inum,int iarray[]);
void speedpk();

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
//	ret
       }
}


void main(void)
{
	const unsigned int SIZE=30;
	int myarray[SIZE];
	int iSize = SIZE;

	int i;
	for(i=0;i<SIZE;i++)
	{
		myarray[i] = SIZE/2 - i;
			printf("%d\t",myarray[i] );
	}

	printf("\r\n asm_var1:%d",(int)(asm_var1)  );
	//  printf("\r\n asm_var2:%s",&asm_var2 );
	printf("\r\n asm_var2:%s",asm_var2 );
	printf("\r\n asm_var3:%d",asm_var3 );
	printf("\r\n asm_ptr :%s\r\n",asm_ptr );


  printf("\r\n\r\n Call asm function:");

  i= asm_sum_para(SIZE,myarray);
  printf("\r\n asm_sum_para:   %d",i);

  i = asm_sum_no_para(SIZE,myarray);
  printf("\r\n asm_sum_no_para:%d",i);

  i = asm_min_para(SIZE,myarray);
  printf("\r\n asm_min_para:%d",i);

  i = c_min_para(SIZE,myarray);
  printf("\r\n c_min_para:   %d",i);
  
  speedpk();
  printf("\r\n \r\n Press any key to exit...");
  _getch();
  //system("pause");

}


int c_sum_para(int inum,int iarray[])
{
	int i, result = 0;
	for(i=0;i<inum;i++)
		result += iarray[i];
	return result;
}

int c_sum_embedded_asm(int inum, int iarrsy[])
{
	int iResult = 0;
	__asm{

	    mov ecx, inum
		xor edx,edx
		xor eax,eax		
		jecxz sum_exit

        mov esi, iarrsy
        mov eax, [esi]
        dec ecx
        jecxz sum_exit
sum_loop:
        add esi, 4
        add eax, [esi]
        adc edx,0
        loop sum_loop
sum_exit:
	}

}
void speedpk()
{
	int *parray;
	int n = 200000;
	unsigned int iRepeatTimes = 20000;
	time_t startTime,endTime;
	unsigned int i;
	int iResult;

	parray = new int[n];	
	for(i=0;i<n;i++)
		parray[i] = i%100;
 
	printf("\r\n \r\n Test speed, please wait...");
		
	iResult = 0;
	time(&startTime);
	for(i=0;i<iRepeatTimes;i++)
		iResult = c_sum_para(n,parray);
	time(&endTime);
	printf("\r\n  cpp_sum_para :%d \t use time: %2ds\r\n",iResult,endTime - startTime);

	iResult = 0;
	time(&startTime);
	for(i=0;i<iRepeatTimes;i++)
		iResult = c_sum_embedded_asm(n,parray);
	time(&endTime);
	printf("\r\n  c_embedded_asm:%d \t use time: %2ds\r\n",iResult,endTime - startTime);


	iResult = 0;
	time(&startTime);
	for(i=0;i<iRepeatTimes;i++)
		iResult = asm_sum_para(n,parray);
	time(&endTime);
	printf("\r\n  asm_sum:      %d \t use time: %2ds\r\n",iResult,endTime - startTime);

	delete parray;
}


