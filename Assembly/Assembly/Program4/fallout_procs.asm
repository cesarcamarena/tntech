.386
.MODEL FLAT

EXTRN strlen_proc:Near32

PUBLIC num_matches_proc
PUBLIC fallout_swap_proc

INCLUDE io.h
INCLUDE debug.h

.CODE
	
source	EQU	[ebp + 12]	;address of the source
dest	EQU [ebp + 8]	;address of the destination

num_matches_proc	PROC 	Near32
	;entry code
	push 	ebp
	mov 	ebp, esp
	push 	edi
	push 	esi
	push 	ecx
	pushf

	mov 	ecx, 0
	mov 	esi, source
	mov 	edi, dest
	cld

	push 	source
	call 	strlen_proc
	mov 	cx, ax	;gets len into counter
	mov		eax, 0

	while_loop:
		cmp 	cx, 0
		je 		finished
		repne 	cmpsb
		jne 	finished
		inc 	ax
		jmp 	while_loop
	finished:

	popf
	pop 	ecx
	pop 	esi
	pop 	edi
	mov 	esp, ebp
	pop 	ebp
	ret 	8
num_matches_proc	ENDP

fallout_swap_proc	PROC 	Near32
	;entry code
	push 	ebp
	mov 	ebp, esp
	push 	edi
	push 	esi
	push 	eax
	push 	ecx
	pushf

	mov 	ecx, 0
	mov 	esi, source
	mov 	edi, dest
	cld

	push 	source
	call 	strlen_proc
	mov 	cx, ax
	mov 	eax, 0	;not sure about this yet, but I think it's fine for now

	swap_loop:		;got this from the lecture
		cmp 	ecx, 0
		je 		finished
		lodsb
		dec 	esi
		xchg 	esi, edi
		movsb
		dec 	esi
		xchg 	esi, edi
		stosb
		dec 	ecx
		jmp swap_loop
	finished:
		popf
		pop ecx
		pop eax
		pop esi
		pop edi
		mov esp, ebp
		pop ebp
		ret 8
fallout_swap_proc	ENDP

END