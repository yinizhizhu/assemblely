// C_ASM.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>

	const unsigned int SIZE=30;
	int myarray[SIZE];
	int iSize = SIZE;

int c_min_para()
{
__asm {
/*   �������е���Сֵ*/
	mov ecx,iSize    //����ʹ��C��ע�ͷ���
	jecxz minexit	;����Ϊ0������
	dec ecx
	//lea esi,myarray //
	mov esi, offset myarray
	mov eax,[esi]
	jecxz minexit	//����Ϊ1������
minlp:	add esi,4
	cmp eax,[esi]	//�Ƚ��������ݵĴ�С
	jle nochange
	mov eax,[esi]	//ȡ�ý�Сֵ
nochange:	loop minlp
minexit:
       }
}
int c_min_para(int inum,int iarray[])
{
__asm {
/*   �������е���Сֵ*/
	mov ecx,inum    //����ʹ��C��ע�ͷ���
	jecxz minexit	;����Ϊ0������
	dec ecx
	mov esi,iarray
	mov eax,[esi]
	jecxz minexit	//����Ϊ1������
minlp:	add esi,4
	cmp eax,[esi]	//�Ƚ��������ݵĴ�С
	jle nochange
	mov eax,[esi]	//ȡ�ý�Сֵ
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
