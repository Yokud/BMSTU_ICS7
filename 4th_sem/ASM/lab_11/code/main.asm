.386
.model flat, stdcall
option casemap :none
 
include \masm32\include\windows.inc
include \masm32\macros\macros.asm
uselib kernel32, user32, masm32, comctl32
 
WndProc PROTO :DWORD,:DWORD,:DWORD,:DWORD
 
LAB_11 = 1000

EDT_FST = 1001
EDT_SND = 1002
EDT_RES = 1003

BTN_EQ = 1004


.data
  curr_item_id dd 0
 
.data?
  hInstance dd ?
  icce INITCOMMONCONTROLSEX <>

 
.code
  start:
    mov icce.dwSize, SIZEOF INITCOMMONCONTROLSEX
    mov icce.dwICC, ICC_DATE_CLASSES or \
                    ICC_INTERNET_CLASSES or \
                    ICC_PAGESCROLLER_CLASS or \
                    ICC_COOL_CLASSES
 
    invoke InitCommonControlsEx, offset icce
 
    invoke GetModuleHandle, NULL
    mov hInstance, eax
 
    invoke DialogBoxParam, hInstance, LAB_11, 0, offset WndProc, 0
 
    invoke ExitProcess,eax
 
WndProc proc hWin :DWORD, uMsg :DWORD, wParam :DWORD, lParam :DWORD
    switch uMsg
        case WM_COMMAND
            .if wParam == BTN_EQ
                invoke GetDlgItemInt, hWin, EDT_FST, 0, FALSE
                .if eax < 0 || eax > 9
                    invoke MessageBox, hWin, chr$("You must enter only digits"), chr$("Error"), 0
                    xor eax, eax
                    ret
                .endif
                mov ebx, eax 

                invoke GetDlgItemInt, hWin, EDT_SND, 0, FALSE
                .if eax < 0 || eax > 9
                    invoke MessageBox, hWin, chr$("You must enter only digits"), chr$("Error"), 0
                    xor eax, eax
                    ret
                .endif

                add eax, ebx
                invoke SetDlgItemInt, hWin, EDT_RES, eax, FALSE
            .endif

        case WM_CLOSE
            exit_program:
            invoke EndDialog, hWin, 0
    endsw

    xor eax, eax
    ret
WndProc ENDP

end start