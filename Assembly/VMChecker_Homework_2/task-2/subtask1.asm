%include "../include/io.mac"

; declare your structs here
zile db 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
; index de la 1
section .data

section .text
    global check_events
    extern printf

check_events:
    ;; DO NOT MODIFY
    enter 0,0
    pusha

    mov ebx, [ebp + 8]      ; events
    mov ecx, [ebp + 12]     ; length
    ;; DO NOT MODIFY

    ;; Your code starts here
mainloop:
    movzx eax, byte [ebx+32]  ; ziua
    movzx edi, byte [ebx+33] ; luna
    movzx edx, word [ebx+34] ; anul (2 byte)
    mov byte [ebx+31], 1 ; valid

    ;comparari
    cmp edx, 1990
    jl invalid
    cmp edx, 2030
    jg invalid

    cmp edi, 1
    jl invalid
    cmp edi, 12
    jg invalid

    cmp eax, 1
    jl invalid
    movzx edi, byte [zile + edi]
    cmp eax, edi ; ziua lunii din edi
    jg invalid

    jmp skip

invalid:
    mov byte [ebx+31], 0

skip:
    add ebx, 36
    loop mainloop

end:
    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY