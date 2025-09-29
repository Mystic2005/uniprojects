%include "../include/io.mac"

extern printf
global remove_numbers

section .data
	fmt db "%d", 10, 0

section .text

; function signature: 
; void remove_numbers(int *a, int n, int *target, int *ptr_len);

remove_numbers:
	;; DO NOT MODIFY
	push    ebp
	mov     ebp, esp
	pusha

	mov     esi, [ebp + 8] ; source array
	mov     ebx, [ebp + 12] ; n
	mov     edi, [ebp + 16] ; dest array
	mov     edx, [ebp + 20] ; pointer to dest length

	;; DO NOT MODIFY
   

	;; Your code starts here
	mov ecx, ebx
	xor edx, edx

mainloop:
	mov eax, [esi]

	test eax, 1 ; test paritate
	jnz skip

	push ecx

	cmp eax, 0 ; test putere
	je skip

	mov ecx, eax
putereloop:
	cmp ecx, 1 ; test putere
	je putere

	test ecx, 1
	jnz notputere

	shr ecx, 1
	jmp putereloop

putere:
	pop ecx
	jmp skip

notputere:
	pop ecx
	mov [edi], eax
	add edi, 4
	inc edx
skip:
	add esi, 4
	loop mainloop

	mov eax, [ebp + 20]
	mov [eax], edx
	;; Your code ends here
	


	;; DO NOT MODIFY

	popa
	leave
	ret
	
	;; DO NOT MODIFY
