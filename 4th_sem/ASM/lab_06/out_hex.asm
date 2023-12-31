EXTRN NUM : word
PUBLIC hex_unsigned

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
hex_unsigned proc near
	mov ax, SEG NUM
	mov ds, ax

	mov ah, 2
	
	mov bx, NUM
	mov cx, 4
	
	begin:
		mov dl, bh
		and dl, 0F0h
		
		mov al, cl
		mov cl, 4
		shr dl, cl
		mov cl, al
		
		cmp dl, 9
			jg letter
		jmp digit
		
		letter:
			sub dl, 10
			add dl, 'A';
			jmp print
			
		digit:
			add dl, '0'
			jmp print
			
		print:
			int 21h
		
		mov al, cl
		mov cl, 4
		shl bx, cl
		mov cl, al
		loop begin
	
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h	
	
	ret
hex_unsigned endp
CSEG ENDS
END
