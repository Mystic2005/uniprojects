%include "../include/io.mac"

; declare your structs here

section .text
    global sort_events
    extern printf

sort_events:
    ;; DO NOT MODIFY
    enter 0, 0
    pusha

    mov ebx, [ebp + 8]      ; events
    mov ecx, [ebp + 12]     ; length
    ;; DO NOT MODIFY

    ;; Your code starts here
    dec ecx ; bubblesort
loop1:
    mov ebx, [ebp + 8]
    mov edi, ecx
loop2:
    ;comparare
    movzx eax, byte [ebx+31]
    movzx edx, byte [ebx+36+31]
    cmp eax, edx
    jl swap
    jg skip

    ;comparare an luna zi
    movzx eax, word [ebx+34]
    movzx edx, word [ebx+36+34]
    cmp eax, edx
    jg swap
    jl skip

    movzx eax, byte [ebx+33]
    movzx edx, byte [ebx+36+33]
    cmp eax, edx
    jg swap
    jl skip

    movzx eax, byte [ebx+32]
    movzx edx, byte [ebx+36+32]
    cmp eax, edx
    jg swap
    jl skip

swap: ; swap byte cu byte prin loop
    xor eax, eax
    xor edx, edx
    push edi
    push ecx
    mov ecx, 36
    mov edi, ebx
    mov esi, ebx
    add esi, 36
swaploop:
    mov al, byte [edi]
    mov dl, byte [esi]
    mov [edi], dl
    mov [esi], al
    inc edi
    inc esi
    loop swaploop
    pop ecx
    pop edi

skip:
    add ebx, 36
    dec edi
    cmp edi, 0
    jg loop2

    loop loop1
    ;; Your code ends here

    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY