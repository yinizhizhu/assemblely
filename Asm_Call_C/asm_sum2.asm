.586
.model flat, c   ;stdcall ;

extern c_var1:dword, c_var2:dword
use_invoke = 1
ifdef use_invoke
   c_min_para PROTO c ,count:dword,darray:PTR dword
else
   extern c_min_para:proc
endif

;public asm_var1,asm_var2,asm_var3,asm_ptr
public C asm_var1,asm_var2,asm_var3,asm_ptr
;asm_sum_para	proto, count:dword,darray:PTR dword	
;asm_sum_no_para proto

.data 
  asm_var1 dword 456321
  asm_var2 byte "Hi,this is string in asm module^_^",0
  asm_var3 dword ($ - offset asm_var2 -1)
  asm_ptr  dword asm_var2
  asm_var4 dword 1,2,3

.code
;32位有符号数据的求和过程
;----------------------------------------------
asm_sum_para	proc c uses ecx esi, count:dword,darray:PTR dword
	
	mov ecx,count	;个数为0，和为0	
	xor edx,edx
	xor eax,eax
	jecxz sum_exit
	
	mov esi,darray	;个数为1，和为本身
	mov eax,[esi]
	dec ecx
	jecxz sum_exit
sum_loop:	add esi,4
	add eax,[esi]	;计算低32位
	adc edx,0	;计算高32位
	loop sum_loop
	
sum_exit:
	ret
asm_sum_para    endp

;-------------------------------------------------
; no parameter
; use ebp to read parameter
asm_sum_no_para proc c uses ecx esi
        push ebp
        mov  ebp, esp
        mov ecx, [ebp+16]
        mov esi, [ebp+20]
        xor edx,edx
        xor eax,eax				
		jecxz sum_exit

        mov eax, [esi]
        dec ecx
        jecxz sum_exit
sum_loop:
        add esi, 4
        add eax, [esi]
        adc edx,0
        loop sum_loop
sum_exit:
        pop ebp
        ret
asm_sum_no_para endp	

;----------------------------------------------
asm_min_para proc c uses ecx esi ,count:dword,darray:PTR
ifdef use_invoke
	invoke c_min_para, count, darray
else
	push darray
	push count
	call c_min_para
	add esp, 8
endif
	ret
asm_min_para endp
;----------------------------------------------
			  
end
		  
		  