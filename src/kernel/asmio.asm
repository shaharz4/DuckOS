global in_byte
global out_byte
global in_word
global out_word

; IN/OUT WORD/BYTE implemented for CDECL

in_byte:
    push    ebp
    mov     ebp, esp
    mov     edx, [ebp + 8]  ; unsigned short port; 0 is ebp; +4 is IP 
    xor     eax, eax
    in      al, dx          ; ret val already in al/eax
    pop     ebp
    ret

out_byte:
    push    ebp
    mov     ebp, esp
    mov     edx, [ebp + 8]  ; unsigned short port
    mov     eax, [ebp + 12] ; unsigned char data
    out     dx, al
    pop     ebp
    ret

in_word:
    push    ebp
    mov     ebp, esp
    mov     edx, [ebp + 8]  ; unsigned short port
    xor     eax, eax
    in      ax, dx 
    pop     ebp
    ret

out_word:
    push    ebp
    mov     ebp, esp
    mov     edx, [ebp + 8]  ; unsigned short port
    mov     eax, [ebp + 12] ; unsigned short data
    out     dx, ax
    pop     ebp
    ret