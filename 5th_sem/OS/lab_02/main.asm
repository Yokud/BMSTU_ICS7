.386P

; Структура для описания дескрипторов сегментов памяти
descr   struct
    lim     dw 0    ; Граница сегмента (0-15)
    base_l  dw 0    ; База (0-15)
    base_m  db 0    ; База (16-23)
    attr_1  db 0    ; Атрибуты 1 (P, DPL, Type)
    attr_2  db 0    ; Атрибуты 2 (G, D, AVL, Граница сегмента(16-19))
    base_h  db 0    ; База(24-31)
descr ends

; Структура для описания шлюзов
idescr struc
    offs_l  dw 0    ; Смещение обработчика (0-15)
    sel     dw 0    ; Селектор сегмента команд
    cntr    db 0    ; Счётчик
    attr    db 0    ; Атрибуты (P, DPL, Type)
    offs_h  dw 0    ; Смещение обработчика (16-31)
idescr ends

stack segment  para stack 'STACK'
    stack_start db  100h dup(0)
    stack_size = $-stack_start
stack ends

; Сегмент данных
data segment para 'DATA'
    gdt_null descr   <> ; нулевой дескриптор
    gdt_data descr   <data_size-1,,,92h> ; сегмент данных
    gdt_code_16 descr   <code_16_size-1,,,98h> ; сегмент команд
    gdt_code_32 descr <code_32_size-1,0,0,98h,40h>
    gdt_stack descr  <stack_size,,,92h> ; сегмент стека
    gdt_screen descr <4095,8000h,0Bh,92h> ; видеопамять
    gdt_datacheck descr<0FFFFh,,,92h,0CFh> ; старшая память (4 Гб)
    gdt_size=$-gdt_null

    pdescr df 0

    data_s=8
    code_16_s=16
    code_32_s=24
    stack_s=32
    screen_s=40
    datacheck_s=48

    idt label byte
    idescr_0_12 idescr 13 dup (<dummy,code_32_s,0,10001111b,0>) ; тип = 1111(ловушки)
    idescr_13 idescr <exc13, code_32_s, 0, 10001111b,0>
    idescr_14_31 idescr 18 dup (<dummy,code_32_s,0,10001111b,0>)
    int08 idescr <timerInt,code_32_s,0,10001110b,0> ; тип = 1110 (прерывание)
    int09 idescr <keybInt,code_32_s,0,10001110b,0>
    idt_size = $-idt 

    ipdescr df 0

    mask_master db 0        
    mask_slave  db 0        

    interval_time db 0            

    interval=10
    enter_but db 0
    mempos=80*2+mem_msg_len*2+2
    cursor_pos=mempos+2+6
    syml_pos dw 80*2*2
    cursor_symb_on=220
    cursor_symb_off=223
    prmod_pos=0
    memmsg_pos=80*2

    protectmode  db  'Protected Mode!'
    protectmode_len=$-protectmode

    mem_msg db 'Free memory available: '
    mem_msg_len=$-mem_msg

    rm_msg      db 27, '[29;44mReal Mode. Press any key to enter to protected mode.', 27, '[0m$'
    pm_msg_out  db 27, '[29;44mReal Mode again!', 27, '[0m$'
    color=16h

    asciimap db 0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0
             db 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0
             db 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0, 0, 0, '\'
             db 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'

    data_size = $-gdt_null 
data ends

