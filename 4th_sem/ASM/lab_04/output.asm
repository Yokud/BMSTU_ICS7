PUBLIC output
EXTRN STRING: byte

CSG SEGMENT PARA public 'CODE'
	assume CS: CSG
output:
	mov ah, 2
	mov dl, 10
	int 21h
	mov dl, 13
	int 21h
	mov dx, offset STRING
	mov ah, 9
	int 21h
	
	mov ah, 4ch
	int 21h
CSG ENDS
END