section .text
global sort
global get_words
extern qsort
extern strlen
extern strcmp
global compare



;; sort(char **words, int number_of_words, int size)
;  functia va trebui sa apeleze qsort pentru soratrea cuvintelor 
;  dupa lungime si apoi lexicografix
sort:
    ; create a new stack frame
    enter 0, 0
    xor eax, eax
    push ebx
    push edi
    push esi

    push compare
    ;size
    push dword [ebp + 16]
    ;nmbr of words
    push dword [ebp + 12]
    ;wrods
    push dword [ebp + 8]

    call qsort

    ; 4 push de size 4
    add esp, 16

    pop esi
    pop edi
    pop ebx
    leave
    ret

;; get_words(char *s, char **words, int number_of_words)
;  separa stringul s in cuvinte si salveaza cuvintele in words
;  number_of_words reprezinta numarul de cuvinte
get_words:
    ; create a new stack frame
    enter 0, 0
    xor eax, eax
    push ebx
    push edi
    push esi

    ; s
    mov eax, [ebp + 8]
    ; words
    mov ebx, [ebp + 12]
    ; contoru
    mov ecx, [ebp + 16]
    xor edi, edi

mainloop:
    ; citesc char cu char adica doar cate 1 byte
    mov dl, [eax]

    ; null
    cmp dl, 0
    je finish
    ; space in ascii
    cmp dl, 32
    je delim
    ; punct in ascii
    cmp dl, 46
    je delim
    ; newl in ascii
    cmp dl, 10
    je delim
    ; virgula in ascii
    cmp dl, 44
    je delim

    ; nu e delim deci e cuvant nou si salvez adresa de la care incepe
    mov [ebx + edi*4], eax

cuvantnou:
    mov dl, [eax]
    ; null
    cmp dl, 0
    je finish
    ; space in ascii
    cmp dl, 32
    je terminator
    ; punct in ascii
    cmp dl, 46
    je terminator
    ; newl in ascii
    cmp dl, 10
    je terminator
    ; virgula in ascii
    cmp dl, 44
    je terminator

    ; daca nu a iesit inseamna ca continua cuv
    inc eax
    jmp cuvantnou

terminator:
    ; se termina cuvantul si bag doar pe byte ul pe care se afla term sir
    mov byte [eax], 0
    inc eax
    inc edi
    loop mainloop

delim:
    ; delim peste care trebuie sa sarim fara sa contorizam ca fiind cuv
    inc eax
    jmp mainloop

finish:
    pop esi
    pop edi
    pop ebx
    leave
    ret


compare:
    ; pentru qsort
    enter 0, 0
    push ebx
    push edi
    push esi


    ; primul cuvant
    mov edi, [ebp + 8]
    ; al doilea cuvant
    mov esi, [ebp + 12]
    mov edi, [edi]
    mov esi, [esi]
    ; diferentiez cuvintele

    ; strlen pe primul cuv
    push edi
    call strlen
    ; readuc stiva
    add esp, 4
    mov ebx, eax

    ; strlen pe al doilea cuv
    push esi
    call strlen
    ; readuc stiva
    add esp, 4
    mov ecx, eax

    cmp ebx, ecx
    je skip
    jg pozitiv
    jl negativ

skip:
    ; continui cu strcmp
    push esi
    push edi
    call strcmp
    ; readuc stiva
    add esp, 8
    jmp end

negativ:
    ; return negativ
    mov eax, -1
    jmp end

pozitiv:
    ; return pozitiv
    mov eax, 1
    jmp end

end:
    pop esi
    pop edi
    pop ebx
    leave
    ret