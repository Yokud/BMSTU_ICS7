EXTRN binary_signed : proc
EXTRN hex_unsigned : proc
EXTRN input_oct_number : proc


SSEG SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
SSEG ENDS

MENUSEG SEGMENT PARA PUBLIC 'DATA'
	ENTRY db "This program get unsigned oct number and can translate to hex and binary system.", 10, 13, '$'
	MENU_MES db "Menu:", 10, 13, "1 - Enter unsigned oct number", 10, 13, "2 - Output unsigned hex number", 10, 13,
		"3 - Output signed binary number", 10, 13, "0 - Exit", 10, 13, 10, 13, "Choice: ", '$'
	ERR db "Unknown program!", 10, 13, 10, 13, '$'
	PROCS dw input_oct_number, hex_unsigned, binary_signed
MENUSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:MENUSEG
	
err_print:
	mov ah, 9
	lea dx, ERR
	int 21h
	jmp menu
	
call_proc:
	
	
main:
	mov ax, MENUSEG
	mov ds, ax

	mov ah, 9
	lea dx, ENTRY
	int 21h
	
	menu:
		mov ax, MENUSEG
		mov ds, ax
		
		mov ah, 9
		lea dx, MENU_MES
		int 21h
		
		mov ah, 1
		int 21h
		
		mov dh, al
		
		mov ah, 2
		mov dl, 10
		int 21h
		mov dl, 13
		int 21h
		
		mov al, dh
		
		sub al, '0'
		mov bl, al
		xor bh, bh
		
		
		cmp bl, 0
			je exit
		cmp bl, 4
			jge err_print
			
		dec bx
		shl bx,1
		call PROCS[bx]

		jmp menu
	
	exit:
		mov ah, 4Ch
		int 21h
CSEG ENDS
END main