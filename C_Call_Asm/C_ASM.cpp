// C_ASM.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>

extern "C" int asm_sum_para(unsigned int,int *);
extern "C" int asm_sum_no_para(unsigned int,int *);

extern "C" unsigned int  asm_var1;
extern "C" unsigned char asm_var2[];
extern "C" unsigned int asm_var3;
extern "C" char *asm_ptr;

void main(void)
{
  int i;
  const unsigned int iSize=30;
  int myarray[iSize];
  
  for(i=0;i<iSize;i++)
	  myarray[i] = i+1;

  printf("\r\n asm_var1:%d",asm_var1 );
  printf("\r\n asm_var2:%s",asm_var2 );
  printf("\r\n asm_var3:%d",asm_var3 );
  printf("\r\n asm_ptr :%s\r\n",asm_ptr );

  i= asm_sum_para(iSize,myarray);
  printf("\r\n asm_sum_para:   %d",i);

  i = asm_sum_no_para(iSize,myarray);
  printf("\r\n asm_sum_no_para:%d",i);

  printf("\r\n \r\n Press any key to exit...");
  _getch();
  //system("pause");
}


