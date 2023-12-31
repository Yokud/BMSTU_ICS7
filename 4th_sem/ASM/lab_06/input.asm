PUBLIC input_oct_number
PUBLIC NUM

OCT_SEG SEGMENT PARA PUBLIC 'DATA'
	NUM dw 1 dup(0)
OCT_SEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:OCT_SEG
input_oct_number proc near
	mov ax, OCT_SEG
	mov ds, ax

	mov ah, 1
	xor bx, bx
	mov cx, 6
	put_digit:
		mov al, cl
		mov cl, 3
		shl bx, cl
		mov cl, al
		
		int 21h
		sub al, '0'
		or bl, al
		loop put_digit
	
	mov NUM, bx
	
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h
	
	ret
input_oct_number endp
CSEG ENDS
END