section .text
global sort

;   struct node {
;    int val;
;    struct node* next;
;   };

;; struct node* sort(int n, struct node* node);
;   The function will link the nodes in the array
;   in ascending order and will return the address
;   of the new found head of the list
; @params:
;   n -> the number of nodes in the array
;   node -> a pointer to the beginning in the array
;   @returns:
;   the address of the head of the sorted list
sort:
    ; create a new stack frame
    enter 0, 0
    push ebx
    push edi
    push esi
    xor eax, eax

    ; contor
    mov ecx, [ebp + 8]
    ; vector main
    mov esi, [ebp + 12]

    ; size pt vector de pointeri
    mov eax, 4
    mul ecx
    mov ecx, eax
    sub esp, ecx
    ; aloc memorie pe stiva
    mov ecx, [ebp + 8]
    ; contor

auxloop: ; loop pentru a aranja adresele in vectorul de ptr
    ; size of fiecare celula din esi
    mov eax, 8
    mov edi, ecx
    dec edi
    mul edi
    mov edx, eax
    add edx, esi
    ; edx = adresa lui esi[eax]
    mov ebx, [edx]
    dec ebx
    ; valoare int
    mov [esp + ebx*4], edx
    loop auxloop

    ; n
    mov ecx, [ebp + 8]
    dec ecx
    xor edx, edx
mainloop:
    ; curr
    mov eax, [esp + edx*4]
    ; urm
    mov ebx, [esp + edx*4 + 4]
    ; +4 sizeof pointer
    mov [eax + 4], ebx
    inc edx
    loop mainloop

    ; n
    mov ecx, [ebp + 8]
    dec ecx
    ; 4 sizeof pointer
    mov eax, 4
    mul ecx
    mov eax, [esp + eax]
    ; +4 sizeof pointer
    mov dword [eax+4], 0

    mov eax, [esp]

    ; readuc stiva cu 4*n
    add esp, [ebp + 8]
    ; readuc stiva cu 4*n
    add esp, [ebp + 8]
    ; readuc stiva cu 4*n
    add esp, [ebp + 8]
    ; readuc stiva cu 4*n
    add esp, [ebp + 8]

    pop esi
    pop edi
    pop ebx
    leave
    ret

