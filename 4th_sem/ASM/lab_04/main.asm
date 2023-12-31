PUBLIC STRING
EXTRN output: near

STSG SEGMENT PARA STACK 'STACK'
	db 100 dup (0)
STSG ENDS

DSG SEGMENT PARA public 'DATA'
	BUFF dw 11
	STRING db 10 dup (' ')
	db '$'
DSG ENDS

CSG SEGMENT PARA public 'CODE'
	assume CS:CSG, DS:DSG
main:
	mov ax, DSG
	mov ds, ax
	mov ah, 0Ah
	mov dx, offset BUFF
	int 21h
	
	mov si, offset BUFF + 1 ; Длина строки
	mov cl, [si] ; Длина строки лежит в cx
	mov ch, 0 ; Обнуление для использования cx (Изначально в нём лежит код первого символа строки)
	inc cx ; Сдвиг с символу возврата каретки
	add si, cx ; Смещение указателя на строку к символу возврата каретки
	mov al, '$'
	mov [si], al ; Вставка символа '$' вместо символа возврата каретки
	
	jmp output
CSG ENDS
END main