section .text
global kfib

kfib:
    ; create a new stack frame
    enter 0, 0
    push ebx
    push esi
    push edi
    xor eax, eax

    ; n
    mov ecx, [ebp + 8]
    ; K
    mov edx, [ebp + 12]

    cmp ecx, edx
    ; n<K
    jl zero
    ; n==K
    je unu

    xor edi, edi
    ; primesc n si K ca parametrii deci fac un fel de fibonnaci clasic recursiv
    mov ebx, 1
mainloop:
    ; n
    mov ecx, [ebp + 8]
    sub ecx, ebx
    push edx
    push ecx
    call kfib
    ; readuc stiva dupa apelul recursiv
    add esp, 8

    add edi, eax
    inc ebx
    cmp ebx, edx
    jle mainloop

    mov eax, edi
    jmp end

zero:
    xor eax, eax
    jmp end

unu:
    ; return conf cerintei
    mov eax, 1

end:
    pop edi
    pop esi
    pop ebx
    leave
    ret

