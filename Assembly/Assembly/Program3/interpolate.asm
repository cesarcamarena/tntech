.386
.MODEL FLAT

INCLUDE debug.h
INCLUDE compute_b.h

PUBLIC interpolate_proc

array_addr		EQU [ebp + 14]
x_coord			EQU [ebp + 10]
degree			EQU [ebp + 8]
x 				EQU [ebp - 4] ;last on the stack

.CODE
	_obtain_x MACRO val_index, array
		mov ebx, array
		mov ax, val_index
		shl ax, 3
		movzx eax, ax
		add ebx, eax
		mov eax, [ebx]
	ENDM

	interpolate_proc PROC Near32
		push ebp
		mov ebp, esp
		pushd 0
		push eax
		push ecx
		push edx
		pushf

		;f(x) = [b0] + [b1 * (x - x0)] + [b2 * (x - x0) * (x - x1)] + [b3 * (x -x0) * (x - x1) * (x - x2)] + ...
		mov cx, 1
		mov ax, 0
		compute_b DWORD PTR array_addr, ax ;top of the stack: b0
		cmp cx, degree ;check if 1 < 3
		jg done

	b_loop:
		compute_b DWORD PTR array_addr, cx
		mov dx, 0

	mul_loop:
		fld DWORD PTR x_coord ;x
		_obtain_x dx, array_addr ;x0
		mov x, eax
		fld DWORD PTR x
		fsub ;x - x0
		fmul ;b1 * (x - x0)
		add dx, 1 ;dx = 1
		cmp dx, cx ;dx >= 1
		jl mul_loop
		fadd ;b0 + b1x
		add cx, 1
		cmp cx, degree
		jle b_loop

	done:
		popf
		pop edx
		pop ecx
		pop eax
		mov esp, ebp
		pop ebp
		ret 10
	interpolate_proc ENDP

END