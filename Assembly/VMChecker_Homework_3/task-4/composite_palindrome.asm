section .data
    ; valori ajutatoare pentru ca mi se da overflow la registrii de la functiile externe
    copy dd 0
    ; sunt alocate dinamic si retin pointeri
    maxcopy dd 0

section .text
global check_palindrome
global composite_palindrome

extern strcpy
extern strcat
extern strcmp
extern malloc
extern strlen
extern free

check_palindrome:
    ; create a new stack frame
    enter 0, 0
    xor eax, eax
    push ebx
    push esi
    push edi

    ; incep de la n-1 cu indexul din eax[n-1] practic
    mov ecx, [ebp + 12]
    dec ecx

    xor edx, edx
mainloop:
    cmp edx, ecx
    jge endpozitiv

    ; primul pointer
    mov eax, [ebp + 8]
    add eax, edx
    mov al, [eax]
    ; al doilea pointer
    mov ebx, [ebp + 8]
    add ebx, ecx
    mov bl, [ebx]
    cmp al, bl
    jne endnegativ

    inc edx
    dec ecx
    jmp mainloop

endpozitiv:
    ; pozitiv
    mov eax, 1
    jmp end

endnegativ:
    xor eax, eax

end:
    pop edi
    pop esi
    pop ebx
    leave
    ret



composite_palindrome:
    ; create a new stack frame
    enter 0, 0
    xor eax, eax
    push esi
    push ebx
    push edi

    ; 10 * 15 + terminator
    mov eax, 151
    push eax
    call malloc
    ; malloc la char*
    add esp, 4
    ; string doar cu terminator \0
    mov byte [eax], 0
    mov esi, eax
    ; copie la esi care tine max-ul
    mov [maxcopy], esi

    ; 10 * 15 + terminator
    mov eax, 151
    push eax
    call malloc
    ; malloc la char*
    add esp, 4
    ; string doar cu terminator \0
    mov byte [eax], 0
    mov esi, eax
    ; copie la esi care tine current-ul
    mov [copy], esi

    ; contor esi pentru floop, folosim un fel de masca de care ne folosim sa generam toate subsirurile 2^n
    xor esi, esi
    inc esi
firstloop:
    mov eax, [copy]
    ; string cu terminator \0
    mov byte [eax], 0

    ; strlen pentru subsir
    xor edx, edx
    xor edi, edi
secondloop:
    ; 1<<cl
    mov ebx, 1
    mov ecx, edi
    shl ebx, cl

    and ebx, esi
    ; verific daca iau si cuvantul respectiv de ex daca vreau sa iau pentru 1 ar fi 00000001 and 00000001 adevarat
    cmp ebx, 0
    je skipsecondloop

    ; mut current in ecx si o fac cu pointer ul alocat si salvat in data
    ; pentru ca altfel se eax ecx si edx nu sunt callee-saved
    mov ecx, [copy]
    mov eax, edi
    ; *4 pentru pointer
    shl eax, 2
    ; words[j]
    add eax, [ebp + 8]
    mov eax, [eax]

    ; formez/concatenez subsirul
    push eax
    push ecx
    call strcat
    ; strcat pe current cu words[j]
    add esp, 8
    ; actualizez current ca sa nu existe sansa sa fie suprascris
    mov [copy], eax

skipsecondloop:
    inc edi
    ; ebp + 12 = len
    cmp edi, [ebp + 12]
    jl secondloop

    push eax
    call strlen
    ; strlen la curr
    add esp, 4
    mov ebx, eax

    mov eax, [maxcopy]
    push eax
    call strlen
    ; max strlen
    add esp, 4

    ; daca curr nu e mai mare ca lungime e inutil
    cmp ebx, eax
    jl skip
    jg skipstrcmp

    push dword [maxcopy]
    push dword [copy]
    call strcmp
    ; strcmp(copy, maxcopy)
    add esp, 8

    ; daca e >= 0 skip
    cmp eax, 0
    jge skip

skipstrcmp:
    mov ecx, [copy]
    push ebx
    push ecx
    call check_palindrome
    ; check pali
    add esp, 8

    ; false
    cmp eax, 0
    je skip

    ; readuc registrii la valorile lor ca se strica de la apelurile de functii
    mov ecx, [copy]
    mov eax, [maxcopy]

    push ecx
    push eax
    call strcpy
    ; strcpy la noul max
    add esp, 8
    mov [maxcopy], eax

skip:
    inc esi
    ; ebp + 12 = len
    mov ecx, [ebp + 12]
    ; conditii pt firstloop
    mov edx, 1
    shl edx, cl
    cmp esi, edx
    jl firstloop


    mov eax, [copy]
    push eax
    call free
    ; free curent
    add esp, 4
finish:
    ; returnez valoarea maxima
    mov eax, [maxcopy]
    pop edi
    pop ebx
    pop esi
    leave
    ret