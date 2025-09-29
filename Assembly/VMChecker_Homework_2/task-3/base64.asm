%include "../include/io.mac"

extern printf
global base64

section .data
	alphabet db 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
	fmt db "%d", 10, 0

section .text

base64:
	;; DO NOT MODIFY
    push ebp
    mov ebp, esp
	pusha

	mov esi, [ebp + 8] ; source array
	mov ebx, [ebp + 12] ; n
	mov edi, [ebp + 16] ; dest array
	mov edx, [ebp + 20] ; pointer to dest length

	;; DO NOT MODIFY


	; -- Your code starts here --
	mov ecx, ebx
	xor edx, edx
mainloop:
	movzx eax, byte [esi]
	shr eax, 2
	mov bl, [alphabet + eax]
	mov [edi], bl ; first number
	inc edi

	; impartire pe biti cu ajutorul shl si shr
	mov al, [esi]
	inc esi
	mov bl, [esi]
	shl al, 6
	shr al, 2
	shr bl, 4
	add al, bl
	movzx eax, al
	mov bl, [alphabet + eax]
	mov [edi], bl ; second number
	inc edi

	mov al, [esi]
	inc esi
	mov bl, [esi]
	shl al, 4
	shr al, 2
	shr bl, 6
	add al, bl
	movzx eax, al
	mov bl, [alphabet + eax]
	mov [edi], bl ; third number
	inc edi

	mov bl, [esi]
	inc esi
	shl bl, 2
	shr bl, 2
	movzx eax, bl
	mov bl, [alphabet + eax]
	mov [edi], bl ; fourth number
	inc edi
	sub ecx, 3
	cmp ecx, 0
	jge mainloop

	mov eax, [ebp + 12] ; length pentru varianta base64
	mov ebx, 4
	mul ebx
	mov ebx, 3
	div ebx
	mov edx, [ebp + 20]
	mov [edx], eax
	; -- Your code ends here --


	;; DO NOT MODIFY

	popa
	leave
	ret

	;; DO NOT MODIFY