code_32 segment para public 'CODE' use32
     assume cs:code_32, ds:data, ss:stack
     
    protected:
        mov ax, data_s
        mov ds, ax
        mov ax, screen_s
        mov es, ax
        mov ax, stack_s
        mov ss, ax
        mov eax, stack_size
        mov esp, eax

        mov edi, prmod_pos
        mov ebx, offset protectmode
        mov ecx, protectmode_len
        mov ah, color

        loop_02:
            mov al, byte ptr [bx]
            inc bx
            stosw
        loop loop_02

        mov edi, memmsg_pos
        mov ebx, offset mem_msg
        mov ecx, mem_msg_len
        mov ah, color

        loop_03:
            mov al, byte ptr [bx]
            inc bx
            stosw
        loop loop_03

        call count_memory
        mov ax, data_s
        mov ds, ax

        looplab:
        cmp enter_but, 1
        jne looplab
        
        mov gdt_data.lim, 0FFFFh
        mov gdt_code_16.lim, 0FFFFh
        mov gdt_stack.lim, 0FFFFh
        mov gdt_screen.lim, 0FFFFh
        mov gdt_datacheck.lim, 0FFFFh

        push ds
        pop  ds
        push es
        pop  es
        push ss
        pop  ss
        
        ; Загрузка селектора в регистр CS и модификация теневого регистра
        db  0EAh
        dd  offset next
        dw  code_32_s
        next:
        mov eax, cr0
        and eax, 0FFFFFFFEh
        mov cr0, eax

        db  0EAh
        dd  offset real
        dw  code_16

    dummy proc
        iret
    dummy endp

    exc13 proc
        pop eax
        iret
    exc13 endp

    ; Перевод числа доступной памяти в десятичный вид
    output_in_dec proc near
        push edx
        push ecx
        push ebx
        xor edx, edx
        mov ecx, 1048576
        div ecx
        inc eax
        mov ecx, 10
        mov bx, mempos
        add bx, 6
        mov dh, color
        mov dl, 'b'
        mov es:[bx], dx
        dec bx
        dec bx
        mov dl, 'M'
        mov dh, color
        mov es:[bx], dx
        dec bx
        dec bx
        mov dl, ' '
        mov dh, color
        mov es:[bx], dx
        dec bx
        dec bx

        prmem:
            xor edx, edx
            div ecx; edx:eax / 10
            add dl, '0'
            mov dh, color
            mov es:[bx], dx
            dec bx
            dec bx
            cmp eax, 0
            jnz prmem

        pop ebx
        pop ecx
        pop edx
        ret
    output_in_dec endp

    ; Подсчёт доступной памяти (в Кб)
    count_memory proc 
        mov ax, datacheck_s
        mov ds, ax

        push eax
        push ebx
        push edx
        mov ebx, 100000h
        mov eax, 400h
        xor edx, edx
    cloop:
        mov [ebx], eax
        cmp eax, [ebx]
        je cloop1
        jmp exit
    cloop1:
        add edx, 4h
        add ebx, 4h
    
        jz exit
        jmp cloop
    exit:

    mov eax, edx
    call output_in_dec

    pop edx
    pop ebx
    pop eax
    ret
    count_memory endp

    timerInt proc uses eax
        cmp interval_time, interval
        je ON
        cmp interval_time, interval*2
        jne skip

        mov al, cursor_symb_off
        mov interval_time, 0
        jmp pr
    ON:
        mov al, cursor_symb_on
    pr:
        mov ah, color
        mov bx, cursor_pos
        mov es:[bx], ax      
    skip:
        mov  al, interval_time
        inc al
        mov interval_time, al

        ; Разрешение на выполнение других прерываний
        mov al, 20h
        out 20h, al
        
        iretd
    timerInt endp

    keybInt proc
        push eax
        push bx
        push dx
        xor eax, eax
        in  al, 60h
        cmp al, 1Ch
        jne print         
        or enter_but, 1
        jmp endlab
    print:
        cmp al, 80h  ;  При отпускании клавиши контроллер клавиатуры посылает в тот же порт скан-код, увеличенный на 80h
        ja endlab

        cmp eax, 0Eh
        je backspace

        mov dl, asciimap[eax]
        mov al, dl
        mov ah, color
        mov bx, syml_pos
        mov es:[bx], ax      
        add syml_pos, 2
        jmp endlab

    backspace:
        cmp syml_pos, 80*2*2
        je endlab

        mov al, 0
        mov ah, 0
        sub syml_pos, 2
        mov bx, syml_pos
        mov es:[bx], ax      

    endlab:
        in  al, 61h 
        or  al, 80h 
        out 61h, al 
        and al, 7Fh 
        out 61h, al

        mov al, 20h 
        out 20h, al

        pop dx
        pop bx
        pop eax

        iretd

    keybInt endp
 code_32_size = $-protected
 code_32 ends

