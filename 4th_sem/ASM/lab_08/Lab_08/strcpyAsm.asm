.686
.MODEL FLAT, C
.STACK

.CODE
strncpyAsm proc dst:DWORD, src:DWORD, len:DWORD
	pushf
	mov ecx, len
    mov esi, src
    mov edi, dst

    cld

	cmp esi, edi
        je exit
    cmp esi, edi
        jg copy

    mov eax, esi
    sub eax, edi
    cmp eax, len
        jge copy

    add edi, len
    dec edi
    add esi, len
    dec esi
    std
    
copy:
    rep movsb

exit:
	popf
	ret
strncpyAsm endp
END