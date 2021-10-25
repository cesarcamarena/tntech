.386
.MODEL FLAT

INCLUDE io.h
INCLUDE debug.h

PUBLIC compute_b_proc

array_addr		EQU [ebp + 12]
first_index		EQU [ebp + 10]
second_index	EQU [ebp + 8]
x				EQU [ebp - 4]

.CODE
	_obtain_x MACRO array_name, index
		_setup array_name, index
		mov eax, [ebx]
	ENDM

	_obtain_y MACRO array_name, index
		_setup array_name, index
		add ebx, 4
		mov eax, [ebx]
	ENDM

	_setup MACRO array_name, index
		mov ebx, array_name
		mov ax, index
		movzx eax, ax
		shl eax, 3
		add ebx, eax
	ENDM

	compute_b_proc PROC Near32
			push ebp
			mov ebp, esp
			push ebx
			pushf

		body:
			push DWORD PTR array_addr
			push WORD PTR first_index
			push WORD PTR second_index
			call recursion

		done:
			popf
			mov esp, ebp
			pop ebp
			ret 8
	compute_b_proc ENDP

	recursion PROC Near32
		push ebp
		mov ebp, esp
		lea esp, [esp - 4]
		mov ax, first_index
		cmp ax, second_index
		je base_case

	body:
		mov ax, second_index
		add ax, 1
		push DWORD PTR array_addr
		push WORD PTR first_index ;n
		push ax ;m+1

		call recursion ;f[n...(m+1)]
		mov ax, first_index
		sub ax, 1

		push DWORD PTR array_addr
		push ax ;n-1
		push WORD PTR second_index ;m
		call recursion ;f[n-1 ... m]

		fsub ;f[n...(m+1)] - f[(n-1)...m]

		_obtain_x array_addr, first_index ;x_n
		mov x, eax
		fld DWORD PTR x

		_obtain_x array_addr, second_index ;x_m
		mov x, eax
		fld DWORD PTR x

		fsub ;x_n - x_m
		fdiv
		jmp done

	base_case:
		_obtain_y array_addr, first_index ;f(x_n)
		mov x, eax
		fld DWORD PTR x ;y_n

	done:
		mov esp, ebp
		pop ebp
		ret 8
	recursion ENDP
	
END