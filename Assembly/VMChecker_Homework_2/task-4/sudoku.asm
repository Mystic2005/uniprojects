%include "../include/io.mac"

extern printf
global check_row
global check_column
global check_box
; you can declare any helper variables in .data or .bss

section .data
frecv db 0,0,0,0,0,0,0,0,0

section .text


; int check_row(char* sudoku, int row);
check_row:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    push ebx
    push ecx
    push edx
    push esi
    push edi

    mov     esi, [ebp + 8]  ; char* sudoku, pointer to 81-long char array
    mov     edx, [ebp + 12]  ; int row 
    ;; DO NOT MODIFY

    ;; Freestyle starts here
    mov eax, edx
    mov ebx, 9
    mul ebx
    mov edi, eax ; 9 * row pt a parcurge vectorul

    mov ecx, 9
    mov ebx, frecv
clearfrecv:
    mov byte [ebx], 0
    inc ebx
    loop clearfrecv

    mov ecx, 9
mainloop:
    movzx eax, byte [esi + edi]
    cmp eax, 1
    jl skip
    cmp eax, 9
    jg skip
    dec eax
    movzx ebx, byte [frecv + eax]
    cmp ebx, 1
    je skip
    mov byte [frecv + eax], 1
    inc edi
    dec ecx
    cmp ecx, 0
    jg mainloop
    mov eax, 1
    jmp end_check_row
    ; 

skip:
    mov eax, 2 ; caz invalid
    ;; MAKE SURE TO LEAVE YOUR RESULT IN EAX BY THE END OF THE FUNCTION
    ;; Remember: OK = 1, NOT_OKAY = 2
    ;; ex. if this row is okay, by this point eax should contain the value 1 

    ;; Freestyle ends here
end_check_row:
    ;; DO NOT MODIFY

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    leave
    ret
    
    ;; DO NOT MODIFY

; int check_column(char* sudoku, int column);
check_column:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    push ebx
    push ecx
    push edx
    push esi
    push edi

    mov     esi, [ebp + 8]  ; char* sudoku, pointer to 81-long char array
    mov     edx, [ebp + 12]  ; int column 
    ;; DO NOT MODIFY
   
    ;; Freestyle starts here
    mov ecx, 9
    mov ebx, frecv
clearfrecv1:
    mov byte [ebx], 0
    inc ebx
    loop clearfrecv1

    mov edi, [ebp + 12]
    mov ecx, 9
mainloop1:
    movzx eax, byte [esi + edi]
    cmp eax, 1
    jl skip1
    cmp eax, 9
    jg skip1
    dec eax
    movzx ebx, byte [frecv + eax]
    cmp ebx, 1
    je skip1
    mov byte [frecv + eax], 1
    add edi, 9
    dec ecx
    cmp ecx, 0
    jg mainloop1

    mov eax, 1
    jmp end_check_column
    ; 

skip1:
    mov eax, 2 ; caz invalid

    ;; MAKE SURE TO LEAVE YOUR RESULT IN EAX BY THE END OF THE FUNCTION
    ;; Remember: OK = 1, NOT_OKAY = 2
    ;; ex. if this column is okay, by this point eax should contain the value 1 

    ;; Freestyle ends here
end_check_column:
    ;; DO NOT MODIFY

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    leave
    ret
    
    ;; DO NOT MODIFY


; int check_box(char* sudoku, int box);
check_box:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    push ebx
    push ecx
    push edx
    push esi
    push edi

    mov     esi, [ebp + 8]  ; char* sudoku, pointer to 81-long char array
    mov     edx, [ebp + 12]  ; int box 
    ;; DO NOT MODIFY
   
    ;; Freestyle starts here
    mov ecx, 9
    mov ebx, frecv
clearfrecv2:
    mov byte [ebx], 0
    inc ebx
    loop clearfrecv2

    mov eax, edx
    mov ecx, 3
    xor edx, edx
    div ecx
    mov ebx, eax ; row
    mov ecx, edx ; col

    mov eax, ebx
    mov ebx, 27
    mul ebx
    mov edi, eax
    ; calculez index de start (row * 27) + (col * 3)
    mov eax, ecx
    mov ecx, 3
    mul ecx ; col * 3
    add edi, eax ; start index
    mov ecx, 3 ; contor loop1
    xor ebx, ebx ; contor rows
loop1:
    push ecx
    mov ecx, 3 ; index pt loop2
    xor edx, edx ; contor col
loop2: ; comparatie ca la restul
    movzx eax, byte [esi + edi]
    cmp eax, 1
    jl skip2
    cmp eax, 9
    jg skip2
    dec eax
    movzx ebx, byte [frecv + eax]
    cmp ebx, 1
    je skip2
    mov byte [frecv + eax], 1
    inc edi
    dec ecx
    cmp ecx, 0
    jg loop2 ; se foloseste ecx loop2

    add edi, 6 ; 9-3 = 6 (sar un rand)
    pop ecx ; ecx loop1
    dec ecx
    cmp ecx, 0
    jg loop1

    mov eax, 1
    jmp end_check_box
    ; loop de verificare box

skip2:
    pop ecx
    mov eax, 2 ; caz invalid


    ;; MAKE SURE TO LEAVE YOUR RESULT IN EAX BY THE END OF THE FUNCTION
    ;; Remember: OK = 1, NOT_OKAY = 2
    ;; ex. if this box is okay, by this point eax should contain the value 1 

    ;; Freestyle ends here
end_check_box:
    ;; DO NOT MODIFY

    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    leave
    ret
    
    ;; DO NOT MODIFY