code_16 segment para public 'CODE' use16
assume cs:code_16, ds:data, ss: stack
start:
    main    proc
        mov ax, data
        mov ds, ax

        ; очистить экран
        mov ax, 3
        int 10h

        mov ah, 09h
        lea dx, rm_msg
        int 21h
        xor dx, dx
        mov ah, 2
        mov dl, 13
        int 21h
        mov dl, 10
        int 21h

        ; ожидание ввода символа
        mov ah, 10h
        int 16h

        ; очистить экран
        mov ax, 3
        int 10h

        ; Загрузка линейного адреса сегмента данных в GDT
        xor eax, eax
        mov ax, data
        shl eax, 4
        mov bx, offset gdt_data
        mov (descr ptr [bx]).base_l, ax
        shr eax, 16
        mov (descr ptr [bx]).base_m, al

        ; Загрузка линейного адреса сегмента команд реального режима в GDT
        xor eax, eax
        mov ax, code_16
        shl eax, 4
        mov bx, offset gdt_code_16
        mov (descr ptr [bx]).base_l, ax
        shr eax, 16
        mov (descr ptr [bx]).base_m, al


        ; Загрузка линейного адреса сегмента команд защищенного режима в GDT
        xor eax, eax
        mov ax, code_32
        shl eax, 4
        mov bx, offset gdt_code_32
        mov (descr ptr [bx]).base_l, ax
        shr eax, 16
        mov (descr ptr [bx]).base_m, al

        ; Загрузка линейного адреса сегмента стека в GDT
        xor eax, eax
        mov ax, stack
        shl eax, 4
        mov bx, offset gdt_stack
        mov (descr ptr [bx]).base_l, ax
        shr eax, 16
        mov (descr ptr [bx]).base_m, al

        ; загрузка gdtr через псевдодескриптор
        xor eax, eax
        mov ax, data
        shl eax, 4
        add eax, offset gdt_null
        mov dword ptr pdescr + 2, eax
        mov word ptr pdescr, gdt_size - 1
        lgdt pdescr          

        ; сохранение масок  
        in  al, 21h                     
        mov mask_master, al             
        in  al, 0A1h                    
        mov mask_slave, al

        ; устанавливаем базовый вектор ведущего контроллера в 32
        mov al, 11h
        out 20h, al                     
        mov al, 32
        out 21h, al                     
        mov al, 4
        out 21h, al
        mov al, 1
        out 21h, al
        
        ; маска для ведущего контроллера (запрещаем все прерывания, кроме IRQ0 IRQ1)
        mov al, 0FCh
        out 21h, al

        ; маска для ведомого контроллера (запрещаем прерывания)
        mov al, 0FFh
        out 0A1h, al

        ; загрузка idtr через псевдодескриптор
        mov  word ptr  ipdescr, idt_size-1 
        xor eax, eax
        mov ax, data
        shl eax, 4
        add eax, offset idt
        mov  dword ptr ipdescr + 2, eax 
        lidt fword ptr ipdescr 
        
        ; открытие линии А20
        in  al, 92h
        or  al, 2
        out 92h, al


        ; Переход в защищенный режим
        mov eax, cr0
        or  eax, 1
        mov cr0, eax

        db  66h 
        db  0EAh
        dd  offset protected
        dw  code_32_s
        
    real:
        mov ax, data   
        mov ds, ax
        mov ax, stack   
        mov ss, ax
        mov ax, stack_size
        mov sp, ax

        ; контроллер прерываний отправляет процессору номер вектора, который формируется
        ; путём сложения базового номера с номером линии, по которой поступил запрос от устройства

        ; восстановление ведущего контроллера, установив базовый вектор в 8
        mov al, 11h
        out 20h, al
        mov al, 8
        out 21h, al
        mov al, 4
        out 21h, al
        mov al, 1
        out 21h, al

        ;восстановление масок 
        mov al, mask_master
        out 21h, al
        mov al, mask_slave
        out 0A1h, al

        ; восстановление idtr
        mov ax, 3FFh ; граница таблицы векторов (1кб)
        mov word ptr ipdescr, ax
        mov eax, 0 ; лин базовый адрес
        mov dword ptr ipdescr+2, eax 
        lidt ipdescr

        ;закрытие линии A20
        mov al, 0D1h 
        out 64h, al
        mov al, 0DDh
        out 60h, al

        ; очистить экран
        mov ax, 3
        int 10h

        mov ah, 09h
        lea dx, pm_msg_out
        int 21h
        xor dx, dx
        mov ah, 2
        mov dl, 13
        int 21h
        mov dl, 10
        int 21h

        mov ax, 4C00h
        int 21h
    main    endp
code_16_size = $-start  
code_16 ends

end main