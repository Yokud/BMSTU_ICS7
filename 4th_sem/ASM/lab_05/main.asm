SSEG SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
SSEG ENDS

MTSEG SEGMENT PARA PUBLIC 'DATA'
	MTROWS db 9
	MTCOLS db 9
	MT db 81 dup(0)
	MAXROW db 1 dup(0)
	MINROW db 1 dup(0)
MTSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:MTSEG

input proc near
	mov ah, 1
	int 21h
	sub al, '0'
	mov [MTROWS], al
	
	mov ah, 2
	mov dl, ' '
	int 21h
	
	mov ah, 1
	int 21h
	sub al, '0'
	mov [MTCOLS], al
	
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h
	
	lea si, MT ; Указатель на очередной элемент матрицы
	xor cx, cx
	mov cl, [MTROWS]
	input_rows:
		mov bl, cl
		mov cl, [MTCOLS]
		
		input_row: 
			mov ah, 1
			int 21h
			sub al, '0'
			mov [si], al
			inc si
			
			mov ah, 2
			mov dl, ' '
			int 21h
			
			loop input_row
		
		mov ah, 2
		mov dl, 10
		int 21h
		mov dl, 13
		int 21h
		
		mov cl, bl
		loop input_rows
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h
	ret
input endp

output proc near
	lea si, MT ; Указатель на очередной элемент матрицы
	
	xor cx, cx
	mov cl, [MTROWS]
	output_rows:
		mov bl, cl
		mov cl, [MTCOLS]
		
		output_row: 
			mov dl, [si]
			add dl, '0' 
			inc si
			
			mov ah, 2
			int 21h
			
			mov dl, ' '
			int 21h
			
			loop output_row
		
		mov dl, 10
		int 21h
		mov dl, 13
		int 21h
		
		mov cl, bl
		loop output_rows
	ret
output endp

swap_rows proc near
	lea si, MT 
	mov ah, 0
	mov al, [MTCOLS]
	mul [MAXROW]
	add si, ax
	
	lea di, MT
	mov ah, 0
	mov al, [MTCOLS]
	mul [MINROW]
	add di, ax
	
	xor cx, cx
	mov cl, [MTCOLS]
	xchg_elems:
		xchg ah, [si]
		xchg ah, [di]
		xchg ah, [si]
		
		inc si
		inc di
		loop xchg_elems
	
	ret
swap_rows endp

findmax proc near
	lea si, MT ; Указатель на очередной элемент матрицы
	
	mov dl, [si] ; Сюда кладём максимальный элемент
	xor cx, cx
	mov cl, [MTROWS]
	rows:
		mov bl, cl
		mov cl, [MTCOLS]
		
		row: 
			cmp dl, [si]
			jl replace_max
			max_back:
				inc si
			
			loop row
		
		mov cl, bl
		loop rows
	ret
replace_max:
	mov dl, [si]
	mov al, [MTROWS]
	sub al, bl
	mov MAXROW, al ; [MTROWS] - bl
	jmp max_back
findmax endp

findmin proc near
	lea si, MT ; Указатель на очередной элемент матрицы
	
	mov dl, [si] ; Сюда кладём минимальный элемент
	xor cx, cx
	mov cl, [MTROWS]
	rows:
		mov bl, cl
		mov cl, [MTCOLS]
		
		row: 
			cmp dl, [si]
			jg replace_min
			min_back:
				inc si
			
			loop row
		
		mov cl, bl
		loop rows
	ret
replace_min:
	mov dl, [si]
	mov al, [MTROWS]
	sub al, bl
	mov MINROW, al
	jmp min_back
findmin endp
	
main:
	call input
	
	call findmax
	call findmin
	call swap_rows
	
	call output
	mov ah, 4Ch
	int 21h
CSEG ENDS
END main