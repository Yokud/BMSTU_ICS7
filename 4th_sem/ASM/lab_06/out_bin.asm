EXTRN NUM : word
PUBLIC binary_signed


CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG
binary_signed proc near
	mov ax, SEG NUM
	mov ds, ax

	mov ah, 2
	xor dl, dl
	
	mov bx, NUM
	and bx, 8000h
	cmp bx, 8000h
		je print_sign
	jmp begin
	
	print_sign:
		mov dl, '-'
		int 21h
		jmp begin
	
	to_neg:
		not bx
		inc bx
		jmp print_begin
	
	begin:
		mov bx, NUM
		
		cmp dl, '-'
			je to_neg
		
		print_begin:
			mov cx, 16
		
	print_bits:
		shl bx, 1
		jc one
		
		mov dl, '0'
		jmp print_bit
		
		one:
			mov dl, '1'
		
		print_bit:
			int 21h
			loop print_bits
			
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h
		
	ret
binary_signed endp
CSEG ENDS
END